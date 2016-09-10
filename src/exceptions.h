#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <array>
#include <exception>
#include <map>
#include <string>

#define LXINTERNAL_EXCEPTION_LIST \
        ITEM_EXCEPTION(CantOpenIO,\
                       "Unable to open IO stream.",\
                       ITEM_DATA("Object")\
                       ITEM_DATA("Message"))\
        ITEM_EXCEPTION(CantPerformIO,\
                       "IO failure.",\
                       ITEM_DATA("Object")\
                       ITEM_DATA("Action")\
                       ITEM_DATA("Message"))\
        ITEM_EXCEPTION(CantParse,\
                       "Data parsing failed.",\
                       ITEM_DATA("Source")\
                       ITEM_DATA("Error"))\
        ITEM_EXCEPTION(BadData,\
                       "Bad data.",\
                       ITEM_DATA("Source")\
                       ITEM_DATA("Expected content")\
                       ITEM_DATA("Current content"))\
        ITEM_EXCEPTION(RenderingQueueOverflow,\
                       "Rendering queue overflow.",\
                       ITEM_DATA("Queue length"))\
        ITEM_EXCEPTION(ShaderCompilationError,\
                       "Shader compilation error.",\
                       ITEM_DATA("Shader name")\
                       ITEM_DATA("Vertex shader status")\
                       ITEM_DATA("Fragment shader status")\
                       ITEM_DATA("Vertex shader log")\
                       ITEM_DATA("Fragment shader log"))\
        ITEM_EXCEPTION(ShaderLinkingError,\
                       "Shader linking error.",\
                       ITEM_DATA("Shader name")\
                       ITEM_DATA("Log"))\
        ITEM_EXCEPTION(BadCubeMapImage,\
                       "Attempt to use incorrectly sized image as a cubemap side.",\
                       ITEM_DATA("Size"))\
        ITEM_EXCEPTION(FontAtlasOverflow,\
                       "Not enough space in a font atlas to store all requested glyphs.",\
                       ITEM_DATA("Font")\
                       ITEM_DATA("Atlas size"))\

class Exception final : public std::exception
{
  public:
    enum class Enum : unsigned int {
    #define ITEM_EXCEPTION(token, desc, data_names) token,
    LXINTERNAL_EXCEPTION_LIST
    #undef ITEM_EXCEPTION
    };
  private:
    Enum type;
    std::string description;
    std::map<std::string, std::string> data;

    Exception() {};

  public:
    #define ITEM_DATA(name) name,
    #define ITEM_EXCEPTION(token, desc_unused, data_names) static void token(std::array<const char *, (std::initializer_list<const char *>{data_names}.size())> args) \
    { \
        Exception ret; \
        ret.type = Enum::token; \
        ret.description = ret.desc(); \
        const char *arr[] {data_names}; \
        const char **ptr = arr; \
        for (auto it : args) \
        { \
            if (it[0]) \
                goto skip; \
            ret.data[*ptr] = it; \
            ret.description += '\n'; \
            ret.description += *ptr; \
            ret.description += ": "; \
            ret.description += it; \
          skip: \
            ptr++; \
        } \
        throw ret; \
    }
    LXINTERNAL_EXCEPTION_LIST
    #undef ITEM_DATA
    #undef ITEM_EXCEPTION

    const char *what() const noexcept override {return description.c_str();}
    const char *desc() const noexcept
    {
        static const std::string names_table[]{
        #define ITEM_EXCEPTION(token, desc, data_names) desc,
        LXINTERNAL_EXCEPTION_LIST
        #undef ITEM_EXCEPTION
        };
        return names_table[(unsigned int)type].c_str();
    }

    Enum Type() const noexcept {return type;}

    const std::string &get(const char *name)
    {
        auto it = data.find(std::string(name));
        static const std::string null = "";
        return it != data.end() ? it->second : null;
    }
};

#undef LXINTERNAL_EXCEPTION_LIST

// Internal declarations
namespace Exceptions
{
    inline namespace Any
    {
        class Type : public std::exception
        {
          protected:
            template <typename ...P>
            void generate_description(const char *desc, char *names, P &&... p)
            {
                description = desc;
                std::string *fields[]{&p...};
                std::string **current_field = fields;
                const char *current_name = names;
                bool at_separator = 1;
                while (1)
                {
                    if (*names == ' ' || *names == ',' || *names == '\0')
                    {
                        bool end_of_str = *names == '\0';
                        if (!at_separator)
                        {
                            *names = '\0';
                            description += "\n - ";
                            description += current_name;
                            description += ": ";
                            description += **current_field;
                            current_field++;
                            at_separator = 1;
                        }
                        if (end_of_str)
                            break;
                    }
                    else
                    {
                        if (at_separator)
                        {
                            current_name = names;
                            at_separator = 0;
                        }
                    }

                    if (*names == '_')
                        *names = ' ';
                    else if (names == current_name && *names >= 'a' && *names <= 'z')
                        *names -= 'a' - 'A';

                    names++;
                }
            }

            std::string description;

          public:
            virtual const char *what() const noexcept override final {return description.c_str();};
            virtual void update_description() = 0;
            virtual ~Type() {}
        };

        using Base = Type;
    }

    #define LXINTERNAL_EXCEPTION_FOR_EACH_1(m, a0                     )  m(a0)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_2(m, a0,a1                  )  m(a0) , m(a1)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_3(m, a0,a1,a2               )  m(a0) , m(a1) , m(a2)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_4(m, a0,a1,a2,a3            )  m(a0) , m(a1) , m(a2) , m(a3)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_5(m, a0,a1,a2,a3,a4         )  m(a0) , m(a1) , m(a2) , m(a3) , m(a4)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_6(m, a0,a1,a2,a3,a4,a5      )  m(a0) , m(a1) , m(a2) , m(a3) , m(a4) , m(a5)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_7(m, a0,a1,a2,a3,a4,a5,a6   )  m(a0) , m(a1) , m(a2) , m(a3) , m(a4) , m(a5) , m(a6)
    #define LXINTERNAL_EXCEPTION_FOR_EACH_8(m, a0,a1,a2,a3,a4,a5,a6,a7)  m(a0) , m(a1) , m(a2) , m(a3) , m(a4) , m(a5) , m(a6) , m(a7)
    #define LXINTERNAL_EXCEPTION_ARGS(name) const char *name##_
    #define LXINTERNAL_EXCEPTION_ASSIGN(name) ret.name = name##_
    #define LXINTERNAL_EXCEPTION_COMMA ,

    #define NEW_EXCEPTION(name, desc, field_c, ...) \
        namespace name \
        { \
            struct Type final : Base \
            { \
                std::string __VA_ARGS__; \
                \
                Type() {} \
                \
                void update_description() override \
                { \
                    char field_names[] = #__VA_ARGS__; \
                    generate_description(desc, field_names, __VA_ARGS__); \
                } \
            }; \
            \
            [[noreturn]] inline void Throw(LXINTERNAL_EXCEPTION_FOR_EACH_##field_c(LXINTERNAL_EXCEPTION_ARGS, __VA_ARGS__)) \
            { \
                Type ret; \
                LXINTERNAL_EXCEPTION_FOR_EACH_##field_c(LXINTERNAL_EXCEPTION_ASSIGN, __VA_ARGS__); \
                ret.update_description(); \
                throw ret; \
            } \
        }
    #define EXCEPTION_CATEGORY(name) namespace name {struct Type : Base {void update_description() override = 0;};} namespace name
}

// Exception definitions
namespace Exceptions
{
    EXCEPTION_CATEGORY(IO)
    {
        NEW_EXCEPTION(CantOpen, "Unable to open IO stream.", 2, object, message)
        NEW_EXCEPTION(Failure, "IO failure.", 3, object, action, message)
        NEW_EXCEPTION(CantParse, "Data parsing failed.", 2, source, error)
        NEW_EXCEPTION(BadData, "Data parsing failed.", 3, source, expected, received)
    }
    EXCEPTION_CATEGORY(Graphics)
    {
        NEW_EXCEPTION(RenderingQueueOverflow, "Rendering queue overflow.", 1, queue_length)
        NEW_EXCEPTION(BadCubeMapImage, "Attempt to use incorrectly sized image as a cubemap side.", 1, size)
        NEW_EXCEPTION(FontAtlasOverflow, "Not enough space in a font atlas to store all requested glyphs.", 2, font, atlas_size)

        EXCEPTION_CATEGORY(Shaders)
        {
            NEW_EXCEPTION(CompilationError, "Shader compilation error.", 5, shader_name, vertex_shader_status, fragment_shader_status, vertex_shader_log, fragment_shader_log)
            NEW_EXCEPTION(LinkingError, "Shader linking error.", 2, shader_name, log)
        }
    }
}

#endif