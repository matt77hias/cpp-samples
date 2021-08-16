template< typename F >
class Foo
{
    template< typename B > 
    friend constexpr int Bar(Foo foo, B b);

    int m_i = {};
};

template< typename F, typename B >
constexpr int Bar(Foo< F > foo, B b)
{
    return foo.m_i;
}

int main()
{
    return 0;
}
