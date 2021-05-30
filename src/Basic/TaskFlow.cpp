#include <Common/Taskflow.h>

void KTKR::TaskFlow::RunTaskAsyc(std::function<void()> fn)
{
    exe->silent_async(fn);
}