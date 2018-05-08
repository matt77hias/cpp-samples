#include <iostream>
 
struct Widget {
  Widget() { std::cout << "Widget::Widget()" << std::endl; };
  Widget(const Widget&) = delete;
  Widget(const Widget&&) = delete;
  ~Widget() { std::cout << "Widget::~Widget()" << std::endl; };
  Widget &operator=(const Widget&) = delete;
  Widget &operator=(const Widget&&) = delete;
};

Widget f_non_const() {
    std::cout << "f_non_const" << std::endl;
    return Widget();
}
const Widget f_const() {
    std::cout << "f_const" << std::endl;
    return Widget();
}

int main() {
    const Widget w0 = f_non_const();
    const Widget w1 = f_const();
    return 0;
}
