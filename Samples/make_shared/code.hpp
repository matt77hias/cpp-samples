#include <memory>
#include <iostream>

bool logging = false;

void* operator new(std::size_t size) {
    const auto ptr = std::malloc(size);
    if (logging) {
        std::cout << "Allocated: " << (uintptr_t)ptr << std::endl;
    }
    return ptr;
}
void operator delete(void* ptr) noexcept {
    std::free(ptr);
    if (logging) {
       std::cout << "Deallocated: " << (uintptr_t)ptr << std::endl; 
    }
}

struct Widget {
    ~Widget() {
        std::cout << "Widget::~Widget()" << std::endl;
    }
    int data;
};

void test(bool use_make_shared) {
    std::shared_ptr< Widget > sp;
    if (use_make_shared) {
        sp = std::make_shared< Widget >();
    } else {
        sp = std::shared_ptr< Widget >(new Widget());
    }
    std::weak_ptr< Widget > wp(sp);
    
    sp.reset();
    std::cout << "No std::shared_ptr's anymore." << std::endl;
    wp.reset();
    std::cout << "No std::weak_ptr's anymore." << std::endl;
}

int main() { 
    logging = true;
    test(true);
    std::cout << std::endl;
    test(false);
    logging = false;
    
    return 0;
};
