#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include <string>
#include <type_traits>

#include "extended_math.h"
#include "preprocessor.h"

namespace Reflection
{
    namespace InterfaceDetails
    {
        template <typename...> struct type_list {};
        template <auto...> struct value_list {};
        template <int I> using int_const = std::integral_constant<int, I>;


        // Default interface functions

        inline constexpr int reflection_interface_field_count(const void *) {return 0;}

        // These should return references to fields.
        template <int I> inline void reflection_interface_field(      void *, int_const<I>) {}
        template <int I> inline void reflection_interface_field(const void *, int_const<I>) {}

        template <int I> inline constexpr bool reflection_interface_field_has_default_value(const void *, int_const<I>) {return 0;}

        template <int I> inline constexpr const char *reflection_interface_field_name(const void *, int_const<I>) {return "?";}

        // Should not be used for structs.
        inline std::string reflection_interface_to_string(const void *) {return "??";}
        // Should be used for structs only and return a short single-line summary of contents. Optional.
        inline std::string reflection_interface_summary_string(const void *) {return "...";}


        // Interface function specializations
        template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> std::string reflection_interface_to_string(const T *obj) {return Math::num_to_string<T>(*obj);}
        inline std::string reflection_interface_to_string(const bool *obj) {return (*obj ? "true" : "false");}


        class Interface
        {
            ~Interface() = delete;
          public:

            template <typename T> static constexpr int field_count(const T &obj) {return reflection_interface_field_count(&obj);}

            template <int I, typename T> static auto field(      T &obj) {return reflection_interface_field(&obj, int_const<I>{});}
            template <int I, typename T> static auto field(const T &obj) {return reflection_interface_field(&obj, int_const<I>{});}

            template <int I, typename T> static constexpr bool field_has_default_value(const T &obj) {return reflection_interface_field_has_default_value(&obj, int_const<I>{});}

            template <int I, typename T> static constexpr const char *field_name(const T &obj) {return reflection_interface_field_name(&obj, int_const<I>{});}

            template <typename T> static std::string to_string(const T &obj) {return reflection_interface_to_string(&obj);}
            template <typename T> static std::string summary_string(const T &obj) {return reflection_interface_summary_string(&obj);}


            class Impl
            {
                ~Impl() = delete;
              public:
                // Returns 1 only when the string consists of non-printable characters only.
                template <std::size_t N> static constexpr bool cexpr_string_is_empty(const char (&str)[N])
                {
                    for (std::size_t i = 0; i < N; i++)
                        if (str[i] > ' ')
                            return 0;
                    return 1;
                }


                // Counter

                template <typename T, typename Tag, int I, typename Unique, typename = void> struct counter_has_crumb
                {
                    static constexpr bool value = 0;
                };
                template <typename T, typename Tag, int I, typename Unique> struct counter_has_crumb<T,Tag,I,Unique,std::void_t<decltype(T::_reflection_internal_counter_crumb(type_list<Tag>{}, int_const<I>{}))>>
                {
                    static constexpr bool value = 1;
                };

                template <typename T, typename Tag, typename Unique, int I = 0> struct counter_value
                {
                    static constexpr bool has_crumb = counter_has_crumb<T,Tag,I,Unique>::value;
                    static constexpr int value = has_crumb + counter_value<T, Tag, Unique, has_crumb ? I+1 : -1>::value;
                };
                template <typename T, typename Tag, typename Unique> struct counter_value<T,Tag,Unique,-1>
                {
                    static constexpr int value = 0;
                };

                struct counter_tag_fields {};
            };
        };
    }

    using InterfaceDetails::Interface;


    template <typename T, int ...Seq> std::string impl_to_string_tree(const T &object, int depth, std::integer_sequence<int, Seq...>)
    {
        using InterfaceDetails::int_const;

        std::string ret;

        auto lambda = [&](auto index)
        {
            const auto &field = Interface::field<index.value>(object);
            using field_t = std::remove_reference_t<decltype(field)>;

            constexpr bool is_struct = Interface::field_count(field_t{}) > 0;

            if (index.value != 0) ret += '\n';
            ret += (index.value != sizeof...(Seq)-1 ? '|' : '`');
            ret += (depth == 1 && is_struct ? '*' : '-');
            ret += Interface::field_name<index.value>(object);
            if constexpr (is_struct)
            {
                if (depth == 1)
                {
                    ret += '=';
                    ret += Interface::summary_string(field);
                }
                else
                {
                    std::string tmp = '\n' + impl_to_string_tree(field, depth - 1, std::make_integer_sequence<int, Interface::field_count(field_t{})>{});
                    auto lf_c = std::count(tmp.begin(), tmp.end(), '\n');
                    std::string indented;
                    indented.reserve(tmp.size() + lf_c*2);
                    for (char ch : tmp)
                    {
                        if (ch != '\n')
                            indented += ch;
                        else
                            indented += (index.value != sizeof...(Seq)-1 ? "\n| " : "\n  ");
                    }
                    ret += indented;
                }
            }
            else
            {
                ret += '=';
                ret += Interface::to_string(field);
            }
        };

        (lambda(int_const<Seq>{}) , ...);

        return ret;
    }

    template <typename T> std::string to_string_tree(const T &obj, int depth = -1) // `depth == -1` means no limit.
    {
        return impl_to_string_tree(obj, depth, std::make_integer_sequence<int, Interface::field_count(T{})>{});
    }
}


#define Reflectable(name_) \
    friend class ::Reflection::Interface; \
    using _reflection_internal_this_type = name_; \
    /* Interface: Get field count */\
    /* (Making it a template delays the expansion so we can get a proper counter value.) */\
    template <typename = void> friend constexpr int reflection_interface_field_count(const _reflection_internal_this_type *) {return ::Reflection::Interface::Impl::counter_value<_reflection_internal_this_type, ::Reflection::Interface::Impl::counter_tag_fields, void>::value;} \
    Reflect

#define Reflect(...) \
    PP0_SEQ_APPLY(PP0_VA_TO_SEQ_DISCARD_LAST(__VA_ARGS__), REFL0_Reflect_A, PP0_F_NULL, )

#define REFL0_Reflect_A(i, data, seq) \
    PP0_SEQ_CALL(REFL0_Reflect_B_, seq)(i, seq)

#define REFL0_Reflect_B_1(i, expr) \
    PP0_DEL_PARENS(expr)

#define REFL0_Reflect_B_2(i, seq) \
    PP0_SEQ_APPLY_A(PP0_VA_TO_SEQ(PP0_SEQ_AT(1,seq)), REFL0_Reflect_C, PP0_F_NULL, (i, PP0_SEQ_FIRST(seq)/*type*/ , 0 , ))

#define REFL0_Reflect_B_3(i, seq) \
    PP0_SEQ_APPLY_A(PP0_VA_TO_SEQ(PP0_SEQ_AT(1,seq)), REFL0_Reflect_C, PP0_F_NULL, (i, PP0_SEQ_FIRST(seq)/*type*/ , 1 , PP0_SEQ_AT(2,seq)/*init*/))

#define REFL0_Reflect_C(j, data, name) \
    PP0_CALL_B(REFL0_Reflect_D, name, j, PP0_DEL_PARENS(data))

#define REFL0_Reflect_D(name_, j_, i_, type_, has_init_, .../*init*/) \
    /* Define the field. */\
    std::enable_if_t<1, type_> name_ __VA_ARGS__; \
    /* Make sure there is no explicit empty init (because it would make `has_init_ == 1` without a good reason). */\
    static_assert(has_init_ == 0 || !::Reflection::Interface::Impl::cexpr_string_is_empty(#__VA_ARGS__), "Empty default value."); \
    /* Field index. */\
    static constexpr int _reflection_internal_field_index_##name_ = ::Reflection::Interface::Impl::counter_value<_reflection_internal_this_type, ::Reflection::Interface::Impl::counter_tag_fields, ::Reflection::InterfaceDetails::value_list<__LINE__, i_, j_>>::value; \
    using _reflection_internal_field_indextype_##name_ = ::Reflection::InterfaceDetails::int_const<_reflection_internal_field_index_##name_>; \
    /* Increment field counter. */\
    static void _reflection_internal_counter_crumb(::Reflection::InterfaceDetails::type_list<::Reflection::Interface::Impl::counter_tag_fields>, ::Reflection::InterfaceDetails::int_const<_reflection_internal_field_index_##name_>) {} \
    /* Inteface: Get the field by index. */\
    friend       auto &reflection_interface_field(      _reflection_internal_this_type *ptr, _reflection_internal_field_indextype_##name_) {return ptr->name_;} \
    friend const auto &reflection_interface_field(const _reflection_internal_this_type *ptr, _reflection_internal_field_indextype_##name_) {return ptr->name_;} \
    /* Inteface: Whether the field has a default value or not. */\
    friend constexpr bool reflection_interface_field_has_default_value(const _reflection_internal_this_type *, _reflection_internal_field_indextype_##name_) {return has_init_;} \
    /* Inteface: Field name. */\
    friend constexpr const char *reflection_interface_field_name(const _reflection_internal_this_type *, _reflection_internal_field_indextype_##name_) {return #name_;} \

#endif
