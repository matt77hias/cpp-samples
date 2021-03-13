class Foo
{

public:
    
    void foo();
};

class Bar : private Foo
{

private:

    using Base = Foo;

public:
    
    using Base::Foo;
};

int main()
{
    return 0;
}
