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

auto main()
    -> int
{
   [[maybe_unused]] ns::A::type a0 = ns::B::type{};
   [[maybe_unused]] ns::A::type a1 = Tag< ns::C >{};
   //ns::A::type a1 = Tag< C >{};
   
   return 0;
}
