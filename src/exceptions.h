#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

#include <array>
#include <exception>
#include <map>
#include <string>

#define LXINTERNAL_EXCEPTION_LIST \
        ITEM_EXCEPTION(CantOpenIO,\
                       "Unable to open IO stream.",\
                       "",\
                       ITEM_DATA("Object")\
                       ITEM_DATA("Message"))\
        ITEM_EXCEPTION(CantPerformIO,\
                       "IO failure.",\
                       "",\
                       ITEM_DATA("Object")\
                       ITEM_DATA("Action")\
                       ITEM_DATA("Message"))\
        ITEM_EXCEPTION(CantParse,\
                       "Data parsing failed.",\
                       "Fix the data.",\
                       ITEM_DATA("Source")\
                       ITEM_DATA("Error"))\
        ITEM_EXCEPTION(UnexpectedFileContent,\
                       "Unexpected file content.",\
                       "Fix the file.",\
                       ITEM_DATA("File name")\
                       ITEM_DATA("Expected content")\
                       ITEM_DATA("Current content"))\
        ITEM_EXCEPTION(RenderingQueueOverflow,\
                       "Rendering queue overflow.",\
                       "Try to reduce an amount of rendered polygons. Lowering resoluton or quality settings may help. This is a bug, please tell the developer about it.",\
                       ITEM_DATA("Queue name")\
                       ITEM_DATA("Queue length"))\
        ITEM_EXCEPTION(ShaderCompilationError,\
                       "Shader compilation error.",\
                       "It is probably a bug, please tell the developer about it. Updating videocard drivers may help. If you're skilled enough, you can try to fix the shader yourself.",\
                       ITEM_DATA("Shader name")\
                       ITEM_DATA("Vertex shader status")\
                       ITEM_DATA("Fragment shader status")\
                       ITEM_DATA("Vertex shader log")\
                       ITEM_DATA("Fragment shader log"))\
        ITEM_EXCEPTION(ShaderLinkingError,\
                       "Shader linking error.",\
                       "It is probably a bug, please tell the developer about it. Updating videocard drivers may help. If you're skilled enough, you can try to fix the shader yourself.",\
                       ITEM_DATA("Shader name")\
                       ITEM_DATA("Log"))\
        ITEM_EXCEPTION(BadCubeMapImage,\
                       "Attempt to use incorrectly sized image as a cubemap side.",\
                       "",\
                       ITEM_DATA("Size"))\

class Exception final : public std::exception
{
  public:
    enum class Enum : unsigned int {
    #define ITEM_EXCEPTION(token, desc, solution, data_names) token,
    LXINTERNAL_EXCEPTION_LIST
    #undef ITEM_EXCEPTION
    };
  private:
    Enum type;
    std::string description, solution;
    std::map<std::string, std::string> data;

    Exception() {};

  public:
    #define ITEM_DATA(name) name,
    #define ITEM_EXCEPTION(token, desc, solution_unused, data_names) static void token(std::array<const char *, (std::initializer_list<const char *>{data_names}.size())> args, const char *sol = 0) \
    { \
        Exception ret; \
        ret.type = Enum::token; \
        ret.solution = (sol && *sol ? sol : ""); \
        ret.description = ret.Description(); \
        const char *arr[] {data_names}; \
        const char **ptr = arr; \
        for (auto it : args) \
        { \
            if (!it || !*it) \
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
    const char *FullText() const noexcept {return what();}
    const char *Description() const noexcept
    {
        static constexpr const char *names_table[]{
        #define ITEM_EXCEPTION(token, desc, solution, data_names) desc,
        LXINTERNAL_EXCEPTION_LIST
        #undef ITEM_EXCEPTION
        };
        return names_table[(unsigned int)type];
    }
    const char *Solution() const noexcept
    {
        static constexpr const char *solutions_table[]{
        #define ITEM_EXCEPTION(token, desc, solution, data_names) solution,
        LXINTERNAL_EXCEPTION_LIST
        #undef ITEM_EXCEPTION
        };
        if (solution[0])
            return solution.c_str();
        else
            return solutions_table[(unsigned int)type];
    }

    Enum Type() const noexcept {return type;}

    const char *Get(const char *name)
    {
        auto it = data.find(name);
        return it != data.end() ? it->second.c_str() : "";
    }
};

#undef LXINTERNAL_EXCEPTION_LIST

#endif