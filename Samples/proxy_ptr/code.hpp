#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace experimental {
    struct Component { 
        virtual ~Component() = default;
        virtual void Test() const noexcept {
            std::cout << "Component::test()" << std::endl;
        }
    };
    struct Camera : Component {
        virtual void Test() const noexcept {
            std::cout << "Camera::test()" << std::endl;
        }
    };
    struct Light  : Component {
        virtual void Test() const noexcept {
            std::cout << "Light::test()" << std::endl;
        }
    };

    std::vector< Camera > g_cameras; 
    std::vector< Light >  g_lights;

    template< typename T >
    T &Get(size_t index) noexcept;
    template<>
    inline Camera &Get< Camera >(size_t index) noexcept {
        return g_cameras[index];
    }
    template<>
    inline Light &Get< Light >(size_t index) noexcept {
        return g_lights[index];
    }

    template< typename T >
    struct H final {
  
        explicit H(std::function< T *() > getter) 
            : m_getter(std::move(getter)) {}
    
        H(const H &h) = default;
        H(H &&h) = default;
    
        template< typename U >
        H(const H< U > &h) 
            : m_getter(h.m_getter) {}
        template< typename U >
        H(H< U > &&h) 
            : m_getter(std::move(h.m_getter)) {}
    
        ~H() = default;
    
        H &operator=(const H &h) = default;
        H &operator=(H &&h) = default;
    
        explicit operator bool() const noexcept {
            return nullptr != Get();
        }
    
        T &operator*() const { 
            return *Get(); 
        }
        T *operator->() const { 
            return  Get(); 
        }
        T *Get() const { 
            return m_getter(); 
        }
    
        std::function< T *() > m_getter;
    };
    
    template< typename U >
    static H< U > Create(size_t index) {
        return H< U >([index]() { 
            return index == 0 ? nullptr : &experimental::Get< U >(index - 1); 
        });
    }
}

using namespace experimental;

int main() {
    // Sizes
    std::cout << "Size of a raw    ptr: " << sizeof(Component *) << std::endl;
    std::cout << "Size of a unique ptr: " << sizeof(std::unique_ptr< Component *() >) << std::endl;
    std::cout << "Size of a shared ptr: " << sizeof(std::shared_ptr< Component *() >) << std::endl;
    std::cout << "Size of a handle ptr: " << sizeof(H< Component *() >) << std::endl;
    
    // Populate
    g_cameras.emplace_back();
    g_lights.emplace_back();
    
    H< Component > camera = Create< Camera >(1);
    H< Component > light  = Create< Light >(1);
    camera->Test();
    light->Test();
    
    return 0;
}
