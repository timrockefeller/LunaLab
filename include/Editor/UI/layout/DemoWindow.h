#pragma once
#include <Core/Runtime/GlobalStorage.h>
#include <Common/Common.h>
#include "../ViewComponent.h"

namespace LUNA::Editor
{

    class DemoWindow : public ViewComponent
    {
    protected:
        const ImVec4 clear_color = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    public:
        virtual bool Enter() const
        {
            _GS<ImVec4>::getInstance()->Register("clear_color", ImVec4(0.15f, 0.15f, 0.15f, 1.00f));
            _GS<int>::getInstance()->Register("pointsize", 5);

            _GS<bool>::getInstance()->Register("ply1", true);
            _GS<bool>::getInstance()->Register("ply2", false);

            return false;
        }
        virtual bool Draw() const
        {
            static bool show_demo_window = true;
            static bool show_another_window = false;
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::Checkbox("ply original", _GS<bool>::getInstance()->getPtr("ply1"));
                ImGui::Checkbox("ply adjusted", _GS<bool>::getInstance()->getPtr("ply2"));

                ImGui::SliderInt("point size", _GS<int>::getInstance()->getPtr("pointsize"), 1, 10);          // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float *)_GS<ImVec4>::getInstance()->getPtr("clear_color")); // Edit 3 floats representing a color

                if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }
            return false;
        }
        virtual bool Close() const { return false; }
        virtual ~DemoWindow() = default;
    };

} // namespace LUNA::Editor
