#ifndef REFLECTION_H_INCLUDED
#define REFLECTION_H_INCLUDED

#include <cstddef>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>

#include "extended_math.h"
#include "preprocessor.h"

namespace Reflection
{
    namespace Cexpr
    {
        // Strings

        template <char ...C> struct str
        {
            static constexpr char value[] = {C..., '\0'};
        };

        template <typename F, typename ...P> struct str_cat_impl {using type = typename str_cat_impl<F, typename str_cat_impl<P...>::type>::type;};
        template <typename T> struct str_cat_impl<T> {using type = T;};
        template <char ...A, char ...B> struct str_cat_impl<str<A...>, str<B...>> {using type = str<A..., B...>;};
        template <typename F, typename ...P> using str_cat = typename str_cat_impl<F, P...>::type;

        template <char C> inline constexpr bool char_is_alphanum = (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || (C >= '0' && C <= '9') || C == '_';

        template <typename F, typename ...P> struct str_smart_cat_impl {using type = typename str_smart_cat_impl<F, typename str_smart_cat_impl<P...>::type>::type;};
        template <typename T> struct str_smart_cat_impl<T> {using type = T;};
        template <char ...A, char ...B> struct str_smart_cat_impl<str<A...>, str<B...>>
        {
            using type = std::conditional_t<sizeof...(A) == 0
                                             || sizeof...(B) == 0
                                             || !char_is_alphanum<str<A...>::value[(sizeof...(A)-1) * bool(sizeof...(A))]>
                                             || !char_is_alphanum<str<B...>::value[0]>,
                                            str_cat<str<A...>, str<B...>>,
                                            str_cat<str<A...>, str<' '>, str<B...>>>;
        };
        template <typename F, typename ...P> using str_smart_cat = typename str_smart_cat_impl<F, P...>::type;

        template <std::size_t A, std::size_t B> struct pow
        {
            static constexpr std::size_t value = A * pow<A, B-1>::value;
        };
        template <std::size_t A> struct pow<A, 0>
        {
            static constexpr std::size_t value = 1;
        };

        template <std::size_t N, std::size_t Pow, std::size_t ...Seq> constexpr auto num_to_str_impl(std::index_sequence<Seq...>)
        {
            if constexpr (N >= pow<10, Pow>::value)
                return num_to_str_impl<N, Pow+1>(std::make_index_sequence<Pow+1>{});
            else
                return str<(N / pow<10, Pow-1-Seq>::value % 10 + '0')...>{};
        }
        template <std::size_t N> using num_to_str = decltype(num_to_str_impl<N, 1>(std::make_index_sequence<1>{}));

        // Returns 1 only when the string consists of non-printable characters only.
        template <std::size_t N> static constexpr bool cexpr_string_is_empty(const char (&str)[N])
        {
            for (std::size_t i = 0; i < N; i++)
                if (str[i] > ' ')
                    return 0;
            return 1;
        }
    }

    namespace InterfaceDetails
    {
        template <typename...> struct type_list {};
        template <auto...> struct value_list {};
        template <int I> using int_const = std::integral_constant<int, I>;

        template <typename F, typename ...P> struct last_of_impl {using type = typename last_of_impl<P...>::type;};
        template <typename F> struct last_of_impl<F> {using type = F;};
        template <typename F, typename ...P> using last_of = typename last_of_impl<F, P...>::type;

        template <typename T> inline constexpr bool forced_primitive = std::is_same_v<std::string, T>;


        // Default interface functions

        inline constexpr int reflection_interface_field_count(/*unused*/ const void *) {return 0;}

        // This should return reference to the field.
        template <int I> void reflection_interface_field(const void *, int_const<I>) {}

        template <int I> constexpr bool reflection_interface_field_has_default_value(/*unused*/ const void *, int_const<I>) {return 0;}

        template <int I> constexpr const char *reflection_interface_field_name(/*unused*/ const void *, int_const<I>) {return "?";}

        // Should be used for primitives only.
        inline std::string reflection_interface_primitive_to_string(const void *) {return "??";}
        // Should be used for composites only and return a short single-line summary of contents. Optional.
        inline std::string reflection_interface_composite_summary_string(const void *) {return "...";}

        inline std::size_t reflection_interface_container_size(const void *) {return 0;}
        // Those should return corresponding iterators.
        inline void reflection_interface_container_begin(void *) {}
        inline void reflection_interface_container_end(void *) {}
        inline void reflection_interface_container_cbegin(const void *) {}
        inline void reflection_interface_container_cend(const void *) {}


        // Interface function specializations

        // Strings
        inline std::string reflection_interface_primitive_to_string(const std::string *obj)
        {
            auto Escape = [](char c) constexpr -> char
            {
                switch (c)
                {
                    case '\"': return '"';
                    case '\a': return 'a';
                    case '\b': return 'b';
                    case '\f': return 'f';
                    case '\n': return 'n';
                    case '\r': return 'r';
                    case '\t': return 't';
                    case '\v': return 'v';
                    default: return 0;
                }
            };
            auto HexEscape = [](char c) constexpr -> bool
            {
                return (c >= '\0' && c < ' ') || c == 127;
            };

            auto esc = std::count_if(obj->begin(), obj->end(), Escape);
            auto hex = std::count_if(obj->begin(), obj->end(), HexEscape);

            std::string ret;
            ret.reserve(obj->size() + esc + hex * 3 + 2);
            ret.push_back('"');
            for (char ch : *obj)
            {
                if (Escape(ch))
                {
                    char tmp[] {'\\', Escape(ch), '\0'};
                    ret += tmp;
                }
                else if (HexEscape(ch))
                {
                    char tmp[] {'\\', 'x', char((unsigned char)ch / 16 + '0'), char((unsigned char)ch % 16 + '0'), '\0'};
                    ret += tmp;
                }
                else
                    ret += ch;
            }
            ret.push_back('"');
            return ret;
        }

        // Arithmetic types
        template <typename T> std::enable_if_t<std::is_arithmetic_v<T>, std::string> reflection_interface_primitive_to_string(const T *obj) {return Math::num_to_string<T>(*obj);}
        inline std::string reflection_interface_primitive_to_string(const bool *obj) {return (*obj ? "true" : "false");}

        // Vectors/matrices
        template <typename T> constexpr std::enable_if_t<Math::type_category<T>::vec_or_mat, int> reflection_interface_field_count(const T *)
        {
            if constexpr (Math::type_category<T>::vec)
                return T::size;
            else
                return T::width;
        }
        template <typename T, int I> std::enable_if_t<Math::type_category<T>::vec_or_mat, const decltype(T::x) &> reflection_interface_field(const T *ptr, int_const<I>)
        {
                 if constexpr (I == 0) return ptr->x;
            else if constexpr (I == 1) return ptr->y;
            else if constexpr (I == 2) return ptr->z;
            else if constexpr (I == 3) return ptr->w;
            else                       return {};
        }
        template <typename T, int I, typename = std::enable_if_t<Math::type_category<T>::vec_or_mat>> constexpr const char *reflection_interface_field_name(const T *, int_const<I>)
        {
                 if constexpr (I == 0) return "x";
            else if constexpr (I == 1) return "y";
            else if constexpr (I == 2) return "z";
            else if constexpr (I == 3) return "w";
        }
        template <typename T, typename = std::enable_if_t<Math::type_category<T>::vec_or_mat>> std::string reflection_interface_composite_summary_string(const T *ptr) {return ptr->to_string();}

        // Tuples, pairs and `std::array`s.
        template <typename T       > constexpr last_of<decltype(std::tuple_size<T>::value), int         > reflection_interface_field_count(const T *              ) {return std::tuple_size<T>::value;}
        template <typename T, int I> constexpr auto reflection_interface_field(const T *ptr, int_const<I>) -> last_of<decltype(std::tuple_size<T>::value), decltype(std::get<I>(*ptr))> {return std::get<I>(*ptr);}
        template <typename T, int I> constexpr last_of<decltype(std::tuple_size<T>::value), const char *> reflection_interface_field_name (const T *, int_const<I>) {return Cexpr::num_to_str<I>::value;}

        // Plain arrays.
        template <typename T       > constexpr std::enable_if_t<std::is_array_v<T>, int                            > reflection_interface_field_count(const T *              ) {return std::extent_v<T>;}
        template <typename T, int I> constexpr std::enable_if_t<std::is_array_v<T>, const std::remove_extent_t<T> &> reflection_interface_field(const T *ptr, int_const<I>) {return (*ptr)[I];}
        template <typename T, int I> constexpr std::enable_if_t<std::is_array_v<T>, const char *                   > reflection_interface_field_name (const T *, int_const<I>) {return Cexpr::num_to_str<I>::value;}

        // Standard containers
        template <typename T, typename = std::enable_if_t<!forced_primitive<T>, decltype(std::size  (std::declval<const T &>()))>> std::size_t reflection_interface_container_size  (const T *ptr) {return std::size  (*ptr);}
        template <typename T, typename = std::enable_if_t<!forced_primitive<T>, decltype(std::begin (std::declval<      T &>()))>> auto        reflection_interface_container_begin (      T *ptr) {return std::begin (*ptr);}
        template <typename T, typename = std::enable_if_t<!forced_primitive<T>, decltype(std::end   (std::declval<      T &>()))>> auto        reflection_interface_container_end   (      T *ptr) {return std::end   (*ptr);}
        template <typename T, typename = std::enable_if_t<!forced_primitive<T>, decltype(std::cbegin(std::declval<const T &>()))>> auto        reflection_interface_container_cbegin(const T *ptr) {return std::cbegin(*ptr);}
        template <typename T, typename = std::enable_if_t<!forced_primitive<T>, decltype(std::cend  (std::declval<const T &>()))>> auto        reflection_interface_container_cend  (const T *ptr) {return std::cend  (*ptr);}


        class Interface
        {
            ~Interface() = delete;
          public:

            template <typename T> static constexpr bool is_structure() {return field_count<T>() > 0;}

            template <typename T> static constexpr int field_count() {return reflection_interface_field_count((const T *)0);}

            template <int I, typename T> static const auto &field(const T &obj) {return reflection_interface_field(&obj, int_const<I>{});}
            template <int I, typename T> static       auto &field(      T &obj) {return (std::remove_const_t<std::remove_reference_t<decltype(field<I>((const T &)obj))>> &)field<I>((const T &)obj);}

            template <typename T, int I> static constexpr bool field_has_default_value() {return reflection_interface_field_has_default_value((const T *)0, int_const<I>{});}

            template <typename T, int I> static constexpr const char *field_name() {return reflection_interface_field_name((const T *)0, int_const<I>{});}

            template <typename T> static std::string to_string(const T &obj)
            {
                if constexpr (is_primitive<T>())
                    return reflection_interface_primitive_to_string(&obj);
                else
                    return reflection_interface_composite_summary_string(&obj);
            }


            template <typename T> static constexpr bool is_container()
            {
                using type = std::remove_cv_t<T> *;
                return !is_structure<T>()
                    && !std::is_void_v<decltype(reflection_interface_container_size  (std::declval<type>()))>
                    && !std::is_void_v<decltype(reflection_interface_container_begin (std::declval<type>()))>
                    && !std::is_void_v<decltype(reflection_interface_container_end   (std::declval<type>()))>
                    && !std::is_void_v<decltype(reflection_interface_container_cbegin(std::declval<type>()))>
                    && !std::is_void_v<decltype(reflection_interface_container_cend  (std::declval<type>()))>;
            }

            template <typename T> static std::size_t container_size  (const T &obj) {return reflection_interface_container_size  (&obj);}
            template <typename T> static auto        container_begin (      T &obj) {return reflection_interface_container_begin (&obj);}
            template <typename T> static auto        container_end   (      T &obj) {return reflection_interface_container_end   (&obj);}
            template <typename T> static auto        container_cbegin(const T &obj) {return reflection_interface_container_cbegin(&obj);}
            template <typename T> static auto        container_cend  (const T &obj) {return reflection_interface_container_cend  (&obj);}

            template <typename T> using container_value_t = std::remove_const_t<std::remove_reference_t<decltype(*container_cbegin(std::declval<T>()))>>;

            template <typename T, typename F> static void container_for_each(      T &obj, F &&func) {std::for_each(container_begin(obj), container_end(obj), (F &&) func);}
            template <typename T, typename F> static void container_for_each(const T &obj, F &&func) {std::for_each(container_cbegin(obj), container_cend(obj), (F &&) func);}

            template <typename T> static constexpr bool is_primitive() {return !is_structure<T>() && !is_container<T>();}

            class Impl
            {
                ~Impl() = delete;
              public:

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

        [[maybe_unused]] auto Indent = [](std::string param, char symbol) -> std::string
        {
            param = '\n' + param;
            auto lf_c = std::count(param.begin(), param.end(), '\n');
            std::string indented;
            indented.reserve(param.size() + lf_c*2);

            for (char ch : param)
            {
                if (ch != '\n')
                    indented += ch;
                else
                {
                    indented += '\n';
                    indented += symbol;
                    indented += ' ';
                }
            }
            return indented;
        };


        if constexpr (Interface::is_structure<T>())
        {
            std::string ret;

            auto lambda = [&](auto index)
            {
                const auto &field = Interface::field<index.value>(object);
                using field_t = std::remove_reference_t<decltype(field)>;

                constexpr bool is_primitive = Interface::is_primitive<field_t>();

                if (index.value != 0) ret += '\n';
                ret += (index.value != sizeof...(Seq)-1 ? '|' : '`');
                ret += (depth == 0 && !is_primitive ? '*' : '-');
                ret += Interface::field_name<T, index.value>();
                if constexpr (!is_primitive)
                {
                    if (depth == 0)
                    {
                        ret += '=';
                        ret += Interface::to_string(field);
                    }
                    else
                        ret += Indent(impl_to_string_tree(field, depth - 1, std::make_integer_sequence<int, Interface::field_count<field_t>()>{}), "| "[index.value == sizeof...(Seq)-1]);
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
        else if constexpr (Interface::is_container<T>())
        {
            std::string ret;

            std::size_t pos = 0, size = Interface::container_size(object);

            using value_t = Interface::container_value_t<T>;

            constexpr bool primitive_value = Interface::is_primitive<value_t>();


            for (auto it = Interface::container_cbegin(object); it != Interface::container_cend(object); it++)
            {
                if (pos != 0) ret += '\n';
                ret += (pos != size-1 ? ':' : '`');
                ret += (depth == 0 && !primitive_value ? '*' : '-');
                ret += std::to_string(pos);
                if constexpr (!primitive_value)
                {
                    if (depth == 0)
                    {
                        ret += '=';
                        ret += Interface::to_string(*it);
                    }
                    else
                        ret += Indent(impl_to_string_tree(*it, depth - 1, std::make_integer_sequence<int, Interface::field_count<value_t>()>{}), ": "[pos == size-1]);
                }
                else
                {
                    ret += '=';
                    ret += Interface::to_string(*it);
                }
                pos++;
            }

            return ret;
        }
        else /* is_primitive<T>() */ // This is not used recursively.
        {
            return Interface::to_string(object);
        }
    }

    template <typename T> std::string to_string_tree(const T &obj, int depth = -1) // `depth == -1` means no limit.
    {
        return impl_to_string_tree(obj, depth, std::make_integer_sequence<int, Interface::field_count<T>()>{});
    }
}

/* Struct/class reflection.
 * Example struct definition:
 *
 *   struct A
 *   {
 *     Reflectable(A)
 *     (
 *       (int)(a),
 *       (int[3])(b),
         (float)(c,d)
 *       (int)(e,f)(=42),
 *       (private:),
 *       (int)(g),
 *     )
 *   };
 *
 * If you want to reflect more fields separately, you can use Reflect() macro with the same syntax (but without the class name enclosed in `()`).
 */

#define Reflect(name_) \
    friend class ::Reflection::Interface; \
    using _reflection_internal_this_type = name_; \
    /* Interface: Get field count */\
    /* (Making it a template delays the expansion so we can get a proper counter value.) */\
    template <typename = void> friend constexpr int reflection_interface_field_count(const _reflection_internal_this_type *) {return ::Reflection::Interface::Impl::counter_value<_reflection_internal_this_type, ::Reflection::Interface::Impl::counter_tag_fields, void>::value;} \
    ReflectMembers

#define ReflectMembers(...) \
    PP0_SEQ_APPLY(PP0_VA_TO_SEQ_DISCARD_LAST(__VA_ARGS__), REFL0_Reflect_A, PP0_F_NULL, )

#define REFL0_Reflect_A(i, data, seq) \
    PP0_SEQ_CALL(REFL0_Reflect_B_, seq)(i, seq)

#define REFL0_Reflect_B_1(i, expr) \
    PP0_DEL_PARENS(expr)

#define REFL0_Reflect_B_2(i, seq) \
    PP0_SEQ_APPLY_A(PP0_VA_TO_SEQ(PP0_SEQ_AT(1,seq)), REFL0_Reflect_C, PP0_F_NULL, (i, (PP0_SEQ_FIRST(seq))/*type*/ , 0 , ))

#define REFL0_Reflect_B_3(i, seq) \
    PP0_SEQ_APPLY_A(PP0_VA_TO_SEQ(PP0_SEQ_AT(1,seq)), REFL0_Reflect_C, PP0_F_NULL, (i, (PP0_SEQ_FIRST(seq))/*type*/ , 1 , PP0_SEQ_AT(2,seq)/*init*/))

#define REFL0_Reflect_C(j, data, name) \
    PP0_CALL_B(REFL0_Reflect_D, name, j, PP0_DEL_PARENS(data))

#define REFL0_Reflect_D(name_, j_, i_, type_, has_init_, .../*init*/) \
    /* Define the field. */\
    std::enable_if_t<1, PP0_DEL_PARENS(type_)> name_ __VA_ARGS__; \
    /* Make sure there is no explicit empty init (because it would make `has_init_ == 1` without a good reason). */\
    static_assert(has_init_ == 0 || !::Reflection::Cexpr::cexpr_string_is_empty(#__VA_ARGS__), "Empty default value."); \
    /* Field index. */\
    using _reflection_internal_field_index_type_##name_ = ::Reflection::InterfaceDetails::int_const<::Reflection::Interface::Impl::counter_value<_reflection_internal_this_type, ::Reflection::Interface::Impl::counter_tag_fields, ::Reflection::InterfaceDetails::value_list<__LINE__, i_, j_>>::value>; \
    /* Increment field counter. */\
    static void _reflection_internal_counter_crumb(::Reflection::InterfaceDetails::type_list<::Reflection::Interface::Impl::counter_tag_fields>, _reflection_internal_field_index_type_##name_) {} \
    /* Inteface: Get the field by index. */\
    friend const auto &reflection_interface_field(const _reflection_internal_this_type *ptr, _reflection_internal_field_index_type_##name_) {return ptr->name_;} \
    /* Inteface: Whether the field has a default value or not. */\
    friend constexpr bool reflection_interface_field_has_default_value(const _reflection_internal_this_type *, _reflection_internal_field_index_type_##name_) {return has_init_;} \
    /* Inteface: Field name. */\
    friend constexpr const char *reflection_interface_field_name(const _reflection_internal_this_type *, _reflection_internal_field_index_type_##name_) {return #name_;}


/* Enum reflection.
 * Grammar:
 * [optional]
 * `placeholders`
 *
 *   Reflect[Member]Enum[Class]('name' [,'type'], 'list`)
 *
 * Where `list` is a delimiter-less list of either
 *   ('name')
 * or
 *   ('name', 'value')
 */

// `...` is `[underlying_type,] seq`
#define ReflectEnum(name, ...)             PP0_VA_CALL(REFL0_ReflectEnum_A_, __VA_ARGS__)(name, inline,      , __VA_ARGS__)
#define ReflectEnumClass(name, ...)        PP0_VA_CALL(REFL0_ReflectEnum_A_, __VA_ARGS__)(name, inline, class, __VA_ARGS__)
#define ReflectMemberEnum(name, ...)       PP0_VA_CALL(REFL0_ReflectEnum_A_, __VA_ARGS__)(name, friend,      , __VA_ARGS__)
#define ReflectMemberEnumClass(name, ...)  PP0_VA_CALL(REFL0_ReflectEnum_A_, __VA_ARGS__)(name, friend, class, __VA_ARGS__)

#define REFL0_ReflectEnum_A_1(name, func_specifiers, pre, seq)                  REFL0_ReflectEnum_B(name, seq, func_specifiers, pre,)
#define REFL0_ReflectEnum_A_2(name, func_specifiers, pre, underlying_type, seq) REFL0_ReflectEnum_B(name, seq, func_specifiers, pre, : underlying_type)

#define REFL0_ReflectEnum_B(name, seq, func_specifiers, pre, post) enum pre name post { PP0_SEQ_APPLY(seq, REFL0_ReflectEnum_C, PP0_F_NULL,) }; ReflectExistingEnum(name, seq, func_specifiers)

#define REFL0_ReflectEnum_C(i, data, ...) PP0_VA_CALL(REFL0_ReflectEnum_D_, __VA_ARGS__)(__VA_ARGS__)

#define REFL0_ReflectEnum_D_1(name)        name,
#define REFL0_ReflectEnum_D_2(name, value) name = value,

// `func_specifiers_` depends on the scope. At namespace scope it must be `inline` (if the file is not a header, empty string may be used instead). At class scope it must be `friend`.
#define ReflectExistingEnum(type_, seq_, func_specifiers_) \
    /* Interface: To string. */\
    func_specifiers_ ::std::string reflection_interface_primitive_to_string(const type_ *ptr) \
    { \
        switch (*ptr) \
        { \
            PP0_SEQ_APPLY(seq_, REFL0_ReflectEnum_Func_ToString_A, PP0_F_NULL, type_) \
            default: return "invalid:" + ::std::to_string((::std::underlying_type_t<type_>)*ptr); \
        } \
    }

#define REFL0_ReflectEnum_Func_ToString_A(i, type, ...) case type::PP0_VA_AT(0, __VA_ARGS__): return PP0_STR(PP0_VA_AT(0, __VA_ARGS__));

#endif
