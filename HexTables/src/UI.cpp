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
        auto start = 0;
        auto end = table.size();

        auto pos = traverser.WhereIsNextData(table, start);
        auto end_data = traverser.WhereIsEndOfData(table, pos);

        auto start_next_data = traverser.WhereIsNextData(table, end_data + 1);

        auto x = "baba booey";
        /*
        if (ImGui::BeginTable("Data", 5, ResizableTableFlags))
        {
            ImGui::TableSetupColumn("No.");
            ImGui::TableSetupColumn("As Char");
            ImGui::TableSetupColumn("As Hex");
            ImGui::TableSetupColumn("First byte");
            ImGui::TableSetupColumn("Last byte");
            ImGui::TableHeadersRow();
            for (std::size_t i = 1; i <= nodes.size(); i++)
            {
                const BaseNode& node = *nodes[i];
                ImGui::TableNextRow();
                for (std::size_t column = 0; column < 4; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    switch (column)
                    {
                    case 0: //index
                        ImGui::Text("%i", node.GetIdx());
                        if (root == i)
                        {
                            ImGui::SameLine();
                            ImGui::Text("(ROOT)");
                        }
                        break;
                    case 1: //type
                        ImGui::Text(node.GetPrettyType());
                        break;
                    case 2: //text
                        ImGui::Text(node.text.data());
                        break;
                    case 3: //tags
                        if (node.tags.empty())
                        {
                            break;
                        }
                        for (auto it = std::begin(node.tags); it != std::end(node.tags); it = std::next(it))
                        {
                            const auto& pair = *it;
                            const auto& type = pair.first;
                            const auto& entries = pair.second;
                            ImGui::Text("%s:", type.data());
                            ImGui::SameLine();
                            for (const auto& entry : entries)
                            {
                                TextFromTagEntry(entry);
                                ImGui::SameLine();
                            }
                            ImGui::NewLine();
                        }
                        break;
                    }
                }
            }
            ImGui::EndTable();
        }
        */

		ImGui::End();

        #ifdef HEX_DEBUG
        ImGui::ShowMetricsWindow();
        #endif
	}
}