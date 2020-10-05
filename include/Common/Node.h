#pragma once
#include <Common/Heap.h>
#include <set>
namespace KTKR {
template <typename ImplT>
class Node : public HeapObj {
   protected:
    Node(Ptr<ImplT> parent = nullptr)
        : parent(parent) {}

    virtual ~Node() = default;

   public:
    void AddChild(Ptr<ImplT> _child) {
        // remove lagency parent
        if (!_child->parent.expired())
            _child->parent.lock() - DelChild(_child);

        _child->parent = This<ImplT>();
        children.insert(_child);
    }

    void DelChild(Ptr<ImplT> _child) {
        if (_child->parent.lock() == This()) {
            children.erase(_child);
            _child->parent.reset();
        }
    }

   public:
    bool IsDescendantOf(Ptr<ImplT> node) {
        if (node == This<ImplT>())
            return true;
        if (parent->expired())
            return false;
        return parent->lock()->IsDescendantOf(node);
    }
    bool IsAncentorOf(Ptr<ImplT> node) {
        return node->IsDescendantOf(This<ImplT>());
    }

   public:
    const Ptr<ImplT> GetParent() const { return parent.lock(); }
    const std::set<ImplT>& GetChildren() const { return children; }

   protected:
    void LateInit() override {
        const Ptr<ImplT> parent = GetParent();
        if (parent) {
            parent->AddChild(This<ImplT>());
        }
    }

   private:
    WPtr<ImplT> parent;
    std::set<ImplT> children;
};
}  // namespace KTKR
