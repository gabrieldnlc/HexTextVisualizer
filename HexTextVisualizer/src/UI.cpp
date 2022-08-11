#include <exception>
#include <algorithm>

#include "imgui.h"
#include "imgui_internal.h" // for ImRect

#include "UI.hpp"
#include "DataTraverser.hpp"

namespace gui
{
	UI::UI(vector<int>&& hex, string name) : hex(std::move(hex)), name(std::move(name))
	{

	}

    void PrintDataAsChar(vector<int>& v, size_t start, size_t end)
    {
        for (size_t i = start; i <= end; i++)
        {
            int c = v[i];
            if (c == 0) continue;
            ImGui::Text("%c", c);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    void PrintDataAsHex(vector<int>& v, size_t start, size_t end)
    {
        for (size_t i = start; i <= end; i++)
        {
            int c = v[i];
            ImGui::Text("%.2X", c);
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

	void UI::Render()
	{
		
		const ImGuiTableFlags TableFlags =
			ImGuiTableFlags_Borders | ImGuiTableFlags_NoSavedSettings;

		const ImGuiTableFlags ResizableTableFlags =
			TableFlags | ImGuiTableFlags_ScrollX;

        const ImGuiWindowFlags WindowFlags =
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize;
 

        // "Fullscreen" window
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize);
        ImGui::SetNextWindowFocus();
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);


		ImGui::Begin(name.data(), NULL, WindowFlags);

        const static int divider = 0;
        const static int divider_limit = 3;

        static auto traverser = tables::DataTraverser<int>(divider, divider_limit);

        const float s_unit = ImGui::GetFontSize();

        ImGui::Text("Parsing options: ");

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Table starts at byte");
        ImGui::SameLine();

        ImGui::PushItemWidth(s_unit * 8.5f);
        ImGui::PushID("start_byte");
        ImGui::InputInt("", &first_byte, 1, 1);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("and ends at byte");
        ImGui::SameLine();

        ImGui::PushItemWidth(s_unit * 8.5f);
        ImGui::PushID("end_byte");
        ImGui::InputInt("", &last_byte, 1, 1);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Data blocks are divided by ");
        
        ImGui::SameLine();
        ImGui::PushItemWidth(s_unit * 4.5f);
        ImGui::PushID("divider_limit_picker");
        ImGui::InputInt("", &traverser.settings.divider_limit, NULL, NULL);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("bytes of value ");
        ImGui::SameLine();
        
        ImGui::PushItemWidth(s_unit * 4.5f);
        ImGui::PushID("divider_picker");
        ImGui::InputInt("", &traverser.settings.divider, NULL, NULL);
        ImGui::PopID();
        ImGui::PopItemWidth();

        
        
        ImGui::Separator();
        ImGui::NewLine();
        
        auto pos = first_byte;
        auto end = 0; // For initialization purposes only
        auto count = 1;
        
        if (ImGui::BeginTable("Data", 5, ResizableTableFlags))
        {
            
            ImGui::TableSetupColumn("No.", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("As Char");
            ImGui::TableSetupColumn("As Hex");
            ImGui::TableSetupColumn("First byte");
            ImGui::TableSetupColumn("Last byte");
            ImGui::TableHeadersRow();
            while (pos != -1 && end < last_byte)
            {
                end = traverser.FindEndOfData(hex, pos, last_byte);
                ImGui::TableNextRow();
                for (std::size_t column = 0; column <= 4; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    switch (column)
                    {
                    case 0: // No.
                        ImGui::Text("%i", count++);
                        break;
                    case 1: // As Char
                        PrintDataAsChar(hex, pos, end);
                        break;
                    case 2: // As Hex
                        PrintDataAsHex(hex, pos, end);
                        break;
                    case 3: // First byte
                        ImGui::Text("%#X", pos);
                        break;
                    case 4: // Last byte
                    default:
                        ImGui::Text("%#X", end);
                        break;
                    }
                }
                pos = traverser.FindData(hex, end + 1);
            }
            ImGui::EndTable();
        }

		ImGui::End();
        ImGui::PopStyleVar();

        #ifdef HEX_DEBUG
        ImGui::ShowMetricsWindow();
        #endif
	}
}