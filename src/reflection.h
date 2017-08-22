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

    struct GenericContext
    {
        std::string name;

        GenericContext() : GenericContext(Context<void>{}) {}
        template <typename Data> GenericContext(Context<Data>) : name(Context<Data>::name) {}
    };


    enum Category {primitive, structure};


    class GenericReflection
    {
        struct impl_table
        {
            Category category;
            bool is_const;

            int               (*field_count   )(const GenericReflection *           );
            GenericReflection (*field         )(const GenericReflection *, int index);
            std::string       (*to_string     )(const GenericReflection *           );
            std::string       (*to_string_tree)(const GenericReflection *, int depth); // `depth == 0` means infinte depth (this is the default).
        };
        impl_table *pimpl;
      protected:
        const void *value_ptr;
        GenericContext con;
        GenericReflection(const void *value_ptr, GenericContext con) : value_ptr(value_ptr), con(con) {set_impl_table<void>();}
        template <typename T> void set_impl_table()
        {
            if constexpr (std::is_same_v<T, void>)
            {
                static impl_table table
                {
                    primitive,
                    1,

                    [](const GenericReflection *     )->int              {return 0;       },
                    [](const GenericReflection *, int)->GenericReflection{return {};      },
                    [](const GenericReflection *     )->std::string      {return "<null>";},
                    [](const GenericReflection *, int)->std::string      {return "<null>";},
                };
                pimpl = &table;
            }
            else
            {
                static impl_table table
                {
                    T::impl_category,
                    T::impl_is_const,

                    T::impl_field_count,
                    T::impl_field,
                    T::impl_to_string,
                    T::impl_to_string_tree,
                };
                pimpl = &table;
            }
        }
      public:
        GenericReflection() : value_ptr(0) {}
        const void *pointer() const {return value_ptr;}
        const GenericContext &context() const {return con;}

        Category category() const
        {
            return pimpl->category;
        }
        bool is_const() const
        {
            return pimpl->is_const;
        }
        int field_count() const
        {
            return pimpl->field_count(this);
        };
        GenericReflection field(int index) const
        {
            return pimpl->field(this, index);
        }
        std::string to_string() const
        {
            return pimpl->to_string(this);
        }
        std::string to_string_tree(int depth = 0) const
        {
            return pimpl->to_string_tree(this, depth);
        }
    };


    /* `refl_traits_(const volatile T *)` (a member of ::Refl namespace or found by ADL) must return a type providing:
     *
     *   static constexpr Category category() {return ::Refl[::Category]::blah;}
     *
     *
     *   if category = structure
     *   (
     *     static constexpr int field_count() {}
     *
     *     // Returns class Reflection<..> to a field.
     *     template <int I, typename T_with_opt_cv> static auto cexpr_field(T_with_opt_cv *ptr) {}
     *   )
     *
     *   if category = primitive
     *   (
     *     static std::string to_string(const T *) {}
     *     static std::string to_string_tree(const T *) {}
     *   )
     *
     * `refl_traits_structure_generated_(const volatile T *)` can be used instead, with following differences:
     *   field_count() is replaced by a PP0_COUNTER tagged with ::Refl::field_counter_tag.
     */

    // For generated structs
    template <typename T, typename = decltype(refl_traits_structure_generated_(std::declval<const volatile T *>()))> constexpr auto refl_traits_(const volatile T *)
    {
        struct S : decltype(refl_traits_structure_generated_(std::declval<const volatile T *>()))
        {
            static constexpr Category category() {return structure;}

            static constexpr int field_count()
            {
                return PP0_COUNTER_READ_CONTEXT(field_counter_tag, T::);
            }
        };
        return S{};
    }


    inline namespace PrimitiveTraits
    {
        template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> auto refl_traits_(const volatile T *)
        {
            struct S
            {
                static constexpr Category category() {return primitive;}

                static std::string to_string(const T *ptr) {return Math::num_to_string<T>(*ptr);}
                static std::string to_string_tree(const T *ptr) {return to_string(ptr);}
            };
            return S{};
        }

        auto refl_traits_(const volatile bool *)
        {
            struct S
            {
                static constexpr Category category() {return primitive;}

                static std::string to_string(const bool *ptr) {return (*ptr ? "true" : "false");}
                static std::string to_string_tree(const bool *ptr) {return to_string(ptr);}
            };
            return S{};
        }
    }


    template <typename T> struct DefaultTraits
    {
        static constexpr Category category() {return primitive;}

        static std::string to_string(const T *) {return "??";}
        static std::string to_string_tree(const T *) {return "??";}
    };

    template <typename T, typename = void> struct Traits_impl
    {
        using type = DefaultTraits<T>;
    };
    template <typename T> struct Traits_impl<T, std::void_t<decltype(refl_traits_(std::declval<const volatile T *>()))>>
    {
        using type = decltype(refl_traits_(std::declval<const volatile T *>()));
    };

    template <typename T> using Traits = typename Traits_impl<T>::type;


    template <typename T, Category = Traits<T>::category> struct CategoryReflection;
    template <typename T> struct CategoryReflection<T, primitive> : GenericReflection
    {
        static constexpr Category impl_category = primitive;

        static constexpr bool impl_is_const = std::is_const_v<T>;

        CategoryReflection(const void *ptr, GenericContext con) : GenericReflection(ptr, con)
        {
            set_impl_table<CategoryReflection>();
        }

        static int impl_field_count(const GenericReflection *)
        {
            return 0;
        }
        static GenericReflection impl_field(const GenericReflection *, int /*index*/)
        {
            return {};
        }

        static std::string impl_to_string(const GenericReflection *refl)
        {
            return Traits<T>::to_string((const T *)refl->pointer());
        }
        static std::string impl_to_string_tree(const GenericReflection *refl, int /*depth*/)
        {
            return Traits<T>::to_string_tree((const T *)refl->pointer());
        }
    };
    template <typename T> struct CategoryReflection<T, structure> : GenericReflection
    {
        static constexpr Category impl_category = structure;

        static constexpr bool impl_is_const = std::is_const_v<T>;

        CategoryReflection(const void *ptr, GenericContext con) : GenericReflection(ptr, con)
        {
            set_impl_table<CategoryReflection>();
        }

        static int impl_field_count(const GenericReflection *)
        {
            return Traits<T>::field_count();
        }

      private:
        template <int ...Seq> static GenericReflection impl_field_impl(const void *ptr, int index, int_seq<Seq...>)
        {
            if (index < 0 || index >= Traits<T>::field_count())
                return {};

            GenericReflection ret;
            ( (index-- == 0 ? void(ret = Traits<T>::template cexpr_field<Seq>((T *)ptr)) : void()) , ... );
            return ret;
        }
      public:
        static GenericReflection impl_field(const GenericReflection *refl, int index)
        {
            return impl_field_impl(refl->pointer(), index, make_int_seq<Traits<T>::field_count()>{});
        }
        template <int I> auto field() const
        {
            return Traits<T>::template cexpr_field<I>((T *)pointer());
        }

        static std::string impl_to_string(const GenericReflection *refl)
        {
            std::string ret = "{";
            for (int i = 0; i < impl_field_count(refl); i++)
            {
                if (i != 0) ret += ",";
                ret += impl_field(refl, i).to_string();
            }
            ret += "}";
            return ret;
        }
        static std::string impl_to_string_tree(const GenericReflection *refl, int depth)
        {
            //auto indent = [](std::string, )
            std::string ret;
            int field_c = impl_field_count(refl);
            for (int i = 0; i < field_c; i++)
            {
                auto f = impl_field(refl, i);

                if (i != 0) ret += '\n';
                ret += (i != field_c-1 ? '|' : '`');
                ret += (depth == 1 && f.category() == structure ? '*' : '-');
                ret += f.context().name;
                if (f.category() == structure)
                {
                    if (depth != 1)
                    {
                        std::string tmp = '\n' + f.to_string_tree(depth - 1);
                        auto lf_c = std::count(tmp.begin(), tmp.end(), '\n');
                        std::string indented;
                        indented.reserve(tmp.size() + lf_c*2);
                        for (char ch : tmp)
                        {
                            if (ch != '\n')
                                indented += ch;
                            else
                                indented += (i != field_c-1 ? "\n| " : "\n  ");
                        }
                        ret += indented;
                    }
                }
                else
                {
                    ret += '=';
                    ret += f.to_string_tree(depth - 1);
                }
            }
            return ret;
        }
    };

    template <typename T, typename ObjContext = void> struct Reflection : CategoryReflection<T, Traits<T>::category()>
    {
        using type = T;
        using type_no_cv = std::remove_cv_t<T>;
        static constexpr bool is_const = std::is_const_v<T>;

        Reflection(T &ref) : CategoryReflection<T, Traits<T>::category()>(&ref, Context<ObjContext>{}) {}
        T &value() const {return *(T*)this->pointer();}
    };


/*
    namespace Structure
    {
        template <typename T, typename T_no_cv, typename = void> struct Traits
        {
            using not_found = void;
        };
        template <typename T, typename T_no_cv> struct Traits<T, T_no_cv, std::void_t<decltype(refl_traits_(std::declval<T>()))>> : decltype(refl_traits_(std::declval<T>()))
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
                using vec_field_type = std::remove_reference_t<decltype((ptr->x))>; // Note the (()). Without them compiler ignores cv-qualifiers on the decltype.
                     if constexpr (I == 0) return Reflection<vec_field_type, field_data<'x',&type_no_cv::x>>(&ptr->x);
                else if constexpr (I == 1) return Reflection<vec_field_type, field_data<'y',&type_no_cv::y>>(&ptr->y);
                else if constexpr (I == 2) return Reflection<vec_field_type, field_data<'z',&type_no_cv::z>>(&ptr->z);
                else                       return Reflection<vec_field_type, field_data<'w',&type_no_cv::w>>(&ptr->w);
            }
        };
    }

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
        std::string to_string_tree() const
        {
            constexpr char indentation[] = ".";

            if (traits::field_count == 0)
                return "{}";

            std::string ret;
            for_each_field([&ret, fields_left = traits::field_count](auto refl) mutable
            {
                if (refl.category == structure)
                {
                    std::string tmp = '\n' + refl.to_string_tree();
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
                    ret += refl.to_string_tree();
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
        std::string to_string_tree() const
        {
            return traits::to_string_tree(&value);
        }
    };
*/

/*
    template <typename T, typename ContextData > struct Reflection : Context<ContextData>, Wrapper<T>
    {
        using type_cv = T;
        using type    = std::remove_cv_t<T>;
        static constexpr bool is_const    = std::is_const_v   <type_cv>;
        static constexpr bool is_volatile = std::is_volatile_v<type_cv>;

        Reflection(type_cv *ptr) : Wrapper<T>(ptr) {}
    };*/
}


using Refl::GenericReflection;
using Refl::Reflection;


#define Reflectable(name_) \
    template <typename T> friend class ::Refl::Reflection; \
    using _refl_name_str = PP0_STR_LIT(#name_); \
    static constexpr const char *name = _refl_name_str::value; \
    template <int I> auto _refl_field()                {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    template <int I> auto _refl_field() const          {return _refl_field_by_tag(std::integral_constant<int,I>{});} \
    PP0_COUNTER_DEFINE(::Refl::field_counter_tag,static) \
    struct _refl_traits_t \
    { \
        template <int I, typename T> static auto cexpr_field(T *ptr) {return ptr->template _refl_field<I>();} \
    }; \
    friend constexpr auto refl_traits_structure_generated_(const volatile name_ *) \
    { \
        return _refl_traits_t{}; \
    }; \
    Reflect


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
    REFL0_Reflect_MakeFunc(name_,      ) \
    REFL0_Reflect_MakeFunc(name_, const) \
    PP0_COUNTER_INCR_TO_X(_refl_field_index_##name_+1, ::Refl::field_counter_tag, static)

#define REFL0_Reflect_MakeFunc(name_, c_) \
    auto _refl_field_by_tag(std::integral_constant<int,_refl_field_index_##name_>) c_ \
    { \
        using this_t = std::remove_reference_t<decltype(*this)>; \
        using data = _refl_field_data_##name_<this_t>; \
        return Reflection<c_ _refl_field_type_##name_, data>(this->*data::mem_ptr); \
    }



#endif
