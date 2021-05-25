[[nodiscard]]
consteval int Foo() noexcept
{
    return 1;
}

int main()
{
   int bar = 2;
   int baz = bar + Foo();

   return baz;
}
