#include <Windows.h>
#include "AboutPanel.h"


AboutPanel::AboutPanel(int _id, bool isActive)
{
}

AboutPanel::~AboutPanel()
{
}

void AboutPanel::Init()
{
	window_flags = ImGuiWindowFlags_NoDocking;
	borderOffset = 0;
}

void AboutPanel::Update()
{
    if (!active)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("About Real Engine"))
    {
        OnHovered();
        OnResize();
        string githubWebPage = "https://github.com/allenbateman/Real-Engine";
        
        if (!opened)
        {
          ShellExecute(NULL, "open", githubWebPage.c_str(), NULL, NULL, SW_SHOWNORMAL);
          opened = true;
        }
       
        //ImGui::Text("Hello world");
    }
    

   
   
    ImGui::End();
    ImGui::PopStyleVar();
}

bool AboutPanel::CleanUp()
{
	return true;
}
