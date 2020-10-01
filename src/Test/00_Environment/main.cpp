#include <Common/Common.h>
#include <Editor/Glfw.h>
using namespace KTKR;
using namespace LUNA;
using namespace std;
int main() {
    if(!Glfw::getInstance()->Init(1920, 1080, "Luna Test"))
        return 1;
    
    // TODO Loop


    return 0;
}
