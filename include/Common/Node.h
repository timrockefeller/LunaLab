#pragma once
#include <Common/Heap.h>
#include <set>
namespace KTKR
{
    template <typename ImplT>
    class Node : public HeapObj
    {
    protected:
        Node(Ptr<ImplT> parent = nullptr)
            : parent(parent) {}

        virtual ~Node() = default;

    public:
        void AddChild(Ptr<ImplT> _child);
        void DelChild(Ptr<ImplT> _child);

    public:
        bool IsDescendantOf(Ptr<ImplT> node);
        bool IsAncentorOf(Ptr<ImplT> node);

    public:
        const Ptr<ImplT> GetParent() const { return parent.lock(); }
        const std::set<Ptr<ImplT>> &GetChildren() const { return children; }

    protected:
        void LateInit() override
        {
            const Ptr<ImplT> parent = GetParent();
            if (parent)
            {
                parent->AddChild(This<ImplT>());
            }
        }

    private:
        WPtr<ImplT> parent;
        std::set<Ptr<ImplT>> children;
    };
} // namespace KTKR
