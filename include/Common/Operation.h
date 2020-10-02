/*
    COPYRIGHT TO Kitekii 2020

    该类抽象并封装了functional，成为函数指针，更容易被引用。
*/

#pragma once
#include <functional>
#include <memory>

namespace KTKR {
class Operation {
    friend class OpQueue;

   public:
    /**
     * @param op_ 函数本体
     * @param isHold_
     */
    Operation(const std::function<void()>& op_, bool isHold_ = true);

    bool isHold();

    void Run();

    void operator()();

   protected:
    std::function<void()> op;
    bool hold;

   private:
    // 禁用复制与赋值，保证其初始化与执行作用域相同
    Operation(const Operation&) = delete;
    Operation& operator=(const Operation&) = delete;
};

}  // namespace KTKR
