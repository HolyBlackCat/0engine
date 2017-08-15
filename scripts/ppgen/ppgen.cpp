#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE
#define VERSION "0.0.1"
// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE

std::ofstream out_file("preprocessor.h");

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
            Indent();
            indentation++;
            break;
          case '}':
            indentation--;
            Indent();
            break;
          case '@':
            Indent(-2);
            break;
          case '$':
            Indent(-4);
            break;
          default:
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

static constexpr int pp_args = 64;

int main()
{
    r R"(
#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

// Version )" VERSION R"( by HolyBlackCat

)";
    // Utils
    l "#define PP0_F_NULL()\n";
    l "#define PP0_F_COMMA() ,\n";
    l '\n';
    l "#define PP0_E(...) __VA_ARGS__\n";
    l '\n';
    l "#define PP0_VA_FIRST(...) PP0_VA_FIRST_IMPL_(__VA_ARGS__,)\n";
    l "#define PP0_VA_FIRST_IMPL_(x, ...) x\n";
    l '\n';
    l "#define PP0_PARENS(...) (__VA_ARGS__)\n";
    l "#define PP0_DEL_PARENS(...) PP0_E __VA_ARGS__\n";
    l "#define PP0_2_PARENS(...) ((__VA_ARGS__))\n";
    l '\n';
    l "#define PP0_CC(a, b) PP0_CC_IMPL_(a,b)\n";
    l "#define PP0_CC_IMPL_(a, b) a##b\n";
    l '\n';
    l "#define PP0_CALL(macro, ...) macro(__VA_ARGS__)\n";
    l '\n';

    // Variadic size
    l "#define PP0_VA_SIZE(...) PP0_VA_SIZE_IMPL_(__VA_ARGS__";
    for (int i = pp_args; i >= 0; i--)
        l "," << i;
    l ")\n";
    l "#define PP0_VA_SIZE_IMPL_(";
    for (int i = 0; i < pp_args; i++)
        l "i" << i+1 << ",";
    l "size,...) size\n";
    l '\n';

    // To string
    l "#define PP0_STR(...) PP0_STR_IMPL_(__VA_ARGS__)\n";
    l "#define PP0_STR_IMPL_(...) #__VA_ARGS__\n";
    l '\n';

    // Overload
    l "#define PP0_VA_CALL(name, ...) PP0_CC(name, PP0_VA_SIZE(__VA_ARGS__))\n";
    l '\n';

    // Seq overload
    l "#define PP0_SEQ_CALL(name, seq) PP0_CC(name, PP0_SEQ_SIZE(seq))\n";
    l '\n';

    // Seq ops
    l "#define PP0_SEQ_TO_VA(seq) PP0_SEQ_APPLY(seq, PP0_E, PP0_F_COMMA)\n";
    l "#define PP0_SEQ_TO_VA_PARENS(seq) PP0_SEQ_APPLY(seq, PP0_PARENS, PP0_F_COMMA)\n";
    l "#define PP0_SEQ_EXPAND(seq) PP0_SEQ_APPLY(seq, PP0_E, PP0_F_NULL)\n";
    l "#define PP0_VA_EXPAND(seq) PP0_SEQ_APPLY(PP0_VA_TO_SEQ(seq), PP0_E, PP0_F_NULL)\n";
    l '\n';

    // Seq remove first
    l "#define PP0_SEQ_DEL_FIRST(seq) PP0_SEQ_DEL_FIRST_IMPL_ seq\n";
    l "#define PP0_SEQ_DEL_FIRST_IMPL_(...)\n";
    l '\n';

    // Seq first
    l "#define PP0_SEQ_FIRST(seq) PP0_DEL_PARENS(PP0_VA_FIRST(PP0_SEQ_FIRST_IMPL_ seq,))\n";
    l "#define PP0_SEQ_FIRST_IMPL_(...) (__VA_ARGS__),\n";
    l '\n';

    // Va to seq
    l "#define PP0_VA_TO_SEQ(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__)(__VA_ARGS__)\n";
    for (int i = 0; i <= pp_args; i++)
    {
        l "#define PP0_VA_TO_SEQ_" << i << "(";
        for (int j = 0; j < i; j++)
        {
            if (j != 0) l ",";
            l "i" << j;
        }
        l ") ";
        for (int j = 0; j < i; j++)
            l "(i" << j << ")";
        l "\n";
    }
    l '\n';

    // Seq size
    l "#define PP0_SEQ_SIZE(seq) PP0_CC(PP0_SEQ_SIZE_0 seq, _VAL)\n";
    for (int i = 0; i <= pp_args; i++)
        l "#define PP0_SEQ_SIZE_" << i << "(...) PP0_SEQ_SIZE_" << i+1 << '\n';
    for (int i = 0; i <= pp_args; i++)
        l "#define PP0_SEQ_SIZE_" << i << "_VAL " << i << "\n";
    l '\n';

    // At
    l "#define PP0_VA_AT(index, ...) PP0_CC(PP0_VA_AT_, index)(__VA_ARGS__,)\n";
    l "#define PP0_SEQ_AT(index, seq) PP0_DEL_PARENS(PP0_VA_AT(index, PP0_SEQ_APPLY(seq, PP0_PARENS, PP0_F_COMMA)))\n";
    for (int i = 0; i <= pp_args; i++)
    {
        l "#define PP0_VA_AT_" << i << "(";
        for (int j = 0; j < i; j++)
            l "i" << j << ",";
        l "ret, ...) ret\n";
    }
    l '\n';

    // Seq apply
    l "// macro(i, element)\n";
    l "#define PP0_SEQ_APPLY(seq, macro, macro_sep_f) PP0_SEQ_CALL(PP0_SEQ_APPLY_, seq)(macro, macro_sep_f, seq, )\n";
    l "#define PP0_SEQ_APPLY_0(macro, macro_sep_f, seq, seq_)\n";
    l "#define PP0_SEQ_APPLY_1(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq))\n";
    for (int i = 2; i <= pp_args; i++)
        l "#define PP0_SEQ_APPLY_" << i << "(macro, macro_sep_f, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_SEQ_DEL_FIRST(seq))(macro, macro_sep_f, PP0_SEQ_DEL_FIRST(seq), (PP0_SEQ_FIRST(seq)) seq_)\n";
    l '\n';

    l "\n#endif\n";
}
