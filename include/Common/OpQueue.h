/*
    COPYRIGHT TO Kitekii 2020

    函数队列，
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
    // 禁用复制与赋值，保证其初始化与执行作用域相同
    OpQueue(const OpQueue&) = delete;
    OpQueue& operator=(const OpQueue&) = delete;
};

}  // namespace KTKR
