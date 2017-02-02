#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

// Version 1.9.1 by HolyBlackCat

#include <functional>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <type_traits>
#include <utility>


namespace Math
{
    namespace Vector
    {
        template <unsigned int D, typename T> struct vec;
        template <unsigned int W, unsigned int H, typename T> using mat = vec<W, vec<H, T>>;
        template <typename T> using vec2 = vec<2, T>;
        template <typename T> using vec3 = vec<3, T>;
        template <typename T> using vec4 = vec<4, T>;
        template <typename T> using mat2x2 = mat<2,2,T>;
        template <typename T> using mat3x2 = mat<3,2,T>;
        template <typename T> using mat4x2 = mat<4,2,T>;
        template <typename T> using mat2x3 = mat<2,3,T>;
        template <typename T> using mat3x3 = mat<3,3,T>;
        template <typename T> using mat4x3 = mat<4,3,T>;
        template <typename T> using mat2x4 = mat<2,4,T>;
        template <typename T> using mat3x4 = mat<3,4,T>;
        template <typename T> using mat4x4 = mat<4,4,T>;
        template <typename T> using mat2 = mat2x2<T>;
        template <typename T> using mat3 = mat3x3<T>;
        template <typename T> using mat4 = mat4x4<T>;
        template <unsigned int D> using cvec = vec<D,char>;
        template <unsigned int W, unsigned int H> using cmat = mat<W,H,char>;
        using cvec2 = vec<2,char>;
        using cvec3 = vec<3,char>;
        using cvec4 = vec<4,char>;
        using cmat2x2 = mat<2,2,char>;
        using cmat3x2 = mat<3,2,char>;
        using cmat4x2 = mat<4,2,char>;
        using cmat2x3 = mat<2,3,char>;
        using cmat3x3 = mat<3,3,char>;
        using cmat4x3 = mat<4,3,char>;
        using cmat2x4 = mat<2,4,char>;
        using cmat3x4 = mat<3,4,char>;
        using cmat4x4 = mat<4,4,char>;
        using cmat2 = cmat2x2;
        using cmat3 = cmat3x3;
        using cmat4 = cmat4x4;
        template <unsigned int D> using ucvec = vec<D,unsigned char>;
        template <unsigned int W, unsigned int H> using ucmat = mat<W,H,unsigned char>;
        using ucvec2 = vec<2,unsigned char>;
        using ucvec3 = vec<3,unsigned char>;
        using ucvec4 = vec<4,unsigned char>;
        using ucmat2x2 = mat<2,2,unsigned char>;
        using ucmat3x2 = mat<3,2,unsigned char>;
        using ucmat4x2 = mat<4,2,unsigned char>;
        using ucmat2x3 = mat<2,3,unsigned char>;
        using ucmat3x3 = mat<3,3,unsigned char>;
        using ucmat4x3 = mat<4,3,unsigned char>;
        using ucmat2x4 = mat<2,4,unsigned char>;
        using ucmat3x4 = mat<3,4,unsigned char>;
        using ucmat4x4 = mat<4,4,unsigned char>;
        using ucmat2 = ucmat2x2;
        using ucmat3 = ucmat3x3;
        using ucmat4 = ucmat4x4;
        template <unsigned int D> using scvec = vec<D,signed char>;
        template <unsigned int W, unsigned int H> using scmat = mat<W,H,signed char>;
        using scvec2 = vec<2,signed char>;
        using scvec3 = vec<3,signed char>;
        using scvec4 = vec<4,signed char>;
        using scmat2x2 = mat<2,2,signed char>;
        using scmat3x2 = mat<3,2,signed char>;
        using scmat4x2 = mat<4,2,signed char>;
        using scmat2x3 = mat<2,3,signed char>;
        using scmat3x3 = mat<3,3,signed char>;
        using scmat4x3 = mat<4,3,signed char>;
        using scmat2x4 = mat<2,4,signed char>;
        using scmat3x4 = mat<3,4,signed char>;
        using scmat4x4 = mat<4,4,signed char>;
        using scmat2 = scmat2x2;
        using scmat3 = scmat3x3;
        using scmat4 = scmat4x4;
        template <unsigned int D> using svec = vec<D,short>;
        template <unsigned int W, unsigned int H> using smat = mat<W,H,short>;
        using svec2 = vec<2,short>;
        using svec3 = vec<3,short>;
        using svec4 = vec<4,short>;
        using smat2x2 = mat<2,2,short>;
        using smat3x2 = mat<3,2,short>;
        using smat4x2 = mat<4,2,short>;
        using smat2x3 = mat<2,3,short>;
        using smat3x3 = mat<3,3,short>;
        using smat4x3 = mat<4,3,short>;
        using smat2x4 = mat<2,4,short>;
        using smat3x4 = mat<3,4,short>;
        using smat4x4 = mat<4,4,short>;
        using smat2 = smat2x2;
        using smat3 = smat3x3;
        using smat4 = smat4x4;
        template <unsigned int D> using usvec = vec<D,unsigned short>;
        template <unsigned int W, unsigned int H> using usmat = mat<W,H,unsigned short>;
        using usvec2 = vec<2,unsigned short>;
        using usvec3 = vec<3,unsigned short>;
        using usvec4 = vec<4,unsigned short>;
        using usmat2x2 = mat<2,2,unsigned short>;
        using usmat3x2 = mat<3,2,unsigned short>;
        using usmat4x2 = mat<4,2,unsigned short>;
        using usmat2x3 = mat<2,3,unsigned short>;
        using usmat3x3 = mat<3,3,unsigned short>;
        using usmat4x3 = mat<4,3,unsigned short>;
        using usmat2x4 = mat<2,4,unsigned short>;
        using usmat3x4 = mat<3,4,unsigned short>;
        using usmat4x4 = mat<4,4,unsigned short>;
        using usmat2 = usmat2x2;
        using usmat3 = usmat3x3;
        using usmat4 = usmat4x4;
        template <unsigned int D> using ivec = vec<D,int>;
        template <unsigned int W, unsigned int H> using imat = mat<W,H,int>;
        using ivec2 = vec<2,int>;
        using ivec3 = vec<3,int>;
        using ivec4 = vec<4,int>;
        using imat2x2 = mat<2,2,int>;
        using imat3x2 = mat<3,2,int>;
        using imat4x2 = mat<4,2,int>;
        using imat2x3 = mat<2,3,int>;
        using imat3x3 = mat<3,3,int>;
        using imat4x3 = mat<4,3,int>;
        using imat2x4 = mat<2,4,int>;
        using imat3x4 = mat<3,4,int>;
        using imat4x4 = mat<4,4,int>;
        using imat2 = imat2x2;
        using imat3 = imat3x3;
        using imat4 = imat4x4;
        template <unsigned int D> using uvec = vec<D,unsigned int>;
        template <unsigned int W, unsigned int H> using umat = mat<W,H,unsigned int>;
        using uvec2 = vec<2,unsigned int>;
        using uvec3 = vec<3,unsigned int>;
        using uvec4 = vec<4,unsigned int>;
        using umat2x2 = mat<2,2,unsigned int>;
        using umat3x2 = mat<3,2,unsigned int>;
        using umat4x2 = mat<4,2,unsigned int>;
        using umat2x3 = mat<2,3,unsigned int>;
        using umat3x3 = mat<3,3,unsigned int>;
        using umat4x3 = mat<4,3,unsigned int>;
        using umat2x4 = mat<2,4,unsigned int>;
        using umat3x4 = mat<3,4,unsigned int>;
        using umat4x4 = mat<4,4,unsigned int>;
        using umat2 = umat2x2;
        using umat3 = umat3x3;
        using umat4 = umat4x4;
        template <unsigned int D> using lvec = vec<D,long>;
        template <unsigned int W, unsigned int H> using lmat = mat<W,H,long>;
        using lvec2 = vec<2,long>;
        using lvec3 = vec<3,long>;
        using lvec4 = vec<4,long>;
        using lmat2x2 = mat<2,2,long>;
        using lmat3x2 = mat<3,2,long>;
        using lmat4x2 = mat<4,2,long>;
        using lmat2x3 = mat<2,3,long>;
        using lmat3x3 = mat<3,3,long>;
        using lmat4x3 = mat<4,3,long>;
        using lmat2x4 = mat<2,4,long>;
        using lmat3x4 = mat<3,4,long>;
        using lmat4x4 = mat<4,4,long>;
        using lmat2 = lmat2x2;
        using lmat3 = lmat3x3;
        using lmat4 = lmat4x4;
        template <unsigned int D> using ulvec = vec<D,unsigned long>;
        template <unsigned int W, unsigned int H> using ulmat = mat<W,H,unsigned long>;
        using ulvec2 = vec<2,unsigned long>;
        using ulvec3 = vec<3,unsigned long>;
        using ulvec4 = vec<4,unsigned long>;
        using ulmat2x2 = mat<2,2,unsigned long>;
        using ulmat3x2 = mat<3,2,unsigned long>;
        using ulmat4x2 = mat<4,2,unsigned long>;
        using ulmat2x3 = mat<2,3,unsigned long>;
        using ulmat3x3 = mat<3,3,unsigned long>;
        using ulmat4x3 = mat<4,3,unsigned long>;
        using ulmat2x4 = mat<2,4,unsigned long>;
        using ulmat3x4 = mat<3,4,unsigned long>;
        using ulmat4x4 = mat<4,4,unsigned long>;
        using ulmat2 = ulmat2x2;
        using ulmat3 = ulmat3x3;
        using ulmat4 = ulmat4x4;
        template <unsigned int D> using llvec = vec<D,long long>;
        template <unsigned int W, unsigned int H> using llmat = mat<W,H,long long>;
        using llvec2 = vec<2,long long>;
        using llvec3 = vec<3,long long>;
        using llvec4 = vec<4,long long>;
        using llmat2x2 = mat<2,2,long long>;
        using llmat3x2 = mat<3,2,long long>;
        using llmat4x2 = mat<4,2,long long>;
        using llmat2x3 = mat<2,3,long long>;
        using llmat3x3 = mat<3,3,long long>;
        using llmat4x3 = mat<4,3,long long>;
        using llmat2x4 = mat<2,4,long long>;
        using llmat3x4 = mat<3,4,long long>;
        using llmat4x4 = mat<4,4,long long>;
        using llmat2 = llmat2x2;
        using llmat3 = llmat3x3;
        using llmat4 = llmat4x4;
        template <unsigned int D> using ullvec = vec<D,unsigned long long>;
        template <unsigned int W, unsigned int H> using ullmat = mat<W,H,unsigned long long>;
        using ullvec2 = vec<2,unsigned long long>;
        using ullvec3 = vec<3,unsigned long long>;
        using ullvec4 = vec<4,unsigned long long>;
        using ullmat2x2 = mat<2,2,unsigned long long>;
        using ullmat3x2 = mat<3,2,unsigned long long>;
        using ullmat4x2 = mat<4,2,unsigned long long>;
        using ullmat2x3 = mat<2,3,unsigned long long>;
        using ullmat3x3 = mat<3,3,unsigned long long>;
        using ullmat4x3 = mat<4,3,unsigned long long>;
        using ullmat2x4 = mat<2,4,unsigned long long>;
        using ullmat3x4 = mat<3,4,unsigned long long>;
        using ullmat4x4 = mat<4,4,unsigned long long>;
        using ullmat2 = ullmat2x2;
        using ullmat3 = ullmat3x3;
        using ullmat4 = ullmat4x4;
        template <unsigned int D> using fvec = vec<D,float>;
        template <unsigned int W, unsigned int H> using fmat = mat<W,H,float>;
        using fvec2 = vec<2,float>;
        using fvec3 = vec<3,float>;
        using fvec4 = vec<4,float>;
        using fmat2x2 = mat<2,2,float>;
        using fmat3x2 = mat<3,2,float>;
        using fmat4x2 = mat<4,2,float>;
        using fmat2x3 = mat<2,3,float>;
        using fmat3x3 = mat<3,3,float>;
        using fmat4x3 = mat<4,3,float>;
        using fmat2x4 = mat<2,4,float>;
        using fmat3x4 = mat<3,4,float>;
        using fmat4x4 = mat<4,4,float>;
        using fmat2 = fmat2x2;
        using fmat3 = fmat3x3;
        using fmat4 = fmat4x4;
        template <unsigned int D> using dvec = vec<D,double>;
        template <unsigned int W, unsigned int H> using dmat = mat<W,H,double>;
        using dvec2 = vec<2,double>;
        using dvec3 = vec<3,double>;
        using dvec4 = vec<4,double>;
        using dmat2x2 = mat<2,2,double>;
        using dmat3x2 = mat<3,2,double>;
        using dmat4x2 = mat<4,2,double>;
        using dmat2x3 = mat<2,3,double>;
        using dmat3x3 = mat<3,3,double>;
        using dmat4x3 = mat<4,3,double>;
        using dmat2x4 = mat<2,4,double>;
        using dmat3x4 = mat<3,4,double>;
        using dmat4x4 = mat<4,4,double>;
        using dmat2 = dmat2x2;
        using dmat3 = dmat3x3;
        using dmat4 = dmat4x4;
        template <unsigned int D> using ldvec = vec<D,long double>;
        template <unsigned int W, unsigned int H> using ldmat = mat<W,H,long double>;
        using ldvec2 = vec<2,long double>;
        using ldvec3 = vec<3,long double>;
        using ldvec4 = vec<4,long double>;
        using ldmat2x2 = mat<2,2,long double>;
        using ldmat3x2 = mat<3,2,long double>;
        using ldmat4x2 = mat<4,2,long double>;
        using ldmat2x3 = mat<2,3,long double>;
        using ldmat3x3 = mat<3,3,long double>;
        using ldmat4x3 = mat<4,3,long double>;
        using ldmat2x4 = mat<2,4,long double>;
        using ldmat3x4 = mat<3,4,long double>;
        using ldmat4x4 = mat<4,4,long double>;
        using ldmat2 = ldmat2x2;
        using ldmat3 = ldmat3x3;
        using ldmat4 = ldmat4x4;
        template <unsigned int D> using i8vec = vec<D,int8_t>;
        template <unsigned int W, unsigned int H> using i8mat = mat<W,H,int8_t>;
        using i8vec2 = vec<2,int8_t>;
        using i8vec3 = vec<3,int8_t>;
        using i8vec4 = vec<4,int8_t>;
        using i8mat2x2 = mat<2,2,int8_t>;
        using i8mat3x2 = mat<3,2,int8_t>;
        using i8mat4x2 = mat<4,2,int8_t>;
        using i8mat2x3 = mat<2,3,int8_t>;
        using i8mat3x3 = mat<3,3,int8_t>;
        using i8mat4x3 = mat<4,3,int8_t>;
        using i8mat2x4 = mat<2,4,int8_t>;
        using i8mat3x4 = mat<3,4,int8_t>;
        using i8mat4x4 = mat<4,4,int8_t>;
        using i8mat2 = i8mat2x2;
        using i8mat3 = i8mat3x3;
        using i8mat4 = i8mat4x4;
        template <unsigned int D> using u8vec = vec<D,uint8_t>;
        template <unsigned int W, unsigned int H> using u8mat = mat<W,H,uint8_t>;
        using u8vec2 = vec<2,uint8_t>;
        using u8vec3 = vec<3,uint8_t>;
        using u8vec4 = vec<4,uint8_t>;
        using u8mat2x2 = mat<2,2,uint8_t>;
        using u8mat3x2 = mat<3,2,uint8_t>;
        using u8mat4x2 = mat<4,2,uint8_t>;
        using u8mat2x3 = mat<2,3,uint8_t>;
        using u8mat3x3 = mat<3,3,uint8_t>;
        using u8mat4x3 = mat<4,3,uint8_t>;
        using u8mat2x4 = mat<2,4,uint8_t>;
        using u8mat3x4 = mat<3,4,uint8_t>;
        using u8mat4x4 = mat<4,4,uint8_t>;
        using u8mat2 = u8mat2x2;
        using u8mat3 = u8mat3x3;
        using u8mat4 = u8mat4x4;
        template <unsigned int D> using i16vec = vec<D,int16_t>;
        template <unsigned int W, unsigned int H> using i16mat = mat<W,H,int16_t>;
        using i16vec2 = vec<2,int16_t>;
        using i16vec3 = vec<3,int16_t>;
        using i16vec4 = vec<4,int16_t>;
        using i16mat2x2 = mat<2,2,int16_t>;
        using i16mat3x2 = mat<3,2,int16_t>;
        using i16mat4x2 = mat<4,2,int16_t>;
        using i16mat2x3 = mat<2,3,int16_t>;
        using i16mat3x3 = mat<3,3,int16_t>;
        using i16mat4x3 = mat<4,3,int16_t>;
        using i16mat2x4 = mat<2,4,int16_t>;
        using i16mat3x4 = mat<3,4,int16_t>;
        using i16mat4x4 = mat<4,4,int16_t>;
        using i16mat2 = i16mat2x2;
        using i16mat3 = i16mat3x3;
        using i16mat4 = i16mat4x4;
        template <unsigned int D> using u16vec = vec<D,uint16_t>;
        template <unsigned int W, unsigned int H> using u16mat = mat<W,H,uint16_t>;
        using u16vec2 = vec<2,uint16_t>;
        using u16vec3 = vec<3,uint16_t>;
        using u16vec4 = vec<4,uint16_t>;
        using u16mat2x2 = mat<2,2,uint16_t>;
        using u16mat3x2 = mat<3,2,uint16_t>;
        using u16mat4x2 = mat<4,2,uint16_t>;
        using u16mat2x3 = mat<2,3,uint16_t>;
        using u16mat3x3 = mat<3,3,uint16_t>;
        using u16mat4x3 = mat<4,3,uint16_t>;
        using u16mat2x4 = mat<2,4,uint16_t>;
        using u16mat3x4 = mat<3,4,uint16_t>;
        using u16mat4x4 = mat<4,4,uint16_t>;
        using u16mat2 = u16mat2x2;
        using u16mat3 = u16mat3x3;
        using u16mat4 = u16mat4x4;
        template <unsigned int D> using i32vec = vec<D,int32_t>;
        template <unsigned int W, unsigned int H> using i32mat = mat<W,H,int32_t>;
        using i32vec2 = vec<2,int32_t>;
        using i32vec3 = vec<3,int32_t>;
        using i32vec4 = vec<4,int32_t>;
        using i32mat2x2 = mat<2,2,int32_t>;
        using i32mat3x2 = mat<3,2,int32_t>;
        using i32mat4x2 = mat<4,2,int32_t>;
        using i32mat2x3 = mat<2,3,int32_t>;
        using i32mat3x3 = mat<3,3,int32_t>;
        using i32mat4x3 = mat<4,3,int32_t>;
        using i32mat2x4 = mat<2,4,int32_t>;
        using i32mat3x4 = mat<3,4,int32_t>;
        using i32mat4x4 = mat<4,4,int32_t>;
        using i32mat2 = i32mat2x2;
        using i32mat3 = i32mat3x3;
        using i32mat4 = i32mat4x4;
        template <unsigned int D> using u32vec = vec<D,uint32_t>;
        template <unsigned int W, unsigned int H> using u32mat = mat<W,H,uint32_t>;
        using u32vec2 = vec<2,uint32_t>;
        using u32vec3 = vec<3,uint32_t>;
        using u32vec4 = vec<4,uint32_t>;
        using u32mat2x2 = mat<2,2,uint32_t>;
        using u32mat3x2 = mat<3,2,uint32_t>;
        using u32mat4x2 = mat<4,2,uint32_t>;
        using u32mat2x3 = mat<2,3,uint32_t>;
        using u32mat3x3 = mat<3,3,uint32_t>;
        using u32mat4x3 = mat<4,3,uint32_t>;
        using u32mat2x4 = mat<2,4,uint32_t>;
        using u32mat3x4 = mat<3,4,uint32_t>;
        using u32mat4x4 = mat<4,4,uint32_t>;
        using u32mat2 = u32mat2x2;
        using u32mat3 = u32mat3x3;
        using u32mat4 = u32mat4x4;
        template <unsigned int D> using i64vec = vec<D,int64_t>;
        template <unsigned int W, unsigned int H> using i64mat = mat<W,H,int64_t>;
        using i64vec2 = vec<2,int64_t>;
        using i64vec3 = vec<3,int64_t>;
        using i64vec4 = vec<4,int64_t>;
        using i64mat2x2 = mat<2,2,int64_t>;
        using i64mat3x2 = mat<3,2,int64_t>;
        using i64mat4x2 = mat<4,2,int64_t>;
        using i64mat2x3 = mat<2,3,int64_t>;
        using i64mat3x3 = mat<3,3,int64_t>;
        using i64mat4x3 = mat<4,3,int64_t>;
        using i64mat2x4 = mat<2,4,int64_t>;
        using i64mat3x4 = mat<3,4,int64_t>;
        using i64mat4x4 = mat<4,4,int64_t>;
        using i64mat2 = i64mat2x2;
        using i64mat3 = i64mat3x3;
        using i64mat4 = i64mat4x4;
        template <unsigned int D> using u64vec = vec<D,uint64_t>;
        template <unsigned int W, unsigned int H> using u64mat = mat<W,H,uint64_t>;
        using u64vec2 = vec<2,uint64_t>;
        using u64vec3 = vec<3,uint64_t>;
        using u64vec4 = vec<4,uint64_t>;
        using u64mat2x2 = mat<2,2,uint64_t>;
        using u64mat3x2 = mat<3,2,uint64_t>;
        using u64mat4x2 = mat<4,2,uint64_t>;
        using u64mat2x3 = mat<2,3,uint64_t>;
        using u64mat3x3 = mat<3,3,uint64_t>;
        using u64mat4x3 = mat<4,3,uint64_t>;
        using u64mat2x4 = mat<2,4,uint64_t>;
        using u64mat3x4 = mat<3,4,uint64_t>;
        using u64mat4x4 = mat<4,4,uint64_t>;
        using u64mat2 = u64mat2x2;
        using u64mat3 = u64mat3x3;
        using u64mat4 = u64mat4x4;

        template <typename T> struct vec<2,T> // vec2
        {
            static constexpr int size = 2;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = std::is_floating_point<type>::value;union {T x,r,s;};
            union {T y,g,t;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py) : x(px), y(py) {}
            constexpr vec(type obj) : x(obj), y(obj) {}
            template <typename TT> constexpr vec(vec2<TT> obj) : x(obj.x), y(obj.y) {}
            constexpr auto sum() const {return x + y;}
            constexpr auto product() const {return x * y;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec2<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec2<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y};}
            constexpr vec change_r(type o) const {return {o, y};}
            constexpr vec change_s(type o) const {return {o, y};}
            constexpr vec change_y(type o) const {return {x, o};}
            constexpr vec change_g(type o) const {return {x, o};}
            constexpr vec change_t(type o) const {return {x, o};}
            constexpr vec3<type> to_vec3() const {return {x, y, type{}};}
            constexpr vec4<type> to_vec4() const {return {x, y, type{}, type{}};}
            constexpr auto len_sqr() const {return x*x + y*y;}
            constexpr auto len() const {return std::sqrt(len_sqr());}
            template <typename TT> constexpr auto dot(const vec2<TT> &o) const {return x*o.x + y*o.y;}
            template <typename TT> constexpr auto cross(const vec2<TT> &o) const -> decltype(x * o.y - y * o.x) {return x * o.y - y * o.x;}
            constexpr decltype(std::sqrt(x/y)) ratio() const {return decltype(std::sqrt(x/y))(x) / decltype(std::sqrt(x/y))(y);}
            constexpr auto norm() const -> vec2<decltype(type{}/len())> {auto l = len(); if (l == 0) return {0}; else return *this / l;}
            template <typename TT> vec2<decltype(std::declval<TT>()(x))> apply(TT *func) const {return {func(x), func(y)};}
            constexpr bool none() const {return !(x || y);}
            constexpr bool any() const {return x || y;}
            constexpr bool each() const {return x && y;}
            template <typename TT> constexpr decltype(T{}*TT{}+T{}*TT{}) mul(const vec2<TT> &o) const {return {x*o.x+y*o.y};}
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{})> mul(const mat2x2<TT> &o) const {return {x*o.x.x+y*o.x.y, x*o.y.x+y*o.y.y};}
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{})> mul(const mat3x2<TT> &o) const {return {x*o.x.x+y*o.x.y, x*o.y.x+y*o.y.y, x*o.z.x+y*o.z.y};}
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{})> mul(const mat4x2<TT> &o) const {return {x*o.x.x+y*o.x.y, x*o.y.x+y*o.y.y, x*o.z.x+y*o.z.y, x*o.w.x+y*o.w.y};}
        };
        template <typename T> struct vec<3,T> // vec3
        {
            static constexpr int size = 3;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = std::is_floating_point<type>::value;union {T x,r,s;};
            union {T y,g,t;};
            union {T z,b,p;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz) : x(px), y(py), z(pz) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj) {}
            template <typename TT> constexpr vec(vec3<TT> obj) : x(obj.x), y(obj.y), z(obj.z) {}
            constexpr auto sum() const {return x + y + z;}
            constexpr auto product() const {return x * y * z;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec3<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec3<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z};}
            constexpr vec change_r(type o) const {return {o, y, z};}
            constexpr vec change_s(type o) const {return {o, y, z};}
            constexpr vec change_y(type o) const {return {x, o, z};}
            constexpr vec change_g(type o) const {return {x, o, z};}
            constexpr vec change_t(type o) const {return {x, o, z};}
            constexpr vec change_z(type o) const {return {x, y, o};}
            constexpr vec change_b(type o) const {return {x, y, o};}
            constexpr vec change_p(type o) const {return {x, y, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec4<type> to_vec4() const {return {x, y, z, type{}};}
            constexpr auto len_sqr() const {return x*x + y*y + z*z;}
            constexpr auto len() const {return std::sqrt(len_sqr());}
            template <typename TT> constexpr auto dot(const vec3<TT> &o) const {return x*o.x + y*o.y + z*o.z;}
            template <typename TT> constexpr auto cross(const vec3<TT> &o) const -> vec3<decltype(y * o.z - z * o.y)> {return {y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x};}
            constexpr auto norm() const -> vec3<decltype(type{}/len())> {auto l = len(); if (l == 0) return {0}; else return *this / l;}
            template <typename TT> vec3<decltype(std::declval<TT>()(x))> apply(TT *func) const {return {func(x), func(y), func(z)};}
            constexpr bool none() const {return !(x || y || z);}
            constexpr bool any() const {return x || y || z;}
            constexpr bool each() const {return x && y && z;}
            template <typename TT> constexpr decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}) mul(const vec3<TT> &o) const {return {x*o.x+y*o.y+z*o.z};}
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x3<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z, x*o.y.x+y*o.y.y+z*o.y.z};}
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x3<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z, x*o.y.x+y*o.y.y+z*o.y.z, x*o.z.x+y*o.z.y+z*o.z.z};}
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x3<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z, x*o.y.x+y*o.y.y+z*o.y.z, x*o.z.x+y*o.z.y+z*o.z.z, x*o.w.x+y*o.w.y+z*o.w.z};}
        };
        template <typename T> struct vec<4,T> // vec4
        {
            static constexpr int size = 4;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = std::is_floating_point<type>::value;union {T x,r,s;};
            union {T y,g,t;};
            union {T z,b,p;};
            union {T w,a,q;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z || (bool)w;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz, decltype(x) pw) : x(px), y(py), z(pz), w(pw) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj), w(obj) {}
            template <typename TT> constexpr vec(vec4<TT> obj) : x(obj.x), y(obj.y), z(obj.z), w(obj.w) {}
            constexpr auto sum() const {return x + y + z + w;}
            constexpr auto product() const {return x * y * z * w;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec4<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec4<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z, w};}
            constexpr vec change_r(type o) const {return {o, y, z, w};}
            constexpr vec change_s(type o) const {return {o, y, z, w};}
            constexpr vec change_y(type o) const {return {x, o, z, w};}
            constexpr vec change_g(type o) const {return {x, o, z, w};}
            constexpr vec change_t(type o) const {return {x, o, z, w};}
            constexpr vec change_z(type o) const {return {x, y, o, w};}
            constexpr vec change_b(type o) const {return {x, y, o, w};}
            constexpr vec change_p(type o) const {return {x, y, o, w};}
            constexpr vec change_w(type o) const {return {x, y, z, o};}
            constexpr vec change_a(type o) const {return {x, y, z, o};}
            constexpr vec change_q(type o) const {return {x, y, z, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec3<type> to_vec3() const {return {x, y, z};}
            constexpr auto len_sqr() const {return x*x + y*y + z*z + w*w;}
            constexpr auto len() const {return std::sqrt(len_sqr());}
            template <typename TT> constexpr auto dot(const vec4<TT> &o) const {return x*o.x + y*o.y + z*o.z + w*o.w;}
            constexpr auto norm() const -> vec4<decltype(type{}/len())> {auto l = len(); if (l == 0) return {0}; else return *this / l;}
            template <typename TT> vec4<decltype(std::declval<TT>()(x))> apply(TT *func) const {return {func(x), func(y), func(z), func(w)};}
            constexpr bool none() const {return !(x || y || z || w);}
            constexpr bool any() const {return x || y || z || w;}
            constexpr bool each() const {return x && y && z && w;}
            template <typename TT> constexpr decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{}) mul(const vec4<TT> &o) const {return {x*o.x+y*o.y+z*o.z+w*o.w};}
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x4<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z+w*o.x.w, x*o.y.x+y*o.y.y+z*o.y.z+w*o.y.w};}
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x4<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z+w*o.x.w, x*o.y.x+y*o.y.y+z*o.y.z+w*o.y.w, x*o.z.x+y*o.z.y+z*o.z.z+w*o.z.w};}
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x4<TT> &o) const {return {x*o.x.x+y*o.x.y+z*o.x.z+w*o.x.w, x*o.y.x+y*o.y.y+z*o.y.z+w*o.y.w, x*o.z.x+y*o.z.y+z*o.z.z+w*o.z.w, x*o.w.x+y*o.w.y+z*o.w.z+w*o.w.w};}
        };
        template <typename T> struct vec<2,vec<2,T>> // mat2x2
        {
            static constexpr int width = 2, height = 2;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec2<T>::is_floating_point;union {vec2<T> x,r,s;};
            union {vec2<T> y,g,t;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py) : x(px), y(py) {}
            constexpr vec(type obj) : x(obj), y(obj) {}
            template <typename TT> constexpr vec(vec2<TT> obj) : x(obj.x), y(obj.y) {}
            constexpr auto sum() const {return x + y;}
            constexpr auto product() const {return x * y;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec2<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec2<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y};}
            constexpr vec change_r(type o) const {return {o, y};}
            constexpr vec change_s(type o) const {return {o, y};}
            constexpr vec change_y(type o) const {return {x, o};}
            constexpr vec change_g(type o) const {return {x, o};}
            constexpr vec change_t(type o) const {return {x, o};}
            constexpr vec3<type> to_vec3() const {return {x, y, type{}};}
            constexpr vec4<type> to_vec4() const {return {x, y, type{}, type{}};}
            constexpr vec(type xx, type xy, type yx, type yy) : x(xx,xy), y(yx,yy) {}
            constexpr mat2x2<type> transpose() const {return {x.x,y.x,x.y,y.y};}
            static constexpr vec identity() {return {1, 0, 0, 1};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, v.y};}
            static constexpr vec ortho2D(const vec2<type> &sz)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                return {2 / sz.x, 0,
                        0, 2 / sz.y};
            }
            static constexpr vec rotate2D(type angle)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                type c = std::cos(angle);
                type s = std::sin(angle);
                return {c, s,
                        -s, c};
            }
            static constexpr vec scale2D(const vec2<type> &v)
            {
                return {v.x, 0,
                        0, v.y};
            }
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,0,0};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,0,0,0,0};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,0,y.x,y.y,0};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,0,y.x,y.y,0,0,0,1};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,0,y.x,y.y,0,0,0,1,0,0,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,0,0,1,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,0,0,1,0,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat2x2<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || y.x || y.y);}
            constexpr bool any() const {return x.x || x.y || y.x || y.y;}
            constexpr bool each() const {return x.x && x.y && y.x && y.y;}
            constexpr mat2<type> inverse() const
            {
                mat2<type> inv;
                inv.x.x =  y.y;
                inv.y.x = -y.x;
                inv.x.y = -x.y;
                inv.y.y =  x.x;
                type det = x.x * inv.x.x + x.y * inv.y.x;
                if (det == 0)
                    return mat2<type>::identity();
                det = 1.0f / det;
                return inv * det;
            }
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{})> mul(const vec2<TT> &o) const {return {x.x*o.x+y.x*o.y, x.y*o.x+y.y*o.y};}
            template <typename TT> constexpr mat2x2<decltype(T{}*TT{}+T{}*TT{})> mul(const mat2x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y};}
            template <typename TT> constexpr mat3x2<decltype(T{}*TT{}+T{}*TT{})> mul(const mat3x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y};}
            template <typename TT> constexpr mat4x2<decltype(T{}*TT{}+T{}*TT{})> mul(const mat4x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y, x.x*o.w.x+y.x*o.w.y, x.y*o.w.x+y.y*o.w.y};}
        };
        template <typename T> struct vec<3,vec<2,T>> // mat3x2
        {
            static constexpr int width = 3, height = 2;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec2<T>::is_floating_point;union {vec2<T> x,r,s;};
            union {vec2<T> y,g,t;};
            union {vec2<T> z,b,p;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz) : x(px), y(py), z(pz) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj) {}
            template <typename TT> constexpr vec(vec3<TT> obj) : x(obj.x), y(obj.y), z(obj.z) {}
            constexpr auto sum() const {return x + y + z;}
            constexpr auto product() const {return x * y * z;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec3<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec3<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z};}
            constexpr vec change_r(type o) const {return {o, y, z};}
            constexpr vec change_s(type o) const {return {o, y, z};}
            constexpr vec change_y(type o) const {return {x, o, z};}
            constexpr vec change_g(type o) const {return {x, o, z};}
            constexpr vec change_t(type o) const {return {x, o, z};}
            constexpr vec change_z(type o) const {return {x, y, o};}
            constexpr vec change_b(type o) const {return {x, y, o};}
            constexpr vec change_p(type o) const {return {x, y, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec4<type> to_vec4() const {return {x, y, z, type{}};}
            constexpr vec(type xx, type xy, type yx, type yy, type zx, type zy) : x(xx,xy), y(yx,yy), z(zx,zy) {}
            constexpr mat2x3<type> transpose() const {return {x.x,y.x,z.x,x.y,y.y,z.y};}
            static constexpr vec identity() {return {1, 0, 0, 1, 0, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, v.y, 0, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat3x2();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                return {2 / (max.x - min.x), 0,
                        0, 2 / (max.y - min.y),
                        (min.x + max.x) / (min.x - max.x), (min.y + max.y) / (min.y - max.y)};
            }
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat3x2();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat3x2();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y,0,0};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,0,y.x,y.y,0};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,0,y.x,y.y,0,z.x,z.y,1};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,0,y.x,y.y,0,z.x,z.y,1,0,0,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,z.x,z.y,1,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,z.x,z.y,1,0,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat3x2<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || y.x || y.y || z.x || z.y);}
            constexpr bool any() const {return x.x || x.y || y.x || y.y || z.x || z.y;}
            constexpr bool each() const {return x.x && x.y && y.x && y.y && z.x && z.y;}
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec3<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z, x.y*o.x+y.y*o.y+z.y*o.z};}
            template <typename TT> constexpr mat2x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z};}
            template <typename TT> constexpr mat3x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z};}
            template <typename TT> constexpr mat4x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z};}
        };
        template <typename T> struct vec<4,vec<2,T>> // mat4x2
        {
            static constexpr int width = 4, height = 2;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec2<T>::is_floating_point;union {vec2<T> x,r,s;};
            union {vec2<T> y,g,t;};
            union {vec2<T> z,b,p;};
            union {vec2<T> w,a,q;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z || (bool)w;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz, decltype(x) pw) : x(px), y(py), z(pz), w(pw) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj), w(obj) {}
            template <typename TT> constexpr vec(vec4<TT> obj) : x(obj.x), y(obj.y), z(obj.z), w(obj.w) {}
            constexpr auto sum() const {return x + y + z + w;}
            constexpr auto product() const {return x * y * z * w;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec4<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec4<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z, w};}
            constexpr vec change_r(type o) const {return {o, y, z, w};}
            constexpr vec change_s(type o) const {return {o, y, z, w};}
            constexpr vec change_y(type o) const {return {x, o, z, w};}
            constexpr vec change_g(type o) const {return {x, o, z, w};}
            constexpr vec change_t(type o) const {return {x, o, z, w};}
            constexpr vec change_z(type o) const {return {x, y, o, w};}
            constexpr vec change_b(type o) const {return {x, y, o, w};}
            constexpr vec change_p(type o) const {return {x, y, o, w};}
            constexpr vec change_w(type o) const {return {x, y, z, o};}
            constexpr vec change_a(type o) const {return {x, y, z, o};}
            constexpr vec change_q(type o) const {return {x, y, z, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec3<type> to_vec3() const {return {x, y, z};}
            constexpr vec(type xx, type xy, type yx, type yy, type zx, type zy, type wx, type wy) : x(xx,xy), y(yx,yy), z(zx,zy), w(wx,wy) {}
            constexpr mat2x4<type> transpose() const {return {x.x,y.x,z.x,w.x,x.y,y.y,z.y,w.y};}
            static constexpr vec identity() {return {1, 0, 0, 1, 0, 0, 0, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, v.y, 0, 0, 0, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat4x2();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max) {return mat3x2<type>::ortho2D(min, max).to_mat4x2();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat4x2();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat4x2();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,0,y.x,y.y,0};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,0,y.x,y.y,0,z.x,z.y,1};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,0,y.x,y.y,0,z.x,z.y,1,w.x,w.y,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,z.x,z.y,1,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,0,0,y.x,y.y,0,0,z.x,z.y,1,0,w.x,w.y,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat4x2<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func), w.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || y.x || y.y || z.x || z.y || w.x || w.y);}
            constexpr bool any() const {return x.x || x.y || y.x || y.y || z.x || z.y || w.x || w.y;}
            constexpr bool each() const {return x.x && x.y && y.x && y.y && z.x && z.y && w.x && w.y;}
            template <typename TT> constexpr vec2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec4<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z+w.x*o.w, x.y*o.x+y.y*o.y+z.y*o.z+w.y*o.w};}
            template <typename TT> constexpr mat2x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w};}
            template <typename TT> constexpr mat3x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w};}
            template <typename TT> constexpr mat4x2<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z+w.x*o.w.w, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z+w.y*o.w.w};}
        };
        template <typename T> struct vec<2,vec<3,T>> // mat2x3
        {
            static constexpr int width = 2, height = 3;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec3<T>::is_floating_point;union {vec3<T> x,r,s;};
            union {vec3<T> y,g,t;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py) : x(px), y(py) {}
            constexpr vec(type obj) : x(obj), y(obj) {}
            template <typename TT> constexpr vec(vec2<TT> obj) : x(obj.x), y(obj.y) {}
            constexpr auto sum() const {return x + y;}
            constexpr auto product() const {return x * y;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec2<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec2<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y};}
            constexpr vec change_r(type o) const {return {o, y};}
            constexpr vec change_s(type o) const {return {o, y};}
            constexpr vec change_y(type o) const {return {x, o};}
            constexpr vec change_g(type o) const {return {x, o};}
            constexpr vec change_t(type o) const {return {x, o};}
            constexpr vec3<type> to_vec3() const {return {x, y, type{}};}
            constexpr vec4<type> to_vec4() const {return {x, y, type{}, type{}};}
            constexpr vec(type xx, type xy, type xz, type yx, type yy, type yz) : x(xx,xy,xz), y(yx,yy,yz) {}
            constexpr mat3x2<type> transpose() const {return {x.x,y.x,x.y,y.y,x.z,y.z};}
            static constexpr vec identity() {return {1, 0, 0, 0, 1, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, v.y, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat2x3();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat2x3();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat2x3();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,0,0};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,0,0,0,0};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,0,0,1};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,0,0,1,0,0,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,0,0,1,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,0,0,1,0,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat2x3<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || y.x || y.y || y.z);}
            constexpr bool any() const {return x.x || x.y || x.z || y.x || y.y || y.z;}
            constexpr bool each() const {return x.x && x.y && x.z && y.x && y.y && y.z;}
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{})> mul(const vec2<TT> &o) const {return {x.x*o.x+y.x*o.y, x.y*o.x+y.y*o.y, x.z*o.x+y.z*o.y};}
            template <typename TT> constexpr mat2x3<decltype(T{}*TT{}+T{}*TT{})> mul(const mat2x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y};}
            template <typename TT> constexpr mat3x3<decltype(T{}*TT{}+T{}*TT{})> mul(const mat3x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y, x.z*o.z.x+y.z*o.z.y};}
            template <typename TT> constexpr mat4x3<decltype(T{}*TT{}+T{}*TT{})> mul(const mat4x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y, x.z*o.z.x+y.z*o.z.y, x.x*o.w.x+y.x*o.w.y, x.y*o.w.x+y.y*o.w.y, x.z*o.w.x+y.z*o.w.y};}
        };
        template <typename T> struct vec<3,vec<3,T>> // mat3x3
        {
            static constexpr int width = 3, height = 3;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec3<T>::is_floating_point;union {vec3<T> x,r,s;};
            union {vec3<T> y,g,t;};
            union {vec3<T> z,b,p;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz) : x(px), y(py), z(pz) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj) {}
            template <typename TT> constexpr vec(vec3<TT> obj) : x(obj.x), y(obj.y), z(obj.z) {}
            constexpr auto sum() const {return x + y + z;}
            constexpr auto product() const {return x * y * z;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec3<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec3<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z};}
            constexpr vec change_r(type o) const {return {o, y, z};}
            constexpr vec change_s(type o) const {return {o, y, z};}
            constexpr vec change_y(type o) const {return {x, o, z};}
            constexpr vec change_g(type o) const {return {x, o, z};}
            constexpr vec change_t(type o) const {return {x, o, z};}
            constexpr vec change_z(type o) const {return {x, y, o};}
            constexpr vec change_b(type o) const {return {x, y, o};}
            constexpr vec change_p(type o) const {return {x, y, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec4<type> to_vec4() const {return {x, y, z, type{}};}
            constexpr vec(type xx, type xy, type xz, type yx, type yy, type yz, type zx, type zy, type zz) : x(xx,xy,xz), y(yx,yy,yz), z(zx,zy,zz) {}
            constexpr mat3x3<type> transpose() const {return {x.x,y.x,z.x,x.y,y.y,z.y,x.z,y.z,z.z};}
            static constexpr vec identity() {return {1, 0, 0, 0, 1, 0, 0, 0, 1};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, v.y, 0, 0, 0, 1};}
            static constexpr vec dia(const vec3<type> &v) {return {v.x, 0, 0, 0, v.y, 0, 0, 0, v.z};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat3x3();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max) {return mat3x2<type>::ortho2D(min, max).to_mat3x3();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat3x3();}
            static constexpr vec rotate_with_normalized_axis(const vec3<type> &in, type angle)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                type c = std::cos(angle);
                type s = std::sin(angle);
                return {in.x * in.x * (1 - c) + c, in.y * in.x * (1 - c) + in.z * s, in.x * in.z * (1 - c) - in.y * s,
                        in.x * in.y * (1 - c) - in.z * s, in.y * in.y * (1 - c) + c, in.y * in.z * (1 - c) + in.x * s,
                        in.x * in.z * (1 - c) + in.y * s, in.y * in.z * (1 - c) - in.x * s, in.z * in.z * (1 - c) + c};
            }
            static constexpr vec rotate(const vec3<type> &in, type angle)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                return rotate_with_normalized_axis(in.norm(), angle);
            }
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat3x3();}
            static constexpr vec scale(const vec3<type> &v)
            {
                return {v.x, 0, 0,
                        0, v.y, 0,
                        0, 0, v.z};
            }
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y,0,0};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z};}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z,0,0,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,z.x,z.y,z.z,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,z.x,z.y,z.z,0,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat3x3<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || y.x || y.y || y.z || z.x || z.y || z.z);}
            constexpr bool any() const {return x.x || x.y || x.z || y.x || y.y || y.z || z.x || z.y || z.z;}
            constexpr bool each() const {return x.x && x.y && x.z && y.x && y.y && y.z && z.x && z.y && z.z;}
            constexpr mat3<type> inverse() const
            {
                mat3<type> inv;
                inv.x.x =  y.y * z.z -
                           z.y * y.z;
                inv.y.x = -y.x * z.z +
                           z.x * y.z;
                inv.z.x =  y.x * z.y -
                           z.x * y.y;
                inv.x.y = -x.y * z.z +
                           z.y * x.z;
                inv.y.y =  x.x * z.z -
                           z.x * x.z;
                inv.z.y = -x.x * z.y +
                           z.x * x.y;
                inv.x.z =  x.y * y.z -
                           y.y * x.z;
                inv.y.z = -x.x * y.z +
                           y.x * x.z;
                inv.z.z =  x.x * y.y -
                           y.x * x.y;
                type det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x;
                if (det == 0)
                    return mat3<type>::identity();
                det = 1.0f / det;
                return inv * det;
            }
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec3<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z, x.y*o.x+y.y*o.y+z.y*o.z, x.z*o.x+y.z*o.y+z.z*o.z};}
            template <typename TT> constexpr mat2x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z};}
            template <typename TT> constexpr mat3x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z};}
            template <typename TT> constexpr mat4x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z, x.z*o.w.x+y.z*o.w.y+z.z*o.w.z};}
        };
        template <typename T> struct vec<4,vec<3,T>> // mat4x3
        {
            static constexpr int width = 4, height = 3;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec3<T>::is_floating_point;union {vec3<T> x,r,s;};
            union {vec3<T> y,g,t;};
            union {vec3<T> z,b,p;};
            union {vec3<T> w,a,q;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z || (bool)w;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz, decltype(x) pw) : x(px), y(py), z(pz), w(pw) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj), w(obj) {}
            template <typename TT> constexpr vec(vec4<TT> obj) : x(obj.x), y(obj.y), z(obj.z), w(obj.w) {}
            constexpr auto sum() const {return x + y + z + w;}
            constexpr auto product() const {return x * y * z * w;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec4<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec4<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z, w};}
            constexpr vec change_r(type o) const {return {o, y, z, w};}
            constexpr vec change_s(type o) const {return {o, y, z, w};}
            constexpr vec change_y(type o) const {return {x, o, z, w};}
            constexpr vec change_g(type o) const {return {x, o, z, w};}
            constexpr vec change_t(type o) const {return {x, o, z, w};}
            constexpr vec change_z(type o) const {return {x, y, o, w};}
            constexpr vec change_b(type o) const {return {x, y, o, w};}
            constexpr vec change_p(type o) const {return {x, y, o, w};}
            constexpr vec change_w(type o) const {return {x, y, z, o};}
            constexpr vec change_a(type o) const {return {x, y, z, o};}
            constexpr vec change_q(type o) const {return {x, y, z, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec3<type> to_vec3() const {return {x, y, z};}
            constexpr vec(type xx, type xy, type xz, type yx, type yy, type yz, type zx, type zy, type zz, type wx, type wy, type wz) : x(xx,xy,xz), y(yx,yy,yz), z(zx,zy,zz), w(wx,wy,wz) {}
            constexpr mat3x4<type> transpose() const {return {x.x,y.x,z.x,w.x,x.y,y.y,z.y,w.y,x.z,y.z,z.z,w.z};}
            static constexpr vec identity() {return {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, v.y, 0, 0, 0, 1, 0, 0, 0};}
            static constexpr vec dia(const vec3<type> &v) {return {v.x, 0, 0, 0, v.y, 0, 0, 0, v.z, 0, 0, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat4x3();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max) {return mat3x2<type>::ortho2D(min, max).to_mat4x3();}
            static constexpr vec ortho(const vec2<type> &sz, type near, type far)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                return {2 / sz.x, 0, 0,
                        0, 2 / sz.y, 0,
                        0, 0, 2 / (near - far),
                        0, 0, (near + far) / (near - far)};
            }
            static constexpr vec ortho(const vec2<type> &min, const vec2<type> &max, type near, type far)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                return {2 / (max.x - min.x), 0, 0,
                        0, 2 / (max.y - min.y), 0,
                        0, 0, 2 / (near - far),
                        (min.x + max.x) / (min.x - max.x), (min.y + max.y) / (min.y - max.y), (near + far) / (near - far)};
            }
            static constexpr vec look_at(const vec3<type> &src, const vec3<type> &dst, const vec3<type> &local_up)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                vec3<T> v3 = (src-dst).norm();
                vec3<T> v1 = local_up.cross(v3).norm();
                vec3<T> v2 = v3.cross(v1);
                return {v1.x, v2.x, v3.x,
                        v1.y, v2.y, v3.y,
                        v1.z, v2.z, v3.z,
                        -src.x*v1.x - src.y*v1.y - src.z*v1.z, -src.x*v2.x - src.y*v2.y - src.z*v2.z, -src.x*v3.x - src.y*v3.y - src.z*v3.z};
            }
            static constexpr vec translate(const vec3<type> &in)
            {
                return {1, 0, 0,
                        0, 1, 0,
                        0, 0, 1,
                        in.x, in.y, in.z};
            }
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat4x3();}
            static constexpr vec rotate_with_normalized_axis(const vec3<type> &in, type angle) {return mat3x3<type>::rotate_with_normalized_axis(in, angle).to_mat4x3();}
            static constexpr vec rotate(const vec3<type> &in, type angle) {return mat3x3<type>::rotate(in, angle).to_mat4x3();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat4x3();}
            static constexpr vec scale(const vec3<type> &v) {return mat3x3<type>::scale(v).to_mat4x3();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y,w.x,w.y};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,z.x,z.y,z.z,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,x.z,0,y.x,y.y,y.z,0,z.x,z.y,z.z,0,w.x,w.y,w.z,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat4x3<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func), w.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || y.x || y.y || y.z || z.x || z.y || z.z || w.x || w.y || w.z);}
            constexpr bool any() const {return x.x || x.y || x.z || y.x || y.y || y.z || z.x || z.y || z.z || w.x || w.y || w.z;}
            constexpr bool each() const {return x.x && x.y && x.z && y.x && y.y && y.z && z.x && z.y && z.z && w.x && w.y && w.z;}
            template <typename TT> constexpr vec3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec4<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z+w.x*o.w, x.y*o.x+y.y*o.y+z.y*o.z+w.y*o.w, x.z*o.x+y.z*o.y+z.z*o.z+w.z*o.w};}
            template <typename TT> constexpr mat2x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w};}
            template <typename TT> constexpr mat3x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z+w.z*o.z.w};}
            template <typename TT> constexpr mat4x3<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z+w.z*o.z.w, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z+w.x*o.w.w, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z+w.y*o.w.w, x.z*o.w.x+y.z*o.w.y+z.z*o.w.z+w.z*o.w.w};}
        };
        template <typename T> struct vec<2,vec<4,T>> // mat2x4
        {
            static constexpr int width = 2, height = 4;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec4<T>::is_floating_point;union {vec4<T> x,r,s;};
            union {vec4<T> y,g,t;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py) : x(px), y(py) {}
            constexpr vec(type obj) : x(obj), y(obj) {}
            template <typename TT> constexpr vec(vec2<TT> obj) : x(obj.x), y(obj.y) {}
            constexpr auto sum() const {return x + y;}
            constexpr auto product() const {return x * y;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec2<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec2<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y};}
            constexpr vec change_r(type o) const {return {o, y};}
            constexpr vec change_s(type o) const {return {o, y};}
            constexpr vec change_y(type o) const {return {x, o};}
            constexpr vec change_g(type o) const {return {x, o};}
            constexpr vec change_t(type o) const {return {x, o};}
            constexpr vec3<type> to_vec3() const {return {x, y, type{}};}
            constexpr vec4<type> to_vec4() const {return {x, y, type{}, type{}};}
            constexpr vec(type xx, type xy, type xz, type xw, type yx, type yy, type yz, type yw) : x(xx,xy,xz,xw), y(yx,yy,yz,yw) {}
            constexpr mat4x2<type> transpose() const {return {x.x,y.x,x.y,y.y,x.z,y.z,x.w,y.w};}
            static constexpr vec identity() {return {1, 0, 0, 0, 0, 1, 0, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat2x4();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat2x4();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat2x4();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,0,0};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,0,0,0,0};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,0,0,1};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,0,0,1,0,0,0};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w,0,0,1,0};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w,0,0,1,0,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat2x4<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w);}
            constexpr bool any() const {return x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w;}
            constexpr bool each() const {return x.x && x.y && x.z && x.w && y.x && y.y && y.z && y.w;}
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{})> mul(const vec2<TT> &o) const {return {x.x*o.x+y.x*o.y, x.y*o.x+y.y*o.y, x.z*o.x+y.z*o.y, x.w*o.x+y.w*o.y};}
            template <typename TT> constexpr mat2x4<decltype(T{}*TT{}+T{}*TT{})> mul(const mat2x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.w*o.x.x+y.w*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y, x.w*o.y.x+y.w*o.y.y};}
            template <typename TT> constexpr mat3x4<decltype(T{}*TT{}+T{}*TT{})> mul(const mat3x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.w*o.x.x+y.w*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y, x.w*o.y.x+y.w*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y, x.z*o.z.x+y.z*o.z.y, x.w*o.z.x+y.w*o.z.y};}
            template <typename TT> constexpr mat4x4<decltype(T{}*TT{}+T{}*TT{})> mul(const mat4x2<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y, x.y*o.x.x+y.y*o.x.y, x.z*o.x.x+y.z*o.x.y, x.w*o.x.x+y.w*o.x.y, x.x*o.y.x+y.x*o.y.y, x.y*o.y.x+y.y*o.y.y, x.z*o.y.x+y.z*o.y.y, x.w*o.y.x+y.w*o.y.y, x.x*o.z.x+y.x*o.z.y, x.y*o.z.x+y.y*o.z.y, x.z*o.z.x+y.z*o.z.y, x.w*o.z.x+y.w*o.z.y, x.x*o.w.x+y.x*o.w.y, x.y*o.w.x+y.y*o.w.y, x.z*o.w.x+y.z*o.w.y, x.w*o.w.x+y.w*o.w.y};}
        };
        template <typename T> struct vec<3,vec<4,T>> // mat3x4
        {
            static constexpr int width = 3, height = 4;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec4<T>::is_floating_point;union {vec4<T> x,r,s;};
            union {vec4<T> y,g,t;};
            union {vec4<T> z,b,p;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz) : x(px), y(py), z(pz) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj) {}
            template <typename TT> constexpr vec(vec3<TT> obj) : x(obj.x), y(obj.y), z(obj.z) {}
            constexpr auto sum() const {return x + y + z;}
            constexpr auto product() const {return x * y * z;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec3<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec3<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z};}
            constexpr vec change_r(type o) const {return {o, y, z};}
            constexpr vec change_s(type o) const {return {o, y, z};}
            constexpr vec change_y(type o) const {return {x, o, z};}
            constexpr vec change_g(type o) const {return {x, o, z};}
            constexpr vec change_t(type o) const {return {x, o, z};}
            constexpr vec change_z(type o) const {return {x, y, o};}
            constexpr vec change_b(type o) const {return {x, y, o};}
            constexpr vec change_p(type o) const {return {x, y, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec4<type> to_vec4() const {return {x, y, z, type{}};}
            constexpr vec(type xx, type xy, type xz, type xw, type yx, type yy, type yz, type yw, type zx, type zy, type zz, type zw) : x(xx,xy,xz,xw), y(yx,yy,yz,yw), z(zx,zy,zz,zw) {}
            constexpr mat4x3<type> transpose() const {return {x.x,y.x,z.x,x.y,y.y,z.y,x.z,y.z,z.z,x.w,y.w,z.w};}
            static constexpr vec identity() {return {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, 1, 0};}
            static constexpr vec dia(const vec3<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat3x4();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max) {return mat3x2<type>::ortho2D(min, max).to_mat3x4();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat3x4();}
            static constexpr vec rotate_with_normalized_axis(const vec3<type> &in, type angle) {return mat3x3<type>::rotate_with_normalized_axis(in, angle).to_mat3x4();}
            static constexpr vec rotate(const vec3<type> &in, type angle) {return mat3x3<type>::rotate(in, angle).to_mat3x4();}
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat3x4();}
            static constexpr vec scale(const vec3<type> &v) {return mat3x3<type>::scale(v).to_mat3x4();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y,0,0};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z,0,0,0};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w};}
            constexpr mat4x4<type> to_mat4x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w,z.x,z.y,z.z,z.w,0,0,0,1};}
            constexpr mat4<type> to_mat4() const {return to_mat4x4();}
            template <typename TT> mat3x4<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w || z.x || z.y || z.z || z.w);}
            constexpr bool any() const {return x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w || z.x || z.y || z.z || z.w;}
            constexpr bool each() const {return x.x && x.y && x.z && x.w && y.x && y.y && y.z && y.w && z.x && z.y && z.z && z.w;}
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec3<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z, x.y*o.x+y.y*o.y+z.y*o.z, x.z*o.x+y.z*o.y+z.z*o.z, x.w*o.x+y.w*o.y+z.w*o.z};}
            template <typename TT> constexpr mat2x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z};}
            template <typename TT> constexpr mat3x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z, x.w*o.z.x+y.w*o.z.y+z.w*o.z.z};}
            template <typename TT> constexpr mat4x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x3<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z, x.w*o.z.x+y.w*o.z.y+z.w*o.z.z, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z, x.z*o.w.x+y.z*o.w.y+z.z*o.w.z, x.w*o.w.x+y.w*o.w.y+z.w*o.w.z};}
        };
        template <typename T> struct vec<4,vec<4,T>> // mat4x4
        {
            static constexpr int width = 4, height = 4;
            using type = std::remove_reference_t<T>;
            static constexpr bool is_ref = std::is_lvalue_reference<T>::value;
            static_assert(!std::is_const<T>::value && !std::is_volatile<T>::value &&
                          !std::is_const<type>::value && !std::is_volatile<type>::value, "The vector base type must not have any cv qualifiers.");
            static_assert(!std::is_rvalue_reference<T>::value, "The vectors of rvalue references are not allowed.");
            static constexpr bool is_floating_point = vec4<T>::is_floating_point;union {vec4<T> x,r,s;};
            union {vec4<T> y,g,t;};
            union {vec4<T> z,b,p;};
            union {vec4<T> w,a,q;};
            decltype(x) &operator[](int pos) {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: static type ret; ret = type{}; return ret;}}
            constexpr decltype(x) operator[](int pos) const {switch (pos) {case 0: return x; case 1: return y; case 2: return z; case 3: return w; default: return decltype(x){};}}
            constexpr operator bool() const {return (bool)x || (bool)y || (bool)z || (bool)w;}
            constexpr vec() {}
            constexpr vec(decltype(x) px, decltype(x) py, decltype(x) pz, decltype(x) pw) : x(px), y(py), z(pz), w(pw) {}
            constexpr vec(type obj) : x(obj), y(obj), z(obj), w(obj) {}
            template <typename TT> constexpr vec(vec4<TT> obj) : x(obj.x), y(obj.y), z(obj.z), w(obj.w) {}
            constexpr auto sum() const {return x + y + z + w;}
            constexpr auto product() const {return x * y * z * w;}
            constexpr type *as_array() {return (type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            constexpr const type *as_array() const {return (const type *)&x; static_assert(!is_ref, "This function does not work for reference vectors.");}
            template <typename TT, typename TTT> constexpr vec4<decltype(type{}*(1-TTT{})+TT{}*TTT{})> interpolate(const vec4<TT> &o, TTT fac) const {return *this * (1 - fac) + o * fac;}
            constexpr vec change_x(type o) const {return {o, y, z, w};}
            constexpr vec change_r(type o) const {return {o, y, z, w};}
            constexpr vec change_s(type o) const {return {o, y, z, w};}
            constexpr vec change_y(type o) const {return {x, o, z, w};}
            constexpr vec change_g(type o) const {return {x, o, z, w};}
            constexpr vec change_t(type o) const {return {x, o, z, w};}
            constexpr vec change_z(type o) const {return {x, y, o, w};}
            constexpr vec change_b(type o) const {return {x, y, o, w};}
            constexpr vec change_p(type o) const {return {x, y, o, w};}
            constexpr vec change_w(type o) const {return {x, y, z, o};}
            constexpr vec change_a(type o) const {return {x, y, z, o};}
            constexpr vec change_q(type o) const {return {x, y, z, o};}
            constexpr vec2<type> to_vec2() const {return {x, y};}
            constexpr vec3<type> to_vec3() const {return {x, y, z};}
            constexpr vec(type xx, type xy, type xz, type xw, type yx, type yy, type yz, type yw, type zx, type zy, type zz, type zw, type wx, type wy, type wz, type ww) : x(xx,xy,xz,xw), y(yx,yy,yz,yw), z(zx,zy,zz,zw), w(wx,wy,wz,ww) {}
            constexpr mat4x4<type> transpose() const {return {x.x,y.x,z.x,w.x,x.y,y.y,z.y,w.y,x.z,y.z,z.z,w.z,x.w,y.w,z.w,w.w};}
            static constexpr vec identity() {return {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};}
            static constexpr vec dia(const vec2<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};}
            static constexpr vec dia(const vec3<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, 1};}
            static constexpr vec dia(const vec4<type> &v) {return {v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, v.w};}
            static constexpr vec ortho2D(const vec2<type> &sz) {return mat2x2<type>::ortho2D(sz).to_mat4x4();}
            static constexpr vec ortho2D(const vec2<type> &min, const vec2<type> &max) {return mat3x2<type>::ortho2D(min, max).to_mat4x4();}
            static constexpr vec ortho(const vec2<type> &sz, type near, type far) {return mat4x3<type>::ortho(sz, near, far).to_mat4x4();}
            static constexpr vec ortho(const vec2<type> &min, const vec2<type> &max, type near, type far) {return mat4x3<type>::ortho(min, max, near, far).to_mat4x4();}
            static constexpr vec look_at(const vec3<type> &src, const vec3<type> &dst, const vec3<type> &local_up) {return mat4x3<type>::look_at(src, dst, local_up).to_mat4x4();}
            static constexpr vec translate(const vec3<type> &in) {return mat4x3<type>::translate(in).to_mat4x4();}
            static constexpr vec rotate2D(type angle) {return mat2x2<type>::rotate2D(angle).to_mat4x4();}
            static constexpr vec rotate_with_normalized_axis(const vec3<type> &in, type angle) {return mat3x3<type>::rotate_with_normalized_axis(in, angle).to_mat4x4();}
            static constexpr vec rotate(const vec3<type> &in, type angle) {return mat3x3<type>::rotate(in, angle).to_mat4x4();}
            static constexpr vec perspective(type yfov, type wh_aspect, type near, type far)
            {
                static_assert(is_floating_point, "This function only makes sense for floating-point matrices.");
                yfov = (T)1 / std::tan(yfov / 2);
                return {yfov / wh_aspect , 0    , 0                             , 0  ,
                        0                , yfov , 0                             , 0  ,
                        0                , 0    , (near + far) / (near - far)   , -1 ,
                        0                , 0    , 2 * near * far / (near - far) , 0  };
            }
            static constexpr vec scale2D(const vec2<type> &v) {return mat2x2<type>::scale2D(v).to_mat4x4();}
            static constexpr vec scale(const vec3<type> &v) {return mat3x3<type>::scale(v).to_mat4x4();}
            constexpr mat2x2<type> to_mat2x2() const {return {x.x,x.y,y.x,y.y};}
            constexpr mat2<type> to_mat2() const {return to_mat2x2();}
            constexpr mat3x2<type> to_mat3x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y};}
            constexpr mat4x2<type> to_mat4x2() const {return {x.x,x.y,y.x,y.y,z.x,z.y,w.x,w.y};}
            constexpr mat2x3<type> to_mat2x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z};}
            constexpr mat3x3<type> to_mat3x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z};}
            constexpr mat3<type> to_mat3() const {return to_mat3x3();}
            constexpr mat4x3<type> to_mat4x3() const {return {x.x,x.y,x.z,y.x,y.y,y.z,z.x,z.y,z.z,w.x,w.y,w.z};}
            constexpr mat2x4<type> to_mat2x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w};}
            constexpr mat3x4<type> to_mat3x4() const {return {x.x,x.y,x.z,x.w,y.x,y.y,y.z,y.w,z.x,z.y,z.z,z.w};}
            template <typename TT> mat4x4<decltype(std::declval<TT>()(x.x))> apply(TT *func) const {return {x.apply(func), y.apply(func), z.apply(func), w.apply(func)};}
            constexpr bool none() const {return !(x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w || z.x || z.y || z.z || z.w || w.x || w.y || w.z || w.w);}
            constexpr bool any() const {return x.x || x.y || x.z || x.w || y.x || y.y || y.z || y.w || z.x || z.y || z.z || z.w || w.x || w.y || w.z || w.w;}
            constexpr bool each() const {return x.x && x.y && x.z && x.w && y.x && y.y && y.z && y.w && z.x && z.y && z.z && z.w && w.x && w.y && w.z && w.w;}
            constexpr mat4<type> inverse() const
            {
                mat4<type> inv;
                inv.x.x =  y.y * z.z * w.w -
                           y.y * z.w * w.z -
                           z.y * y.z * w.w +
                           z.y * y.w * w.z +
                           w.y * y.z * z.w -
                           w.y * y.w * z.z;
                inv.y.x = -y.x * z.z * w.w +
                           y.x * z.w * w.z +
                           z.x * y.z * w.w -
                           z.x * y.w * w.z -
                           w.x * y.z * z.w +
                           w.x * y.w * z.z;
                inv.z.x =  y.x * z.y * w.w -
                           y.x * z.w * w.y -
                           z.x * y.y * w.w +
                           z.x * y.w * w.y +
                           w.x * y.y * z.w -
                           w.x * y.w * z.y;
                inv.w.x = -y.x * z.y * w.z +
                           y.x * z.z * w.y +
                           z.x * y.y * w.z -
                           z.x * y.z * w.y -
                           w.x * y.y * z.z +
                           w.x * y.z * z.y;
                inv.x.y = -x.y * z.z * w.w +
                           x.y * z.w * w.z +
                           z.y * x.z * w.w -
                           z.y * x.w * w.z -
                           w.y * x.z * z.w +
                           w.y * x.w * z.z;
                inv.y.y =  x.x * z.z * w.w -
                           x.x * z.w * w.z -
                           z.x * x.z * w.w +
                           z.x * x.w * w.z +
                           w.x * x.z * z.w -
                           w.x * x.w * z.z;
                inv.z.y = -x.x * z.y * w.w +
                           x.x * z.w * w.y +
                           z.x * x.y * w.w -
                           z.x * x.w * w.y -
                           w.x * x.y * z.w +
                           w.x * x.w * z.y;
                inv.w.y =  x.x * z.y * w.z -
                           x.x * z.z * w.y -
                           z.x * x.y * w.z +
                           z.x * x.z * w.y +
                           w.x * x.y * z.z -
                           w.x * x.z * z.y;
                inv.x.z =  x.y * y.z * w.w -
                           x.y * y.w * w.z -
                           y.y * x.z * w.w +
                           y.y * x.w * w.z +
                           w.y * x.z * y.w -
                           w.y * x.w * y.z;
                inv.y.z = -x.x * y.z * w.w +
                           x.x * y.w * w.z +
                           y.x * x.z * w.w -
                           y.x * x.w * w.z -
                           w.x * x.z * y.w +
                           w.x * x.w * y.z;
                inv.z.z =  x.x * y.y * w.w -
                           x.x * y.w * w.y -
                           y.x * x.y * w.w +
                           y.x * x.w * w.y +
                           w.x * x.y * y.w -
                           w.x * x.w * y.y;
                inv.w.z = -x.x * y.y * w.z +
                           x.x * y.z * w.y +
                           y.x * x.y * w.z -
                           y.x * x.z * w.y -
                           w.x * x.y * y.z +
                           w.x * x.z * y.y;
                inv.x.w = -x.y * y.z * z.w +
                           x.y * y.w * z.z +
                           y.y * x.z * z.w -
                           y.y * x.w * z.z -
                           z.y * x.z * y.w +
                           z.y * x.w * y.z;
                inv.y.w =  x.x * y.z * z.w -
                           x.x * y.w * z.z -
                           y.x * x.z * z.w +
                           y.x * x.w * z.z +
                           z.x * x.z * y.w -
                           z.x * x.w * y.z;
                inv.z.w = -x.x * y.y * z.w +
                           x.x * y.w * z.y +
                           y.x * x.y * z.w -
                           y.x * x.w * z.y -
                           z.x * x.y * y.w +
                           z.x * x.w * y.y;
                inv.w.w =  x.x * y.y * z.z -
                           x.x * y.z * z.y -
                           y.x * x.y * z.z +
                           y.x * x.z * z.y +
                           z.x * x.y * y.z -
                           z.x * x.z * y.y;
                type det = x.x * inv.x.x + x.y * inv.y.x + x.z * inv.z.x + x.w * inv.w.x;
                if (det == 0)
                    return mat4<type>::identity();
                det = 1.0f / det;
                return inv * det;
            }
            template <typename TT> constexpr vec4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const vec4<TT> &o) const {return {x.x*o.x+y.x*o.y+z.x*o.z+w.x*o.w, x.y*o.x+y.y*o.y+z.y*o.z+w.y*o.w, x.z*o.x+y.z*o.y+z.z*o.z+w.z*o.w, x.w*o.x+y.w*o.y+z.w*o.z+w.w*o.w};}
            template <typename TT> constexpr mat2x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat2x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z+w.w*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z+w.w*o.y.w};}
            template <typename TT> constexpr mat3x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat3x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z+w.w*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z+w.w*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z+w.z*o.z.w, x.w*o.z.x+y.w*o.z.y+z.w*o.z.z+w.w*o.z.w};}
            template <typename TT> constexpr mat4x4<decltype(T{}*TT{}+T{}*TT{}+T{}*TT{}+T{}*TT{})> mul(const mat4x4<TT> &o) const {return {x.x*o.x.x+y.x*o.x.y+z.x*o.x.z+w.x*o.x.w, x.y*o.x.x+y.y*o.x.y+z.y*o.x.z+w.y*o.x.w, x.z*o.x.x+y.z*o.x.y+z.z*o.x.z+w.z*o.x.w, x.w*o.x.x+y.w*o.x.y+z.w*o.x.z+w.w*o.x.w, x.x*o.y.x+y.x*o.y.y+z.x*o.y.z+w.x*o.y.w, x.y*o.y.x+y.y*o.y.y+z.y*o.y.z+w.y*o.y.w, x.z*o.y.x+y.z*o.y.y+z.z*o.y.z+w.z*o.y.w, x.w*o.y.x+y.w*o.y.y+z.w*o.y.z+w.w*o.y.w, x.x*o.z.x+y.x*o.z.y+z.x*o.z.z+w.x*o.z.w, x.y*o.z.x+y.y*o.z.y+z.y*o.z.z+w.y*o.z.w, x.z*o.z.x+y.z*o.z.y+z.z*o.z.z+w.z*o.z.w, x.w*o.z.x+y.w*o.z.y+z.w*o.z.z+w.w*o.z.w, x.x*o.w.x+y.x*o.w.y+z.x*o.w.z+w.x*o.w.w, x.y*o.w.x+y.y*o.w.y+z.y*o.w.z+w.y*o.w.w, x.z*o.w.x+y.z*o.w.y+z.z*o.w.z+w.z*o.w.w, x.w*o.w.x+y.w*o.w.y+z.w*o.w.z+w.w*o.w.w};}
        };

        template <typename T1, typename T2> constexpr vec2<decltype(T1{}+T2{})> operator+(const vec2<T1> &first, const vec2<T2> &second) {return {first.x+second.x,first.y+second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}+T2{})> operator+(const vec2<T1> &first, const T2 &second) {return {first.x+second,first.y+second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}+T2{})> operator+(const T1 &first, const vec2<T2> &second) {return {first+second.x,first+second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}-T2{})> operator-(const vec2<T1> &first, const vec2<T2> &second) {return {first.x-second.x,first.y-second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}-T2{})> operator-(const vec2<T1> &first, const T2 &second) {return {first.x-second,first.y-second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}-T2{})> operator-(const T1 &first, const vec2<T2> &second) {return {first-second.x,first-second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}*T2{})> operator*(const vec2<T1> &first, const vec2<T2> &second) {return {first.x*second.x,first.y*second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}*T2{})> operator*(const vec2<T1> &first, const T2 &second) {return {first.x*second,first.y*second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}*T2{})> operator*(const T1 &first, const vec2<T2> &second) {return {first*second.x,first*second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}/T2{})> operator/(const vec2<T1> &first, const vec2<T2> &second) {return {first.x/second.x,first.y/second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}/T2{})> operator/(const vec2<T1> &first, const T2 &second) {return {first.x/second,first.y/second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}/T2{})> operator/(const T1 &first, const vec2<T2> &second) {return {first/second.x,first/second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}%T2{})> operator%(const vec2<T1> &first, const vec2<T2> &second) {return {first.x%second.x,first.y%second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}%T2{})> operator%(const vec2<T1> &first, const T2 &second) {return {first.x%second,first.y%second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}%T2{})> operator%(const T1 &first, const vec2<T2> &second) {return {first%second.x,first%second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}^T2{})> operator^(const vec2<T1> &first, const vec2<T2> &second) {return {first.x^second.x,first.y^second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}^T2{})> operator^(const vec2<T1> &first, const T2 &second) {return {first.x^second,first.y^second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}^T2{})> operator^(const T1 &first, const vec2<T2> &second) {return {first^second.x,first^second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}&T2{})> operator&(const vec2<T1> &first, const vec2<T2> &second) {return {first.x&second.x,first.y&second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}&T2{})> operator&(const vec2<T1> &first, const T2 &second) {return {first.x&second,first.y&second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}&T2{})> operator&(const T1 &first, const vec2<T2> &second) {return {first&second.x,first&second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}|T2{})> operator|(const vec2<T1> &first, const vec2<T2> &second) {return {first.x|second.x,first.y|second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}|T2{})> operator|(const vec2<T1> &first, const T2 &second) {return {first.x|second,first.y|second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}|T2{})> operator|(const T1 &first, const vec2<T2> &second) {return {first|second.x,first|second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}>>T2{})> operator>>(const vec2<T1> &first, const vec2<T2> &second) {return {first.x>>second.x,first.y>>second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}>>T2{})> operator>>(const vec2<T1> &first, const T2 &second) {return {first.x>>second,first.y>>second};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}>>T2{})> operator>>(const T1 &first, const vec2<T2> &second) {return {first>>second.x,first>>second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}<<T2{})> operator<<(const vec2<T1> &first, const vec2<T2> &second) {return {first.x<<second.x,first.y<<second.y};}
        template <typename T1, typename T2> constexpr vec2<decltype(T1{}<<T2{})> operator<<(const vec2<T1> &first, const T2 &second) {return {first.x<<second,first.y<<second};}
        template <typename T1, typename T2> constexpr typename std::enable_if_t<!std::is_base_of<std::ostream,T1>::value,vec2<decltype(T1{}<<T2{})>>::type operator<<(const T1 &first, const vec2<T2> &second) {return {first<<second.x,first<<second.y};}
        template <typename T> constexpr vec2<decltype(~T{})> operator~(const vec2<T> &object) {return {~object.x,~object.y};}
        template <typename T> constexpr vec2<decltype(!T{})> operator!(const vec2<T> &object) {return {!object.x,!object.y};}
        template <typename T> constexpr vec2<decltype(+T{})> operator+(const vec2<T> &object) {return {+object.x,+object.y};}
        template <typename T> constexpr vec2<decltype(-T{})> operator-(const vec2<T> &object) {return {-object.x,-object.y};}
        template <typename T> constexpr vec2<T> &operator++(vec2<T> &object) {++object.x; ++object.y; return object;}
        template <typename T> constexpr vec2<T> operator++(vec2<T> &object, int) {return {object.x++,object.y++};}
        template <typename T> constexpr vec2<T> &operator--(vec2<T> &object) {--object.x; --object.y; return object;}
        template <typename T> constexpr vec2<T> operator--(vec2<T> &object, int) {return {object.x--,object.y--};}
        template <typename T1, typename T2> constexpr bool operator<(const vec2<T1> &first, const vec2<T2> &second) {return (first.x < second.x) && (first.y < second.y);}
        template <typename T1, typename T2> constexpr bool operator<(const vec2<T1> &first, const T2 &second) {return (first.x < second) && (first.y < second);}
        template <typename T1, typename T2> constexpr bool operator<(const T1 &first, const vec2<T2> &second) {return (first < second.x) && (first < second.y);}
        template <typename T1, typename T2> constexpr bool operator>(const vec2<T1> &first, const vec2<T2> &second) {return (first.x > second.x) && (first.y > second.y);}
        template <typename T1, typename T2> constexpr bool operator>(const vec2<T1> &first, const T2 &second) {return (first.x > second) && (first.y > second);}
        template <typename T1, typename T2> constexpr bool operator>(const T1 &first, const vec2<T2> &second) {return (first > second.x) && (first > second.y);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec2<T1> &first, const vec2<T2> &second) {return (first.x <= second.x) && (first.y <= second.y);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec2<T1> &first, const T2 &second) {return (first.x <= second) && (first.y <= second);}
        template <typename T1, typename T2> constexpr bool operator<=(const T1 &first, const vec2<T2> &second) {return (first <= second.x) && (first <= second.y);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec2<T1> &first, const vec2<T2> &second) {return (first.x >= second.x) && (first.y >= second.y);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec2<T1> &first, const T2 &second) {return (first.x >= second) && (first.y >= second);}
        template <typename T1, typename T2> constexpr bool operator>=(const T1 &first, const vec2<T2> &second) {return (first >= second.x) && (first >= second.y);}
        template <typename T1, typename T2> constexpr bool operator&&(const vec2<T1> &first, const vec2<T2> &second) {return first.x && second.x && first.y && second.y;}
        template <typename T1, typename T2> constexpr bool operator&&(const vec2<T1> &first, const T2 &second) {return first.x && first.y && second;}
        template <typename T1, typename T2> constexpr bool operator&&(const T1 &first, const vec2<T2> &second) {return first && second.x && second.y;}
        template <typename T1, typename T2> constexpr bool operator||(const vec2<T1> &first, const vec2<T2> &second) {return first.x || second.x || first.y || second.y;}
        template <typename T1, typename T2> constexpr bool operator||(const vec2<T1> &first, const T2 &second) {return first.x || first.y || second;}
        template <typename T1, typename T2> constexpr bool operator||(const T1 &first, const vec2<T2> &second) {return first || second.x || second.y;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator+=(vec2<T1> &first, const vec2<T2> &second) {first.x += second.x; first.y += second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator+=(vec2<T1> &first, const T2 &second) {first.x += second; first.y += second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator-=(vec2<T1> &first, const vec2<T2> &second) {first.x -= second.x; first.y -= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator-=(vec2<T1> &first, const T2 &second) {first.x -= second; first.y -= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator*=(vec2<T1> &first, const vec2<T2> &second) {first.x *= second.x; first.y *= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator*=(vec2<T1> &first, const T2 &second) {first.x *= second; first.y *= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator/=(vec2<T1> &first, const vec2<T2> &second) {first.x /= second.x; first.y /= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator/=(vec2<T1> &first, const T2 &second) {first.x /= second; first.y /= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator%=(vec2<T1> &first, const vec2<T2> &second) {first.x %= second.x; first.y %= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator%=(vec2<T1> &first, const T2 &second) {first.x %= second; first.y %= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator^=(vec2<T1> &first, const vec2<T2> &second) {first.x ^= second.x; first.y ^= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator^=(vec2<T1> &first, const T2 &second) {first.x ^= second; first.y ^= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator&=(vec2<T1> &first, const vec2<T2> &second) {first.x &= second.x; first.y &= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator&=(vec2<T1> &first, const T2 &second) {first.x &= second; first.y &= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator|=(vec2<T1> &first, const vec2<T2> &second) {first.x |= second.x; first.y |= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator|=(vec2<T1> &first, const T2 &second) {first.x |= second; first.y |= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator<<=(vec2<T1> &first, const vec2<T2> &second) {first.x <<= second.x; first.y <<= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator<<=(vec2<T1> &first, const T2 &second) {first.x <<= second; first.y <<= second; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator>>=(vec2<T1> &first, const vec2<T2> &second) {first.x >>= second.x; first.y >>= second.y; return first;}
        template <typename T1, typename T2> constexpr vec2<T1> &operator>>=(vec2<T1> &first, const T2 &second) {first.x >>= second; first.y >>= second; return first;}

        template <typename T1, typename T2> constexpr bool operator==(const vec2<T1> &first, const vec2<T2> &second) {return (first.x == second.x) && (first.y == second.y);}
        template <typename T1, typename T2> constexpr bool operator==(const vec2<T1> &first, const T2 &second) {return (first.x == second) && (first.y == second);}
        template <typename T1, typename T2> constexpr bool operator==(const T1 &first, const vec2<T2> &second) {return (first == second.x) && (first == second.y);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec2<T1> &first, const vec2<T2> &second) {return (first.x != second.x) || (first.y != second.y);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec2<T1> &first, const T2 &second) {return (first.x != second) || (first.y != second);}
        template <typename T1, typename T2> constexpr bool operator!=(const T1 &first, const vec2<T2> &second) {return (first != second.x) || (first != second.y);}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}+T2{})> operator+(const vec3<T1> &first, const vec3<T2> &second) {return {first.x+second.x,first.y+second.y,first.z+second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}+T2{})> operator+(const vec3<T1> &first, const T2 &second) {return {first.x+second,first.y+second,first.z+second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}+T2{})> operator+(const T1 &first, const vec3<T2> &second) {return {first+second.x,first+second.y,first+second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}-T2{})> operator-(const vec3<T1> &first, const vec3<T2> &second) {return {first.x-second.x,first.y-second.y,first.z-second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}-T2{})> operator-(const vec3<T1> &first, const T2 &second) {return {first.x-second,first.y-second,first.z-second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}-T2{})> operator-(const T1 &first, const vec3<T2> &second) {return {first-second.x,first-second.y,first-second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}*T2{})> operator*(const vec3<T1> &first, const vec3<T2> &second) {return {first.x*second.x,first.y*second.y,first.z*second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}*T2{})> operator*(const vec3<T1> &first, const T2 &second) {return {first.x*second,first.y*second,first.z*second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}*T2{})> operator*(const T1 &first, const vec3<T2> &second) {return {first*second.x,first*second.y,first*second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}/T2{})> operator/(const vec3<T1> &first, const vec3<T2> &second) {return {first.x/second.x,first.y/second.y,first.z/second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}/T2{})> operator/(const vec3<T1> &first, const T2 &second) {return {first.x/second,first.y/second,first.z/second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}/T2{})> operator/(const T1 &first, const vec3<T2> &second) {return {first/second.x,first/second.y,first/second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}%T2{})> operator%(const vec3<T1> &first, const vec3<T2> &second) {return {first.x%second.x,first.y%second.y,first.z%second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}%T2{})> operator%(const vec3<T1> &first, const T2 &second) {return {first.x%second,first.y%second,first.z%second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}%T2{})> operator%(const T1 &first, const vec3<T2> &second) {return {first%second.x,first%second.y,first%second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}^T2{})> operator^(const vec3<T1> &first, const vec3<T2> &second) {return {first.x^second.x,first.y^second.y,first.z^second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}^T2{})> operator^(const vec3<T1> &first, const T2 &second) {return {first.x^second,first.y^second,first.z^second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}^T2{})> operator^(const T1 &first, const vec3<T2> &second) {return {first^second.x,first^second.y,first^second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}&T2{})> operator&(const vec3<T1> &first, const vec3<T2> &second) {return {first.x&second.x,first.y&second.y,first.z&second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}&T2{})> operator&(const vec3<T1> &first, const T2 &second) {return {first.x&second,first.y&second,first.z&second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}&T2{})> operator&(const T1 &first, const vec3<T2> &second) {return {first&second.x,first&second.y,first&second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}|T2{})> operator|(const vec3<T1> &first, const vec3<T2> &second) {return {first.x|second.x,first.y|second.y,first.z|second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}|T2{})> operator|(const vec3<T1> &first, const T2 &second) {return {first.x|second,first.y|second,first.z|second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}|T2{})> operator|(const T1 &first, const vec3<T2> &second) {return {first|second.x,first|second.y,first|second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}>>T2{})> operator>>(const vec3<T1> &first, const vec3<T2> &second) {return {first.x>>second.x,first.y>>second.y,first.z>>second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}>>T2{})> operator>>(const vec3<T1> &first, const T2 &second) {return {first.x>>second,first.y>>second,first.z>>second};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}>>T2{})> operator>>(const T1 &first, const vec3<T2> &second) {return {first>>second.x,first>>second.y,first>>second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}<<T2{})> operator<<(const vec3<T1> &first, const vec3<T2> &second) {return {first.x<<second.x,first.y<<second.y,first.z<<second.z};}
        template <typename T1, typename T2> constexpr vec3<decltype(T1{}<<T2{})> operator<<(const vec3<T1> &first, const T2 &second) {return {first.x<<second,first.y<<second,first.z<<second};}
        template <typename T1, typename T2> constexpr typename std::enable_if_t<!std::is_base_of<std::ostream,T1>::value,vec3<decltype(T1{}<<T2{})>>::type operator<<(const T1 &first, const vec3<T2> &second) {return {first<<second.x,first<<second.y,first<<second.z};}
        template <typename T> constexpr vec3<decltype(~T{})> operator~(const vec3<T> &object) {return {~object.x,~object.y,~object.z};}
        template <typename T> constexpr vec3<decltype(!T{})> operator!(const vec3<T> &object) {return {!object.x,!object.y,!object.z};}
        template <typename T> constexpr vec3<decltype(+T{})> operator+(const vec3<T> &object) {return {+object.x,+object.y,+object.z};}
        template <typename T> constexpr vec3<decltype(-T{})> operator-(const vec3<T> &object) {return {-object.x,-object.y,-object.z};}
        template <typename T> constexpr vec3<T> &operator++(vec3<T> &object) {++object.x; ++object.y; ++object.z; return object;}
        template <typename T> constexpr vec3<T> operator++(vec3<T> &object, int) {return {object.x++,object.y++,object.z++};}
        template <typename T> constexpr vec3<T> &operator--(vec3<T> &object) {--object.x; --object.y; --object.z; return object;}
        template <typename T> constexpr vec3<T> operator--(vec3<T> &object, int) {return {object.x--,object.y--,object.z--};}
        template <typename T1, typename T2> constexpr bool operator<(const vec3<T1> &first, const vec3<T2> &second) {return (first.x < second.x) && (first.y < second.y) && (first.z < second.z);}
        template <typename T1, typename T2> constexpr bool operator<(const vec3<T1> &first, const T2 &second) {return (first.x < second) && (first.y < second) && (first.z < second);}
        template <typename T1, typename T2> constexpr bool operator<(const T1 &first, const vec3<T2> &second) {return (first < second.x) && (first < second.y) && (first < second.z);}
        template <typename T1, typename T2> constexpr bool operator>(const vec3<T1> &first, const vec3<T2> &second) {return (first.x > second.x) && (first.y > second.y) && (first.z > second.z);}
        template <typename T1, typename T2> constexpr bool operator>(const vec3<T1> &first, const T2 &second) {return (first.x > second) && (first.y > second) && (first.z > second);}
        template <typename T1, typename T2> constexpr bool operator>(const T1 &first, const vec3<T2> &second) {return (first > second.x) && (first > second.y) && (first > second.z);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec3<T1> &first, const vec3<T2> &second) {return (first.x <= second.x) && (first.y <= second.y) && (first.z <= second.z);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec3<T1> &first, const T2 &second) {return (first.x <= second) && (first.y <= second) && (first.z <= second);}
        template <typename T1, typename T2> constexpr bool operator<=(const T1 &first, const vec3<T2> &second) {return (first <= second.x) && (first <= second.y) && (first <= second.z);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec3<T1> &first, const vec3<T2> &second) {return (first.x >= second.x) && (first.y >= second.y) && (first.z >= second.z);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec3<T1> &first, const T2 &second) {return (first.x >= second) && (first.y >= second) && (first.z >= second);}
        template <typename T1, typename T2> constexpr bool operator>=(const T1 &first, const vec3<T2> &second) {return (first >= second.x) && (first >= second.y) && (first >= second.z);}
        template <typename T1, typename T2> constexpr bool operator&&(const vec3<T1> &first, const vec3<T2> &second) {return first.x && second.x && first.y && second.y && first.z && second.z;}
        template <typename T1, typename T2> constexpr bool operator&&(const vec3<T1> &first, const T2 &second) {return first.x && first.y && first.z && second;}
        template <typename T1, typename T2> constexpr bool operator&&(const T1 &first, const vec3<T2> &second) {return first && second.x && second.y && second.z;}
        template <typename T1, typename T2> constexpr bool operator||(const vec3<T1> &first, const vec3<T2> &second) {return first.x || second.x || first.y || second.y || first.z || second.z;}
        template <typename T1, typename T2> constexpr bool operator||(const vec3<T1> &first, const T2 &second) {return first.x || first.y || first.z || second;}
        template <typename T1, typename T2> constexpr bool operator||(const T1 &first, const vec3<T2> &second) {return first || second.x || second.y || second.z;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator+=(vec3<T1> &first, const vec3<T2> &second) {first.x += second.x; first.y += second.y; first.z += second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator+=(vec3<T1> &first, const T2 &second) {first.x += second; first.y += second; first.z += second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator-=(vec3<T1> &first, const vec3<T2> &second) {first.x -= second.x; first.y -= second.y; first.z -= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator-=(vec3<T1> &first, const T2 &second) {first.x -= second; first.y -= second; first.z -= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator*=(vec3<T1> &first, const vec3<T2> &second) {first.x *= second.x; first.y *= second.y; first.z *= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator*=(vec3<T1> &first, const T2 &second) {first.x *= second; first.y *= second; first.z *= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator/=(vec3<T1> &first, const vec3<T2> &second) {first.x /= second.x; first.y /= second.y; first.z /= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator/=(vec3<T1> &first, const T2 &second) {first.x /= second; first.y /= second; first.z /= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator%=(vec3<T1> &first, const vec3<T2> &second) {first.x %= second.x; first.y %= second.y; first.z %= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator%=(vec3<T1> &first, const T2 &second) {first.x %= second; first.y %= second; first.z %= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator^=(vec3<T1> &first, const vec3<T2> &second) {first.x ^= second.x; first.y ^= second.y; first.z ^= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator^=(vec3<T1> &first, const T2 &second) {first.x ^= second; first.y ^= second; first.z ^= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator&=(vec3<T1> &first, const vec3<T2> &second) {first.x &= second.x; first.y &= second.y; first.z &= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator&=(vec3<T1> &first, const T2 &second) {first.x &= second; first.y &= second; first.z &= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator|=(vec3<T1> &first, const vec3<T2> &second) {first.x |= second.x; first.y |= second.y; first.z |= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator|=(vec3<T1> &first, const T2 &second) {first.x |= second; first.y |= second; first.z |= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator<<=(vec3<T1> &first, const vec3<T2> &second) {first.x <<= second.x; first.y <<= second.y; first.z <<= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator<<=(vec3<T1> &first, const T2 &second) {first.x <<= second; first.y <<= second; first.z <<= second; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator>>=(vec3<T1> &first, const vec3<T2> &second) {first.x >>= second.x; first.y >>= second.y; first.z >>= second.z; return first;}
        template <typename T1, typename T2> constexpr vec3<T1> &operator>>=(vec3<T1> &first, const T2 &second) {first.x >>= second; first.y >>= second; first.z >>= second; return first;}

        template <typename T1, typename T2> constexpr bool operator==(const vec3<T1> &first, const vec3<T2> &second) {return (first.x == second.x) && (first.y == second.y) && (first.z == second.z);}
        template <typename T1, typename T2> constexpr bool operator==(const vec3<T1> &first, const T2 &second) {return (first.x == second) && (first.y == second) && (first.z == second);}
        template <typename T1, typename T2> constexpr bool operator==(const T1 &first, const vec3<T2> &second) {return (first == second.x) && (first == second.y) && (first == second.z);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec3<T1> &first, const vec3<T2> &second) {return (first.x != second.x) || (first.y != second.y) || (first.z != second.z);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec3<T1> &first, const T2 &second) {return (first.x != second) || (first.y != second) || (first.z != second);}
        template <typename T1, typename T2> constexpr bool operator!=(const T1 &first, const vec3<T2> &second) {return (first != second.x) || (first != second.y) || (first != second.z);}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}+T2{})> operator+(const vec4<T1> &first, const vec4<T2> &second) {return {first.x+second.x,first.y+second.y,first.z+second.z,first.w+second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}+T2{})> operator+(const vec4<T1> &first, const T2 &second) {return {first.x+second,first.y+second,first.z+second,first.w+second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}+T2{})> operator+(const T1 &first, const vec4<T2> &second) {return {first+second.x,first+second.y,first+second.z,first+second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}-T2{})> operator-(const vec4<T1> &first, const vec4<T2> &second) {return {first.x-second.x,first.y-second.y,first.z-second.z,first.w-second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}-T2{})> operator-(const vec4<T1> &first, const T2 &second) {return {first.x-second,first.y-second,first.z-second,first.w-second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}-T2{})> operator-(const T1 &first, const vec4<T2> &second) {return {first-second.x,first-second.y,first-second.z,first-second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}*T2{})> operator*(const vec4<T1> &first, const vec4<T2> &second) {return {first.x*second.x,first.y*second.y,first.z*second.z,first.w*second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}*T2{})> operator*(const vec4<T1> &first, const T2 &second) {return {first.x*second,first.y*second,first.z*second,first.w*second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}*T2{})> operator*(const T1 &first, const vec4<T2> &second) {return {first*second.x,first*second.y,first*second.z,first*second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}/T2{})> operator/(const vec4<T1> &first, const vec4<T2> &second) {return {first.x/second.x,first.y/second.y,first.z/second.z,first.w/second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}/T2{})> operator/(const vec4<T1> &first, const T2 &second) {return {first.x/second,first.y/second,first.z/second,first.w/second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}/T2{})> operator/(const T1 &first, const vec4<T2> &second) {return {first/second.x,first/second.y,first/second.z,first/second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}%T2{})> operator%(const vec4<T1> &first, const vec4<T2> &second) {return {first.x%second.x,first.y%second.y,first.z%second.z,first.w%second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}%T2{})> operator%(const vec4<T1> &first, const T2 &second) {return {first.x%second,first.y%second,first.z%second,first.w%second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}%T2{})> operator%(const T1 &first, const vec4<T2> &second) {return {first%second.x,first%second.y,first%second.z,first%second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}^T2{})> operator^(const vec4<T1> &first, const vec4<T2> &second) {return {first.x^second.x,first.y^second.y,first.z^second.z,first.w^second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}^T2{})> operator^(const vec4<T1> &first, const T2 &second) {return {first.x^second,first.y^second,first.z^second,first.w^second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}^T2{})> operator^(const T1 &first, const vec4<T2> &second) {return {first^second.x,first^second.y,first^second.z,first^second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}&T2{})> operator&(const vec4<T1> &first, const vec4<T2> &second) {return {first.x&second.x,first.y&second.y,first.z&second.z,first.w&second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}&T2{})> operator&(const vec4<T1> &first, const T2 &second) {return {first.x&second,first.y&second,first.z&second,first.w&second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}&T2{})> operator&(const T1 &first, const vec4<T2> &second) {return {first&second.x,first&second.y,first&second.z,first&second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}|T2{})> operator|(const vec4<T1> &first, const vec4<T2> &second) {return {first.x|second.x,first.y|second.y,first.z|second.z,first.w|second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}|T2{})> operator|(const vec4<T1> &first, const T2 &second) {return {first.x|second,first.y|second,first.z|second,first.w|second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}|T2{})> operator|(const T1 &first, const vec4<T2> &second) {return {first|second.x,first|second.y,first|second.z,first|second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}>>T2{})> operator>>(const vec4<T1> &first, const vec4<T2> &second) {return {first.x>>second.x,first.y>>second.y,first.z>>second.z,first.w>>second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}>>T2{})> operator>>(const vec4<T1> &first, const T2 &second) {return {first.x>>second,first.y>>second,first.z>>second,first.w>>second};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}>>T2{})> operator>>(const T1 &first, const vec4<T2> &second) {return {first>>second.x,first>>second.y,first>>second.z,first>>second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}<<T2{})> operator<<(const vec4<T1> &first, const vec4<T2> &second) {return {first.x<<second.x,first.y<<second.y,first.z<<second.z,first.w<<second.w};}
        template <typename T1, typename T2> constexpr vec4<decltype(T1{}<<T2{})> operator<<(const vec4<T1> &first, const T2 &second) {return {first.x<<second,first.y<<second,first.z<<second,first.w<<second};}
        template <typename T1, typename T2> constexpr typename std::enable_if_t<!std::is_base_of<std::ostream,T1>::value,vec4<decltype(T1{}<<T2{})>>::type operator<<(const T1 &first, const vec4<T2> &second) {return {first<<second.x,first<<second.y,first<<second.z,first<<second.w};}
        template <typename T> constexpr vec4<decltype(~T{})> operator~(const vec4<T> &object) {return {~object.x,~object.y,~object.z,~object.w};}
        template <typename T> constexpr vec4<decltype(!T{})> operator!(const vec4<T> &object) {return {!object.x,!object.y,!object.z,!object.w};}
        template <typename T> constexpr vec4<decltype(+T{})> operator+(const vec4<T> &object) {return {+object.x,+object.y,+object.z,+object.w};}
        template <typename T> constexpr vec4<decltype(-T{})> operator-(const vec4<T> &object) {return {-object.x,-object.y,-object.z,-object.w};}
        template <typename T> constexpr vec4<T> &operator++(vec4<T> &object) {++object.x; ++object.y; ++object.z; ++object.w; return object;}
        template <typename T> constexpr vec4<T> operator++(vec4<T> &object, int) {return {object.x++,object.y++,object.z++,object.w++};}
        template <typename T> constexpr vec4<T> &operator--(vec4<T> &object) {--object.x; --object.y; --object.z; --object.w; return object;}
        template <typename T> constexpr vec4<T> operator--(vec4<T> &object, int) {return {object.x--,object.y--,object.z--,object.w--};}
        template <typename T1, typename T2> constexpr bool operator<(const vec4<T1> &first, const vec4<T2> &second) {return (first.x < second.x) && (first.y < second.y) && (first.z < second.z) && (first.w < second.w);}
        template <typename T1, typename T2> constexpr bool operator<(const vec4<T1> &first, const T2 &second) {return (first.x < second) && (first.y < second) && (first.z < second) && (first.w < second);}
        template <typename T1, typename T2> constexpr bool operator<(const T1 &first, const vec4<T2> &second) {return (first < second.x) && (first < second.y) && (first < second.z) && (first < second.w);}
        template <typename T1, typename T2> constexpr bool operator>(const vec4<T1> &first, const vec4<T2> &second) {return (first.x > second.x) && (first.y > second.y) && (first.z > second.z) && (first.w > second.w);}
        template <typename T1, typename T2> constexpr bool operator>(const vec4<T1> &first, const T2 &second) {return (first.x > second) && (first.y > second) && (first.z > second) && (first.w > second);}
        template <typename T1, typename T2> constexpr bool operator>(const T1 &first, const vec4<T2> &second) {return (first > second.x) && (first > second.y) && (first > second.z) && (first > second.w);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec4<T1> &first, const vec4<T2> &second) {return (first.x <= second.x) && (first.y <= second.y) && (first.z <= second.z) && (first.w <= second.w);}
        template <typename T1, typename T2> constexpr bool operator<=(const vec4<T1> &first, const T2 &second) {return (first.x <= second) && (first.y <= second) && (first.z <= second) && (first.w <= second);}
        template <typename T1, typename T2> constexpr bool operator<=(const T1 &first, const vec4<T2> &second) {return (first <= second.x) && (first <= second.y) && (first <= second.z) && (first <= second.w);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec4<T1> &first, const vec4<T2> &second) {return (first.x >= second.x) && (first.y >= second.y) && (first.z >= second.z) && (first.w >= second.w);}
        template <typename T1, typename T2> constexpr bool operator>=(const vec4<T1> &first, const T2 &second) {return (first.x >= second) && (first.y >= second) && (first.z >= second) && (first.w >= second);}
        template <typename T1, typename T2> constexpr bool operator>=(const T1 &first, const vec4<T2> &second) {return (first >= second.x) && (first >= second.y) && (first >= second.z) && (first >= second.w);}
        template <typename T1, typename T2> constexpr bool operator&&(const vec4<T1> &first, const vec4<T2> &second) {return first.x && second.x && first.y && second.y && first.z && second.z && first.w && second.w;}
        template <typename T1, typename T2> constexpr bool operator&&(const vec4<T1> &first, const T2 &second) {return first.x && first.y && first.z && first.w && second;}
        template <typename T1, typename T2> constexpr bool operator&&(const T1 &first, const vec4<T2> &second) {return first && second.x && second.y && second.z && second.w;}
        template <typename T1, typename T2> constexpr bool operator||(const vec4<T1> &first, const vec4<T2> &second) {return first.x || second.x || first.y || second.y || first.z || second.z || first.w || second.w;}
        template <typename T1, typename T2> constexpr bool operator||(const vec4<T1> &first, const T2 &second) {return first.x || first.y || first.z || first.w || second;}
        template <typename T1, typename T2> constexpr bool operator||(const T1 &first, const vec4<T2> &second) {return first || second.x || second.y || second.z || second.w;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator+=(vec4<T1> &first, const vec4<T2> &second) {first.x += second.x; first.y += second.y; first.z += second.z; first.w += second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator+=(vec4<T1> &first, const T2 &second) {first.x += second; first.y += second; first.z += second; first.w += second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator-=(vec4<T1> &first, const vec4<T2> &second) {first.x -= second.x; first.y -= second.y; first.z -= second.z; first.w -= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator-=(vec4<T1> &first, const T2 &second) {first.x -= second; first.y -= second; first.z -= second; first.w -= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator*=(vec4<T1> &first, const vec4<T2> &second) {first.x *= second.x; first.y *= second.y; first.z *= second.z; first.w *= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator*=(vec4<T1> &first, const T2 &second) {first.x *= second; first.y *= second; first.z *= second; first.w *= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator/=(vec4<T1> &first, const vec4<T2> &second) {first.x /= second.x; first.y /= second.y; first.z /= second.z; first.w /= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator/=(vec4<T1> &first, const T2 &second) {first.x /= second; first.y /= second; first.z /= second; first.w /= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator%=(vec4<T1> &first, const vec4<T2> &second) {first.x %= second.x; first.y %= second.y; first.z %= second.z; first.w %= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator%=(vec4<T1> &first, const T2 &second) {first.x %= second; first.y %= second; first.z %= second; first.w %= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator^=(vec4<T1> &first, const vec4<T2> &second) {first.x ^= second.x; first.y ^= second.y; first.z ^= second.z; first.w ^= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator^=(vec4<T1> &first, const T2 &second) {first.x ^= second; first.y ^= second; first.z ^= second; first.w ^= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator&=(vec4<T1> &first, const vec4<T2> &second) {first.x &= second.x; first.y &= second.y; first.z &= second.z; first.w &= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator&=(vec4<T1> &first, const T2 &second) {first.x &= second; first.y &= second; first.z &= second; first.w &= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator|=(vec4<T1> &first, const vec4<T2> &second) {first.x |= second.x; first.y |= second.y; first.z |= second.z; first.w |= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator|=(vec4<T1> &first, const T2 &second) {first.x |= second; first.y |= second; first.z |= second; first.w |= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator<<=(vec4<T1> &first, const vec4<T2> &second) {first.x <<= second.x; first.y <<= second.y; first.z <<= second.z; first.w <<= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator<<=(vec4<T1> &first, const T2 &second) {first.x <<= second; first.y <<= second; first.z <<= second; first.w <<= second; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator>>=(vec4<T1> &first, const vec4<T2> &second) {first.x >>= second.x; first.y >>= second.y; first.z >>= second.z; first.w >>= second.w; return first;}
        template <typename T1, typename T2> constexpr vec4<T1> &operator>>=(vec4<T1> &first, const T2 &second) {first.x >>= second; first.y >>= second; first.z >>= second; first.w >>= second; return first;}

        template <typename T1, typename T2> constexpr bool operator==(const vec4<T1> &first, const vec4<T2> &second) {return (first.x == second.x) && (first.y == second.y) && (first.z == second.z) && (first.w == second.w);}
        template <typename T1, typename T2> constexpr bool operator==(const vec4<T1> &first, const T2 &second) {return (first.x == second) && (first.y == second) && (first.z == second) && (first.w == second);}
        template <typename T1, typename T2> constexpr bool operator==(const T1 &first, const vec4<T2> &second) {return (first == second.x) && (first == second.y) && (first == second.z) && (first == second.w);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec4<T1> &first, const vec4<T2> &second) {return (first.x != second.x) || (first.y != second.y) || (first.z != second.z) || (first.w != second.w);}
        template <typename T1, typename T2> constexpr bool operator!=(const vec4<T1> &first, const T2 &second) {return (first.x != second) || (first.y != second) || (first.z != second) || (first.w != second);}
        template <typename T1, typename T2> constexpr bool operator!=(const T1 &first, const vec4<T2> &second) {return (first != second.x) || (first != second.y) || (first != second.z) || (first != second.w);}
        template <typename X, typename Y, typename T> std::basic_ostream<X,Y> &operator<<(std::basic_ostream<X,Y> &stream, const vec<2,T> &vector) {stream << '[' << vector.x << ',' << vector.y << ']'; return stream;}
        template <typename X, typename Y, typename T> std::basic_ostream<X,Y> &operator<<(std::basic_ostream<X,Y> &stream, const vec<3,T> &vector) {stream << '[' << vector.x << ',' << vector.y << ',' << vector.z << ']'; return stream;}
        template <typename X, typename Y, typename T> std::basic_ostream<X,Y> &operator<<(std::basic_ostream<X,Y> &stream, const vec<4,T> &vector) {stream << '[' << vector.x << ',' << vector.y << ',' << vector.z << ',' << vector.w << ']'; return stream;}
    }

    namespace Quaternion
    {
        template <typename T = float> struct GenericQuaternion
        {
            static_assert(std::is_floating_point<T>::value, "Quaternion template parameter must be floating-point.");

            Vector::vec4<T> vec;

            GenericQuaternion() : vec{0,0,0,1} {}
            GenericQuaternion(const Vector::vec4<T> &o) : vec(o) {}

            static GenericQuaternion from_norm_axis_and_angle(const Vector::vec3<T> &v, T angle)
            {
                return GenericQuaternion({v.x * std::sin(angle / 2.f), v.y * std::sin(angle / 2.f), v.z * std::sin(angle / 2.f), std::cos(angle / 2.f)});
            }
            static GenericQuaternion from_axis_and_angle(const Vector::vec3<T> &v, T angle)
            {
                return from_norm_axis_and_angle(v.norm(), angle);
            }

            GenericQuaternion norm() const
            {
                return GenericQuaternion(vec.norm());
            }

            void normalize()
            {
                vec = vec.norm();
            }
            GenericQuaternion operator+(const GenericQuaternion &o) const
            {
                return GenericQuaternion(vec + o.vec);
            }
            GenericQuaternion &operator+=(const GenericQuaternion &o)
            {
                vec += o.vec;
                return *this;
            }
            GenericQuaternion operator-(const GenericQuaternion &o) const
            {
                return GenericQuaternion(vec - o.vec);
            }
            GenericQuaternion &operator-=(const GenericQuaternion &o)
            {
                vec -= o.vec;
                return *this;
            }
            GenericQuaternion operator-() const
            {
                return GenericQuaternion(-vec.x, -vec.y, -vec.z, vec.w);
            }
            GenericQuaternion operator*(const GenericQuaternion &o) const
            {
                return GenericQuaternion(vec.w*o.vec.x + vec.x*o.vec.w + vec.y*o.vec.z - vec.z*o.vec.y,
                                         vec.w*o.vec.y - vec.x*o.vec.z + vec.y*o.vec.w + vec.z*o.vec.x,
                                         vec.w*o.vec.z + vec.x*o.vec.y - vec.y*o.vec.x + vec.z*o.vec.w,
                                         vec.w*o.vec.w - vec.x*o.vec.x - vec.y*o.vec.y - vec.z*o.vec.z);
            }
            GenericQuaternion &operator*=(const GenericQuaternion &o)
            {
                vec = {vec.w*o.vec.x + vec.x*o.vec.w + vec.y*o.vec.z - vec.z*o.vec.y,
                       vec.w*o.vec.y - vec.x*o.vec.z + vec.y*o.vec.w + vec.z*o.vec.x,
                       vec.w*o.vec.z + vec.x*o.vec.y - vec.y*o.vec.x + vec.z*o.vec.w,
                       vec.w*o.vec.w - vec.x*o.vec.x - vec.y*o.vec.y - vec.z*o.vec.z};
                return *this;
            }
            T dot(const GenericQuaternion &o) const
            {
                return vec.dot(o.vec);
            }
            T len_sqr() const
            {
                return vec.len_sqr();
            }
            T len() const
            {
                return vec.len();
            }
            GenericQuaternion combine(const GenericQuaternion &o, T fac) const
            {
                return GenericQuaternion(vec.interpolate(o.vec, fac));
            }

            bool operator==(const GenericQuaternion &o) const
            {
                return vec == o.vec;
            }
            bool operator!=(const GenericQuaternion &o) const
            {
                return vec != o.vec;
            }

            Vector::vec3<T> get_axis() const
            {
                return vec.to_vec3().norm();
            }
            Vector::vec3<T> get_not_norm_axis() const
            {
                return vec.to_vec3();
            }
            T get_angle() const
            {
                return std::atan2(vec.to_vec3().len(), vec.w) * 2;
            }

            template <typename TT> GenericQuaternion mult_angle(TT n) const
            {
                return from_axis_and_angle(get_not_norm_axis(), get_angle() * n);
            }

            template <typename TT> Vector::vec3<TT> apply(const Vector::vec3<TT> &in) const // 24x [*|/]  17x [+|-]
            {
                float newx = vec.w*in.x + vec.y*in.z - vec.z*in.y;
                float newy = vec.w*in.y - vec.x*in.z + vec.z*in.x;
                float newz = vec.w*in.z + vec.x*in.y - vec.y*in.x;
                float neww = vec.x*in.x + vec.y*in.y + vec.z*in.z;

                return {newx*vec.w + neww*vec.x - newy*vec.z + newz*vec.y,
                        neww*vec.y + newx*vec.z + newy*vec.w - newz*vec.x,
                        neww*vec.z - newx*vec.y + newy*vec.x + newz*vec.w};
            }
            template <typename TT> Vector::vec4<TT> apply(const Vector::vec4<TT> &in) const // 24x [*|/]  17x [+|-]
            {
                float newx = vec.w*in.x + vec.y*in.z - vec.z*in.y;
                float newy = vec.w*in.y - vec.x*in.z + vec.z*in.x;
                float newz = vec.w*in.z + vec.x*in.y - vec.y*in.x;
                float neww = vec.x*in.x + vec.y*in.y + vec.z*in.z;

                return {newx*vec.w + neww*vec.x - newy*vec.z + newz*vec.y,
                        neww*vec.y + newx*vec.z + newy*vec.w - newz*vec.x,
                        neww*vec.z - newx*vec.y + newy*vec.x + newz*vec.w,
                        in.w};
            }

            Vector::mat3<T> get_matrix_from_normalized() const // 18x [*|/]  12x [+|-]    +    mult: 9x [*|/]  6x [+|-]
            {
                return {1 - 2*vec.y*vec.y - 2*vec.z*vec.z, 2*vec.x*vec.y + 2*vec.z*vec.w, 2*vec.x*vec.z - 2*vec.y*vec.w,
                        2*vec.x*vec.y - 2*vec.z*vec.w, 1 - 2*vec.x*vec.x - 2*vec.z*vec.z, 2*vec.y*vec.z + 2*vec.x*vec.w,
                        2*vec.x*vec.z + 2*vec.y*vec.w, 2*vec.y*vec.z - 2*vec.x*vec.w, 1 - 2*vec.x*vec.x - 2*vec.y*vec.y};
            }
            Vector::mat3<T> normalize_and_get_matrix() // 18x [*|/]  12x [+|-]    +    mult: 9x [*|/]  6x [+|-]
            {
                normalize();
                return get_matrix_from_normalized();
            }
        };

        using Quaternion = GenericQuaternion<>;
    }

    namespace CustomOperators
    {
        namespace Internal
        {
            template <typename T> struct dot_tmp
            {
                T ref;
                template <typename TT> constexpr auto operator/(const Vector::vec2<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec2<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec3<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec3<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec4<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec4<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x2<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x2<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x2<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x2<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x2<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x2<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x3<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x3<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x3<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x3<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x3<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x3<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x4<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x4<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x4<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x4<TT> &&obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x4<TT> &obj) const {return ref.dot(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x4<TT> &&obj) const {return ref.dot(obj);}
            };
            template <typename T> struct cross_tmp
            {
                T ref;
                template <typename TT> constexpr auto operator/(const Vector::vec2<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec2<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec3<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec3<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec4<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec4<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x2<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x2<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x2<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x2<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x2<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x2<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x3<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x3<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x3<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x3<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x3<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x3<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x4<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x4<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x4<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x4<TT> &&obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x4<TT> &obj) const {return ref.cross(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x4<TT> &&obj) const {return ref.cross(obj);}
            };
            template <typename T> struct mul_tmp
            {
                T ref;
                template <typename TT> constexpr auto operator/(const Vector::vec2<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec2<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec3<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec3<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::vec4<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::vec4<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x2<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x2<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x2<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x2<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x2<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x2<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x3<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x3<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x3<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x3<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x3<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x3<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat2x4<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat2x4<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat3x4<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat3x4<TT> &&obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(const Vector::mat4x4<TT> &obj) const {return ref.mul(obj);}
                template <typename TT> constexpr auto operator/(Vector::mat4x4<TT> &&obj) const {return ref.mul(obj);}
            };
        }

        namespace Internal {struct dot_type {constexpr dot_type(){}};} static constexpr Internal::dot_type dot;
        template <typename T> constexpr auto operator/(const Vector::vec2<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::vec2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec2<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::vec2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec3<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::vec3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec3<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::vec3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec4<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::vec4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec4<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::vec4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x2<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat2x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x2<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat2x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x2<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat3x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x2<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat3x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x2<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat4x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x2<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat4x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x3<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat2x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x3<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat2x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x3<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat3x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x3<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat3x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x3<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat4x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x3<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat4x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x4<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat2x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x4<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat2x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x4<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat3x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x4<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat3x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x4<T> &obj, decltype(dot)) {return Internal::dot_tmp<const Vector::mat4x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x4<T> &&obj, decltype(dot)) {return Internal::dot_tmp<Vector::mat4x4<T>>{obj};}
        namespace Internal {struct cross_type {constexpr cross_type(){}};} static constexpr Internal::cross_type cross;
        template <typename T> constexpr auto operator/(const Vector::vec2<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::vec2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec2<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::vec2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec3<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::vec3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec3<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::vec3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec4<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::vec4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec4<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::vec4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x2<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat2x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x2<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat2x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x2<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat3x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x2<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat3x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x2<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat4x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x2<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat4x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x3<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat2x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x3<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat2x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x3<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat3x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x3<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat3x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x3<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat4x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x3<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat4x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x4<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat2x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x4<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat2x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x4<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat3x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x4<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat3x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x4<T> &obj, decltype(cross)) {return Internal::cross_tmp<const Vector::mat4x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x4<T> &&obj, decltype(cross)) {return Internal::cross_tmp<Vector::mat4x4<T>>{obj};}
        namespace Internal {struct mul_type {constexpr mul_type(){}};} static constexpr Internal::mul_type mul;
        template <typename T> constexpr auto operator/(const Vector::vec2<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::vec2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec2<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::vec2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec3<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::vec3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec3<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::vec3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::vec4<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::vec4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::vec4<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::vec4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x2<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat2x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x2<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat2x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x2<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat3x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x2<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat3x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x2<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat4x2<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x2<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat4x2<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x3<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat2x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x3<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat2x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x3<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat3x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x3<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat3x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x3<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat4x3<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x3<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat4x3<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat2x4<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat2x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat2x4<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat2x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat3x4<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat3x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat3x4<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat3x4<T>>{obj};}
        template <typename T> constexpr auto operator/(const Vector::mat4x4<T> &obj, decltype(mul)) {return Internal::mul_tmp<const Vector::mat4x4<T> &>{obj};}
        template <typename T> constexpr auto operator/(Vector::mat4x4<T> &&obj, decltype(mul)) {return Internal::mul_tmp<Vector::mat4x4<T>>{obj};}
    }

    namespace Misc
    {
        template <typename T> T pi()
        {
            static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
            static const T ret = std::atan((T)1)*4;
            return ret;
        }

        template <typename T> T to_rad(T in)
        {
            static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
            return in * pi<T>() / (T)180;
        }
        template <typename T> T to_deg(T in)
        {
            static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
            return in * (T)180 / pi<T>();
        }

        template <typename T, typename TT> constexpr T ipow(T a, TT b)
        {
            static_assert(std::is_integral<TT>::value, "Non integral template parameters make no sense for this function.");
            T ret = 1;
            while (b--)
            {
                ret *= a;
            }
            return ret;
        }

        template <typename T, typename MIN, typename MAX> constexpr T clamp(T val, MIN min, MAX max)
        {
            static_assert(std::is_arithmetic<T>::value &&
                          std::is_arithmetic<MIN>::value &&
                          std::is_arithmetic<MAX>::value, "Non arithmetic template parameters make no sense for this function.");
            if (val < min) return min;
            if (val > max) return max;
            return val;
        }

        template <typename T> constexpr int sign(T val)
        {
            return (val > 0) - (val < 0);
        }

        template <typename T> constexpr T smoothstep(T x)
        {
            static_assert(!std::is_integral<T>::value, "Integral template parameter makes no sense for this function.");
            return 3*x*x-2*x*x*x;
        }

        template <typename T, typename TT> constexpr T true_div(T a, TT b)
        {
            static_assert(std::is_integral<T>::value &&
                          std::is_integral<TT>::value, "Argument types must be integral.");
            if (a >= 0)
                return a / b;
            else
                return (a + 1) / b - (b >= 0 ? 1 : -1);
        }

        template <typename T, typename TT> constexpr T true_mod(T a, TT b)
        {
            static_assert(std::is_integral<T>::value &&
                          std::is_integral<TT>::value, "Argument types must be integral.");
            if (a >= 0)
                return a % b;
            else
                return (b >= 0 ? b : -b) - 1 + (a + 1) % b;
        }
    }
}

namespace std
{
    template <typename T> struct less<Math::Vector::vec2<T>>
    {
        using result_type = bool;
        using first_argument_type = Math::Vector::vec2<T>;
        using second_argument_type = Math::Vector::vec2<T>;
        constexpr bool operator()(const first_argument_type &a, const second_argument_type &b) const
        {
            if (a.x < b.x) return 1;
            if (a.x > b.x) return 0;
            if (a.y < b.y) return 1;
            if (a.y > b.y) return 0;
            return 0;
        }
    };
    template <typename T> struct less<Math::Vector::vec3<T>>
    {
        using result_type = bool;
        using first_argument_type = Math::Vector::vec3<T>;
        using second_argument_type = Math::Vector::vec3<T>;
        constexpr bool operator()(const first_argument_type &a, const second_argument_type &b) const
        {
            if (a.x < b.x) return 1;
            if (a.x > b.x) return 0;
            if (a.y < b.y) return 1;
            if (a.y > b.y) return 0;
            if (a.z < b.z) return 1;
            if (a.z > b.z) return 0;
            return 0;
        }
    };
    template <typename T> struct less<Math::Vector::vec4<T>>
    {
        using result_type = bool;
        using first_argument_type = Math::Vector::vec4<T>;
        using second_argument_type = Math::Vector::vec4<T>;
        constexpr bool operator()(const first_argument_type &a, const second_argument_type &b) const
        {
            if (a.x < b.x) return 1;
            if (a.x > b.x) return 0;
            if (a.y < b.y) return 1;
            if (a.y > b.y) return 0;
            if (a.z < b.z) return 1;
            if (a.z > b.z) return 0;
            if (a.w < b.w) return 1;
            if (a.w > b.w) return 0;
            return 0;
        }
    };
}

using namespace Math::Vector;
using namespace Math::Quaternion;
using namespace Math::CustomOperators;
using namespace Math::Misc;

#endif
