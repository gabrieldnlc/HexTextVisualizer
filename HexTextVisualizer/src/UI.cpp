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

    void DrawSelectionRect(ImRect rect, float s_unit)
    {
        rect.Min.x -= s_unit * 0.2f;
        rect.Max.x += s_unit * 0.2f;
        ImGui::GetWindowDrawList()->AddRect(rect.Min, rect.Max, IM_COL32_WHITE);
    }

    void PrintDataAsChar(vector<int>& v, size_t start, size_t end, bool print_spaces, float s_unit, int& hovered_column, bool& hovered)
    {
        for (size_t i = start; i <= end; i++)
        {
            int c = v[i];
            if (c == 0 && !print_spaces)
            {
                continue;
            }
            
            ImGui::Text("%c", (c == 0 ? '.' : c));
            ImGui::SameLine();
            if (ImGui::IsItemHovered())
            {
                hovered = true;
                hovered_column = i;
            }
            if (hovered_column == i)
            {
                const ImRect item(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
                DrawSelectionRect(item, s_unit);
            }
            
        }
        ImGui::NewLine();
    }

    void PrintDataAsHex(vector<int>& v, size_t start, size_t end, float s_unit, int& hovered_column, bool& hovered)
    {
        for (size_t i = start; i <= end; i++)
        {
            int c = v[i];
            ImGui::Text("%.2X", c);
            ImGui::SameLine();
            if (ImGui::IsItemHovered())
            {
                hovered = true;
                hovered_column = i;
            }
            if (hovered_column == i)
            {
                const ImRect rect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
                DrawSelectionRect(rect, s_unit);
            }
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

        // - Default values for DataTraverser
        const static int divider = 0;
        const static int divider_limit = 3;

        static auto traverser = tables::DataTraverser<int>(divider, divider_limit);

        static bool print_spaces = false;

        const float s_unit = ImGui::GetFontSize();
        const float big_input = s_unit * 8.5f;
        const float small_input = s_unit * 3.f;

        ImGui::Text("Parsing options: ");

        ImGui::Checkbox("Display spaces between chars", &print_spaces);

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Table starts at byte");
        ImGui::SameLine();

        ImGui::PushItemWidth(big_input);
        ImGui::PushID("start_byte");
        ImGui::InputInt("", &first_byte, 1, 1);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("and ends at byte");
        ImGui::SameLine();

        ImGui::PushItemWidth(big_input);
        ImGui::PushID("end_byte");
        ImGui::InputInt("", &last_byte, 1, 1);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Data blocks are divided by ");
        
        ImGui::SameLine();
        ImGui::PushItemWidth(small_input);
        ImGui::PushID("divider_limit_picker");
        ImGui::InputInt("", &traverser.settings.divider_limit, NULL, NULL);
        ImGui::PopID();
        ImGui::PopItemWidth();

        ImGui::SameLine();
        ImGui::Text("bytes of value ");
        ImGui::SameLine();
        
        ImGui::PushItemWidth(small_input);
        ImGui::PushID("divider_picker");
        ImGui::InputInt("", &traverser.settings.divider, NULL, NULL);
        ImGui::PopID();
        ImGui::PopItemWidth();

        
        
        ImGui::Separator();
        ImGui::NewLine();
        
        auto pos = first_byte;
        auto end = 0; // For initialization purposes only
        auto count = 1;

        static int hovered_row = -1;
        static int hovered_column = -1;
        static bool hovered_this_frame = false;
        
        if (ImGui::BeginTable("Data", 5, ResizableTableFlags))
        {
            hovered_this_frame = false;

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
                        PrintDataAsChar(hex, pos, end, print_spaces, s_unit, hovered_column, hovered_this_frame);
                        break;
                    case 2: // As Hex
                        PrintDataAsHex(hex, pos, end, s_unit, hovered_column, hovered_this_frame);
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
            if (!hovered_this_frame)
            {
                hovered_column = -1;
            }
        }

		ImGui::End();
        ImGui::PopStyleVar();

        #ifdef HEX_DEBUG
        ImGui::ShowMetricsWindow();
        #endif
	}
}