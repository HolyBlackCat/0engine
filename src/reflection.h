#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include <type_traits>

#include "preprocessor.h"



#define Reflectable(opt_name) \
    template <typename T> friend class Reflection; \
    static constexpr const char *_refl_name = #opt_name; \
    template <int I> auto _refl_field()                {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const          {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field()       volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    PP0_COUNTER_DEFINE(::ReflectionBase::field_counter_tag,static)


#define Reflect(...) \
    PP0_SEQ_APPLY(PP0_VA_TO_SEQ_DISCARD_LAST(__VA_ARGS__), REFL0_Reflect_A, PP0_F_NULL, )

#define REFL0_Reflect_A(i, data, seq) \
    PP0_SEQ_CALL(REFL0_Reflect_B_, seq)(seq)

#define REFL0_Reflect_B_1(expr) \
    PP0_DEL_PARENS(expr)

#define REFL0_Reflect_B_2(seq) \
    REFL0_Reflect_B_3( seq () )

#define REFL0_Reflect_B_3(seq) \
    PP0_SEQ_APPLY_A(PP0_VA_TO_SEQ(PP0_SEQ_AT(1,seq)), REFL0_Reflect_C, PP0_F_NULL, (PP0_SEQ_FIRST(seq) , PP0_SEQ_AT(2,seq)))

#define REFL0_Reflect_C(i, data, name) \
    PP0_CALL_B(REFL0_Reflect_D, name, PP0_DEL_PARENS(data))

#define REFL0_Reflect_D(name_, type_, init_) \
    using _refl_field_type_##name_ = type_; \
    _refl_field_type_##name_ name_ init_; \
    template <typename This> struct _refl_impl_field_##name_ \
    { \
        using enclosing_class_cv = This; \
        using enclosing_class    = std::remove_cv_t<This>; \
        using type_cv            = ::ReflectionBase::copy_cv_t<This, type_>; \
        using type               = type_; \
        static constexpr const char *type_name = #type_, \
                                    *name      = #name_; \
        static constexpr type_ This::*mem_ptr = &This::name_; \
        type_cv &value; \
    }; \
    REFL0_Reflect_MakeFunc(type_, name_, init_,      ,         ) \
    REFL0_Reflect_MakeFunc(type_, name_, init_, const,         ) \
    REFL0_Reflect_MakeFunc(type_, name_, init_,      , volatile) \
    REFL0_Reflect_MakeFunc(type_, name_, init_, const, volatile) \
    PP0_COUNTER_INCR(::ReflectionBase::field_counter_tag,static)

#define REFL0_Reflect_MakeFunc(type_, name_, init_, c_, v_) \
    auto _refl_field_by_tag(std::integral_constant<int,PP0_COUNTER_READ(::ReflectionBase::field_counter_tag)>) c_ v_ \
    { \
        using ret_t = _refl_impl_field_##name_<std::remove_reference_t<decltype(*this)>>; \
        return ret_t{this->*ret_t::mem_ptr}; \
    }


class ReflectionBase
{
  public:
    template <int ...Seq> using int_seq = std::integer_sequence<int, Seq...>;
    template <int I> using make_int_seq = std::make_integer_sequence<int, I>;
    struct field_counter_tag {constexpr field_counter_tag() {}};

    template <typename A, typename B> struct copy_cv {using type = B;};
    template <typename A, typename B> struct copy_cv<const          A, B> {using type = const          B;};
    template <typename A, typename B> struct copy_cv<      volatile A, B> {using type =       volatile B;};
    template <typename A, typename B> struct copy_cv<const volatile A, B> {using type = const volatile B;};
    template <typename A, typename B> using copy_cv_t = typename copy_cv<A, B>::type;
};

template <typename T> class Reflection : public ReflectionBase
{
  public:
    T &ref;
    Reflection(T &ref) : ref(ref) {}

    static constexpr const char *name = T::_refl_name;
    static constexpr int field_count = PP0_COUNTER_READ_CONTEXT(::ReflectionBase::field_counter_tag, T::);

    template <typename F, int ...Seq> void for_constexpr_indices(F &&func, int_seq<Seq...>)
    {
        (func(ref.template _refl_field<Seq>()) , ...);
    }
    template <typename F> void for_each(F &&func)
    {
        for_constexpr_indices((F&&)func, make_int_seq<field_count>{});
    }
};

#endif
