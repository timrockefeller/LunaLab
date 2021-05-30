#include <3rdParty/taskflow/taskflow.hpp>
#include <Ikit/STL/Singleton.h>
#include "Ptr.h"
#include <functional>
#include <vector>
//runtime task manager

namespace KTKR
{
    class TaskFlow : public KTKR::Singleton<TaskFlow>
    {

        Ptr<tf::Executor> exe;
        std::vector<tf::Taskflow> tfs;
    public:
        TaskFlow() : exe{std::make_shared<tf::Executor>()}
        {
        }
        ~TaskFlow()
        {
            exe->wait_for_all();
        };
        void RunTaskAsyc(std::function<void()>);
    };
}