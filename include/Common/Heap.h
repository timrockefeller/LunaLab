#pragma once
#include <Common/Ptr.h>
namespace KTKR {

class Heap : public std::enable_shared_from_this<Heap> {
    template <typename ImplT, typename... Args>
    friend const Ptr<ImplT> New(Args&&... args);

   protected:
    template <typename T = Heap>
    const Ptr<T> This() { return CastTo<T>(shared_from_this()); }
    template <typename T = Heap>
    const PtrC<T> This() const { return CastTo<const T>(shared_from_this()); }
    template <typename T = Heap>
    const WPtr<T> WThis() noexcept { return CastTo<T>(weak_from_this()); }
    template <typename T = Heap>
    const WPtrC<T> WThis() const noexcept { return CastTo<const T>(weak_from_this()); }

   protected:
    virtual void LateInit() {}

   private:
    static void Delete(Heap* obj) { delete obj; }

   private:
    void* operator new(size_t size) {
        if (void* mem = malloc(size))
            return mem;
        else
            throw std::bad_alloc();
    }
    void operator delete(void* mem) noexcept {
        free(mem);
    }

   private:
    using std::enable_shared_from_this<Heap>::shared_from_this;
    using std::enable_shared_from_this<Heap>::weak_from_this;
};

// https://stackoverflow.com/questions/48327250/in-function-parameter-pack
// Combining forwarding reference with parameter pack, one can write easily generic proxy functions without performance loss in terms of lvalue/rvalue.
template <typename ImplT, typename... Args>
const Ptr<ImplT> New(Args&&... args) {
    const auto pImplT = Ptr<ImplT>(new ImplT(std::forward<Args>(args)...), Heap::Delete);
    auto pHeap = static_cast<Ptr<Heap>>(pImplT);
    pHeap->LateInit();
    return pImplT;
}

}  // namespace KTKR
