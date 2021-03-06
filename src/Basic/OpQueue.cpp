#include <Common/OpQueue.h>
#include <vector>
using namespace KTKR;
using namespace std;

OpQueue::OpQueue()
    : hold(true), queue(std::list<Ptr<Operation>>()) {}

OpQueue& OpQueue::operator<<(const Ptr<Operation>& op) {
    if (op != NULL) {
        queue.push_back(op);
    }
    return *this;
}

OpQueue& OpQueue::operator<<(Operation* op) {
    if (op != NULL) {
        (*this) << (toPtr(op));
    }
    return *this;
}

OpQueue& OpQueue::operator<<(const std::function<void()>& op) {
    if (op != NULL) {
        (*this) << (new Operation(op));
    }
    return *this;
}

void OpQueue::Run() {
    vector<list<Ptr<Operation>>::const_iterator> removeIt;
    for (auto it = queue.cbegin(); it != queue.cend(); ++it) {
        (*it)->Run();
        // 删除 isHold 为 false 的值，来区分单次执行与多次执行的函数
        if (!(*it)->isHold())
            removeIt.push_back(it);
    }
    for (int i = removeIt.size() - 1; i >= 0; i--)
        queue.erase(removeIt[i]);

    if (queue.empty())
        hold = false;
}

bool OpQueue::isHold() {
    return hold;
}

OpQueue::~OpQueue() {
    //clean all
    // vector<list<Ptr<Operation>>::const_iterator> removeIt;
    // for (auto it = queue.cbegin(); it != queue.cend(); ++it) {
    //     removeIt.push_back(it);
    // }
    // for (int i = removeIt.size() - 1; i >= 0; i--)
    //     queue.erase(removeIt[i]);
}
