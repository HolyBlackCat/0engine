#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include <type_traits>

#include "preprocessor.h"

#define REFL0_MAKE_VAR_1(i, expr) expr
#define REFL0_MAKE_VAR_2(i, type, name) REFL0_MAKE_VAR_3(i, type, name, )
#define REFL0_MAKE_VAR_3(i, type_, name_, init_) type_ name_ init_; \
                                                 REFL0_MAKE_VAR_FUNC(type_, name_, init_,      ,         ) \
                                                 REFL0_MAKE_VAR_FUNC(type_, name_, init_, const,         ) \
                                                 REFL0_MAKE_VAR_FUNC(type_, name_, init_,      , volatile) \
                                                 REFL0_MAKE_VAR_FUNC(type_, name_, init_, const, volatile) \
                                                 PP0_COUNTER_INCR(::Reflection::field_counter_tag,static)
#define REFL0_MAKE_VAR_FUNC(type_, name_, init_, c_, v_) template <typename This> struct _refl_impl_field_t_0##c_##0##v_##0##name_ \
                                                         { \
                                                             using enclosing_class = This; \
                                                             using type = type_; \
                                                             using type_cv = c_ v_ type; \
                                                             static constexpr const char *type_name = #type_, \
                                                                                         *name = #name_; \
                                                             static constexpr type_ This::*mem_ptr = &This::name_; \
                                                             type_cv &value; \
                                                         }; \
                                                         auto _refl_field_by_tag(std::integral_constant<int,PP0_COUNTER_READ(::Reflection::field_counter_tag)>) c_ v_ \
                                                         { \
                                                             using ret_t = _refl_impl_field_t_0##c_##0##v_##0##name_<std::remove_reference_t<decltype(*this)>>; \
                                                             return ret_t{this->*ret_t::mem_ptr}; \
                                                         }
#define REFL0_MAKE_VAR(i, ...) PP0_VA_CALL(REFL0_MAKE_VAR_, __VA_ARGS__)(i, __VA_ARGS__)

#define Reflect(seq) \
    PP0_SEQ_APPLY(seq, REFL0_MAKE_VAR, PP0_F_NULL)

#define Reflectable(opt_name) \
    friend class Reflection; \
    static constexpr const char *_refl_name = #opt_name; \
    template <int I> auto _refl_field()                {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const          {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field()       volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    PP0_COUNTER_DEFINE(::Reflection::field_counter_tag,static)

class Reflection
{
    ~Reflection() = delete;
  public:

    template <int ...Seq> using int_seq = std::integer_sequence<int, Seq...>;
    template <int I> using make_int_seq = std::make_integer_sequence<int, I>;

    struct field_counter_tag {constexpr field_counter_tag() {}};


    template <typename T> static constexpr int field_count = PP0_COUNTER_READ_CONTEXT(::Reflection::field_counter_tag, T::);

    template <typename T, typename F, int ...Seq> static void for_constexpr_indices(T &&obj, F &&func, int_seq<Seq...>)
    {
        (func(obj.template _refl_field<Seq>()) , ...);
    }
    template <typename T, typename F> static void for_each(T &&obj, F &&func)
    {
        for_constexpr_indices((T&&)obj, (F&&)func, make_int_seq<field_count<std::remove_reference_t<T>>>{});
    }
};

#endif
