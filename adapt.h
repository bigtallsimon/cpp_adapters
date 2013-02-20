#ifndef __ADAPT_H__
#define __ADAPT_H__

#include <iostream>
#include <utility>
#include <typeinfo>

using namespace std;

template <typename TAdapter, typename TSource, typename TTarget>
int adapts()
{
    TSource * source_type_ptr;
    type_info const & adaptee_type = typeid(source_type_ptr);
    TTarget* target_type_ptr;
    type_info const & target_type = typeid(target_type_ptr);
    cout << "Adding entry " << adaptee_type.name() << "->" << target_type.name() << endl;
    type2adapterfactory[make_pair(&adaptee_type, &target_type)] =
        new AdapterFactory<TAdapter, TSource>();
    return 0;
}


template<typename TTargetType, typename TSourceType>
TTargetType * adapt(TSourceType * adaptee)
{
    type_info const & adaptee_type = typeid(adaptee);
    TTargetType * target_type_ptr;
    type_info const & target_type = typeid(target_type_ptr);
    cout << adaptee_type.name() << "->" << target_type.name() << endl;
    IAdapterFactory * adapter_factory =
        type2adapterfactory[make_pair(&adaptee_type, &target_type)];
    return static_cast<TTargetType *>(adapter_factory->construct_adapter(adaptee));
}


#endif 
