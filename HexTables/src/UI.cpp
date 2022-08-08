#include <exception>
#include <algorithm>

#include "imgui.h"
#include "imgui_internal.h" // for ImRect

#include "UI.hpp"
#include "DataTraverser.hpp"

namespace gui
{
	UI::UI(MirroredHex&& hex) : hex(std::move(hex))
	{

	}

    void PrintDataAsChar(vector<uint8_t>& v, size_t start, size_t end)
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

    void PrintDataAsHex(vector<uint8_t>& v, size_t start, size_t end)
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
			TableFlags | ImGuiTableFlags_Resizable;
 
		ImGui::Begin("window", NULL, ImGuiWindowFlags_NoSavedSettings);

        static int divider = 0;
        static int divider_limit = 3;

        static auto traverser = tables::DataTraverser<uint8_t>(divider, divider_limit);

        auto& table = hex.int_table;

        auto pos = traverser.FindFirstData(table);
        auto end = 0;
        auto count = 1;
        
        if (ImGui::BeginTable("Data", 5, ResizableTableFlags))
        {
            
            ImGui::TableSetupColumn("No.");
            ImGui::TableSetupColumn("As Char");
            ImGui::TableSetupColumn("As Hex");
            ImGui::TableSetupColumn("First byte");
            ImGui::TableSetupColumn("Last byte");
            ImGui::TableHeadersRow();
            while (pos != -1)
            {
                end = traverser.FindEndOfData(table, pos);
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
                        PrintDataAsChar(table, pos, end);
                        break;
                    case 2: // As Hex
                        PrintDataAsHex(table, pos, end);
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
                pos = traverser.FindData(table, end + 1);
            }
            ImGui::EndTable();
        }

		ImGui::End();

        #ifdef HEX_DEBUG
        ImGui::ShowMetricsWindow();
        #endif
	}
}