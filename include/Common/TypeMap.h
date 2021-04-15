#pragma once
#include <typeinfo>
#include <unordered_map>
namespace KTKR {
using TypeInfoRef = std::reference_wrapper<const std::type_info>;

struct Hasher {
    std::size_t operator()(TypeInfoRef code) const {
        return code.get().hash_code();
    }
};
struct EqualTo {
    bool operator()(TypeInfoRef a, TypeInfoRef b) const {
        return a.get() == b.get();
    }
};
template <typename T>
using TypeMap = std::unordered_map<TypeInfoRef, T, Hasher, EqualTo>;
}  // namespace KTKR
