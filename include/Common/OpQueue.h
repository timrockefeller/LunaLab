/*
    COPYRIGHT TO Kitekii 2020
*/
#pragma once
#include <Common/Operation.h>
#include <Common/Ptr.h>
#include <list>

namespace KTKR {

class OpQueue {
   public:
    OpQueue();
    ~OpQueue();
    OpQueue& operator<<(const Ptr<Operation>& op);
    OpQueue& operator<<(Operation* op);
    OpQueue& operator<<(const std::function<void()>& op);

    void Run();
    bool isHold();

    template <typename T>
    static Ptr<T> toPtr(T* op) {
        return Ptr<T>(op, [&](T* op_) { delete op_; });
    }

   protected:
    bool hold;
    std::list<Ptr<Operation>> queue;

   private:
    // disable copy and assignment, ensure the object in same scope between init and inject
    OpQueue(const OpQueue&) = delete;
    OpQueue& operator=(const OpQueue&) = delete;
};

}  // namespace KTKR
