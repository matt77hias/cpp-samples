struct Widget
{
    int* m_a;
    int& m_b;
    int  m_c;
};

auto main()
	-> int
{
    int i = 0;
    const Widget w{ .m_a = &i, .m_b = i, .m_c = i };
    
    *w.m_a = 1;
     w.m_b = 2;
    //w.m_c = 3;

    return i;
}
