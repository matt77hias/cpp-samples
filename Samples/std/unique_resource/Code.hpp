#include <iostream>
#include <https://raw.githubusercontent.com/PeterSommerlad/scope17/master/scope.hpp>

struct ResourceManager
{
    using Handle = std::size_t;
    
    [[nodiscard("Resource leak")]]
    Handle Acquire()
    {
        std::cout << "ResourceManager::Acquire" << std::endl;
        return 1u;
    }

    void Release(Handle)
    {
        std::cout << "ResourceManager::Deallocate" << std::endl;
    }

    struct Deleter
    {
        void operator ()(Handle resource) const noexcept
        {
            std::cout << "DeleteResource" << std::endl << "  ";
            m_manager->Release(resource);
        }

        ResourceManager* m_manager;
    };

    using UniqueHandle = SCOPE_NS_PREFIX::unique_resource< ResourceManager::Handle, ResourceManager::Deleter >;

    [[nodiscard]]
    UniqueHandle Create()
    {
        std::cout << "CreateResource" << std::endl << "  ";
        return { Acquire(), Deleter{ this } };
    }
};

int main()
{
	ResourceManager manager;
    auto resource = manager.Create();
    std::cout << resource.get() << std::endl;

    std::cout << sizeof(ResourceManager::Handle)       << std::endl;
    std::cout << sizeof(ResourceManager::Deleter)      << std::endl;
    std::cout << sizeof(ResourceManager::UniqueHandle) << std::endl;

    return 0;
}
