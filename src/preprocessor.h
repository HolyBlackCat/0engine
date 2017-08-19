#ifndef PREPROCESSOR_H_INCLUDED
#define PREPROCESSOR_H_INCLUDED

// Version 0.0.6 by HolyBlackCat

#include <cstddef>
#include <type_traits>
#include <utility>


// COUNTER

#define PP0_COUNTER_DEFINE(type_tag, storage) storage constexpr std::integral_constant<int,0> _pp0_impl_counter(type_tag,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short,short) {return {};}
#define PP0_COUNTER_READ(type_tag) PP0_COUNTER_READ_CONTEXT(type_tag,)
#define PP0_COUNTER_READ_CONTEXT(type_tag, context) (void(), decltype(context _pp0_impl_counter(type_tag{},0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0))::value)
#define PP0_COUNTER_INCR_TO_X(value, type_tag, storage) storage constexpr std::integral_constant<int,value> _pp0_impl_counter(type_tag, \
    PP0_CNT_ARG(value, 0),PP0_CNT_ARG(value, 1),PP0_CNT_ARG(value, 2),PP0_CNT_ARG(value, 3),PP0_CNT_ARG(value, 4),PP0_CNT_ARG(value, 5),PP0_CNT_ARG(value, 6),PP0_CNT_ARG(value, 7), \
    PP0_CNT_ARG(value, 8),PP0_CNT_ARG(value, 9),PP0_CNT_ARG(value,10),PP0_CNT_ARG(value,11),PP0_CNT_ARG(value,12),PP0_CNT_ARG(value,13),PP0_CNT_ARG(value,14),PP0_CNT_ARG(value,15), \
    PP0_CNT_ARG(value,16),PP0_CNT_ARG(value,17),PP0_CNT_ARG(value,18),PP0_CNT_ARG(value,19),PP0_CNT_ARG(value,20),PP0_CNT_ARG(value,21),PP0_CNT_ARG(value,22),PP0_CNT_ARG(value,23), \
    PP0_CNT_ARG(value,24),PP0_CNT_ARG(value,25),PP0_CNT_ARG(value,26),PP0_CNT_ARG(value,27),PP0_CNT_ARG(value,28),PP0_CNT_ARG(value,29),PP0_CNT_ARG(value,30),PP0_CNT_ARG(value,31), \
    PP0_CNT_ARG(value,32),PP0_CNT_ARG(value,33),PP0_CNT_ARG(value,34),PP0_CNT_ARG(value,35),PP0_CNT_ARG(value,36),PP0_CNT_ARG(value,37),PP0_CNT_ARG(value,38),PP0_CNT_ARG(value,39), \
    PP0_CNT_ARG(value,40),PP0_CNT_ARG(value,41),PP0_CNT_ARG(value,42),PP0_CNT_ARG(value,43),PP0_CNT_ARG(value,44),PP0_CNT_ARG(value,45),PP0_CNT_ARG(value,46),PP0_CNT_ARG(value,47), \
    PP0_CNT_ARG(value,48),PP0_CNT_ARG(value,49),PP0_CNT_ARG(value,50),PP0_CNT_ARG(value,51),PP0_CNT_ARG(value,52),PP0_CNT_ARG(value,53),PP0_CNT_ARG(value,54),PP0_CNT_ARG(value,55), \
    PP0_CNT_ARG(value,56),PP0_CNT_ARG(value,57),PP0_CNT_ARG(value,58),PP0_CNT_ARG(value,59),PP0_CNT_ARG(value,60),PP0_CNT_ARG(value,61),PP0_CNT_ARG(value,62),PP0_CNT_ARG(value,63)) {return {};}
#define PP0_COUNTER_INCR(type_tag, storage) PP0_COUNTER_INCR_TO_X(PP0_COUNTER_READ(type_tag)+1, type_tag, storage)
#define PP0_CNT_ARG(cur,x) std::conditional_t<(x < cur), int, short>


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
}

// UTILS

#define PP0_F_NULL(...)
#define PP0_F_COMMA(...) ,

#define PP0_E(...) __VA_ARGS__

#define PP0_VA_FIRST(...) PP0_VA_FIRST_IMPL_(__VA_ARGS__,)
#define PP0_VA_FIRST_IMPL_(x, ...) x

#define PP0_PARENS(...) (__VA_ARGS__)
#define PP0_DEL_PARENS(...) PP0_E __VA_ARGS__
#define PP0_2_PARENS(...) ((__VA_ARGS__))
#define PP0_PARENS_COMMA(...) (__VA_ARGS__),

#define PP0_CC(a, b) PP0_CC_IMPL_(a,b)
#define PP0_CC_IMPL_(a, b) a##b

#define PP0_CALL(macro, ...) macro(__VA_ARGS__)
#define PP0_CALL_A(macro, ...) macro(__VA_ARGS__)
#define PP0_CALL_B(macro, ...) macro(__VA_ARGS__)

#define PP0_VA_SIZE(...) PP0_VA_SIZE_IMPL_(__VA_ARGS__,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define PP0_VA_SIZE_IMPL_(i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,i61,i62,i63,i64,size,...) size

#define PP0_STR(...) PP0_STR_IMPL_(__VA_ARGS__)
#define PP0_STR_IMPL_(...) #__VA_ARGS__

#define PP0_VA_CALL(name, ...) PP0_CC(name, PP0_VA_SIZE(__VA_ARGS__))

#define PP0_SEQ_CALL(name, seq) PP0_CC(name, PP0_SEQ_SIZE(seq))

#define PP0_SEQ_FIRST(seq) PP0_DEL_PARENS(PP0_VA_FIRST(PP0_PARENS_COMMA seq,))

#define PP0_VA_TO_SEQ(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__,)(__VA_ARGS__,)
#define PP0_VA_TO_SEQ_DISCARD_LAST(...) PP0_VA_CALL(PP0_VA_TO_SEQ_, __VA_ARGS__)(__VA_ARGS__)
#define PP0_VA_TO_SEQ_NULL
#define PP0_VA_TO_SEQ_1(x) PP0_VA_TO_SEQ_##x##NULL
#define PP0_VA_TO_SEQ_2(x, ...) (x)PP0_VA_TO_SEQ_1(__VA_ARGS__)
#define PP0_VA_TO_SEQ_3(x, ...) (x)PP0_VA_TO_SEQ_2(__VA_ARGS__)
#define PP0_VA_TO_SEQ_4(x, ...) (x)PP0_VA_TO_SEQ_3(__VA_ARGS__)
#define PP0_VA_TO_SEQ_5(x, ...) (x)PP0_VA_TO_SEQ_4(__VA_ARGS__)
#define PP0_VA_TO_SEQ_6(x, ...) (x)PP0_VA_TO_SEQ_5(__VA_ARGS__)
#define PP0_VA_TO_SEQ_7(x, ...) (x)PP0_VA_TO_SEQ_6(__VA_ARGS__)
#define PP0_VA_TO_SEQ_8(x, ...) (x)PP0_VA_TO_SEQ_7(__VA_ARGS__)
#define PP0_VA_TO_SEQ_9(x, ...) (x)PP0_VA_TO_SEQ_8(__VA_ARGS__)
#define PP0_VA_TO_SEQ_10(x, ...) (x)PP0_VA_TO_SEQ_9(__VA_ARGS__)
#define PP0_VA_TO_SEQ_11(x, ...) (x)PP0_VA_TO_SEQ_10(__VA_ARGS__)
#define PP0_VA_TO_SEQ_12(x, ...) (x)PP0_VA_TO_SEQ_11(__VA_ARGS__)
#define PP0_VA_TO_SEQ_13(x, ...) (x)PP0_VA_TO_SEQ_12(__VA_ARGS__)
#define PP0_VA_TO_SEQ_14(x, ...) (x)PP0_VA_TO_SEQ_13(__VA_ARGS__)
#define PP0_VA_TO_SEQ_15(x, ...) (x)PP0_VA_TO_SEQ_14(__VA_ARGS__)
#define PP0_VA_TO_SEQ_16(x, ...) (x)PP0_VA_TO_SEQ_15(__VA_ARGS__)
#define PP0_VA_TO_SEQ_17(x, ...) (x)PP0_VA_TO_SEQ_16(__VA_ARGS__)
#define PP0_VA_TO_SEQ_18(x, ...) (x)PP0_VA_TO_SEQ_17(__VA_ARGS__)
#define PP0_VA_TO_SEQ_19(x, ...) (x)PP0_VA_TO_SEQ_18(__VA_ARGS__)
#define PP0_VA_TO_SEQ_20(x, ...) (x)PP0_VA_TO_SEQ_19(__VA_ARGS__)
#define PP0_VA_TO_SEQ_21(x, ...) (x)PP0_VA_TO_SEQ_20(__VA_ARGS__)
#define PP0_VA_TO_SEQ_22(x, ...) (x)PP0_VA_TO_SEQ_21(__VA_ARGS__)
#define PP0_VA_TO_SEQ_23(x, ...) (x)PP0_VA_TO_SEQ_22(__VA_ARGS__)
#define PP0_VA_TO_SEQ_24(x, ...) (x)PP0_VA_TO_SEQ_23(__VA_ARGS__)
#define PP0_VA_TO_SEQ_25(x, ...) (x)PP0_VA_TO_SEQ_24(__VA_ARGS__)
#define PP0_VA_TO_SEQ_26(x, ...) (x)PP0_VA_TO_SEQ_25(__VA_ARGS__)
#define PP0_VA_TO_SEQ_27(x, ...) (x)PP0_VA_TO_SEQ_26(__VA_ARGS__)
#define PP0_VA_TO_SEQ_28(x, ...) (x)PP0_VA_TO_SEQ_27(__VA_ARGS__)
#define PP0_VA_TO_SEQ_29(x, ...) (x)PP0_VA_TO_SEQ_28(__VA_ARGS__)
#define PP0_VA_TO_SEQ_30(x, ...) (x)PP0_VA_TO_SEQ_29(__VA_ARGS__)
#define PP0_VA_TO_SEQ_31(x, ...) (x)PP0_VA_TO_SEQ_30(__VA_ARGS__)
#define PP0_VA_TO_SEQ_32(x, ...) (x)PP0_VA_TO_SEQ_31(__VA_ARGS__)
#define PP0_VA_TO_SEQ_33(x, ...) (x)PP0_VA_TO_SEQ_32(__VA_ARGS__)
#define PP0_VA_TO_SEQ_34(x, ...) (x)PP0_VA_TO_SEQ_33(__VA_ARGS__)
#define PP0_VA_TO_SEQ_35(x, ...) (x)PP0_VA_TO_SEQ_34(__VA_ARGS__)
#define PP0_VA_TO_SEQ_36(x, ...) (x)PP0_VA_TO_SEQ_35(__VA_ARGS__)
#define PP0_VA_TO_SEQ_37(x, ...) (x)PP0_VA_TO_SEQ_36(__VA_ARGS__)
#define PP0_VA_TO_SEQ_38(x, ...) (x)PP0_VA_TO_SEQ_37(__VA_ARGS__)
#define PP0_VA_TO_SEQ_39(x, ...) (x)PP0_VA_TO_SEQ_38(__VA_ARGS__)
#define PP0_VA_TO_SEQ_40(x, ...) (x)PP0_VA_TO_SEQ_39(__VA_ARGS__)
#define PP0_VA_TO_SEQ_41(x, ...) (x)PP0_VA_TO_SEQ_40(__VA_ARGS__)
#define PP0_VA_TO_SEQ_42(x, ...) (x)PP0_VA_TO_SEQ_41(__VA_ARGS__)
#define PP0_VA_TO_SEQ_43(x, ...) (x)PP0_VA_TO_SEQ_42(__VA_ARGS__)
#define PP0_VA_TO_SEQ_44(x, ...) (x)PP0_VA_TO_SEQ_43(__VA_ARGS__)
#define PP0_VA_TO_SEQ_45(x, ...) (x)PP0_VA_TO_SEQ_44(__VA_ARGS__)
#define PP0_VA_TO_SEQ_46(x, ...) (x)PP0_VA_TO_SEQ_45(__VA_ARGS__)
#define PP0_VA_TO_SEQ_47(x, ...) (x)PP0_VA_TO_SEQ_46(__VA_ARGS__)
#define PP0_VA_TO_SEQ_48(x, ...) (x)PP0_VA_TO_SEQ_47(__VA_ARGS__)
#define PP0_VA_TO_SEQ_49(x, ...) (x)PP0_VA_TO_SEQ_48(__VA_ARGS__)
#define PP0_VA_TO_SEQ_50(x, ...) (x)PP0_VA_TO_SEQ_49(__VA_ARGS__)
#define PP0_VA_TO_SEQ_51(x, ...) (x)PP0_VA_TO_SEQ_50(__VA_ARGS__)
#define PP0_VA_TO_SEQ_52(x, ...) (x)PP0_VA_TO_SEQ_51(__VA_ARGS__)
#define PP0_VA_TO_SEQ_53(x, ...) (x)PP0_VA_TO_SEQ_52(__VA_ARGS__)
#define PP0_VA_TO_SEQ_54(x, ...) (x)PP0_VA_TO_SEQ_53(__VA_ARGS__)
#define PP0_VA_TO_SEQ_55(x, ...) (x)PP0_VA_TO_SEQ_54(__VA_ARGS__)
#define PP0_VA_TO_SEQ_56(x, ...) (x)PP0_VA_TO_SEQ_55(__VA_ARGS__)
#define PP0_VA_TO_SEQ_57(x, ...) (x)PP0_VA_TO_SEQ_56(__VA_ARGS__)
#define PP0_VA_TO_SEQ_58(x, ...) (x)PP0_VA_TO_SEQ_57(__VA_ARGS__)
#define PP0_VA_TO_SEQ_59(x, ...) (x)PP0_VA_TO_SEQ_58(__VA_ARGS__)
#define PP0_VA_TO_SEQ_60(x, ...) (x)PP0_VA_TO_SEQ_59(__VA_ARGS__)
#define PP0_VA_TO_SEQ_61(x, ...) (x)PP0_VA_TO_SEQ_60(__VA_ARGS__)
#define PP0_VA_TO_SEQ_62(x, ...) (x)PP0_VA_TO_SEQ_61(__VA_ARGS__)
#define PP0_VA_TO_SEQ_63(x, ...) (x)PP0_VA_TO_SEQ_62(__VA_ARGS__)
#define PP0_VA_TO_SEQ_64(x, ...) (x)PP0_VA_TO_SEQ_63(__VA_ARGS__)
#define PP0_VA_TO_SEQ_65(x, ...) (x)PP0_VA_TO_SEQ_64(__VA_ARGS__)

#define PP0_SEQ_SIZE(seq) PP0_CC(PP0_SEQ_SIZE_0 seq, _VAL)
#define PP0_SEQ_SIZE_0(...) PP0_SEQ_SIZE_1
#define PP0_SEQ_SIZE_1(...) PP0_SEQ_SIZE_2
#define PP0_SEQ_SIZE_2(...) PP0_SEQ_SIZE_3
#define PP0_SEQ_SIZE_3(...) PP0_SEQ_SIZE_4
#define PP0_SEQ_SIZE_4(...) PP0_SEQ_SIZE_5
#define PP0_SEQ_SIZE_5(...) PP0_SEQ_SIZE_6
#define PP0_SEQ_SIZE_6(...) PP0_SEQ_SIZE_7
#define PP0_SEQ_SIZE_7(...) PP0_SEQ_SIZE_8
#define PP0_SEQ_SIZE_8(...) PP0_SEQ_SIZE_9
#define PP0_SEQ_SIZE_9(...) PP0_SEQ_SIZE_10
#define PP0_SEQ_SIZE_10(...) PP0_SEQ_SIZE_11
#define PP0_SEQ_SIZE_11(...) PP0_SEQ_SIZE_12
#define PP0_SEQ_SIZE_12(...) PP0_SEQ_SIZE_13
#define PP0_SEQ_SIZE_13(...) PP0_SEQ_SIZE_14
#define PP0_SEQ_SIZE_14(...) PP0_SEQ_SIZE_15
#define PP0_SEQ_SIZE_15(...) PP0_SEQ_SIZE_16
#define PP0_SEQ_SIZE_16(...) PP0_SEQ_SIZE_17
#define PP0_SEQ_SIZE_17(...) PP0_SEQ_SIZE_18
#define PP0_SEQ_SIZE_18(...) PP0_SEQ_SIZE_19
#define PP0_SEQ_SIZE_19(...) PP0_SEQ_SIZE_20
#define PP0_SEQ_SIZE_20(...) PP0_SEQ_SIZE_21
#define PP0_SEQ_SIZE_21(...) PP0_SEQ_SIZE_22
#define PP0_SEQ_SIZE_22(...) PP0_SEQ_SIZE_23
#define PP0_SEQ_SIZE_23(...) PP0_SEQ_SIZE_24
#define PP0_SEQ_SIZE_24(...) PP0_SEQ_SIZE_25
#define PP0_SEQ_SIZE_25(...) PP0_SEQ_SIZE_26
#define PP0_SEQ_SIZE_26(...) PP0_SEQ_SIZE_27
#define PP0_SEQ_SIZE_27(...) PP0_SEQ_SIZE_28
#define PP0_SEQ_SIZE_28(...) PP0_SEQ_SIZE_29
#define PP0_SEQ_SIZE_29(...) PP0_SEQ_SIZE_30
#define PP0_SEQ_SIZE_30(...) PP0_SEQ_SIZE_31
#define PP0_SEQ_SIZE_31(...) PP0_SEQ_SIZE_32
#define PP0_SEQ_SIZE_32(...) PP0_SEQ_SIZE_33
#define PP0_SEQ_SIZE_33(...) PP0_SEQ_SIZE_34
#define PP0_SEQ_SIZE_34(...) PP0_SEQ_SIZE_35
#define PP0_SEQ_SIZE_35(...) PP0_SEQ_SIZE_36
#define PP0_SEQ_SIZE_36(...) PP0_SEQ_SIZE_37
#define PP0_SEQ_SIZE_37(...) PP0_SEQ_SIZE_38
#define PP0_SEQ_SIZE_38(...) PP0_SEQ_SIZE_39
#define PP0_SEQ_SIZE_39(...) PP0_SEQ_SIZE_40
#define PP0_SEQ_SIZE_40(...) PP0_SEQ_SIZE_41
#define PP0_SEQ_SIZE_41(...) PP0_SEQ_SIZE_42
#define PP0_SEQ_SIZE_42(...) PP0_SEQ_SIZE_43
#define PP0_SEQ_SIZE_43(...) PP0_SEQ_SIZE_44
#define PP0_SEQ_SIZE_44(...) PP0_SEQ_SIZE_45
#define PP0_SEQ_SIZE_45(...) PP0_SEQ_SIZE_46
#define PP0_SEQ_SIZE_46(...) PP0_SEQ_SIZE_47
#define PP0_SEQ_SIZE_47(...) PP0_SEQ_SIZE_48
#define PP0_SEQ_SIZE_48(...) PP0_SEQ_SIZE_49
#define PP0_SEQ_SIZE_49(...) PP0_SEQ_SIZE_50
#define PP0_SEQ_SIZE_50(...) PP0_SEQ_SIZE_51
#define PP0_SEQ_SIZE_51(...) PP0_SEQ_SIZE_52
#define PP0_SEQ_SIZE_52(...) PP0_SEQ_SIZE_53
#define PP0_SEQ_SIZE_53(...) PP0_SEQ_SIZE_54
#define PP0_SEQ_SIZE_54(...) PP0_SEQ_SIZE_55
#define PP0_SEQ_SIZE_55(...) PP0_SEQ_SIZE_56
#define PP0_SEQ_SIZE_56(...) PP0_SEQ_SIZE_57
#define PP0_SEQ_SIZE_57(...) PP0_SEQ_SIZE_58
#define PP0_SEQ_SIZE_58(...) PP0_SEQ_SIZE_59
#define PP0_SEQ_SIZE_59(...) PP0_SEQ_SIZE_60
#define PP0_SEQ_SIZE_60(...) PP0_SEQ_SIZE_61
#define PP0_SEQ_SIZE_61(...) PP0_SEQ_SIZE_62
#define PP0_SEQ_SIZE_62(...) PP0_SEQ_SIZE_63
#define PP0_SEQ_SIZE_63(...) PP0_SEQ_SIZE_64
#define PP0_SEQ_SIZE_64(...) PP0_SEQ_SIZE_65
#define PP0_SEQ_SIZE_0_VAL 0
#define PP0_SEQ_SIZE_1_VAL 1
#define PP0_SEQ_SIZE_2_VAL 2
#define PP0_SEQ_SIZE_3_VAL 3
#define PP0_SEQ_SIZE_4_VAL 4
#define PP0_SEQ_SIZE_5_VAL 5
#define PP0_SEQ_SIZE_6_VAL 6
#define PP0_SEQ_SIZE_7_VAL 7
#define PP0_SEQ_SIZE_8_VAL 8
#define PP0_SEQ_SIZE_9_VAL 9
#define PP0_SEQ_SIZE_10_VAL 10
#define PP0_SEQ_SIZE_11_VAL 11
#define PP0_SEQ_SIZE_12_VAL 12
#define PP0_SEQ_SIZE_13_VAL 13
#define PP0_SEQ_SIZE_14_VAL 14
#define PP0_SEQ_SIZE_15_VAL 15
#define PP0_SEQ_SIZE_16_VAL 16
#define PP0_SEQ_SIZE_17_VAL 17
#define PP0_SEQ_SIZE_18_VAL 18
#define PP0_SEQ_SIZE_19_VAL 19
#define PP0_SEQ_SIZE_20_VAL 20
#define PP0_SEQ_SIZE_21_VAL 21
#define PP0_SEQ_SIZE_22_VAL 22
#define PP0_SEQ_SIZE_23_VAL 23
#define PP0_SEQ_SIZE_24_VAL 24
#define PP0_SEQ_SIZE_25_VAL 25
#define PP0_SEQ_SIZE_26_VAL 26
#define PP0_SEQ_SIZE_27_VAL 27
#define PP0_SEQ_SIZE_28_VAL 28
#define PP0_SEQ_SIZE_29_VAL 29
#define PP0_SEQ_SIZE_30_VAL 30
#define PP0_SEQ_SIZE_31_VAL 31
#define PP0_SEQ_SIZE_32_VAL 32
#define PP0_SEQ_SIZE_33_VAL 33
#define PP0_SEQ_SIZE_34_VAL 34
#define PP0_SEQ_SIZE_35_VAL 35
#define PP0_SEQ_SIZE_36_VAL 36
#define PP0_SEQ_SIZE_37_VAL 37
#define PP0_SEQ_SIZE_38_VAL 38
#define PP0_SEQ_SIZE_39_VAL 39
#define PP0_SEQ_SIZE_40_VAL 40
#define PP0_SEQ_SIZE_41_VAL 41
#define PP0_SEQ_SIZE_42_VAL 42
#define PP0_SEQ_SIZE_43_VAL 43
#define PP0_SEQ_SIZE_44_VAL 44
#define PP0_SEQ_SIZE_45_VAL 45
#define PP0_SEQ_SIZE_46_VAL 46
#define PP0_SEQ_SIZE_47_VAL 47
#define PP0_SEQ_SIZE_48_VAL 48
#define PP0_SEQ_SIZE_49_VAL 49
#define PP0_SEQ_SIZE_50_VAL 50
#define PP0_SEQ_SIZE_51_VAL 51
#define PP0_SEQ_SIZE_52_VAL 52
#define PP0_SEQ_SIZE_53_VAL 53
#define PP0_SEQ_SIZE_54_VAL 54
#define PP0_SEQ_SIZE_55_VAL 55
#define PP0_SEQ_SIZE_56_VAL 56
#define PP0_SEQ_SIZE_57_VAL 57
#define PP0_SEQ_SIZE_58_VAL 58
#define PP0_SEQ_SIZE_59_VAL 59
#define PP0_SEQ_SIZE_60_VAL 60
#define PP0_SEQ_SIZE_61_VAL 61
#define PP0_SEQ_SIZE_62_VAL 62
#define PP0_SEQ_SIZE_63_VAL 63
#define PP0_SEQ_SIZE_64_VAL 64

#define PP0_VA_AT(index, ...) PP0_CC(PP0_VA_AT_, index)(__VA_ARGS__,)
#define PP0_VA_AT_0(ret, ...) ret
#define PP0_VA_AT_1(_, ...) PP0_VA_AT_0(__VA_ARGS__)
#define PP0_VA_AT_2(_, ...) PP0_VA_AT_1(__VA_ARGS__)
#define PP0_VA_AT_3(_, ...) PP0_VA_AT_2(__VA_ARGS__)
#define PP0_VA_AT_4(_, ...) PP0_VA_AT_3(__VA_ARGS__)
#define PP0_VA_AT_5(_, ...) PP0_VA_AT_4(__VA_ARGS__)
#define PP0_VA_AT_6(_, ...) PP0_VA_AT_5(__VA_ARGS__)
#define PP0_VA_AT_7(_, ...) PP0_VA_AT_6(__VA_ARGS__)
#define PP0_VA_AT_8(_, ...) PP0_VA_AT_7(__VA_ARGS__)
#define PP0_VA_AT_9(_, ...) PP0_VA_AT_8(__VA_ARGS__)
#define PP0_VA_AT_10(_, ...) PP0_VA_AT_9(__VA_ARGS__)
#define PP0_VA_AT_11(_, ...) PP0_VA_AT_10(__VA_ARGS__)
#define PP0_VA_AT_12(_, ...) PP0_VA_AT_11(__VA_ARGS__)
#define PP0_VA_AT_13(_, ...) PP0_VA_AT_12(__VA_ARGS__)
#define PP0_VA_AT_14(_, ...) PP0_VA_AT_13(__VA_ARGS__)
#define PP0_VA_AT_15(_, ...) PP0_VA_AT_14(__VA_ARGS__)
#define PP0_VA_AT_16(_, ...) PP0_VA_AT_15(__VA_ARGS__)
#define PP0_VA_AT_17(_, ...) PP0_VA_AT_16(__VA_ARGS__)
#define PP0_VA_AT_18(_, ...) PP0_VA_AT_17(__VA_ARGS__)
#define PP0_VA_AT_19(_, ...) PP0_VA_AT_18(__VA_ARGS__)
#define PP0_VA_AT_20(_, ...) PP0_VA_AT_19(__VA_ARGS__)
#define PP0_VA_AT_21(_, ...) PP0_VA_AT_20(__VA_ARGS__)
#define PP0_VA_AT_22(_, ...) PP0_VA_AT_21(__VA_ARGS__)
#define PP0_VA_AT_23(_, ...) PP0_VA_AT_22(__VA_ARGS__)
#define PP0_VA_AT_24(_, ...) PP0_VA_AT_23(__VA_ARGS__)
#define PP0_VA_AT_25(_, ...) PP0_VA_AT_24(__VA_ARGS__)
#define PP0_VA_AT_26(_, ...) PP0_VA_AT_25(__VA_ARGS__)
#define PP0_VA_AT_27(_, ...) PP0_VA_AT_26(__VA_ARGS__)
#define PP0_VA_AT_28(_, ...) PP0_VA_AT_27(__VA_ARGS__)
#define PP0_VA_AT_29(_, ...) PP0_VA_AT_28(__VA_ARGS__)
#define PP0_VA_AT_30(_, ...) PP0_VA_AT_29(__VA_ARGS__)
#define PP0_VA_AT_31(_, ...) PP0_VA_AT_30(__VA_ARGS__)
#define PP0_VA_AT_32(_, ...) PP0_VA_AT_31(__VA_ARGS__)
#define PP0_VA_AT_33(_, ...) PP0_VA_AT_32(__VA_ARGS__)
#define PP0_VA_AT_34(_, ...) PP0_VA_AT_33(__VA_ARGS__)
#define PP0_VA_AT_35(_, ...) PP0_VA_AT_34(__VA_ARGS__)
#define PP0_VA_AT_36(_, ...) PP0_VA_AT_35(__VA_ARGS__)
#define PP0_VA_AT_37(_, ...) PP0_VA_AT_36(__VA_ARGS__)
#define PP0_VA_AT_38(_, ...) PP0_VA_AT_37(__VA_ARGS__)
#define PP0_VA_AT_39(_, ...) PP0_VA_AT_38(__VA_ARGS__)
#define PP0_VA_AT_40(_, ...) PP0_VA_AT_39(__VA_ARGS__)
#define PP0_VA_AT_41(_, ...) PP0_VA_AT_40(__VA_ARGS__)
#define PP0_VA_AT_42(_, ...) PP0_VA_AT_41(__VA_ARGS__)
#define PP0_VA_AT_43(_, ...) PP0_VA_AT_42(__VA_ARGS__)
#define PP0_VA_AT_44(_, ...) PP0_VA_AT_43(__VA_ARGS__)
#define PP0_VA_AT_45(_, ...) PP0_VA_AT_44(__VA_ARGS__)
#define PP0_VA_AT_46(_, ...) PP0_VA_AT_45(__VA_ARGS__)
#define PP0_VA_AT_47(_, ...) PP0_VA_AT_46(__VA_ARGS__)
#define PP0_VA_AT_48(_, ...) PP0_VA_AT_47(__VA_ARGS__)
#define PP0_VA_AT_49(_, ...) PP0_VA_AT_48(__VA_ARGS__)
#define PP0_VA_AT_50(_, ...) PP0_VA_AT_49(__VA_ARGS__)
#define PP0_VA_AT_51(_, ...) PP0_VA_AT_50(__VA_ARGS__)
#define PP0_VA_AT_52(_, ...) PP0_VA_AT_51(__VA_ARGS__)
#define PP0_VA_AT_53(_, ...) PP0_VA_AT_52(__VA_ARGS__)
#define PP0_VA_AT_54(_, ...) PP0_VA_AT_53(__VA_ARGS__)
#define PP0_VA_AT_55(_, ...) PP0_VA_AT_54(__VA_ARGS__)
#define PP0_VA_AT_56(_, ...) PP0_VA_AT_55(__VA_ARGS__)
#define PP0_VA_AT_57(_, ...) PP0_VA_AT_56(__VA_ARGS__)
#define PP0_VA_AT_58(_, ...) PP0_VA_AT_57(__VA_ARGS__)
#define PP0_VA_AT_59(_, ...) PP0_VA_AT_58(__VA_ARGS__)
#define PP0_VA_AT_60(_, ...) PP0_VA_AT_59(__VA_ARGS__)
#define PP0_VA_AT_61(_, ...) PP0_VA_AT_60(__VA_ARGS__)
#define PP0_VA_AT_62(_, ...) PP0_VA_AT_61(__VA_ARGS__)
#define PP0_VA_AT_63(_, ...) PP0_VA_AT_62(__VA_ARGS__)
#define PP0_VA_AT_64(_, ...) PP0_VA_AT_63(__VA_ARGS__)

#define PP0_SEQ_AT(index, seq) PP0_SEQ_FIRST( PP0_CC(PP0_SEQ_AT_EAT_, index)(seq) )
#define PP0_SEQ_AT_EAT_0(seq) seq
#define PP0_SEQ_AT_EAT_1(seq) PP0_SEQ_AT_EAT_0(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_2(seq) PP0_SEQ_AT_EAT_1(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_3(seq) PP0_SEQ_AT_EAT_2(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_4(seq) PP0_SEQ_AT_EAT_3(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_5(seq) PP0_SEQ_AT_EAT_4(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_6(seq) PP0_SEQ_AT_EAT_5(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_7(seq) PP0_SEQ_AT_EAT_6(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_8(seq) PP0_SEQ_AT_EAT_7(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_9(seq) PP0_SEQ_AT_EAT_8(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_10(seq) PP0_SEQ_AT_EAT_9(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_11(seq) PP0_SEQ_AT_EAT_10(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_12(seq) PP0_SEQ_AT_EAT_11(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_13(seq) PP0_SEQ_AT_EAT_12(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_14(seq) PP0_SEQ_AT_EAT_13(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_15(seq) PP0_SEQ_AT_EAT_14(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_16(seq) PP0_SEQ_AT_EAT_15(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_17(seq) PP0_SEQ_AT_EAT_16(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_18(seq) PP0_SEQ_AT_EAT_17(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_19(seq) PP0_SEQ_AT_EAT_18(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_20(seq) PP0_SEQ_AT_EAT_19(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_21(seq) PP0_SEQ_AT_EAT_20(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_22(seq) PP0_SEQ_AT_EAT_21(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_23(seq) PP0_SEQ_AT_EAT_22(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_24(seq) PP0_SEQ_AT_EAT_23(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_25(seq) PP0_SEQ_AT_EAT_24(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_26(seq) PP0_SEQ_AT_EAT_25(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_27(seq) PP0_SEQ_AT_EAT_26(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_28(seq) PP0_SEQ_AT_EAT_27(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_29(seq) PP0_SEQ_AT_EAT_28(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_30(seq) PP0_SEQ_AT_EAT_29(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_31(seq) PP0_SEQ_AT_EAT_30(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_32(seq) PP0_SEQ_AT_EAT_31(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_33(seq) PP0_SEQ_AT_EAT_32(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_34(seq) PP0_SEQ_AT_EAT_33(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_35(seq) PP0_SEQ_AT_EAT_34(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_36(seq) PP0_SEQ_AT_EAT_35(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_37(seq) PP0_SEQ_AT_EAT_36(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_38(seq) PP0_SEQ_AT_EAT_37(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_39(seq) PP0_SEQ_AT_EAT_38(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_40(seq) PP0_SEQ_AT_EAT_39(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_41(seq) PP0_SEQ_AT_EAT_40(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_42(seq) PP0_SEQ_AT_EAT_41(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_43(seq) PP0_SEQ_AT_EAT_42(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_44(seq) PP0_SEQ_AT_EAT_43(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_45(seq) PP0_SEQ_AT_EAT_44(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_46(seq) PP0_SEQ_AT_EAT_45(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_47(seq) PP0_SEQ_AT_EAT_46(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_48(seq) PP0_SEQ_AT_EAT_47(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_49(seq) PP0_SEQ_AT_EAT_48(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_50(seq) PP0_SEQ_AT_EAT_49(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_51(seq) PP0_SEQ_AT_EAT_50(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_52(seq) PP0_SEQ_AT_EAT_51(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_53(seq) PP0_SEQ_AT_EAT_52(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_54(seq) PP0_SEQ_AT_EAT_53(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_55(seq) PP0_SEQ_AT_EAT_54(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_56(seq) PP0_SEQ_AT_EAT_55(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_57(seq) PP0_SEQ_AT_EAT_56(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_58(seq) PP0_SEQ_AT_EAT_57(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_59(seq) PP0_SEQ_AT_EAT_58(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_60(seq) PP0_SEQ_AT_EAT_59(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_61(seq) PP0_SEQ_AT_EAT_60(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_62(seq) PP0_SEQ_AT_EAT_61(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_63(seq) PP0_SEQ_AT_EAT_62(PP0_F_NULL seq)
#define PP0_SEQ_AT_EAT_64(seq) PP0_SEQ_AT_EAT_63(PP0_F_NULL seq)
// macro(i, data, element...)
#define PP0_SEQ_APPLY(seq, macro, macro_sep_f, data) PP0_SEQ_CALL(PP0_SEQ_APPLY_, seq)(macro, macro_sep_f, data, seq, )
#define PP0_SEQ_APPLY_0(macro, macro_sep_f, data, seq, seq_)
#define PP0_SEQ_APPLY_1(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq))
#define PP0_SEQ_APPLY_2(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_3(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_4(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_5(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_6(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_7(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_8(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_9(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_10(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_11(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_12(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_13(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_14(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_15(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_16(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_17(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_18(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_19(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_20(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_21(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_22(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_23(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_24(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_25(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_26(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_27(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_28(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_29(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_30(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_31(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_32(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_33(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_34(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_35(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_36(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_37(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_38(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_39(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_40(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_41(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_42(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_43(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_44(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_45(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_46(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_47(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_48(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_49(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_50(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_51(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_52(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_53(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_54(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_55(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_56(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_57(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_58(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_59(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_60(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_61(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_62(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_63(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_64(macro, macro_sep_f, data, seq, seq_) PP0_CALL(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A(seq, macro, macro_sep_f, data) PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, seq)(macro, macro_sep_f, data, seq, )
#define PP0_SEQ_APPLY_A_0(macro, macro_sep_f, data, seq, seq_)
#define PP0_SEQ_APPLY_A_1(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq))
#define PP0_SEQ_APPLY_A_2(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_3(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_4(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_5(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_6(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_7(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_8(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_9(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_10(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_11(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_12(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_13(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_14(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_15(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_16(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_17(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_18(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_19(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_20(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_21(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_22(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_23(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_24(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_25(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_26(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_27(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_28(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_29(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_30(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_31(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_32(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_33(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_34(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_35(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_36(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_37(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_38(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_39(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_40(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_41(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_42(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_43(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_44(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_45(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_46(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_47(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_48(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_49(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_50(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_51(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_52(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_53(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_54(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_55(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_56(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_57(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_58(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_59(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_60(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_61(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_62(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_63(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)
#define PP0_SEQ_APPLY_A_64(macro, macro_sep_f, data, seq, seq_) PP0_CALL_A(macro, PP0_SEQ_SIZE(seq_), data, PP0_SEQ_FIRST(seq)) macro_sep_f() PP0_SEQ_CALL(PP0_SEQ_APPLY_A_, PP0_F_NULL seq)(macro, macro_sep_f, data, PP0_F_NULL seq, (PP0_SEQ_FIRST(seq)) seq_)


#endif
