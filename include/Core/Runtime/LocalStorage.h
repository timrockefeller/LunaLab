#pragma once
#include <map>
#include <string>

namespace LUNA
{

    template <typename T>
    class LocalStorage
    {
    public:
        LocalStorage() = default;
        ~LocalStorage() = default;

        bool Register(const std::string &uniqueID, const T &item);

        bool Unregister(const std::string &uniqueID);

        T *getPtr(const std::string &uniqueID);

    private:
        std::map<std::string, T> directory;
    };

    template <typename T>
    bool LocalStorage<T>::Register(const std::string &uniqueID, const T &item)
    {
        auto target = directory.find(uniqueID);
        if (target != directory.end())
        {
            target->second = item;
            return false;
        }
        directory[uniqueID] = item;
        return true;
    }

    template <typename T>
    bool LocalStorage<T>::Unregister(const std::string &uniqueID)
    {
        auto target = directory.find(uniqueID);
        if (target == directory.end())
            return false;

        directory.erase(target);
        return true;
    }

    template <typename T>
    T *LocalStorage<T>::getPtr(const std::string &uniqueID)
    {
        auto target = directory.find(uniqueID);
        if (target == directory.end())
            return NULL;

        return &(target->second);
    }

} // namespace LUNA