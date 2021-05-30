#pragma once

#include <functional>

#include <Common/Common.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace LUNA::Editor
{

    // =================================================
    // Warning
    //              Only runable after
    // ```
    //              ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    //              ImGui::Columns(2);
    // ```
    //              before
    // ```
    //              ImGui::PopStyleVar();
    // ```
    // =================================================

    inline void ColumnItem(
        const char *title, const char *id, float *v, float step = 0.0f, float step_fast = 0.0f, std::function<void()> callback = []() {})
    {
        {
            ImGui::AlignTextToFramePadding();
            ImGui::BulletText(title);
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1);
            if (ImGui::InputFloat(id, v, step, step_fast))
                callback();
            ImGui::NextColumn();
        }
    }

    inline void ColumnItem(
        const char *title, const char *id, double *v, double step = 0.0f, double step_fast = 0.0f, std::function<void()> callback = []() {})
    {

        {
            ImGui::AlignTextToFramePadding();
            ImGui::BulletText(title);
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1);
            if (ImGui::InputDouble(id, v, step, step_fast))
                callback();
            ImGui::NextColumn();
        }
    }

    inline void ColumnItem(
        const char *title, const char *id, int *v, int step = 0, int step_fast = 0, std::function<void()> callback = []() {})
    {

        {
            ImGui::AlignTextToFramePadding();
            ImGui::BulletText(title);
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1);
            if (ImGui::InputInt(id, v, step, step_fast))
                callback();
            ImGui::NextColumn();
        }
    }

    inline void ColumnItem(
        const char *title, const char *id, int *v, const char *const items[], int size, std::function<void()> callback = []() {})
    {

        {
            ImGui::AlignTextToFramePadding();
            ImGui::BulletText(title);
            ImGui::NextColumn();
            ImGui::SetNextItemWidth(-1);
            if (ImGui::Combo(id, v, items, size))
                callback();
            ImGui::NextColumn();
        }
    }
}