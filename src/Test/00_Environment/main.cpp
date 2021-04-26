#include <iostream>
using namespace std;

template <size_t idx, typename T>
struct G;

template <typename... T>
struct V
{
};

template <typename T, typename... R>
struct V<T, R...>
{
    V(const T &v, const R &...r)
        : v(v), r(r...){};

    T v;
    V<R...> r;

    template <size_t idx>
    auto get()
    {
        return G<idx, V<T, R...>>::get(*this);
    }
};

template <typename T, typename... R>
struct G<0, V<T, R...>>
{
    static T get(V<T, R...> &d)
    {
        return d.v;
    }
};

template <size_t idx, typename T, typename... R>
struct G<idx, V<T, R...>>
{
    static auto get(V<T, R...> &d)
    {
        return G<idx - 1, V<R...>>::get(d.r);
    }
};

struct Cr
{
    int a;
    float b;
    double c;
};

int main()
{
    V<int, float, double> c{1, 2, 3};
    Cr an{2, 3, 4};
    std::cout << c.get<0>();
    std::cout << an.a;
    std::cout << sizeof(c) << std::endl;
    std::cout << sizeof(an) << std::endl;
    return 0;
}