#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>

#include "AboutPanel.h"

using namespace std;
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
    if (ImGui::Begin("About Real Engine", &active), NULL, window_flags)
    {
        OnHovered();
        OnResize();
        
        

        if(ImGui::MenuItem("Github Page"))
        {

            if (!webPage)
            {
                ShellExecute(NULL, "open", githubWebPage.c_str(), NULL, NULL, SW_SHOWNORMAL);
                webPage = true;
            }
        
        }
        if (ImGui::MenuItem("Info"))
        {
            showInfo = !showInfo;

        }
        if (showInfo)
        {
            
            
            file.open("../../README.md");
            if (file.is_open())
            {
                ImGui::Text("\n");
                while (getline(file, line))
                {
                    
                    ImGui::Text(line.c_str());

                }
                ImGui::Text("\n");
                file.close();
            }
            
        }
       
    }
    
    ImGui::End();
    ImGui::PopStyleVar();
}

bool AboutPanel::CleanUp()
{
	return true;
}
