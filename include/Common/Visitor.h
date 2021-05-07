#pragma once
#include "Ptr.h"
#include "TypeMap.h"
#include <functional>
#include <map>
#include <tuple>
#include <type_traits>
#include <typeindex>

namespace KTKR
{
    template <typename BasePtr, typename Func>
    class default_vtable
    {
    public:
        template <typename T>
        inline void Set(Func f)
        {
            data_[std::type_index(typeid(T))] = f;
        }
        inline Func Get(BasePtr base) { return data_[std::type_index(typeid(*base))]; }

    private:
        std::map<std::type_index, Func> data_;
    };

    template <typename Base>
    class default_pointer
    {
    public:
        using type = Base *;
        template <typename Derived>
        static inline Derived *cast(Base *base)
        {
            return static_cast<Derived *>(base);
        }
    };

    template <typename, typename Base, typename, typename, typename = default_pointer<Base>,
              template <typename, typename> typename = default_vtable>
    class GeneralVisitor;

    template <typename Visitor, typename Base, typename... Deriveds, typename Pointer,
              template <typename, typename> typename Vtable, typename R, typename... Args>
    class GeneralVisitor<Visitor, Base, std::tuple<Deriveds...>, R(Args...), Pointer, Vtable>
    {
        using BasePtr = typename Pointer::type;
        using VtableType = Vtable<BasePtr, R (*)(Visitor *, BasePtr, Args...)>;

    public:
        R Visit(BasePtr base, Args... args)
        {
            static VtableType vtable = BuildVtable();
            return vtable.Get(base)(static_cast<Visitor *>(this), base, std::forward<Args>(args)...);
        }

    private:
        template <typename Derived, typename... Rest>
        static void Register(VtableType &vtable)
        {
            vtable.template Set<Derived>([](Visitor *visitor, BasePtr base, Args... args) -> R {
                return visitor->ImplVisit(Pointer::template cast<Derived>(base), std::forward<Args>(args)...);
            });
            if constexpr (sizeof...(Rest) > 0)
            {
                Register<Rest...>(vtable);
            }
        }

        static VtableType BuildVtable()
        {
            VtableType vtable;
            Register<Deriveds...>(vtable);
            return vtable;
        }
    };

    template <typename... Visitors>
    class MultiVisitors : public Visitors...
    {
    public:
        using Visitors::Visit...;
    };
    // =================================================
    // Shared Pointer

    template <typename BasePtr, typename Func>
    class shared_vtable
    {
    public:
        template <typename T>
        inline void Set(Func f)
        {
            data_[std::type_index(typeid(T))] = f;
        }
        inline Func Get(BasePtr base) { return data_[std::type_index(typeid(*base))]; }

    private:
        std::map<std::type_index, Func> data_;
    };

    template <typename Base>
    class shared_pointer
    {
    public:
        using type = Ptr<Base>;
        template <typename Derived>
        static inline Ptr<Derived> cast(Ptr<Base> base)
        {
            return std::static_pointer_cast<Derived>(base);
        }
    };

    template <typename, typename Base, typename, typename, typename = shared_pointer<Base>,
              template <typename, typename> typename = shared_vtable>
    class SharedVisitor;

    template <typename Visitor, typename Base, typename... Deriveds, typename Pointer,
              template <typename, typename> typename Vtable, typename R, typename... Args>
    class SharedVisitor<Visitor, Base, std::tuple<Deriveds...>, R(Args...), Pointer, Vtable>
    {
        using BasePtr = typename Pointer::type;
        using VtableType = Vtable<BasePtr, R (*)(Visitor *, BasePtr, Args...)>;

    public:
        R Visit(BasePtr base, Args... args)
        {
            static VtableType vtable = BuildVtable();
            return vtable.Get(base)(static_cast<Visitor*>(this), base, std::forward<Args>(args)...);
        }

    private:
        template <typename Derived, typename... Rest>
        static void Register(VtableType &vtable)
        {
            vtable.template Set<Derived>([](Visitor *visitor, BasePtr base, Args... args) -> R {
                return visitor->ImplVisit(Pointer::template cast<Derived>(base), std::forward<Args>(args)...);
            });
            if constexpr (sizeof...(Rest) > 0)
            {
                Register<Rest...>(vtable);
            }
        }

        static VtableType BuildVtable()
        {
            VtableType vtable;
            Register<Deriveds...>(vtable);
            return vtable;
        }
    };

    template <typename... Visitors>
    class SharedMultiVisitors : public Visitors...
    {
    public:
        using Visitors::Visit...;
    };
} // namespace KTKR
