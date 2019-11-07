union Widget 
{
    int m_first = 5;
    int m_second;
};

int main()
{
    constexpr Widget w = {};
    return w.m_first;
}
