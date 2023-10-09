// movable
#include <concepts>
// is_nothrow_move_assignable_v
#include <type_traits>
// move
#include <utility>

auto main()
    -> int
{
    int dst_value;
    int src_value = 5;
    
    constexpr auto assign = []< std::movable V >(V& dst_value, V&& src_value)
                            noexcept(std::is_nothrow_move_assignable_v< V >)
    {
        dst_value = std::move(src_value);
    };

    //assign(dst_value, src_value);
    assign(dst_value, std::move(src_value));
    
    return dst_value;
}
