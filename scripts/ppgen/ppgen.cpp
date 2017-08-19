#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE
#define VERSION "0.0.6"
// ---------------------------- UPDATE THIS WHEN YOU CHANGE THE CODE

std::ofstream out_file("preprocessor.h");

int indentation = 0;
bool new_line = 0;

std::stringstream ss;

template <typename ...P> const char *Jo(P &&... p)
{
    static constexpr int ret_buffers_c = 32;
    static std::string ret_buffers[ret_buffers_c];
    static int ret_pos = 0;
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

constexpr int pp_args = 64;
constexpr int counter_max = 64;
constexpr int sl_len_max = 64;

const std::string small_suffixes[] {"", "_A", "_B"},
                  large_suffixes[] {"", "_A"};


namespace Gen
{
    void Counter()
    {
        l "// COUNTER\n\n";
        // Definition
        l "#define PP0_COUNTER_DEFINE(type_tag, storage) storage constexpr std::integral_constant<int,0> _pp0_impl_counter(type_tag";
        for (int i = 0; i < counter_max; i++) l ",short";
        l ") {return {};}\n";

        // Read
        l "#define PP0_COUNTER_READ(type_tag) PP0_COUNTER_READ_CONTEXT(type_tag,)\n";
        // Read with context
        l "#define PP0_COUNTER_READ_CONTEXT(type_tag, context) (void(), decltype(context _pp0_impl_counter(type_tag{}";
        for (int i = 0; i < counter_max; i++) l ",0";
        l "))::value)\n";

        // Increment to x+1
        l "#define PP0_COUNTER_INCR_TO_X(value, type_tag, storage) storage constexpr std::integral_constant<int,value> _pp0_impl_counter(type_tag";
        for (int i = 0; i < counter_max; i++)
        {
            l ",";
            if (i % 8 == 0 && i != 1) l " \\\n    ";
            l "PP0_CNT_ARG(value," << (ss << std::setw(2), i) << ")";
        }
        l ") {return {};}\n";
        // Increment by 1
        l "#define PP0_COUNTER_INCR(type_tag, storage) PP0_COUNTER_INCR_TO_X(PP0_COUNTER_READ(type_tag)+1, type_tag, storage)\n";
        // Increment helper
        l "#define PP0_CNT_ARG(cur,x) std::conditional_t<(x < cur), int, short>\n";
    }

    void Strings()
    {
        r R"(
namespace pp0
{
static constexpr std::size_t max_str_lit_len = 256;

template <std::size_t I, std::size_t N> constexpr char sl_at(const char (&str)[N])
{
if constexpr(I < N)
    return str[I];
else
    return '\0';
}

constexpr std::size_t sl_len(const char *str)
{
for (std::size_t i = 0; i < max_str_lit_len; i++)
    if (str[i] == '\0')
        return i;
return 0;
}

template <char ...C> struct str_lit
{
static constexpr char value[] {C..., '\0'};
static constexpr int size = sl_len(value);

template <typename F, typename ...P> struct concat_impl {using type = typename concat_impl<F>::type::template concat_impl<P...>::type;};
template <char ...CC> struct concat_impl<str_lit<CC...>> {using type = str_lit<C..., CC...>;};
template <typename ...P> using concat = typename concat_impl<P...>::type;
};

template <typename, const char *> struct trim_str_lit_impl;
template <std::size_t ...I, const char *S> struct trim_str_lit_impl<std::index_sequence<I...>, S>
{
using type = str_lit<S[I]...>;
};
template <std::size_t N, const char *S> using trim_str_lit = typename trim_str_lit_impl<std::make_index_sequence<N>, S>::type;

#define PP0_STR_LIT(str) ::pp0::trim_str_lit<::pp0::sl_len(str), ::pp0::str_lit<PP0_STR_TO_VA(str)>::value>
#define PP0_STR_TO_VA(str) PP0_STR_TO_VA_16(str,0),PP0_STR_TO_VA_16(str,16),PP0_STR_TO_VA_16(str,32),PP0_STR_TO_VA_16(str,48)
#define PP0_STR_TO_VA_16(str,off) PP0_STR_TO_VA_4(str,0+off),PP0_STR_TO_VA_4(str,4+off),PP0_STR_TO_VA_4(str,8+off),PP0_STR_TO_VA_4(str,12+off)
#define PP0_STR_TO_VA_4(str,off) ::pp0::sl_at<off+0>(str),::pp0::sl_at<off+1>(str),::pp0::sl_at<off+2>(str),::pp0::sl_at<off+3>(str)

template <char ...C> constexpr str_lit<C...> make_str_lit(str_lit<C...>) {return {};}
template <std::size_t N> constexpr auto make_str_lit(const char (&str)[N])
{
return trim_str_lit<sl_len((const char (&)[N])str), str>{};
}

template <std::size_t A, std::size_t B> struct cexpr_pow {static constexpr std::size_t value = A * cexpr_pow<A,B-1>::value;};
template <std::size_t A> struct cexpr_pow<A,0> {static constexpr std::size_t value = 1;};
template <std::size_t N, std::size_t X, typename = std::make_index_sequence<X>> struct num_to_sl_impl;
template <std::size_t N, std::size_t X, std::size_t ...Seq> struct num_to_sl_impl<N, X, std::index_sequence<Seq...>>
{
static constexpr auto func()
{
if constexpr (N >= cexpr_pow<10,X>::value)
    return num_to_sl_impl<N, X+1>::func();
else
    return str_lit<(N / cexpr_pow<10,X-1-Seq>::value % 10 + '0')...>{};
}
};
template <std::size_t N> using num_to_sl = decltype(num_to_sl_impl<N,1>::func());
})";
    }
}


int main()
{
    r R"(
#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

// Version )" VERSION R"( by HolyBlackCat

#include <cstddef>
#include <type_traits>
#include <utility>


)";
    Gen::Counter();
    l "\n\n";

    Gen::Strings();
    l "\n\n";

    // Utils
    l "// UTILS\n\n";
    l "#define PP0_F_NULL(...)\n";
    l "#define PP0_F_COMMA(...) ,\n";
    l '\n';
    l "#define PP0_E(...) __VA_ARGS__\n";
    l '\n';
    l "#define PP0_VA_FIRST(...) PP0_VA_FIRST_IMPL_(__VA_ARGS__,)\n";
    l "#define PP0_VA_FIRST_IMPL_(x, ...) x\n";
    l '\n';
    l "#define PP0_PARENS(...) (__VA_ARGS__)\n";
    l "#define PP0_DEL_PARENS(...) PP0_E __VA_ARGS__\n";
    l "#define PP0_2_PARENS(...) ((__VA_ARGS__))\n";
    l "#define PP0_PARENS_COMMA(...) (__VA_ARGS__),\n";
    l '\n';
    l "#define PP0_CC(a, b) PP0_CC_IMPL_(a,b)\n";
    l "#define PP0_CC_IMPL_(a, b) a##b\n";
    l '\n';
    for (std::string suffix : small_suffixes)
        l "#define PP0_CALL" << suffix << "(macro, ...) macro(__VA_ARGS__)\n";
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

    // Seq first
    l "#define PP0_SEQ_FIRST(seq) PP0_DEL_PARENS(PP0_VA_FIRST(PP0_PARENS_COMMA seq,))\n";
    l '\n';

    // Va to seq
    l "#define PP0_VA_TO_SEQ(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__,)(__VA_ARGS__,)\n";
    l "#define PP0_VA_TO_SEQ_DISCARD_LAST(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__)(__VA_ARGS__)\n";
    l "#define PP0_VA_TO_SEQ_NULL\n";
    l "#define PP0_VA_TO_SEQ_1(x) PP0_VA_TO_SEQ_##x##NULL\n";
    for (int i = 1; i <= pp_args; i++)
    {
        // Note that 1 is added to all the indices in this block. This was done to simplify VA_TO_SEQ_DISCARD_LAST
        l "#define PP0_VA_TO_SEQ_" << i+1 << "(x, ...) (x)PP0_VA_TO_SEQ_" << i << "(__VA_ARGS__)\n";
    }
    l '\n';

    // Seq size
    l "#define PP0_SEQ_SIZE(seq) PP0_CC(PP0_SEQ_SIZE_0 seq, _VAL)\n";
    for (int i = 0; i <= pp_args; i++)
        l "#define PP0_SEQ_SIZE_" << i << "(...) PP0_SEQ_SIZE_" << i+1 << '\n';
    for (int i = 0; i <= pp_args; i++)
        l "#define PP0_SEQ_SIZE_" << i << "_VAL " << i << "\n";
    l '\n';

    // Va at
    l "#define PP0_VA_AT(index, ...) PP0_CC(PP0_VA_AT_, index)(__VA_ARGS__,)\n";
    l "#define PP0_VA_AT_0(ret, ...) ret\n";
    for (int i = 1; i <= pp_args; i++)
        l "#define PP0_VA_AT_" << i << "(_, ...) PP0_VA_AT_" << i-1 << "(__VA_ARGS__)\n";
    l '\n';

    // Seq at
    l "#define PP0_SEQ_AT(index, seq) PP0_SEQ_FIRST( PP0_CC(PP0_SEQ_AT_EAT_, index)(seq) )\n";
    l "#define PP0_SEQ_AT_EAT_0(seq) seq\n";
    for (int i = 1; i <= pp_args; i++)
        l "#define PP0_SEQ_AT_EAT_" << i << "(seq) PP0_SEQ_AT_EAT_" << i-1 << "(PP0_F_NULL seq)\n";

    // Seq apply
    l "// macro(i, data, element...)\n";
    for (std::string suffix : large_suffixes)
    {
        l "#define PP0_SEQ_APPLY" << suffix << "(seq, macro, macro_sep_f, data) PP0_SEQ_CALL(PP0_SEQ_APPLY" << suffix << "_, seq)(macro, macro_sep_f, data, seq, )\n";
        l "#define PP0_SEQ_APPLY" << suffix << "_0(macro, macro_sep_f, data, seq, seq_)\n";
        l "#define PP0_SEQ_APPLY" << suffix << "_1(macro, macro_sep_f, data, seq, seq_) PP0_CALL" << suffix << "(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq))\n";
        for (int i = 2; i <= pp_args; i++)
            l "#define PP0_SEQ_APPLY" << suffix << "_" << i << "(macro, macro_sep_f, data, seq, seq_) PP0_CALL" << suffix << "(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY" << suffix << "_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)\n";
    }
    l '\n';



    l "\n#endif\n";
}
