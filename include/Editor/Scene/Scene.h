#pragma once

/*

    collection of objects in scene
    
*/

#include <Common/Heap.h>

#include "SceneObject.h"
#include <Editor/Scene/AllCmpts.h>
#include <string>
#include <mutex>
#include <map>

namespace LUNA
{
    class Scene : public KTKR::HeapObj
    {

        using SObj = SceneObject;

    private:
        KTKR::Ptr<SObj> root;
        std::map<std::string, int> name2ID;
        std::map<int, std::string> ID2name;

        mutable std::mutex writeLock;

    public:
        std::string name;

        Scene(KTKR::Ptr<SObj> root, const std::string &name = "") : root{root}, name{name} {}
        static const KTKR::Ptr<Scene> Create(KTKR::Ptr<SObj> root, const std::string &name = "")
        {
            if (!root->HaveComponent<Editor::CmptTransform>())
                root->AddComponent<Editor::CmptTransform>();
            
            return KTKR::Create<Scene>(root, name);
        }

    protected:
        virtual ~Scene() = default;

    public:
        const KTKR::Ptr<SObj> GetRoot() const { return root; }

        // sobjs have no same name
        // ID >= 1
        bool GenID();

        // ID >= 1, return 0 if error
        int GetID(KTKR::Ptr<SObj> sobj) const;
        // ID >= 1, return "" if error
        const std::string GetName(int ID) const;

        void SetWriteLock(bool isLock);

        void AddSobj(KTKR::Ptr<SObj> sobj);
    };
} // namespace LUNA
