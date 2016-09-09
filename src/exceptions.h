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
                       ITEM_DATA("Source name")\
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

namespace Exceptions
{
    #error Запилить создание экзепшонов дефайном типа бля("текст", поле, поле), запилить наружный метод для соединения строк бла(№__ВА_АРГС__, __ВА_АРГС__), чтобы парсил первый арг. Результат в ретурн what()
    class Any : public std::exception
    {
      protected:
        std::string what_buf, details_buf;
      public:
        const char *what() const noexcept override = 0;
        virtual ~Any() {}
    };

    class IO
    {
        const char *what() const noexcept override {return }
    };
}

#endif