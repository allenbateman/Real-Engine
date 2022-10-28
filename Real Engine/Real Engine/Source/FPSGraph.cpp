#include "FPSGraph.h"

FPSGraph::FPSGraph(int _id, bool isActive)
{
}

FPSGraph::~FPSGraph()
{
}

void FPSGraph::Init()
{
    window_flags = ImGuiWindowFlags_NoDocking;
    borderOffset = 0;
}
void FPSGraph::Update()
{
    if (!active)
        return;

    averageFPS = ImGui::GetIO().Framerate;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);

    if (ImGui::Begin("FPS Graph", &active), NULL, window_flags)
    {
        OnHovered();
        OnResize();
        ImGui::Text("FPS: %f", averageFPS);    
        
        for (int i = 0; i < FPS_ON_PANEL - 1 ; i++)
        {
            lines[i] = lines[i + 1];
        }
        lines[FPS_ON_PANEL - 1] = averageFPS;
        
        ImGui::PlotHistogram("FPS Graph", lines, FPS_ON_PANEL, 0, 0, 0, 120, ImVec2(LastSize.x, LastSize.y - LastSize.y / 10));
        
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
bool FPSGraph::CleanUp()
{
    return true;
}
