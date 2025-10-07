struct Widget
{
    bool m_first : 1;
    bool m_second : 1;
};

auto main() -> int
{
    return static_cast< int >(sizeof(Widget));
}
