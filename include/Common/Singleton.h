#pragma once
#include <mutex>
#include <type_traits>
namespace KTKR {
template <typename T, typename = std::enable_if<std::is_class<T>::value>>
class Singleton_Lagacy {
   public:
    static T* getInstance() noexcept {
        static T* instance = new T;
        return instance;
    }

   protected:
    Singleton_Lagacy() = default;
    virtual ~Singleton_Lagacy() = default;

   private:
    Singleton_Lagacy(const Singleton_Lagacy&) = delete;
    Singleton_Lagacy& operator=(const Singleton_Lagacy&) = delete;
};

template <typename T>
class Singleton {
   public:
    static T& getInstanceObj() {
        static std::once_flag flag;
        std::call_once(flag, &Singleton::Get);
        return Get();
    }
    static T* getInstance() {
        static std::once_flag flag;
        std::call_once(flag, &Singleton::Get);
        return &Get();
    }

   protected:
    Singleton() = default;
    virtual ~Singleton() = default;

   private:
    static T& Get() {
        static T instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    const Singleton& operator=(const Singleton&) = delete;
    const Singleton& operator=(Singleton&&) = delete;
};
}  // namespace KTKR
