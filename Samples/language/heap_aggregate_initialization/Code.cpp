struct Widget
{ 
    int m_value = {};
};

int main()
{
    const auto ptr = new Widget{ .m_value = 1 };
    
    return 0;
}
