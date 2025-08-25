// std::size_t
#include <cstddef>
// std::cout
// std::endl
#include <iostream>
// std::unique_resource
#include <https://raw.githubusercontent.com/PeterSommerlad/scope17/master/scope.hpp>

struct ResourceManager
{
    using Handle = std::size_t;
    
    [[nodiscard("Resource leak")]]
    auto Acquire()
		-> Handle
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
        void operator ()(Handle resource) const
			noexcept
        {
            std::cout << "DeleteResource" << std::endl << "  ";
            m_manager->Release(resource);
        }

        ResourceManager* m_manager;
    };

    using UniqueHandle = SCOPE_NS_PREFIX::unique_resource< ResourceManager::Handle, ResourceManager::Deleter >;

    [[nodiscard]]
    auto Create()
		-> UniqueHandle
    {
        std::cout << "CreateResource" << std::endl << "  ";
        return { Acquire(), Deleter{ this } };
    }
};

auto main()
	-> int
{
	ResourceManager manager;
    auto resource = manager.Create();
    std::cout << resource.get() << std::endl;

    std::cout << sizeof(ResourceManager::Handle)       << std::endl;
    std::cout << sizeof(ResourceManager::Deleter)      << std::endl;
    std::cout << sizeof(ResourceManager::UniqueHandle) << std::endl;

    return 0;
}
