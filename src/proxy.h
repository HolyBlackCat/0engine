#ifndef PROXY_H_INCLUDED
#define PROXY_H_INCLUDED

#include <array>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <vector>

namespace Proxy
{
    inline namespace Interfaces
    {
        class StringReferenceInterface
        {
            std::string *ptr;
          public:
            StringReferenceInterface(std::string &obj) {ptr = &obj;}

            operator std::string &&() const
            {
                return (std::string &&)*ptr;
            }
            std::string &&operator*() const
            {
                return *this;
            }
            char *operator+() const
            {
                return &(*ptr)[0];
            }

            char *begin()
            {
                return &*ptr->begin();
            }
            const char *cbegin() const
            {
                return &*ptr->cbegin();
            }
            char *end()
            {
                return &*ptr->end();
            }
            const char *cend() const
            {
                return &*ptr->cend();
            }
        };

        inline std::ostream &operator<<(std::ostream &stream, StringReferenceInterface obj)
        {
            return stream << +obj;
        }

        inline decltype(auto) operator+(StringReferenceInterface a, StringReferenceInterface b)
        {
            return *a + *b;
        }
        template <typename T> inline decltype(auto) operator+(StringReferenceInterface a, const T &b)
        {
            return *a + b;
        }
        template <typename T> inline decltype(auto) operator+(const T &a, StringReferenceInterface b)
        {
            return a + *b;
        }
    }

    template <typename T> class ArrayProxy
    {
        T *first;
        std::size_t length;

      public:
        using type = typename std::remove_const<T>::type;
        static constexpr bool readonly = std::is_const<T>::value;

        T &operator*() const {return *first;}
        operator T *() const {return first;}

        T *begin() const {return first;}
        T *end() const {return first+length;}

        typename std::conditional<readonly, const void *, void *>::type data() const {return first;}
        std::size_t size() const {return length;}

        ArrayProxy() // Null.
        {
            first = 0;
            length = 0;
        }
        ArrayProxy(T &ptr) // From a single object.
        {
            first = &ptr;
            length = 1;
        }
        ArrayProxy(T *a, T *b) // From a pair of pointers.
        {
            first = a;
            length = b - a;
        }
        ArrayProxy(T *ptr, std::size_t len) // From a pointer and a length.
        {
            first = ptr;
            length = len;
        }
        template <typename TT> ArrayProxy(TT && o) // From an array or a container which uses pointers as iterators. Use this with caution on temporary containers.
        {
            static_assert(std::is_pointer<decltype(std::begin(o))>::value, "Underlying container must use pointers as iterators or must use contiguous storage.");
            static_assert(readonly || (!std::is_const<std::remove_pointer_t<decltype(std::begin(o))>>::value), "Attempt to bind read-write proxy to a const object.");
            first = std::begin(o);
            length = std::end(o) - std::begin(o);
        }
        ArrayProxy(std::initializer_list<type> list) // From std::initializer_list (which is always const). Use this with caution on temporary lists.
        {
            first = list.begin();
            length = list.size();
        }
        template <std::size_t S> ArrayProxy(std::array<type, S> &arr) // From std::array.
        {
            // This function may be redundant on some systems, but this is not guaranteed.
            first = &*arr.begin();
            length = &*arr.end() - &*arr.begin();
        }
        template <std::size_t S> ArrayProxy(const std::array<type, S> &arr) // From const std::array. Use this with caution on temporary arrays.
        {
            // This function may be redundant on some systems, but this is not guaranteed.
            static_assert(readonly, "Attempt to bind read-write proxy to a const object.");
            first = &*arr.begin();
            length = &*arr.end() - &*arr.begin();
        }
        ArrayProxy(std::vector<type> &arr) // From std::vector.
        {
            first = &*arr.begin();
            length = &*arr.end() - &*arr.begin();
        }
        ArrayProxy(const std::vector<type> &arr) // From const std::vector. Use this with caution on temporary vectors.
        {
            static_assert(readonly, "Attempt to bind read-write proxy to a const object.");
            first = &*arr.begin();
            length = &*arr.end() - &*arr.begin();
        }
    };

    template <typename T> using ArrayView = ArrayProxy<const T>;

    class StringView
    {
        const char *pointer;
        int length;
        std::string *buf;

      public:
        char operator*() const {return *pointer;}
        operator const char *() const {return pointer;}

        int size_if_known() const
        {
            return length;
        }

        int size()
        {
            if (length == -1)
                length = std::strlen(pointer);
            return length;
        }

        const char *data() const {return pointer;}

        StringView() // Null.
        {
            pointer = 0;
            length = 0;
            buf = 0;
        }
        StringView(const char *ptr) // From a pointer.
        {
            pointer = ptr;
            length = -1;
            buf = 0;
        }
        StringView(const std::string &arr) // From a const string. Use this with caution on temporary string.
        {
            pointer = arr.c_str();
            length = arr.size();
            buf = 0;
        }
        StringView(std::string &&arr)
        {
            buf = new std::string((std::string &&) arr);
            pointer = buf->c_str();
            length = buf->size();
        }
        StringView(StringReferenceInterface interface) : StringView((std::string &&) interface) {}

        StringView(const StringView &o) // Note: If StringView was moved from a string, then copies of it will point it's internal buffer. Be careful or you can get a dangling pointer.
        {
            pointer = o.pointer;
            length = o.length;
            buf = 0;
        }
        StringView(StringView &&o)
        {
            pointer = o.pointer;
            length = o.length;
            buf = o.buf;
            o.buf = 0;
        }
        StringView &operator=(const StringView &) = delete;
        StringView &operator=(StringView &&) = delete;

        ~StringView()
        {
            if (buf)
                delete buf;
        }
    };

    inline bool operator==(StringView a, StringView b)
    {
        if (a.size_if_known() != b.size_if_known())
        {
            if (a.size_if_known() == -1 || b.size_if_known() == -1)
                return std::strcmp(a, b);
        }
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return 0;
        return 1;
    }
    inline bool operator!=(StringView a, StringView b)
    {
        if (a.size() != b.size())
            return 1;
        for (int i = 0; i < a.size(); i++)
            if (a[i] != b[i])
                return 1;
        return 0;
    }
}

using Proxy::ArrayProxy;
using Proxy::ArrayView;
using Proxy::StringView;

#endif