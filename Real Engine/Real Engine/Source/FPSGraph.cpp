#include "FPSGraph.h"

FPSGraph::FPSGraph(int _id, bool isActive)
{
}

FPSGraph::~FPSGraph()
{
}

bool FPSGraph::Init()
{
    
    active = true;
    window_flags = ImGuiWindowFlags_NoDocking;
    borderOffset = 0;
    return true;
}

bool FPSGraph::PreUpdate()
{
   
    return true;
}

bool FPSGraph::Update()
{
    averageFPS = ImGui::GetIO().Framerate;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);

    if (ImGui::Begin("FPS Graph"), NULL, window_flags)
    {

        OnHovered();
        OnResize();
        //ImGui::Image((ImTextureID)app->renderer->buffer.framebufferTexture, availableSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::Text("FPS: %f", averageFPS);
        

    }
    ImGui::End();
    ImGui::PopStyleVar();
    return true;
}

bool FPSGraph::PostUpdate()
{
    
    return true;
}

bool FPSGraph::CleanUp()
{
    return true;
}
