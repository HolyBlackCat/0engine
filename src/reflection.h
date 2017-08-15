#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include "preprocessor.h"

#define REFL0_MAKE_VAR_2(i, type, name) REFL0_MAKE_VAR_3(i, type, name, )
#define REFL0_MAKE_VAR_3(i, type_, name_, init_) type_ name_ init_; \
                                           template <typename T> struct _refl_field_t<i, T> \
                                           { \
                                               using enclosing_class = T; \
                                               using type = type_; \
                                               using type_cv = std::conditional_t<std::is_const_v<T>, const type_, type_>; \
                                               static constexpr const char *type_name = #type_, \
                                                                           *name = #name_; \
                                               static constexpr type_ T::*mem_ptr = &T::name_; \
                                               type_cv &value; \
                                               _refl_field_t(enclosing_class &ref) : value(ref.*mem_ptr) {} \
                                           };
#define REFL0_MAKE_VAR(i, ...) PP0_VA_CALL(REFL0_MAKE_VAR_, __VA_ARGS__)(i, __VA_ARGS__)

#define Reflect(seq) \
    friend class Reflection; \
    static constexpr int _refl_field_c = PP0_SEQ_SIZE(seq); \
    template <int I, typename> struct _refl_field_t; \
    PP0_SEQ_APPLY(seq, REFL0_MAKE_VAR, PP0_F_NULL) \
    template <int I> auto _refl_field() {return _refl_field_t<I, std::remove_reference_t<decltype(*this)>>(*this);} \
    template <int I> auto _refl_field() const {return _refl_field_t<I, std::remove_reference_t<decltype(*this)>>(*this);}

class Reflection
{
  public:
    template <int ...Seq> using int_seq = std::integer_sequence<int, Seq...>;
    template <int I> using make_int_seq = std::make_integer_sequence<int, I>;

    template <typename T, typename F, int ...Seq> static void for_indices(T &&obj, F &&func, int_seq<Seq...>)
    {
        (func(obj.template _refl_field<Seq>()) , ...);
    }
    template <typename T, typename F> static void for_each(T &&obj, F &&func)
    {
        for_indices((T&&)obj, (F&&)func, make_int_seq<std::remove_reference_t<T>::_refl_field_c>{});
    }
};

#endif
