#pragma once
#include "LocalStorage.h"
#include "GSName.h"
#include <Common/Singleton.h>
namespace LUNA
{
    template <typename T>
    class GlobalStorage : public KTKR::Singleton_Lagacy<GlobalStorage<T>>, public LocalStorage<T>
    {
        friend class KTKR::Singleton_Lagacy<GlobalStorage<T>>;

    private:
        GlobalStorage() = default;
        ~GlobalStorage() = default;
    };

    template <typename T>
    using _GS = GlobalStorage<T>;
} // namespace LUNA