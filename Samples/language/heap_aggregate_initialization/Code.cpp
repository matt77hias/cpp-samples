struct Widget
{ 
    int m_value = {};
};

int main()
{
    [[maybe_unused]] const auto ptr = new Widget{ .m_value = 1 };
    
    return 0;
}
