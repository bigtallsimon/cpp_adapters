#ifndef __ADAPTER_FACTORY_H__
#define __ADAPTER_FACTORY_H__

/**
Interface for adapters factory.  Provides a single method for constructing
an adapter for a given adaptee.
*/
class IAdapterFactory
{
public:
    virtual void * construct_adapter(void * adaptee) = 0;
};

/**
Concrete adapter factory for constructing adapters of type TAdapter when given
objects of type TAdaptee
*/
template<typename TAdapter, typename TAdaptee>
class AdapterFactory : public IAdapterFactory
{
public:
    virtual void * construct_adapter(void * adaptee)
    {
        return new TAdapter(static_cast<TAdaptee *>(adaptee));
    }
};

#endif
