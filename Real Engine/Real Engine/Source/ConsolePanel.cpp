#include "ConsolePanel.h"

ConsolePanel::ConsolePanel(int _id, bool isActive)
{

}
ConsolePanel::~ConsolePanel()
{
}

void ConsolePanel::Init()
{
    active = true;
    window_flags = ImGuiWindowFlags_NoDocking;
    borderOffset = 0;
}

void ConsolePanel::Update()
{
    if (!active)
        return;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImVec2{ 720,720 }, ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Console", &active), NULL, window_flags)
    {
        OnHovered();
        OnResize();

        if (ImGui::Button("Clear")) ClearConsole();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
        if (copy) ImGui::LogToClipboard();
        if (filter.IsActive())
        {
            const char* buf_begin = buffer.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < lineOffsets.Size) ? buf_begin + lineOffsets[line_no] : NULL;
                if (filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(buffer.begin());
            
        }

        if (scrollToBottom)
            ImGui::SetScrollHereY(1.0f);

        scrollToBottom = false; 

        ImGui::PopStyleVar();
    }
   
    ImGui::EndChild();
    ImGui::End();
    ImGui::PopStyleVar();
}


bool ConsolePanel::CleanUp()
{
    return true;
}

void ConsolePanel::AddLog(const char* log) IM_FMTARGS(2)
{
    int oldSize = buffer.size();
    va_list args;
    va_start(args, log);
    buffer.appendfv(log, args);
    va_end(args);

    for (int newSize = buffer.size(); oldSize < newSize; oldSize++)
        if (buffer[oldSize] == '\n')
            lineOffsets.push_back(oldSize);
    scrollToBottom = true;

}

void ConsolePanel::ClearConsole()
{
    buffer.clear();
    lineOffsets.clear();
}
