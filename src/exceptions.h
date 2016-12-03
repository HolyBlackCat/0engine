#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <exception>
#include <string>

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
                            if ((**current_field)[0])
                            {
                                description += "\n - ";
                                description += current_name;
                                description += ": ";
                                description += **current_field;
                            }
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
        struct name##_t final : Base \
        { \
            std::string __VA_ARGS__; \
            \
            name##_t() {} \
            \
            void update_description() override \
            { \
                char field_names[] = #__VA_ARGS__; \
                generate_description(desc, field_names, __VA_ARGS__); \
            } \
        }; \
        \
        [[noreturn]] inline void name(LXINTERNAL_EXCEPTION_FOR_EACH_##field_c(LXINTERNAL_EXCEPTION_ARGS, __VA_ARGS__)) \
        { \
            name##_t ret; \
            LXINTERNAL_EXCEPTION_FOR_EACH_##field_c(LXINTERNAL_EXCEPTION_ASSIGN, __VA_ARGS__); \
            ret.update_description(); \
            throw ret; \
        }
    #define EXCEPTION_CATEGORY(name) namespace name {struct Type : Base {void update_description() override = 0;};} namespace name
}

// Exception definitions
namespace Exceptions
{
    EXCEPTION_CATEGORY(IO)
    {
        NEW_EXCEPTION(CantOpen, "Unable to open IO stream.", 2, object, message)
        NEW_EXCEPTION(BadOperation, "IO operation failure.", 3, object, action, message)
        NEW_EXCEPTION(CantParse, "Data parsing failed.", 2, source, error)
        NEW_EXCEPTION(BadData, "Data parsing failed.", 3, source, expected, received)
    }
    EXCEPTION_CATEGORY(Graphics)
    {
        NEW_EXCEPTION(RenderArrayOverflow, "Render array overflow.", 1, queue_length)
        NEW_EXCEPTION(BadCubeMapImage, "Attempt to use incorrectly sized image as a cubemap side.", 1, size)
        NEW_EXCEPTION(FontAtlasOverflow, "Not enough space in a font atlas to store all requested glyphs.", 2, font, atlas_size)
        NEW_EXCEPTION(ShaderCompilationError, "Shader compilation error.", 5, shader_name, vertex_shader_status, fragment_shader_status, vertex_shader_log, fragment_shader_log)
        NEW_EXCEPTION(ShaderLinkingError, "Shader linking error.", 2, shader_name, log)
    }
    EXCEPTION_CATEGORY(Network)
    {
        NEW_EXCEPTION(CantConnect, "Can't connect to a remote host.", 1, address)
        NEW_EXCEPTION(CantResolve, "Can't resolve a host name.", 1, address)
        NEW_EXCEPTION(CantCreateServer, "Can't create a server.", 1, port)
    }
}

#endif