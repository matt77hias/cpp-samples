struct Widget
{
    static int value;
};

int Widget::value = 5;

auto main()
    -> int
{
    using type = const Widget;
    type::value = 7;
    
    return type::value;
}
