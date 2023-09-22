union Widget 
{
    int m_first = 5;
    int m_second;
};

auto main()
    -> int
{
    constexpr Widget w = {};
	static_assert(w.m_first == 5);

    return w.m_first;
}
