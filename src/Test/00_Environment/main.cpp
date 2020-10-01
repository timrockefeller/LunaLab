#include <Common/Common.h>
#include <Editor/Glfw.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
using namespace KTKR;
using namespace LUNA;
using namespace std;
int main() {
    if(!Glfw::getInstance()->Init(1920, 1080, "Luna Test"))
        return 1;
    Glfw::getInstance()->RunDemo();
    return 0;
}
