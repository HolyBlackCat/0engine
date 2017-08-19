#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include <algorithm>
#include <type_traits>

#include "preprocessor.h"

namespace Refl
{
    template <int ...Seq> using int_seq = std::integer_sequence<int, Seq...>;
    template <int I> using make_int_seq = std::make_integer_sequence<int, I>;


    struct field_counter_tag {};


    template <typename Data> struct Context
    {
        /* `Data` must provide:
         *   using name_str = PP0_STR_LIT("blah"); // Aka pp0::str_lit<'b','l','a','h'>.
         *   static constexpr const char *name = name_str::value; // Or equivalent.
         *   using enclosing_class_type = T_without_cv;
         *   static constexpr ?? enclosing_class_type::* mem_ptr = foo;
         */

        static_assert(!std::is_const_v   <typename Data::enclosing_class_type> &&
                      !std::is_volatile_v<typename Data::enclosing_class_type>, "Data member types must have no cv-qualifiers.");

        using name_str = typename Data::name_str;
        static constexpr const char *name = Data::name;
        using enclosing_class_type = typename Data::enclosing_class_type;
        static constexpr auto enclosing_class_type::* mem_ptr = Data::mem_ptr;
        using mem_ptr_type = decltype(mem_ptr);
    };
    template <> struct Context<void>
    {
        using name_str = pp0::str_lit<>;
        static constexpr const char *name = name_str::value;
    };


    template <typename T, typename Context = void> struct Reflection; // forward declaration


    namespace Primitive
    {
        /* `Primitive::Traits<T,T_no_cv>` must provide:
         *   static std::string to_string(T *) {}
         *   static std::string to_string_pretty(T *) {}
         */

        template <typename T, typename T_no_cv, typename = void> struct Traits
        {
            static std::string to_string(T *) {return "??";}
            static std::string to_string_pretty(T *ptr) {return to_string(ptr);}
        };

        template <typename T, typename T_no_cv> struct Traits<T, T_no_cv, std::enable_if_t<std::is_arithmetic_v<T_no_cv>, void>>
        {
            static std::string to_string(T *ptr) {return Math::num_to_string<T>(*ptr);}
            static std::string to_string_pretty(T *ptr) {return to_string(ptr);}
        };

        template <typename T> struct Traits<T, bool, void>
        {
            static std::string to_string(bool *ptr) {return Math::num_to_string<bool>(*ptr);}
            static std::string to_string_pretty(bool *ptr) {return (*ptr ? "true" : "false");}
        };
    }

    namespace Structure
    {
        /* `Structure::Traits<T,T_no_cv>` (or a type returned by ADL call of `_refl_tratis()`) must provide:
         *   template <int I> static auto field(T *ptr) {} // (or equivalent) Returns class Reflection to a field.
         *
         *   One of: static constexpr int field_count = blah;          // For actual `Structure::Traits`.
         *           PP0_COUNTER tagged with ::Refl::field_counter_tag // For structures using `_refl_tratis()`.
         */

        template <typename T, typename T_no_cv, typename = void> struct Traits
        {
            using not_found = void;
        };
        template <typename T, typename T_no_cv> struct Traits<T, T_no_cv, std::void_t<decltype(_refl_traits(std::declval<T>()))>> : decltype(_refl_traits(std::declval<T>()))
        {
            static constexpr int field_count = PP0_COUNTER_READ_CONTEXT(Refl::field_counter_tag, T::);
        };

        template <typename T, typename TT, unsigned int D> struct Traits<T, vec<D,TT>, void>
        {
            using type = T;
            using type_no_cv = vec<D,TT>;

            static constexpr int field_count = D;

            template <char Name, TT type_no_cv::* MemPtr> struct field_data
            {
                using name_str = pp0::str_lit<Name>;
                static constexpr const char *name = name_str::value;
                using enclosing_class_type = type_no_cv;
                static constexpr auto mem_ptr = MemPtr;
            };

            template <int I> static auto field(type *ptr)
            {
                     if constexpr (I == 0) return Reflection<TT, field_data<'x',&type_no_cv::x>>(&ptr->x);
                else if constexpr (I == 1) return Reflection<TT, field_data<'y',&type_no_cv::y>>(&ptr->y);
                else if constexpr (I == 2) return Reflection<TT, field_data<'z',&type_no_cv::z>>(&ptr->z);
                else             /*I == 3*/return Reflection<TT, field_data<'w',&type_no_cv::w>>(&ptr->w);
            }
        };
    }


    enum Category {primitive, structure};


    template <typename T, typename = void> struct Wrapper // structures
    {
        using traits = Structure::Traits<T,std::remove_cv_t<T>>;

        static constexpr Category category = structure;

        T &value;
        Wrapper(T *ptr) : value(*ptr) {}

        template <int I> auto field_at() const // Returns class Reflection for the field.
        {
            static_assert(I >= 0 && I < traits::field_count, "Field index is out of range.");
            return traits::template field<I>(&value);
        }

        template <typename F, int ...Seq> void for_fields_at(F &&func, int_seq<Seq...>)
        {
            (func(field_at<Seq>()) , ...);
        }
        template <typename F, int ...Seq> void for_fields_at(F &&func, int_seq<Seq...>) const
        {
            (func(field_at<Seq>()) , ...);
        }

        template <typename F> void for_each_field(F &&func)
        {
            for_fields_at((F&&)func, make_int_seq<traits::field_count>{});
        }
        template <typename F> void for_each_field(F &&func) const
        {
            for_fields_at((F&&)func, make_int_seq<traits::field_count>{});
        }

        std::string to_string() const
        {
            std::string ret = "{";
            for_each_field([&ret](auto refl){ret += refl.to_string(); ret += ',';});
            if (ret.size() != 1)
                ret[ret.size()-1] = '}';
            else
                ret += '}';
            return ret;
        }
        std::string to_string_pretty() const
        {
            constexpr char indentation[] = ".";

            if (traits::field_count == 0)
                return "{}";

            std::string ret;
            for_each_field([&ret, fields_left = traits::field_count](auto refl) mutable
            {
                if (refl.category == structure)
                {
                    std::string tmp = '\n' + refl.to_string_pretty();
                    std::string indented;
                    auto lf_count = std::count(tmp.begin(), tmp.end(), '\n');
                    indented.reserve(tmp.size() + lf_count * (sizeof(indentation)-1));
                    for (char it : tmp)
                    {
                        if (it == '\n')
                        {
                            indented += "\n";
                            indented += indentation;
                        }
                        else
                            indented += it;
                    }

                    ret += refl.name;
                    ret += indented;
                    if (--fields_left)
                        ret += '\n';
                }
                else
                {
                    ret += refl.name;
                    ret += " = ";
                    ret += refl.to_string_pretty();
                    if (--fields_left)
                        ret += '\n';
                }
            });

            return ret;
        }
    };
    template <typename T> struct Wrapper<T, std::void_t<typename Structure::Traits<T,std::remove_cv_t<T>>::not_found>> // primitives
    {
        using traits = Primitive::Traits<T,std::remove_cv_t<T>>;

        static constexpr Category category = primitive;

        T &value;
        Wrapper(T *ptr) : value(*ptr) {}

        std::string to_string() const
        {
            return traits::to_string(&value);
        }
        std::string to_string_pretty() const
        {
            return traits::to_string_pretty(&value);
        }
    };


    template <typename T, typename ContextData /* = void */> struct Reflection : Context<ContextData>, Wrapper<T>
    {
        using type_cv = T;
        using type    = std::remove_cv_t<T>;
        static constexpr bool is_const    = std::is_const_v   <type_cv>;
        static constexpr bool is_volatile = std::is_volatile_v<type_cv>;

        Reflection(type_cv *ptr) : Wrapper<T>(ptr) {}
    };
}


using namespace Refl;


#define REFL0_Support_Integral(type) \
    auto _refl_traits()


#define Reflectable(name_) \
    template <typename T> friend class ::Refl::Reflection; \
    using _refl_name_str = PP0_STR_LIT(#name_); \
    static constexpr const char *name = _refl_name_str::value; \
    template <int I> auto _refl_field()                {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const          {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field()       volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const volatile {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    PP0_COUNTER_DEFINE(::Refl::field_counter_tag,static) \
    struct _refl_traits_t \
    { \
        template <int I, typename T> static auto field(T *ptr) {return ptr->template _refl_field<I>();} \
    }; \
    friend constexpr auto _refl_traits(name_) \
    { \
        return _refl_traits_t{}; \
    };


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

#define REFL0_Reflect_D(name_, type_, .../*init*/) \
    using _refl_field_type_##name_ = type_; \
    _refl_field_type_##name_ name_ __VA_ARGS__; \
    static constexpr int _refl_field_index_##name_ = PP0_COUNTER_READ(::Refl::field_counter_tag); \
    template <typename This> struct _refl_field_data_##name_ \
    { \
        using enclosing_class_type = std::remove_cv_t<This>; \
        using type                 = type_; \
        using name_str = PP0_STR_LIT(#name_); \
        static constexpr const char *name = name_str::value; \
        static constexpr type This::*mem_ptr = &This::name_; \
    }; \
    REFL0_Reflect_MakeFunc(name_,      ,         ) \
    REFL0_Reflect_MakeFunc(name_, const,         ) \
    REFL0_Reflect_MakeFunc(name_,      , volatile) \
    REFL0_Reflect_MakeFunc(name_, const, volatile) \
    PP0_COUNTER_INCR_TO_X(_refl_field_index_##name_+1, ::Refl::field_counter_tag, static)

#define REFL0_Reflect_MakeFunc(name_, c_, v_) \
    auto _refl_field_by_tag(std::integral_constant<int,_refl_field_index_##name_>) c_ v_ \
    { \
        using this_t = std::remove_reference_t<decltype(*this)>; \
        using data = _refl_field_data_##name_<this_t>; \
        return Reflection<c_ v_ _refl_field_type_##name_, data>(&(this->*data::mem_ptr)); \
    }



#endif
