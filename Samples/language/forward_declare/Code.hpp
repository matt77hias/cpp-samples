template< typename T >
struct Tag
{};

namespace ns
{
    struct A
    {
        using type = Tag< struct C >;
    };

    struct B
    {
        using type = Tag< struct C >;
    };

    struct C
    {};
}

struct C
{};

int main()
{
   ns::A::type a0 = ns::B::type{};
   ns::A::type a1 = Tag< ns::C >{};
   //ns::A::type a1 = Tag< C >{};
   
   return 0;
}
