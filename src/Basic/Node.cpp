#include <Common/Node.h>
using namespace KTKR;

template <typename ImplT>
void Node<ImplT>::AddChild(Ptr<ImplT> _child)
{
    // remove lagency parent
    if (!_child->parent.expired())
        _child->parent.lock()->DelChild(_child);
    ;

    _child->parent = This<ImplT>();
    children.insert(_child);
}

template <typename ImplT>
void Node<ImplT>::DelChild(Ptr<ImplT> _child)
{
    if (_child->parent.lock() == This())
    {
        children.erase(_child);
        _child->parent.reset();
    }
}

template <typename ImplT>
bool Node<ImplT>::IsDescendantOf(Ptr<ImplT> node)
{
    if (node == This<ImplT>())
        return true;
    if (parent->expired())
        return false;
    return parent->lock()->IsDescendantOf(node);
}

template <typename ImplT>
bool Node<ImplT>::IsAncentorOf(Ptr<ImplT> node)
{
    return node->IsDescendantOf(This<ImplT>());
}