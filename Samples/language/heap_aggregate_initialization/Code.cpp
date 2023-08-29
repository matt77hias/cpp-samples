struct Widget
{ 
    int m_value = {};
};

auto main()
    -> int
{
    [[maybe_unused]] const auto ptr = new Widget{ .m_value = 1 };
    
    return 0;
}
