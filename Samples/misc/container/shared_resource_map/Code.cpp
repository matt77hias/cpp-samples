// TODO: update

#include <map>
#include <memory>
#include <mutex>

/**
    A class of shared resource maps.

    @tparam		KeyT
                The key type.
    @tparam		ResourceT
                The resource type.
    */
template< typename KeyT, typename ResourceT >
class SharedResourceMap
{

public:

    //---------------------------------------------------------------------
    // Class Member Types
    //---------------------------------------------------------------------

    /**
        The key type of shared resource maps.
        */
    using key_type = KeyT;

    /**
        The value type of shared resource maps.
        */
    using value_type = ResourceT;

    //---------------------------------------------------------------------
    // Constructors and Destructors
    //---------------------------------------------------------------------

    /**
        Constructs a shared resource map.
        */
    SharedResourceMap() = default;

    /**
        Constructs a shared resource map from the given shared resource map.

        @param[in]		map
                    A reference to the shared resource map to copy.
        */
    SharedResourceMap(const SharedResourceMap& map) = delete;

    /**
        Constructs a shared resource map by moving the given shared resource map.

        @param[in]		map
                    A reference to the shared resource map to move.
        */
    SharedResourceMap(SharedResourceMap&& map)
        noexcept;

    /**
        Destructs this shared resource map.
        */
    ~SharedResourceMap()
        noexcept
    {
        RemoveAll();
    }

    //---------------------------------------------------------------------
    // Assignment Operators
    //---------------------------------------------------------------------

    /**
        Copies the given shared resource map to this shared resource map.

        @param[in]		map
                    A reference to the shared resource map to copy.
        @return		A reference to the copy of the given shared resource 
                    map (i.e. this shared resource map).
        */
    auto operator =(const SharedResourceMap& map)
        -> SharedResourceMap& = delete;

    /**
        Moves the given shared resource map to this shared resource map.

        @param[in]		map
                    A reference to the shared resource map to move.
        @return		A reference to the moved shared resource map (i.e. this
                    shared resource map).
        */
    auto operator =(SharedResourceMap&& map)
        -> SharedResourceMap& = delete;

    //---------------------------------------------------------------------
    // Member Methods
    //---------------------------------------------------------------------

    /**
        Checks whether this shared resource map is empty.

        @return		@c true if this shared resource map is empty. @c false
                    otherwise.
        */
    [[nodiscard]]
    auto empty() const
        noexcept -> bool;

    /**
        Returns the number of resources contained in this shared resource map.

        @return		The number of resources contained in this shared
                    resource map.
        */
    [[nodiscard]]
    auto size() const
        noexcept -> std::size_t;

    /**
        Checks whether this shared resource map contains a resource
        corresponding to the given key.

        @param[in]		key
                    A reference to the key of the resource.
        @return		@c true, if a resource is contained in this shared
                    resource map corresponding to the given key. @c false,
                    otherwise.
        */
    [[nodiscard]]
    bool Contains(const KeyT& key) noexcept;

    /**
        Returns the resource corresponding to the given key from this shared
        resource map.

        @param[in]		key
                    A reference to the key of the resource.
        @return		@c nullptr, if no resource is contained in this shared
                    resource map corresponding to the given key.
        @return		A pointer to the resource corresponding to the given
                    key from this shared resource map.
        */
    [[nodiscard]]
    std::shared_ptr< ResourceT > Get(const KeyT& key) noexcept;

    /**
        Returns the resource corresponding to the given key from this shared
        resource map. If no resource is contained in this shared resource map
        corresponding to the given key, a new resource is created from the
        given arguments, added to this shared resource map and returned.

        @tparam		ConstructorArgsT
                    The constructor argument types for creating a new
                    resource of type @c ResourceT.
        @param[in]		key
                    A reference to the key of the resource.
        @param[in]		args
                    A forwarding reference to the arguments for creating a
                    new resource of type @c ResourceT.
        @return		A pointer to the resource corresponding to the given
                    key from this shared resource map.
        */
    template< typename... ConstructorArgsT >
    std::shared_ptr< ResourceT >
        GetOrCreate(const KeyT& key, ConstructorArgsT&& ... args);

    /**
        Returns the resource corresponding to the given key from this shared
        resource map. If no resource is contained in this shared resource map
        corresponding to the given key, a new resource is created from the
        given arguments, added to this shared resource map and returned.

        @pre			@c DerivedResourceT is a derived class of @c ResourceT.
        @tparam		DerivedResourceT
                    The derived resource type.
        @tparam		ConstructorArgsT
                    The constructor argument types for creating a new
                    resource of type @c DerivedResourceT.
        @param[in]		key
                    A reference to the key of the resource.
        @param[in]		args
                    A forwarding reference to the arguments for creating a
                    new resource of type @c ResourceT.
        @return		A pointer to the resource corresponding to the given
                    key from this shared resource map.
        */
    template< typename DerivedResourceT, typename... ConstructorArgsT >
    std::shared_ptr< ResourceT >
        GetOrCreateDerived(const KeyT& key, ConstructorArgsT&& ... args);

    /**
        Removes the resource corresponding to the given key from this shared
        resource map.

        @param[in]		key
                    A reference to the key of the resource to remove.
        */
    void Remove(const KeyT& key);

    /**
        Removes all resources from this shared resource map.
        */
    void RemoveAll() noexcept;

private:

    //---------------------------------------------------------------------
    // Class Member Types
    //---------------------------------------------------------------------

    /**
        A resource map used by a shared resource map.
        */
    using ResourceMap = std::map< KeyT, std::weak_ptr< ResourceT > >;

    //---------------------------------------------------------------------
    // Member Variables
    //---------------------------------------------------------------------

    /**
        The resource map of this shared resource map.
        */
    ResourceMap m_resource_map;

    /**
        The mutex for accessing the resource map of this shared resource map.
        */
    mutable std::mutex m_mutex;

    /**
        A class of resources.

        @pre			@c ResourceT is a base type of @c DerivedResourceT.
        @tparam		DerivedResourceT
                    The derived resource type.
        */
    template< typename DerivedResourceT >
    class Resource : public DerivedResourceT
    {

    public:

        static_assert(std::is_base_of_v< ResourceT, DerivedResourceT >);

        //-----------------------------------------------------------------
        // Constructors and Destructors
        //-----------------------------------------------------------------

        /**
            Constructs a resource.

            @tparam		ConstructorArgsT
                        The constructor argument types for creating a new
                        resource.
            @param[in,out]	resource_map
                        A reference to the shared resource map.
            @param[in]		resource_key
                        A reference to the key of the resource in the given
                        shared resource map.
            @param[in]		args
                        A forwarding reference to the arguments for
                        creating a new resource of type
                        @c DerivedResourceT.
            */
        template< typename... ConstructorArgsT >
        explicit Resource(SharedResourceMap& resource_map,
                            const KeyT& resource_key,
                            ConstructorArgsT&& ... args);

        /**
            Constructs a resource from the given resource.

            @param[in]		resource
                        A reference to the resource to copy.
            */
        Resource(const Resource& resource) = delete;

        /**
            Constructs a resource by moving the given shared resource mapentry .

            @param[in]		resource
                        A reference to the resource to move.
            */
        Resource(Resource&& resource) noexcept;

        /**
            Destructs this resource.
            */
        virtual ~Resource();

        //-----------------------------------------------------------------
        // Assignment Operators
        //-----------------------------------------------------------------

        /**
            Copies the given resource to this resource.

            @param[in]		resource
                        A reference to the resource to copy.
            @return		A reference to the copy of the given resource (i.e.
                        this resource).
            */
        Resource& operator=(const Resource& resource) = delete;

        /**
            Moves the given resource to this resource.

            @param[in]		resource
                        A reference to the resource to move.
            @return		A reference to the moved resource (i.e. this
                        resource).
            */
        Resource& operator=(Resource&& resource) = delete;

    private:

        //-----------------------------------------------------------------
        // Member Variables
        //-----------------------------------------------------------------

        /**
            A reference to the shared resource map containing this resource.
            */
        SharedResourceMap& m_resource_map;

        /**
            The key of this resource in the shared resource map containing
            this resource.
            */
        KeyT m_resource_key;
    };
};

//-------------------------------------------------------------------------
// SharedResourceMap
//-------------------------------------------------------------------------

template< typename KeyT, typename ResourceT >
SharedResourceMap< KeyT, ResourceT >
    ::SharedResourceMap(SharedResourceMap&& map) noexcept
    : m_resource_map(),
    m_mutex()
{
    const std::scoped_lock lock(map.m_mutex);

    m_resource_map = std::move(map.m_resource_map);
}

template< typename KeyT, typename ResourceT >
[[nodiscard]]
inline bool SharedResourceMap< KeyT, ResourceT >::empty() const noexcept
{
    const std::scoped_lock lock(m_mutex);

    using std::empty;
    return empty(m_resource_map);
}

template< typename KeyT, typename ResourceT >
[[nodiscard]]
inline std::size_t SharedResourceMap< KeyT, ResourceT >::size() const noexcept
{
    const std::scoped_lock lock(m_mutex);

    using std::size;
    return size(m_resource_map);
}

template< typename KeyT, typename ResourceT >
[[nodiscard]]
bool SharedResourceMap< KeyT, ResourceT >::Contains(const KeyT& key) noexcept
{
    const std::scoped_lock lock(m_mutex);

    if (const auto it = m_resource_map.find(key);
        it != m_resource_map.end())
    {
        const auto resource = it->second.lock();

        if (resource)
        {
            return true;
        }

        m_resource_map.erase(it);
    }

    return false;
}

template< typename KeyT, typename ResourceT >
[[nodiscard]]
std::shared_ptr< ResourceT > SharedResourceMap< KeyT, ResourceT >
    ::Get(const KeyT& key) noexcept
{
    const std::scoped_lock lock(m_mutex);

    if (const auto it = m_resource_map.find(key);
        it != m_resource_map.end())
    {
        const auto resource = it->second.lock();

        if (resource)
        {
            return resource;
        }

        m_resource_map.erase(it);
    }

    return {};
}

template< typename KeyT, typename ResourceT >
template< typename... ConstructorArgsT >
inline std::shared_ptr< ResourceT > SharedResourceMap< KeyT, ResourceT >
    ::GetOrCreate(const KeyT& key, ConstructorArgsT&& ... args)
{
    return GetOrCreateDerived< ResourceT, ConstructorArgsT... >(
        key, std::forward< ConstructorArgsT >(args)...);
}

template< typename KeyT, typename ResourceT >
template< typename DerivedResourceT, typename... ConstructorArgsT >
std::shared_ptr< ResourceT > SharedResourceMap< KeyT, ResourceT >
    ::GetOrCreateDerived(const KeyT& key, ConstructorArgsT&& ... args)
{
    const std::scoped_lock lock(m_mutex);

    if (const auto it = m_resource_map.find(key);
        it != m_resource_map.end())
    {
        const auto resource = it->second.lock();

        if (resource)
        {
            return resource;
        }

        m_resource_map.erase(it);
    }

    const std::shared_ptr< DerivedResourceT > new_resource(
        new DerivedResourceT{ *this, key, std::forward< ConstructorArgsT >(args)... });

    m_resource_map.emplace(key, new_resource);

    return new_resource;
}

template< typename KeyT, typename ResourceT >
void SharedResourceMap< KeyT, ResourceT >::Remove(const KeyT& key)
{
    const std::scoped_lock lock(m_mutex);

    if (const auto it = m_resource_map.find(key);
        it != m_resource_map.end() && it->second.expired())
    {
        m_resource_map.erase(it);
    }
}

template< typename KeyT, typename ResourceT >
inline void SharedResourceMap< KeyT, ResourceT >::RemoveAll() noexcept
{
    const std::scoped_lock lock(m_mutex);

    m_resource_map.clear();
}

//-------------------------------------------------------------------------
// Resource
//-------------------------------------------------------------------------

template< typename KeyT, typename ResourceT >
template< typename DerivedResourceT >
template< typename... ConstructorArgsT >
SharedResourceMap< KeyT, ResourceT >::Resource< DerivedResourceT >
    ::Resource(SharedResourceMap& resource_map,
                const KeyT& resource_key,
                ConstructorArgsT&& ... args)
    : DerivedResourceT(std::forward< ConstructorArgsT >(args)...),
    m_resource_map(resource_map),
    m_resource_key(resource_key)
{}

template< typename KeyT, typename ResourceT >
template< typename DerivedResourceT >
SharedResourceMap< KeyT, ResourceT >::Resource< DerivedResourceT >
    ::Resource(Resource&& resource) noexcept = default;

template< typename KeyT, typename ResourceT >
template< typename DerivedResourceT >
SharedResourceMap< KeyT, ResourceT >::Resource< DerivedResourceT >
    ::~Resource()
{
    m_resource_map.Remove(m_resource_key);
}

struct A
{
    virtual ~A() = default;
};

int main()
{
    SharedResourceMap< int, A > map;

    return 0;
}
