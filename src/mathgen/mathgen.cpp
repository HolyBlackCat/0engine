#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE
#define VERSION "1.9.0"
// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE

std::ofstream out_file("math.h");

int indentation = 0;
bool new_line = 0;

template <typename ...P> const char *Jo(P &&... p)
{
    static constexpr int ret_buffers_c = 32;
    static std::string ret_buffers[ret_buffers_c];
    static int ret_pos = 0;
    static std::stringstream ss;
    ss.clear();
    ss.str("");
    int dummy[] {(ss << p, 0)...};
    (void)dummy;
    ret_buffers[ret_pos] = ss.str();
    const char *ret = ret_buffers[ret_pos].c_str();
    ret_pos = (ret_pos + 1) % ret_buffers_c;
    return ret;
}

void Print(const char *ptr)
{
    auto Indent = [&](int off = 0)
    {
        if (new_line)
        {
            new_line = 0;
            for (int i = 0; i < indentation * 4 + off; i++) out_file << ' ';
        }
    };

    while (*ptr)
    {
        switch (*ptr)
        {
          case '\n':
            new_line = 1;
            break;
          case '{':
            if (new_line)
                Indent();
            indentation++;
            break;
          case '}':
            indentation--;
            if (new_line)
                Indent();
            break;
          case '@':
            if (new_line)
                Indent(-2);
            break;
          case '$':
            if (new_line)
                Indent(-4);
          default:
            if (new_line)
                Indent();
            break;
        }
        if (*ptr == '$')
            out_file << ' ';
        else if (*ptr != '@')
            out_file << *ptr;

        ptr++;
    }
}

struct
{
    template <typename T> auto operator<<(T && obj)
    {
        Print(Jo(obj));
        return *this;
    }
} o;

#define r o << 1+
#define l o <<

namespace Gen
{
    // Field names list
    static constexpr char field_names[][4]
    {
        {'x','y','z','w'},
        {'r','g','b','a'},
        {'s','t','p','q'},
    };
    static constexpr const char (&field_names_main)[4] = field_names[0];
    static constexpr int field_names_count = (sizeof field_names) / (sizeof field_names[0]);

    static constexpr const char *custom_op_list[]{"dot","cross","mul"};
    static constexpr char op_delim = '/'; // You shall use / or * or %, others will mess up operator precedence in other existing code.

    void GenVectorPrototypes()
    {
        // Type list
        static constexpr struct {const char *tag, *name;} types[]
        {
            "c",   "char",
            "uc",  "unsigned char",
            "sc",  "signed char",
            "s",   "short",
            "us",  "unsigned short",
            "i",   "int",
            "u",   "unsigned int",
            "l",   "long",
            "ul",  "unsigned long",
            "ll",  "long long",
            "ull", "unsigned long long",
            "f",   "float",
            "d",   "double",
            "ld",  "long double",
            "i8",  "int8_t",
            "u8",  "uint8_t",
            "i16", "int16_t",
            "u16", "uint16_t",
            "i32", "int32_t",
            "u32", "uint32_t",
            "i64", "int64_t",
            "u64", "uint64_t",
        };

        // Header & type-generic usings
        r R"(
template <unsigned int D, typename T> struct vec;
template <unsigned int W, unsigned int H, typename T> using mat = vec<W, vec<H, T>>;
)";
        for (int i = 2; i <= 4; i++)
            l "template <typename T> using vec" << i << " = vec<" << i << ", T>;\n";
        for (int h = 2; h <= 4; h++)
            for (int w = 2; w <= 4; w++)
                l "template <typename T> using mat" << w << 'x' << h << " = mat<" << w << ',' << h << ",T>;\n";
        for (int i = 2; i <= 4; i++)
            l "template <typename T> using mat" << i << " = mat" << i << 'x' << i << "<T>;\n";

        // Type-prefixed usings
        for (const auto &it : types)
        {
            // Size-generic
            l "template <unsigned int D> using " << it.tag << "vec = vec<D," << it.name << ">;\n" <<
              "template <unsigned int W, unsigned int H> using " << it.tag << "mat = mat<W,H," << it.name << ">;\n";
            // Complete
            for (int i = 2; i <= 4; i++)
                l "using " << it.tag << "vec" << i << " = vec<" << i << ',' << it.name << ">;\n";
            for (int h = 2; h <= 4; h++)
                for (int w = 2; w <= 4; w++)
                    l "using " << it.tag << "mat" << w << 'x' << h << " = mat<" << w << ',' << h << ',' << it.name << ">;\n";
            for (int i = 2; i <= 4; i++)
                l "using " << it.tag << "mat" << i << " = " << it.tag << "mat" << i << 'x' << i << ";\n";
        }
    }

    void Vector()
    {
        // Operators list
        static constexpr const char *ops_bin[]{"+","-","*","/","%","^","&","|",">>","<<"}, // "<<" must stay at the end because a special code is generated for it.
                                    *ops_un[]{"~","!","+","-"},
                                    *ops_fix[]{"++","--"},
                                    *ops_comp[]{"<",">","<=",">="},
                                    *ops_bool[]{"&&","||"},
                                    *ops_as[]{"+=","-=","*=","/=","%=","^=","&=","|=","<<=",">>="};

        // Header & type-generic usings
        r R"(
namespace Vector
{
)";
        // Specializations
        auto CommonHeader = [&]
        {
            r R"(
using type = std::remove_reference_t<T>;
static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
              !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
)";
        };
        auto Fields = [&](int len, const char *type)
        {
            for (int i = 0; i < len; i++)
            {
                l "union {" << type << ' ';
                for (int j = 0; j < field_names_count; j++)
                {
                    if (j != 0)
                        l ',';
                    l field_names[j][i];
                }
                l ";};\n";
            }
        };
        auto CommonMembers = [&](int sz)
        {
            // [] operator
            l "decltype(x) &operator[](int pos) {switch (pos) {";
            for (int i = 0; i < sz; i++)
                l "case " << i << ": return " << field_names_main[i] << "; ";
            l "default: static type ret; ret = type{}; return ret;}}\n";

            // const [] operator
            l "constexpr decltype(x) operator[](int pos) const {switch (pos) {";
            for (int i = 0; i < sz; i++)
                l "case " << i << ": return " << field_names_main[i] << "; ";
            l "default: return decltype(x){};}}\n";

            // Cast to bool
            l "constexpr operator bool() const {return ";
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l " || ";
                l "(bool)" << field_names_main[i];
            }
            l ";}\n";

            // Constructors
            l "constexpr vec() {}\n"; // Default
            l "constexpr vec("; // Piece-wise
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l ", ";
                l "decltype(x) p" << field_names_main[i];
            }
            l ") : ";
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l ", ";
                l field_names_main[i] << "(p" << field_names_main[i] << ')';
            }
            l " {}\n";
            l "constexpr vec(type obj) : "; // Same initializer for each component
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l ", ";
                l field_names_main[i] << "(obj)";
            }
            l " {}\n";
            l "template <typename TT> constexpr vec(vec" << sz << "<TT> obj) : "; // Casting from different type of vector.
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l ", ";
                l field_names_main[i] << "(obj." << field_names_main[i] << ')';
            }
            l " {}";

            // Member combinations
            l "constexpr auto sum() const {return "; // Sum
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l " + ";
                l field_names_main[i];
            }
            l ";}\n";
            l "constexpr auto product() const {return "; // Product
            for (int i = 0; i < sz; i++)
            {
                if (i != 0) l " * ";
                l field_names_main[i];
            }
            l ";}\n";

            // As array
            l "constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, \"This function does not work for reference vectors.\");}\n";
            l "constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, \"This function does not work for reference vectors.\");}\n";

            // Interpolate
            l "template <typename TT, typename TTT> constexpr vec" << sz << "<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec" << sz << "<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}\n";

            // Field replacements
            for (int i = 0; i < sz; i++)
            {
                for (int name = 0; name < field_names_count; name++)
                {
                    l "constexpr vec change_" << field_names[name][i] << "(type o) const {return {";
                    for (int j = 0; j < sz; j++)
                    {
                        if (j != 0) l ", ";
                        if (i == j) l 'o';
                        else l field_names_main[j];
                    }
                    l "};}\n";
                }
            }

            // Resizers
            for (int i = 2; i <= 4; i++)
            {
                if (sz == i) continue;
                l "constexpr vec" << i << "<type> to_vec" << i << "() const {return {";
                for (int j = 0; j < i; j++)
                {
                    if (j != 0) l ", ";
                    if (j < sz) l field_names_main[j];
                    else l "type{}";
                }
                l "};}\n";
            }
        };

        auto MatrixInverse = [&](int sz)
        {
            switch (sz)
            {
              case 4:
                r R"(
constexpr mat4<type> inverse() const
{
mat4<type> inv;
inv.x.x =  y.y * z.z * w.w -
           y.y * z.w * w.z -
           z.y * y.z * w.w +
           z.y * y.w * w.z +
           w.y * y.z * z.w -
           w.y * y.w * z.z;
inv.y.x = -y.x * z.z * w.w +
           y.x * z.w * w.z +
           z.x * y.z * w.w -
           z.x * y.w * w.z -
           w.x * y.z * z.w +
           w.x * y.w * z.z;
inv.z.x =  y.x * z.y * w.w -
           y.x * z.w * w.y -
           z.x * y.y * w.w +
           z.x * y.w * w.y +
           w.x * y.y * z.w -
           w.x * y.w * z.y;
inv.w.x = -y.x * z.y * w.z +
           y.x * z.z * w.y +
           z.x * y.y * w.z -
           z.x * y.z * w.y -
           w.x * y.y * z.z +
           w.x * y.z * z.y;
inv.x.y = -x.y * z.z * w.w +
           x.y * z.w * w.z +
           z.y * x.z * w.w -
           z.y * x.w * w.z -
           w.y * x.z * z.w +
           w.y * x.w * z.z;
inv.y.y =  x.x * z.z * w.w -
           x.x * z.w * w.z -
           z.x * x.z * w.w +
           z.x * x.w * w.z +
           w.x * x.z * z.w -
           w.x * x.w * z.z;
inv.z.y = -x.x * z.y * w.w +
           x.x * z.w * w.y +
           z.x * x.y * w.w -
           z.x * x.w * w.y -
           w.x * x.y * z.w +
           w.x * x.w * z.y;
inv.w.y =  x.x * z.y * w.z -
           x.x * z.z * w.y -
           z.x * x.y * w.z +
           z.x * x.z * w.y +
           w.x * x.y * z.z -
           w.x * x.z * z.y;
inv.x.z =  x.y * y.z * w.w -
           x.y * y.w * w.z -
           y.y * x.z * w.w +
           y.y * x.w * w.z +
           w.y * x.z * y.w -
           w.y * x.w * y.z;
inv.y.z = -x.x * y.z * w.w +
           x.x * y.w * w.z +
           y.x * x.z * w.w -
           y.x * x.w * w.z -
           w.x * x.z * y.w +
           w.x * x.w * y.z;
inv.z.z =  x.x * y.y * w.w -
           x.x * y.w * w.y -
           y.x * x.y * w.w +
           y.x * x.w * w.y +
           w.x * x.y * y.w -
           w.x * x.w * y.y;
inv.w.z = -x.x * y.y * w.z +
           x.x * y.z * w.y +
           y.x * x.y * w.z -
           y.x * x.z * w.y -
           w.x * x.y * y.z +
           w.x * x.z * y.y;
inv.x.w = -x.y * y.z * z.w +
           x.y * y.w * z.z +
           y.y * x.z * z.w -
           y.y * x.w * z.z -
           z.y * x.z * y.w +
           z.y * x.w * y.z;
inv.y.w =  x.x * y.z * z.w -
           x.x * y.w * z.z -
           y.x * x.z * z.w +
           y.x * x.w * z.z +
           z.x * x.z * y.w -
           z.x * x.w * y.z;
inv.z.w = -x.x * y.y * z.w +
           x.x * y.w * z.y +
           y.x * x.y * z.w -
           y.x * x.w * z.y -
           z.x * x.y * y.w +
           z.x * x.w * y.y;
inv.w.w =  x.x * y.y * z.z -
           x.x * y.z * z.y -
           y.x * x.y * z.z +
           y.x * x.z * z.y +
           z.x * x.y * y.z -
           z.x * x.z * y.y;
type det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x + x.w * inv.w.x;
if (det == 0)
    return mat4<type>::identity();
det = 1.0f / det;
return inv * det;
}
)";
                break;
              case 3:
                r R"(
constexpr mat3<type> inverse() const
{
mat3<type> inv;
inv.x.x =  y.y * z.z -
           z.y * y.z;
inv.y.x = -y.x * z.z +
           z.x * y.z;
inv.z.x =  y.x * z.y -
           z.x * y.y;
inv.x.y = -x.y * z.z +
           z.y * x.z;
inv.y.y =  x.x * z.z -
           z.x * x.z;
inv.z.y = -x.x * z.y +
           z.x * x.y;
inv.x.z =  x.y * y.z -
           y.y * x.z;
inv.y.z = -x.x * y.z +
           y.x * x.z;
inv.z.z =  x.x * y.y -
           y.x * x.y;
type det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x;
if (det == 0)
    return mat3<type>::identity();
det = 1.0f / det;
return inv * det;
}
)";
                break;
              case 2:
                r R"(
constexpr mat2<type> inverse() const
{
mat2<type> inv;
inv.x.x =  y.y;
inv.y.x = -y.x;
inv.x.y = -x.y;
inv.y.y =  x.x;
type det = x.x * inv.x.x + x.y * inv.y.x;
if (det == 0)
    return mat2<type>::identity();
det = 1.0f / det;
return inv * det;
}
)";
                break;
            }
        };

        auto MatrixMul = [&](int x1y2, int x2, int y1)
        {
            auto Ma = [&](const char *t, int x, int y) -> const char *
            {
                if (x == 1 && y == 1) return t;
                if (x == 1) return Jo("vec", y, '<', t, '>');
                if (y == 1) return Jo("vec", x, '<', t, '>');
                return Jo("mat", x, 'x', y, '<', t, '>');
            };
            auto At = [&](int x, int y, int xx, int yy) -> const char *
            {
                if (xx == 1 && yy == 1) return "";
                if (xx == 1) return Jo(field_names_main[y]);
                if (yy == 1) return Jo(field_names_main[x]);
                return Jo(field_names_main[x], '.', field_names_main[y]);
            };

            std::string str = "decltype(T{}*TT{}";
            for (int i = 1; i < x1y2; i++) str += "+T{}*TT{}";
            str += ')';
            l "template <typename TT> constexpr " << Ma(str.c_str(), x2, y1) << " mul(const " << Ma("TT", x2, x1y2) << " &o) const {return {";
            for (int w = 0; w < x2; w++)
            {
                for (int h = 0; h < y1; h++)
                {
                    if (h != 0 || w != 0) l ", ";
                    for (int i = 0; i < x1y2; i++)
                    {
                        if (i != 0) l '+';
                        l At(i,h,x1y2,y1) << "*o." << At(w,i,x2,x1y2);
                    }
                }
            }
            l "};}\n";
        };

        // Prototypes
        GenVectorPrototypes();
        l "\n";

        { // Vectors
            for (int sz = 2; sz <= 4; sz++)
            {
                // Header
                l "template <typename T> struct vec<" << sz << ",T> // vec" << sz <<"\n{\n" <<
                  "static constexpr int size = " << sz << ";\n";
                CommonHeader();
                l "static constexpr bool is_floating_point = std::is_floating_point<type>::value;";


                // Fields
                Fields(sz, "T");


                // Members
                CommonMembers(sz);
                { // Length
                    l "constexpr auto len_sqr() const {return "; // Squared
                    for (int i = 0; i < sz; i++)
                    {
                        if (i != 0) l " + ";
                        l field_names_main[i] << '*' << field_names_main[i];
                    }
                    l ";}\n";
                    l "constexpr auto len() const {return std::sqrt(len_sqr());}\n"; // Normal
                }
                { // Cross and dot products

                    // Dot
                    l "template <typename TT> constexpr auto dot(const vec" << sz << "<TT> &o) const {return ";
                    for (int i = 0; i < sz; i++)
                    {
                        if (i != 0) l " + ";
                        l field_names_main[i] << "*o." << field_names_main[i];
                    }
                    l ";}\n";

                    // Cross
                    switch (sz)
                    {
                      case 3:
                        l "template <typename TT> constexpr auto cross(const vec3<TT> &o) const -> vec3<decltype(y * o.z - z * o.y)> {return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x};}\n";
                        break;
                      case 2: // Pseudo cross product. Returns z only.
                        l "template <typename TT> constexpr auto cross(const vec2<TT> &o) const -> decltype(x * o.y - y * o.x) {return x * o.y - y * o.x;}\n";
                        break;
                    }
                }
                if (sz == 2) // Ratio
                    l "constexpr decltype(std::sqrt(x/y)) ratio() const {return decltype(std::sqrt(x/y))(x) / decltype(std::sqrt(x/y))(y);}\n"; // std:sqrt is for determining best suitable floating-point type.
                // Normalize
                l "constexpr auto norm() const -> vec" << sz << "<decltype(type{}/len())> {auto l = len(); if (l == 0) return {0}; else return *this / l;}\n";
                { // Apply
                    l "template <typename TT> vec" << sz << "<decltype(std::declval<TT>()(x))> apply(TT *func) const {return {";
                    for (int i = 0; i < sz; i++)
                    {
                        if (i != 0) l ", ";
                        l "func(" << field_names_main[i] << ")";
                    }
                    l "};}\n";
                }
                { // Bool pack
                    auto BoolFunc = [&](const char *name, const char *bin, bool inverted)
                    {
                        l "constexpr bool " << name << "() const {return ";
                        if (inverted) l "!(";
                        for (int i = 0; i < sz; i++)
                        {
                            if (i != 0) l ' ' << bin << ' ';
                            l field_names_main[i];
                        }
                        if (inverted) l ")";
                        l ";}\n";
                    };
                    BoolFunc("none", "||", 1);
                    BoolFunc("any", "||", 0);
                    BoolFunc("each", "&&", 0);
                }
                for (int i = 1; i <= 4; i++) // Multiplication
                    MatrixMul(sz, i, 1);


                l "};\n";
            }
        }
        { // Matrices
            for (int h = 2; h <= 4; h++)
            {
                for (int w = 2; w <= 4; w++)
                {
                    // Header
                    l "template <typename T> struct vec<" << w << ",vec<" << h << ",T>> // mat" << w << 'x' << h << "\n{\n" <<
                      "static constexpr int width = " << w << ", height = " << h << ";\n";
                    CommonHeader();
                    l "static constexpr bool is_floating_point = vec" << h << "<T>::is_floating_point;";


                    // Fields
                    Fields(w, Jo("vec",h,"<T>"));


                    // Members
                    CommonMembers(w);
                    { // Additional ctors
                        l "constexpr vec("; // Full set of initializers
                        for (int ww = 0; ww < w; ww++)
                        {
                            for (int hh = 0; hh < h; hh++)
                            {
                                if (ww != 0 || hh != 0) l ", ";
                                l "type " << field_names_main[ww] << field_names_main[hh];
                            }
                        }
                        l ") : ";
                        for (int ww = 0; ww < w; ww++)
                        {
                            if (ww != 0) l ", ";
                            l field_names_main[ww] << '(';
                            for (int hh = 0; hh < h; hh++)
                            {
                                if (hh != 0) l ',';
                                l field_names_main[ww] << field_names_main[hh];
                            }
                            l ')';
                        }
                        l " {}\n";
                    }
                    { // Transpose
                        l "constexpr mat" << h << 'x' << w << "<type> transpose() const {return {";
                        for (int hh = 0; hh < h; hh++)
                        {
                            for (int ww = 0; ww < w; ww++)
                            {
                                if (ww != 0 || hh != 0) l ',';
                                l field_names_main[ww] << '.' << field_names_main[hh];
                            }
                        }
                        l "};}\n";
                    }
                    { // Static pseudo-constructors
                        l "static constexpr vec identity() {return {"; // Identity
                        for (int ww = 0; ww < w; ww++)
                        {
                            for (int hh = 0; hh < h; hh++)
                            {
                                if (ww != 0 || hh != 0) l ", ";
                                if (ww == hh) l '1';
                                else l '0';
                            }
                        }
                        l "};}\n";

                        for (int i = 2; i <= 4; i++) // Diagonal
                        {
                            if (i > std::min(w,h)) break;
                            l "static constexpr vec dia(const vec" << i << "<type> &v) {return {";
                            for (int ww = 0; ww < w; ww++)
                            {
                                for (int hh = 0; hh < h; hh++)
                                {
                                    if (ww != 0 || hh != 0) l ", ";
                                    if (ww == hh)
                                    {
                                        if (ww < i) l "v." << field_names_main[ww];
                                        else l '1';
                                    }
                                    else l '0';
                                }
                            }
                            l "};}\n";
                        }

                        auto MatrixPseudoCtorCascade = [&](int minw, int minh, const char *name, const char *params, const char *sh_params, const char *body, bool float_only = 1)
                        {
                            if (w == minw && h == minh)
                            {
                                l "static constexpr vec " << name << '(' << params << ")\n{\n";
                                if (float_only) l "static_assert(is_floating_point, \"This function only makes sense for floating-point matrices.\");\n";
                                l (1+body) << "}\n";
                            }
                            else if (w >= minw && h >= minh) l "static constexpr vec " << name << '(' << params << ") {return mat" << minw << 'x' << minh << "<type>::" << name << "(" << sh_params << ").to_mat" << w << 'x' << h << "();}\n";
                        };

                        MatrixPseudoCtorCascade(2, 2, "ortho2D", "const vec2<type> &sz", "sz", R"(
return {2 / sz.x, 0,
$       0, 2 / sz.y};
)");
                        MatrixPseudoCtorCascade(3, 2, "ortho2D", "const vec2<type> &min, const vec2<type> &max", "min, max", R"(
return {2 / (max.x - min.x), 0,
$       0, 2 / (max.y - min.y),
$       (min.x + max.x) / (min.x - max.x), (min.y + max.y) / (min.y - max.y)};
)");
                        MatrixPseudoCtorCascade(4, 3, "ortho", "const vec2<type> &sz, type near, type far", "sz, near, far", R"(
return {2 / sz.x, 0, 0,
$       0, 2 / sz.y, 0,
$       0, 0, 2 / (near - far),
$       0, 0, (near + far) / (near - far)};
)");
                        MatrixPseudoCtorCascade(4, 3, "ortho", "const vec2<type> &min, const vec2<type> &max, type near, type far", "min, max, near, far", R"(
return {2 / (max.x - min.x), 0, 0,
$       0, 2 / (max.y - min.y), 0,
$       0, 0, 2 / (near - far),
$       (min.x + max.x) / (min.x - max.x), (min.y + max.y) / (min.y - max.y), (near + far) / (near - far)};
)");
                        MatrixPseudoCtorCascade(4, 3, "look_at", "const vec3<type> &src, const vec3<type> &dst, const vec3<type> &local_up", "src, dst, local_up", R"(
vec3<T> v3 = (src-dst).norm();
vec3<T> v1 = local_up.cross(v3).norm();
vec3<T> v2 = v3.cross(v1);
return {v1.x, v2.x, v3.x,
$       v1.y, v2.y, v3.y,
$       v1.z, v2.z, v3.z,
$       -src.x*v1.x - src.y*v1.y - src.z*v1.z, -src.x*v2.x - src.y*v2.y - src.z*v2.z, -src.x*v3.x - src.y*v3.y - src.z*v3.z};
)");
                        MatrixPseudoCtorCascade(4, 3, "translate", "const vec3<type> &in", "in", R"(
return {1, 0, 0,
$       0, 1, 0,
$       0, 0, 1,
$       in.x, in.y, in.z};
)", 0);
                        MatrixPseudoCtorCascade(2, 2, "rotate2D", "type angle", "angle", R"(
type c = std::cos(angle);
type s = std::sin(angle);
return {c, s,
$       -s, c};
)");
                        MatrixPseudoCtorCascade(3, 3, "rotate_with_normalized_axis", "const vec3<type> &in, type angle", "in, angle", R"(
type c = std::cos(angle);
type s = std::sin(angle);
return {in.x * in.x * (1 - c) + c, in.y * in.x * (1 - c) + in.z * s, in.x * in.z * (1 - c) - in.y * s,
$       in.x * in.y * (1 - c) - in.z * s, in.y * in.y * (1 - c) + c, in.y * in.z * (1 - c) + in.x * s,
$       in.x * in.z * (1 - c) + in.y * s, in.y * in.z * (1 - c) - in.x * s, in.z * in.z * (1 - c) + c};
)");
                        MatrixPseudoCtorCascade(3, 3, "rotate", "const vec3<type> &in, type angle", "in, angle", R"(
return rotate_with_normalized_axis(in.norm(), angle);
)");
                        MatrixPseudoCtorCascade(4, 4, "perspective", "type yfov, type wh_aspect, type near, type far", "yfov, wh_aspect, near, far", R"(
yfov = (T)1 / std::tan(yfov / 2);
return {yfov / wh_aspect , 0    , 0                             , 0  ,
$       0                , yfov , 0                             , 0  ,
$       0                , 0    , (near + far) / (near - far)   , -1 ,
$       0                , 0    , 2 * near * far / (near - far) , 0  };
)");
                        MatrixPseudoCtorCascade(2, 2, "scale2D", "const vec2<type> &v", "v", R"(
return {v.x, 0,
$       0, v.y};
)", 0);
                        MatrixPseudoCtorCascade(3, 3, "scale", "const vec3<type> &v", "v", R"(
return {v.x, 0, 0,
$       0, v.y, 0,
$       0, 0, v.z};
)", 0);
                    }
                    { // 2D resizers
                        for (int hhh = 2; hhh <= 4; hhh++)
                        {
                            for (int www = 2; www <= 4; www++)
                            {
                                if (www == w && hhh == h) continue;
                                l "constexpr mat" << www << 'x' << hhh << "<type> to_mat" << www << 'x' << hhh << "() const {return {";
                                for (int ww = 0; ww < www; ww++)
                                {
                                    for (int hh = 0; hh < hhh; hh++)
                                    {
                                        if (ww != 0 || hh != 0) l ',';
                                        if (ww < w && hh < h)
                                            l field_names_main[ww] << '.' << field_names_main[hh];
                                        else
                                        {
                                            if (ww == hh) l '1';
                                            else l '0';
                                        }
                                    }
                                }
                                l "};}\n";
                                if (www == hhh)
                                    l "constexpr mat" << www << "<type> to_mat" << www << "() const {return to_mat" << www << 'x' << www << "();}\n";
                            }
                        }
                    }
                    { // Apply
                        l "template <typename TT> mat" << w << 'x' << h << "<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {";
                        for (int i = 0; i < w; i++)
                        {
                            if (i != 0) l ", ";
                            l field_names_main[i] << ".apply(func)";
                        }
                        l "};}\n";
                    }
                    { // Bool pack
                        auto BoolFunc = [&](const char *name, const char *bin, bool inverted)
                        {
                            l "constexpr bool " << name << "() const {return ";
                            if (inverted) l "!(";
                            for (int ww = 0; ww < w; ww++)
                            {
                                for (int hh = 0; hh < h; hh++)
                                {
                                    if (ww != 0 || hh != 0) l ' ' << bin << ' ';
                                    l field_names_main[ww] << '.' << field_names_main[hh];
                                }
                            }
                            if (inverted) l ")";
                            l ";}\n";
                        };
                        BoolFunc("none", "||", 1);
                        BoolFunc("any", "||", 0);
                        BoolFunc("each", "&&", 0);
                    }
                    if (w == h) MatrixInverse(w); // Inverse
                    for (int i = 1; i <= 4; i++) // Multiplication
                        MatrixMul(w, i, h);

                    l "};\n";
                }
            }
        }
        l "\n";

        // Operators
        for (int sz = 2; sz <= 4; sz++)
        {
            for (const char *const &op : ops_bin) // Note the &.
            {
                bool en_if = &op == ops_bin + (sizeof ops_bin / sizeof ops_bin[0]) - 1;
                // vec @ vec
                l "template <typename T1, typename T2> constexpr vec" << sz << "<decltype(T1{}" << op << "T2{})> operator" << op << "(const vec" << sz << "<T1> &first, const vec" << sz << "<T2> &second) {return {";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ',';
                    l "first." << field_names_main[i] << op << "second." << field_names_main[i];
                }
                l "};}\n";
                // vec @ other
                l "template <typename T1, typename T2> constexpr vec" << sz << "<decltype(T1{}" << op << "T2{})> operator" << op << "(const vec" << sz << "<T1> &first, const T2 &second) {return {";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ',';
                    l "first." << field_names_main[i] << op << "second";
                }
                l "};}\n";
                // other @ vec
                l "template <typename T1, typename T2> constexpr " << (en_if ? "typename std::enable_if_t<!std::is_base_of<std::ostream,T1>::value," : "") << "vec" << sz << "<decltype(T1{}" << op << "T2{})>" << (en_if ? ">::type" : "") << " operator" << op << "(const T1 &first, const vec" << sz << "<T2> &second) {return {";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ',';
                    l "first" << op << "second." << field_names_main[i];
                }
                l "};}\n";
            }
            for (const char *op : ops_un)
            {
                l "template <typename T> constexpr vec" << sz << "<decltype(" << op << "T{})> operator" << op << "(const vec" << sz << "<T> &object) {return {";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ',';
                    l op << "object." << field_names_main[i];
                }
                l "};}\n";
            }
            for (const char *op : ops_fix)
            {
                // Prefix
                l "template <typename T> constexpr vec" << sz << "<T> &operator" << op << "(vec" << sz << "<T> &object) {";
                for (int i = 0; i < sz; i++)
                {
                    l op << "object." << field_names_main[i] << "; ";
                }
                l "return object;}\n";
                // Postfix
                l "template <typename T> constexpr vec" << sz <<"<T> operator" << op << "(vec" << sz << "<T> &object, int) {return {";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ',';
                    l "object." << field_names_main[i] << op;
                }
                l "};}\n";
            }
            for (const char *op : ops_comp)
            {
                // vec @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const vec" << sz << "<T2> &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l " && ";
                    l "(first." << field_names_main[i] << ' ' << op << ' ' << "second." << field_names_main[i] << ')';
                }
                l ";}\n";
                // vec @ other
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const T2 &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l " && ";
                    l "(first." << field_names_main[i] << ' ' << op << ' ' << "second" << ')';
                }
                l ";}\n";
                // other @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const T1 &first, const vec" << sz << "<T2> &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l " && ";
                    l "(first" << ' ' << op << ' ' << "second." << field_names_main[i] << ')';
                }
                l ";}\n";
            }
            for (const char *op : ops_bool)
            {
                // vec @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const vec" << sz << "<T2> &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ' ' << op << ' ';
                    l "first." << field_names_main[i] << ' ' << op << ' ' << "second." << field_names_main[i];
                }
                l ";}\n";
                // vec @ other
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const T2 &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ' ' << op << ' ';
                    l "first." << field_names_main[i];
                }
                l ' ' << op << " second;}\n";
                // other @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const T1 &first, const vec" << sz << "<T2> &second) {return first " << op << ' ';
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l ' ' << op << ' ';
                    l "second." << field_names_main[i];
                }
                l ";}\n";
            }
            for (const char *op : ops_as)
            {
                // vec @ vec
                l "template <typename T1, typename T2> constexpr vec" << sz << "<T1> &operator" << op << "(vec" << sz << "<T1> &first, const vec" << sz << "<T2> &second) {";
                for (int i = 0; i < sz; i++)
                    l "first." << field_names_main[i] << ' ' << op << ' ' << "second." << field_names_main[i] << "; ";
                l "return first;}\n";
                // vec @ other
                l "template <typename T1, typename T2> constexpr vec" << sz << "<T1> &operator" << op << "(vec" << sz << "<T1> &first, const T2 &second) {";
                for (int i = 0; i < sz; i++)
                    l "first." << field_names_main[i] << ' ' << op << ' ' << "second; ";
                l "return first;}\n";
            }
            l "\n";

            // == and !=
            const char *eq_ops[] {"==", "!="};
            const char *eq_op_delims[] {" && ", " || "};
            for (int i = 0; i < 2; i++)
            {
                const char *op = eq_ops[i];
                const char *delim = eq_op_delims[i];
                // vec @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const vec" << sz << "<T2> &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l delim;
                    l "(first." << field_names_main[i] << ' ' << op << ' ' << "second." << field_names_main[i] << ')';
                }
                l ";}\n";
                // vec @ other
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const vec" << sz << "<T1> &first, const T2 &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l delim;
                    l "(first." << field_names_main[i] << ' ' << op << ' ' << "second" << ')';
                }
                l ";}\n";
                // other @ vec
                l "template <typename T1, typename T2> constexpr bool operator" << op << "(const T1 &first, const vec" << sz << "<T2> &second) {return ";
                for (int i = 0; i < sz; i++)
                {
                    if (i != 0) l delim;
                    l "(first" << ' ' << op << ' ' << "second." << field_names_main[i] << ')';
                }
                l ";}\n";
            }
        }

        // Stream printers
        for (int i = 2; i <= 4; i++)
        {
            l "template <typename X, typename Y, typename T> std::basic_ostream<X,Y> &operator<<(std::basic_ostream<X,Y> &stream, const vec<" << i << ",T> &vector) {stream << '[' << vector." << field_names_main[0];
            for (int j = 1; j < i; j++)
                l " << ',' << vector." << field_names_main[j];
            l " << ']'; return stream;}\n";
        }

        l "}\n";
    }

    void Quaternion()
    {
        r R"(
namespace Quaternion
{
template <typename T = float> struct GenericQuaternion
{
static_assert(std::is_floating_point<T>::value, "Quaternion template parameter must be floating-point.");

Vector::vec4<T> vec;

GenericQuaternion() : vec{0,0,0,1} {}
GenericQuaternion(const Vector::vec4<T> &o) : vec(o) {}

static GenericQuaternion from_norm_axis_and_angle(const Vector::vec3<T> &v, T angle)
{
return GenericQuaternion({v.x * std::sin(angle / 2.f), v.y * std::sin(angle / 2.f), v.z * std::sin(angle / 2.f), std::cos(angle / 2.f)});
}
static GenericQuaternion from_axis_and_angle(const Vector::vec3<T> &v, T angle)
{
return from_norm_axis_and_angle(v.norm(), angle);
}

GenericQuaternion norm() const
{
return GenericQuaternion(vec.norm());
}

void normalize()
{
vec = vec.norm();
}
GenericQuaternion operator+(const GenericQuaternion &o) const
{
return GenericQuaternion(vec + o.vec);
}
GenericQuaternion &operator+=(const GenericQuaternion &o)
{
vec += o.vec;
return *this;
}
GenericQuaternion operator-(const GenericQuaternion &o) const
{
return GenericQuaternion(vec - o.vec);
}
GenericQuaternion &operator-=(const GenericQuaternion &o)
{
vec -= o.vec;
return *this;
}
GenericQuaternion operator-() const
{
return GenericQuaternion(-vec.x, -vec.y, -vec.z, vec.w);
}
GenericQuaternion operator*(const GenericQuaternion &o) const
{
return GenericQuaternion(vec.w*o.vec.x + vec.x*o.vec.w + vec.y*o.vec.z - vec.z*o.vec.y,
                         vec.w*o.vec.y - vec.x*o.vec.z + vec.y*o.vec.w + vec.z*o.vec.x,
                         vec.w*o.vec.z + vec.x*o.vec.y - vec.y*o.vec.x + vec.z*o.vec.w,
                         vec.w*o.vec.w - vec.x*o.vec.x - vec.y*o.vec.y - vec.z*o.vec.z);
}
GenericQuaternion &operator*=(const GenericQuaternion &o)
{
vec = {vec.w*o.vec.x + vec.x*o.vec.w + vec.y*o.vec.z - vec.z*o.vec.y,
$      vec.w*o.vec.y - vec.x*o.vec.z + vec.y*o.vec.w + vec.z*o.vec.x,
$      vec.w*o.vec.z + vec.x*o.vec.y - vec.y*o.vec.x + vec.z*o.vec.w,
$      vec.w*o.vec.w - vec.x*o.vec.x - vec.y*o.vec.y - vec.z*o.vec.z};
return *this;
}
T dot(const GenericQuaternion &o) const
{
return vec.dot(o.vec);
}
T len_sqr() const
{
return vec.len_sqr();
}
T len() const
{
return vec.len();
}
GenericQuaternion combine(const GenericQuaternion &o, T fac) const
{
return GenericQuaternion(vec.interpolate(o.vec, fac));
}

bool operator==(const GenericQuaternion &o) const
{
return vec == o.vec;
}
bool operator!=(const GenericQuaternion &o) const
{
return vec != o.vec;
}

Vector::vec3<T> get_axis() const
{
return vec.to_vec3().norm();
}
Vector::vec3<T> get_not_norm_axis() const
{
return vec.to_vec3();
}
T get_angle() const
{
return std::atan2(vec.to_vec3().len(), vec.w) * 2;
}

template <typename TT> GenericQuaternion mult_angle(TT n) const
{
return from_axis_and_angle(get_not_norm_axis(), get_angle() * n);
}

template <typename TT> Vector::vec3<TT> apply(const Vector::vec3<TT> &in) const // 24x [*|/]  17x [+|-]
{
float newx = vec.w*in.x + vec.y*in.z - vec.z*in.y;
float newy = vec.w*in.y - vec.x*in.z + vec.z*in.x;
float newz = vec.w*in.z + vec.x*in.y - vec.y*in.x;
float neww = vec.x*in.x + vec.y*in.y + vec.z*in.z;

return {newx*vec.w + neww*vec.x - newy*vec.z + newz*vec.y,
$       neww*vec.y + newx*vec.z + newy*vec.w - newz*vec.x,
$       neww*vec.z - newx*vec.y + newy*vec.x + newz*vec.w};
}
template <typename TT> Vector::vec4<TT> apply(const Vector::vec4<TT> &in) const // 24x [*|/]  17x [+|-]
{
float newx = vec.w*in.x + vec.y*in.z - vec.z*in.y;
float newy = vec.w*in.y - vec.x*in.z + vec.z*in.x;
float newz = vec.w*in.z + vec.x*in.y - vec.y*in.x;
float neww = vec.x*in.x + vec.y*in.y + vec.z*in.z;

return {newx*vec.w + neww*vec.x - newy*vec.z + newz*vec.y,
$       neww*vec.y + newx*vec.z + newy*vec.w - newz*vec.x,
$       neww*vec.z - newx*vec.y + newy*vec.x + newz*vec.w,
$       in.w};
}

Vector::mat3<T> get_matrix_from_normalized() const // 18x [*|/]  12x [+|-]    +    mult: 9x [*|/]  6x [+|-]
{
return {1 - 2*vec.y*vec.y - 2*vec.z*vec.z, 2*vec.x*vec.y + 2*vec.z*vec.w, 2*vec.x*vec.z - 2*vec.y*vec.w,
$       2*vec.x*vec.y - 2*vec.z*vec.w, 1 - 2*vec.x*vec.x - 2*vec.z*vec.z, 2*vec.y*vec.z + 2*vec.x*vec.w,
$       2*vec.x*vec.z + 2*vec.y*vec.w, 2*vec.y*vec.z - 2*vec.x*vec.w, 1 - 2*vec.x*vec.x - 2*vec.y*vec.y};
}
Vector::mat3<T> normalize_and_get_matrix() // 18x [*|/]  12x [+|-]    +    mult: 9x [*|/]  6x [+|-]
{
normalize();
return get_matrix_from_normalized();
}
};

using Quaternion = GenericQuaternion<>;
}
)";
    }

    void CustomOperators()
    {
        l "namespace CustomOperators\n{\n";
        l "namespace Internal\n{\n";
        for (const char *name : custom_op_list)
        {
            l "template <typename T> struct " << name << "_tmp\n{\nT ref;\n";
            for (int i = 2; i <= 4; i++)
            {
                l "template <typename TT> constexpr auto operator" << op_delim << "(const Vector::vec" << i << "<TT> &obj) const {return ref." << name << "(obj);}\n";
                l "template <typename TT> constexpr auto operator" << op_delim << "(Vector::vec" << i << "<TT> &&obj) const {return ref." << name << "(obj);}\n";
            }
            for (int h = 2; h <= 4; h++)
            {
                for (int w = 2; w <= 4; w++)
                {
                    l "template <typename TT> constexpr auto operator" << op_delim << "(const Vector::mat" << w << 'x' << h << "<TT> &obj) const {return ref." << name << "(obj);}\n";
                    l "template <typename TT> constexpr auto operator" << op_delim << "(Vector::mat" << w << 'x' << h << "<TT> &&obj) const {return ref." << name << "(obj);}\n";
                }
            }
            l "};\n";
        }
        l "}\n\n";
        for (const char *name : custom_op_list)
        {
            l "namespace Internal {struct " << name << "_type {constexpr " << name << "_type(){}};} ";
            l "static constexpr Internal::" << name << "_type " << name << ";\n";
            for (int i = 2; i <= 4; i++)
            {
                l "template <typename T> constexpr auto operator" << op_delim << "(const Vector::vec" << i << "<T> &obj, decltype(" << name << ")) {return Internal::" << name << "_tmp<const Vector::vec" << i << "<T> &>{obj};}\n";
                l "template <typename T> constexpr auto operator" << op_delim << "(Vector::vec" << i << "<T> &&obj, decltype(" << name << ")) {return Internal::" << name << "_tmp<Vector::vec" << i << "<T>>{obj};}\n";
            }
            for (int h = 2; h <= 4; h++)
            {
                for (int w = 2; w <= 4; w++)
                {
                    l "template <typename T> constexpr auto operator" << op_delim << "(const Vector::mat" << w << 'x' << h << "<T> &obj, decltype(" << name << ")) {return Internal::" << name << "_tmp<const Vector::mat" << w << 'x' << h << "<T> &>{obj};}\n";
                    l "template <typename T> constexpr auto operator" << op_delim << "(Vector::mat" << w << 'x' << h << "<T> &&obj, decltype(" << name << ")) {return Internal::" << name << "_tmp<Vector::mat" << w << 'x' << h << "<T>>{obj};}\n";
                }
            }
        }
        l "}\n";
    }

    void Misc()
    {
        r R"(
namespace Misc
{
template <typename T> T pi()
{
static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
static const T ret = std::atan((T)1)*4;
return ret;
}

template <typename T> T to_rad(T in)
{
static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
return in * pi<T>() / (T)180;
}
template <typename T> T to_deg(T in)
{
static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
return in * (T)180 / pi<T>();
}

template <typename T, typename TT> constexpr T ipow(T a, TT b)
{
static_assert(std::is_integral<TT>::value, "Non integral template parameters make no sense for this function.");
T ret = 1;
while (b--)
{
ret *= a;
}
return ret;
}

template <typename T, typename MIN, typename MAX> constexpr T clamp(T val, MIN min, MAX max)
{
static_assert(std::is_arithmetic<T>::value &&
              std::is_arithmetic<MIN>::value &&
              std::is_arithmetic<MAX>::value, "Non arithmetic template parameters make no sense for this function.");
if (val < min) return min;
if (val > max) return max;
return val;
}

template <typename T> constexpr int sign(T val)
{
return (val > 0) - (val < 0);
}

template <typename T> constexpr T smoothstep(T x)
{
static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
return 3*x*x-2*x*x*x;
}

template <typename T, typename TT> constexpr T true_div(T a, TT b)
{
static_assert(std::is_integral<T>::value &&
              std::is_integral<TT>::value, "Argument types must be integral.");
if (a >= 0)
    return a / b;
else
    return (a + 1) / b - (b >= 0 ? 1 : -1);
}

template <typename T, typename TT> constexpr T true_mod(T a, TT b)
{
static_assert(std::is_integral<T>::value &&
              std::is_integral<TT>::value, "Argument types must be integral.");
if (a >= 0)
    return a % b;
else
    return (b >= 0 ? b : -b) - 1 + (a + 1) % b;
}
}
)";
    }

    void StdSpecializations()
    {
        r R"(
namespace std
{
)";
        for (int i = 2; i <= 4; i++)
        {
            r R"(
template <typename T> struct less<Math::Vector::vec)" << i << R"(<T>>
{
using result_type = bool;
using first_argument_type = Math::Vector::vec)" << i << R"(<T>;
using second_argument_type = Math::Vector::vec)" << i << R"(<T>;
constexpr bool operator()(const first_argument_type &a, const second_argument_type &b) const
{
)";
            for (int j = 0; j < i; j++)
                l "if (a." << field_names_main[j] << " < b." << field_names_main[j] << ") return 1;\n" <<
                  "if (a." << field_names_main[j] << " > b." << field_names_main[j] << ") return 0;\n";
            r R"(
return 0;
}
};
)";
        }
        r R"(
}
)";
    }
}

int main()
{
    r R"(
#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

// Version )" VERSION R"( by HolyBlackCat

#include <functional>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>
#include <utility>


namespace Math
{
)";
    Gen::Vector();
    l "\n";
    Gen::Quaternion();
    l "\n";
    Gen::CustomOperators();
    l "\n";
    Gen::Misc();
    r R"(
}

)";
    Gen::StdSpecializations();
    r R"(

using namespace Math::Vector;
using namespace Math::Quaternion;
using namespace Math::CustomOperators;
using namespace Math::Misc;

#endif
)";
}