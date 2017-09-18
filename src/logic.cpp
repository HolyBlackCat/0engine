#include "master.h"

#include <array>
#include <tuple>
#include <map>
#include <vector>

void Boot();

static constexpr ivec2 screen_size = {480,270};

void PreInit()
{
    Window::Init::Size(screen_size*2);
    Window::Init::MinimalSize(screen_size);
    Window::Init::Resizable(1);
    Sys::SetCurrentFunction(Boot);
}

void Resize()
{
    Graphics::ViewportFullscreen();
}

struct C
{
    Reflect(C)
    (
        (int)(foo,bar)(=42),
    )
};

struct B
{
    Reflect(B)
    (
        (int)(w,h)(=1),
        (C)(c),
    )
};

struct A
{
    ReflectMemberEnumClass(E, (enum_a)(enum_b)(enum_c))

    Reflect(A)
    (
        (std::vector<fmat2>)(std_vec)({{},{},{}}),
        (B)(b),
        (int)(x)(=1),
        (float)(y)(=12.3),
        (fvec3)(v1)(={1,2,3}),
        (fmat3)(v2)(=fmat3::rotate({1,1,1},1)),
        (std::tuple<int,float,double>)(t)({1,2,3}),
        (std::map<int,int>)(std_map)({{1,2},{3,4}}),
        (int[3])(plain_arr)({5,6,7}),
        (std::string)(str)(="abc\n\t\x18"),
    )
};

void Boot()
{
    MarkLocation("Boot");

    A b;
    b.x = b.y = 0;
    b.v1 = {};
    b.v2 = {};
    b.t = {0,0,0};
    b.std_vec.clear();
    b.std_map.clear();
    b.plain_arr[0] = b.plain_arr[1] = b.plain_arr[2] = 0;
    b.str = "";
    b.b.w = b.b.h = 0;
    b.b.c.foo = b.b.c.bar = 0;

    Reflection::ParsingErrorContext con;
    std::cout << Reflection::from_string(b,
    R"(
    {
        std_vec=[((3,2),(1,0)),((0,0),(0,0)),((7,8),(9,10))],
        b=
        {
            w=1,
            h=1,
            c={foo=42,bar=42}
        }
    }
    )", con) << '\n' << Reflection::to_string_tree(b) << '\n' << con.to_string() << '\n';

    while (1)
    {
        Sys::BeginFrame();

        Sys::Tick();

        Sys::EndFrame();
    }
}
