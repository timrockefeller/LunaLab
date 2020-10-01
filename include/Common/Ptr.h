// 指针相关
#pragma once

#include <memory>
#include <typeinfo>

namespace KTKR {

template <typename T>
using Ptr = std::shared_ptr<T>;

template <typename T>
using PtrC = Ptr<T>;

template <typename T>
using WPtr = std::weak_ptr<T>;

template <typename T>
using WPtrC = WPtr<const T>;

// use _ to avoid _Vector_alloc, base class of vector
template <template <typename, typename...> class ContainerT, typename ValT, typename... Args>
ContainerT<PtrC<ValT>> Const(const ContainerT<Ptr<ValT>, Args...>& c) {
    return ContainerT<PtrC<ValT>>(c.begin(), c.end());
}

}  // namespace KTKR
