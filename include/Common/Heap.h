#pragma once
#include <Common/Ptr.h>
namespace KTKR {

class HeapObj : public std::enable_shared_from_this<HeapObj> {
    template <typename ImplT, typename... Args>
    friend const Ptr<ImplT> New(Args&&... args);

   protected:
    template <typename T = HeapObj>
    const Ptr<T> This() { return CastTo<T>(shared_from_this()); }
    template <typename T = HeapObj>
    const PtrC<T> This() const { return CastTo<const T>(shared_from_this()); }
    template <typename T = HeapObj>
    const WPtr<T> WThis() noexcept { return CastTo<T>(weak_from_this()); }
    template <typename T = HeapObj>
    const WPtrC<T> WThis() const noexcept { return CastTo<const T>(weak_from_this()); }

   protected:
   /*
    In order to use 4 pointer function defined previously, the initializer need be called after 'new' called. 
   */
    virtual void LateInit() {}

   private:
    static void Delete(HeapObj* obj) { delete obj; }

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
    using std::enable_shared_from_this<HeapObj>::shared_from_this;
    using std::enable_shared_from_this<HeapObj>::weak_from_this;
};

// https://stackoverflow.com/questions/48327250/in-function-parameter-pack
// Combining forwarding reference with parameter pack, one can write easily generic proxy functions without performance loss in terms of lvalue/rvalue.
template <typename ImplT, typename... Args>
const Ptr<ImplT> New(Args&&... args) {
    const auto pImplT = Ptr<ImplT>(new ImplT(std::forward<Args>(args)...), HeapObj::Delete);
    auto pHeap = static_cast<Ptr<HeapObj>>(pImplT);
    pHeap->LateInit();
    return pImplT;
}

}  // namespace KTKR
