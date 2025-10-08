struct Foo
{
    bool m_first : 1 = {};
    bool m_second : 1 = {};
};

static_assert(sizeof(Foo) == 1u);

struct Bar
{
    int m_first : 16 = 5;
    int m_second : 16 = 7;
};

static_assert(sizeof(Bar) == 4u);

auto main() -> int
{
    Bar b;
    return b.m_first + b.m_second;
}
