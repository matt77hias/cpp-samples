// Cref.: http://eel.is/c++draft/dcl.type.cv#4

struct Foo
{
    int& m_i;
};
struct Bar
{
    int m_i;
};
struct Baz
{
    mutable int m_i;
};

auto main() -> int
{
    int i = 0; // i is not declared const
   
   // Foo
   {
       const Foo f{ .m_i = i }; // declared const Foo
       const_cast< Foo& >(f).m_i = 1; // not UB
   }
   {
       const Foo* f = new const Foo{ .m_i = i }; // declared pointer to const Foo
       const_cast< Foo* >(f)->m_i = 1; // not UB
   }
   
   // Bar
   {
       const Bar b{ .m_i = i }; // declared const Bar
       const_cast< Bar& >(b).m_i = 1; // UB
   }
   {
       const Bar* b = new const Bar{ .m_i = i }; // declared pointer to const Bar
       const_cast< Bar* >(b)->m_i = 1; // UB
   }
   
   // Baz
   {
       const Baz b{ .m_i = i }; // declared const Baz
       const_cast< Baz& >(b).m_i = 1; // not UB
   }
   {
       const Baz* b = new const Baz{ .m_i = i }; // declared pointer to const Baz
       const_cast< Baz* >(b)->m_i = 1; // not UB
   }

    return i;
}
