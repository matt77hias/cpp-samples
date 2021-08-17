// copy_constructible
#include <concepts>
// nullptr_t
#include <cstddef>

static_assert(std::copy_constructible< std::nullptr_t >);
