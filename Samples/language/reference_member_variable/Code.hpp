struct A
{
    int& m_i;
};

int main()
{
    int i = 0;
    const A a = { .m_i = i };
    a.m_i = 7;
    return i;
}
