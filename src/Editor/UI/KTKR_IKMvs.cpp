#include <string>
#include <imgui/imgui_stdlib.h>

#include <IKMvs/SfM/SfM.h>

#include <Common/Taskflow.h>

#include <Core/Runtime/GlobalStorage.h>
#include <Core/OpenGL/Obj/FmtPLY.h>
#include <Core/OpenGL/Shader.h>

#include <Editor/UI/layout/KTKR_IKmvs.h>
#include <Editor/Scene/AllCmpts.h>
#include <Editor/GView.h>
#include <Editor/UI/UIUtils.h>

using namespace std;
using namespace KTKR;
using namespace LUNA;
using namespace LUNA::Editor;

namespace KTKR::MVS::Private
{
    const char *str_FEATURE_DETECTOR[] = {
        "SIFT",
        "SURF",
        "ORB"};
    const char *str_FEATURE_MATCHER[] = {
        "FLANN",
        "BRUTE"};
    const char *str_MATCH_PAIR_ELECTOR[] = {
        "Best Homography",
        "Sequencial"};

    // const char *str_RUN_MODE[] = {
    //     "Custom Image Set",
    //     ""
    // }
}

bool KTKR_IKMvs::Enter()
{
    // =================================================
    // Render Pipeline
    plyshader = std::make_shared<Shader>("../assets/shader/ply.vs", "../assets/shader/ply.fs");
    _GS<std::string>::getInstance()->Register(IKMVS_PLY_LOAD_PATH, "../assets/pointcloud/06_result_sanae_3_points.ply");
    _GS<std::vector<KTKR::Ptr<Shader>>>::getInstance()->getPtr(RES_SHADER)->push_back(plyshader);

    // =================================================
    // MVS Core
    MVS::SfM::Get()->Init();
    MVS::SfM::Get()->SetConfig(_conf);

    _conf_modified = false;

    return false;
}
bool KTKR_IKMvs::Draw()
{
    ImGui::Begin("IKMvs");
    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("IKMvs_Tabbar", tab_bar_flags))
    {
        if (ImGui::BeginTabItem("PLY"))
        {
            ImGui::TextWrapped("Load .PLY directly to heirachy.");
            ImGui::Spacing();
            ImGui::InputTextWithHint("ply filepath", "( absolute )", _GS<std::string>::getInstance()->getPtr(IKMVS_PLY_LOAD_PATH));
            if (ImGui::Button("Load"))
            {
                auto filepath = _GS<std::string>::getInstance()->getPtr(IKMVS_PLY_LOAD_PATH);
                auto plyobj = FmtPLY::create(*filepath);
                if (plyobj != nullptr)
                {
                    // ./asset/example.ply -> example.ply
                    auto sobj = SceneObject::Create(plyobj->filePath.substr(plyobj->filePath.find_last_of("/") + 1));
                    sobj->AddComponent<CmptGeometry>(plyobj, plyshader);
                    Editor::GView::Get()->AddSobjToTop(sobj);
                }
            }
            ImGui::EndTabItem();
        }

        // =================================================

        if (ImGui::BeginTabItem("Calib"))
        {
            ImGui::TextWrapped("Calibrate your camera.");
            ImGui::SameLine();
            HelpMarker("In this section you will get a .txt file contained several important parameter of your camera.");
            ImGui::Spacing();
            ImGui::EndTabItem();
        }

        // =================================================

        if (ImGui::BeginTabItem("Pipeline"))
        {
            ImGui::TextWrapped("Customable pipeline of SfM processing.");
            ImGui::Spacing();
            // =================================================
            // Source
            if (ImGui::CollapsingHeader("Source", ImGuiTreeNodeFlags_None))
            {
            }
            // =================================================
            // Config
            if (ImGui::CollapsingHeader("Methods", ImGuiTreeNodeFlags_None))
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
                ImGui::Columns(2);

                ColumnItem("Feature Detector", "##Feature Detector", &_conf.FEATURE_DETECTOR, KTKR::MVS::Private::str_FEATURE_DETECTOR, 3, [&]() { _conf_modified = true; });
                ColumnItem("Feature Matcher", "##Feature Matcher", &_conf.FEATURE_MATCHER, KTKR::MVS::Private::str_FEATURE_MATCHER, 2, [&]() { _conf_modified = true; });
                ColumnItem("Match Pair Selector", "##Match Pair Selector", &_conf.MATCH_PAIR_ELECTOR, KTKR::MVS::Private::str_MATCH_PAIR_ELECTOR, 2, [&]() { _conf_modified = true; });

                ImGui::Columns(1);
                ImGui::PopStyleVar();
            }
            if (ImGui::CollapsingHeader("Parameters", ImGuiTreeNodeFlags_None))
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
                ImGui::Columns(2);

                ColumnItem("RANSAC Threshold", "##RANSAC_THRESHOLD", &_conf.RANSAC_THRESHOLD, 0.1, 0.5, [&]() { _conf_modified = true; });
                ColumnItem("Min Reprojection Error", "##MIN_REPROJECTION_ERROR", &_conf.MIN_REPROJECTION_ERROR, 0.1, 0.5, [&]() { _conf_modified = true; });
                ColumnItem("Min point match distance of cloud", "##MERGE_CLOUD_POINT_MIN_MATCH_DISTANCE", &_conf.MERGE_CLOUD_POINT_MIN_MATCH_DISTANCE, 0.1, 0.5, [&]() { _conf_modified = true; });
                ColumnItem("Min feature match distance of cloud", "##MERGE_CLOUD_FEATURE_MIN_MATCH_DISTANCE", &_conf.MERGE_CLOUD_FEATURE_MIN_MATCH_DISTANCE, 0.1, 0.5, [&]() { _conf_modified = true; });
                ColumnItem("Min point count for homography", "##MIN_POINT_COUNT_FOR_HOMOGRAPHY", &_conf.MIN_POINT_COUNT_FOR_HOMOGRAPHY, 1, 5, [&]() { _conf_modified = true; });
                ColumnItem("Pose inliers min ratio", "##POSE_INLIERS_MINIMAL_RATIO", &_conf.POSE_INLIERS_MINIMAL_RATIO, 0.01, 0.5, [&]() { _conf_modified = true; });

                ImGui::Columns(1);
                ImGui::PopStyleVar();
            }
            if (_conf_modified)
            {
                if (ImGui::Button("Confirm", ImVec2(ImGui::GetColumnWidth() * 0.5f, 0)))
                {
                    MVS::SfM::Get()->SetConfig(_conf);
                    _conf_modified = false;
                }
                ImGui::SameLine();
            }
            if (ImGui::Button("Run", ImVec2(ImGui::GetColumnWidth(), 0)))
            {
                // run sfm on another thread
                if (_conf_modified)
                {
                }
            }

            ImGui::EndTabItem();
        }

        // ImGui::ProgressBar(progress, ImVec2(0.0f, 0.0f));

        ImGui::EndTabBar();
    }
    ImGui::End();
    return false;
}