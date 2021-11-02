/*
*  File Name : IMGUImanager.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Debuging system. Can make and modify objects.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"IMGUImanager.h"
#include<iostream>
#include"ObjectController.h"
#include "ControllerType.h"
#include <reader.h>
#include "RustKeyController.h"
#include "TreeController.h"
#include "SeedController.h"
#include "BoxController.h"
#include "LogController.h"
#include "RiverController.h"
#include "AxeController.h"
#include "SpikeController.h"
#include "Portal.h"
#include "Audio.h"
#include "BlastFurnaceController.h"
#include "PoisonplantController.h"
#include "WallController.h"
#include "DoorController.h"
#include "Resolution.h"
#include "VineController.h"
#include "WoodBoardController.h"
#include "TorchController.h"
#include "PuddleController.h"
#include "Graphics.h"
#include "PlayerController.h"
#include "WallController1.h"
#include "WallController2.h"
#include "WallController3.h"

namespace BLUE
{
	glm::vec2 prev_screen_size;
	glm::vec2 curr_screen_size;
	glm::vec2 ratio = { 1.f, 1.f };
	glm::vec2 camera_for_debug;

	IMGUImanager* IMGUI_MANAGER = nullptr;

	namespace
	{
		static constexpr int TextBufferLength = 100;

		static void ShowHelpMarker(const char* desc)
		{
			ImGui::TextDisabled("(?)");
			if (ImGui::IsItemHovered())
			{
				ImGui::BeginTooltip();
				ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
				ImGui::TextUnformatted(desc);
				ImGui::PopTextWrapPos();
				ImGui::EndTooltip();
			}
		}
	}

	IMGUImanager::IMGUImanager()
	{
		std::cout << "IMGUI MANAGER constructor called" << std::endl;
		IMGUI_MANAGER = this;
	}

	void IMGUImanager::Init()
	{
		screen_width = WINDOW_INFORMATION::GetWindowSize().x;
		screen_height = WINDOW_INFORMATION::GetWindowSize().y;
		curr_screen_size = WINDOW_INFORMATION::GetWindowSize();

		io = ImGui::GetIO();  (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
		pWindow = SDL_GL_GetCurrentWindow();
		glContext = SDL_GL_GetCurrentContext();
		ImGui_ImplSDL2_InitForOpenGL(pWindow, glContext);
		ImGui_ImplOpenGL3_Init(nullptr);
		ImGui::StyleColorsDark();

		initialized = true;
	}

	void IMGUImanager::Update()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(pWindow);
		ImGui::NewFrame();
#ifdef DEBUG
		MainWindow();
#endif
		// Rendering
		ImGui::Render();
		SDL_GL_MakeCurrent(pWindow, glContext);
		glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#
	}

	IMGUImanager::~IMGUImanager()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void IMGUImanager::MainWindow()
	{
		static int counter = 0;

		ImGui::Begin("BLUEGUI");
		if (ImGui::TreeNode("ObjectList"))
		{
			ObjectList();

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("ObjectManage"))
		{
			ObjectManage();

			ImGui::TreePop();
		}
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Separator();

		AudioManage();

		ImGui::Separator();
		DebugDrawing();

		ImGui::Separator();

        SetColor();

		ImGui::Separator();

		ImGui::Separator();

		ImGui::NewLine();
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	void IMGUImanager::ObjectList()
	{
		/* IMPORTANT!!!: Set the same order between controller_type and controller_type_enum */
		std::string controller_type[] = { "None", "Tree", "Seed", "Box", "Rust Key" ,"Log","River","Axe","Portal", "Wall", "Spike", "BlastFurnace","PoisonPlant","Door","Vine","WoodBoard","Torch","Puddle","Wall1","Wall2","Wall3"};
		ControllerType controller_type_enum[] = { ControllerType_NULL, ControllerType_TREE, ControllerType_SEED, ControllerType_BOX, ControllerType_RUSTKEY,ControllerType_LOG,ControllerType_RIVER,ControllerType_AXE,ControllerType_PORTAL, ControllerType_WALL, ControllerType_SPIKE,ControllerType_BLASTFURNACE,ControllerType_POISONPLANT,ControllerType_DOOR,ControllerType_VINE,ControllerType_WOODBOARD,ControllerType_TORCH,ControllerType_PUDDLE,ControllerType_WALL1,ControllerType_WALL2,ControllerType_WALL3 };

		static int current_type = 0;
		if (ImGui::BeginCombo(" ", controller_type[current_type].c_str()))
		{
			for (int n = 0; n < IM_ARRAYSIZE(controller_type); n++)
			{
				const bool is_selected = (current_type == n);

				if (ImGui::Selectable(controller_type[n].c_str(), is_selected))
					current_type = n;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		GenerateObject(controller_type_enum[current_type], &current_type);
	}

	void IMGUImanager::ObjectManage() const
	{
		std::vector<std::string> object_name;
		object_name.push_back("None");

		for (int n = 0; n < static_cast<int>(OBJECT_CONTROLLER->objects.size()); n++)
		{
			const std::string str = std::to_string(n) + ". " + OBJECT_CONTROLLER->GetName(n);
			object_name.push_back(str);
		}

		if (!object_name.empty())
		{
			static int current_object_num = -1;

			if (OBJECT_CONTROLLER->objects.empty())
				current_object_num = -1;

			if (ImGui::BeginCombo(" ", object_name.at(current_object_num + 1).c_str()))
			{
				for (int n = 0; n < static_cast<int>(object_name.size()); n++)
				{
					const bool is_selected = (current_object_num == (n - 1));

					if (ImGui::Selectable(object_name.at(n).c_str(), is_selected))
					{
						current_object_num = n - 1;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			if (current_object_num >= 0)
			{
				SetName(current_object_num);
				SetSprite(current_object_num);
				SetTransform(current_object_num);
				SetItemtype(current_object_num);

				if (ImGui::Button("Delete"))
				{
					OBJECT_CONTROLLER->DeleteObject(current_object_num);
					object_name.erase(object_name.begin() + current_object_num + 1);
					current_object_num = -1;
				}
			}
		}
	}

	void IMGUImanager::AudioManage() const
	{

		if (ImGui::TreeNode("Set BackGroundMusic"))
		{
			std::string sounds[] = { "BGM", "Mainmenu_bgm"/*add more*/ };

			static std::string current_sound = "BGM";

			if (ImGui::BeginCombo(" ", current_sound.c_str()))
			{
				for (int n = 0; n < IM_ARRAYSIZE(sounds); n++)
				{
					const bool is_selected = (current_sound == sounds[n]);
					if (ImGui::Selectable(sounds[n].c_str(), is_selected))
						current_sound = sounds[n].c_str();
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			static std::string previousSound = "BGM";
			if (previousSound != current_sound)
				AUDIO_MANAGER->ChangeSound(previousSound, current_sound);
			previousSound = current_sound;
			ImGui::TreePop();
		}
	}

	bool IMGUImanager::Initialized() const
	{
		return initialized;
	}

	void IMGUImanager::ShutDown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		initialized = false;
	}

	void IMGUImanager::SetColor() const
	{
		ImGui::Text("Background Color");
		ImVec4 color = clear_color;
		
		ImGui::ColorEdit3("clear color", (float*)(&clear_color));

		if (color.x != clear_color.x || color.y != clear_color.y || color.z != clear_color.y)
			clearcolor();
	}

	void IMGUImanager::SetResolution() const
	{
		bool is_changed = false;
		static std::string current_resolution = to_string(RESOLUTION->GetCurrentResolution());
		if (ImGui::TreeNode("Resolution"))
		{
			std::string resolutions[] = { "R_1920X1080", "R_1680X1050", "R_1600X900", "R_1280X720", "R_800X600" };

			if (ImGui::BeginCombo(" ", current_resolution.c_str()))
			{
				for (int n = 0; n < IM_ARRAYSIZE(resolutions); n++)
				{
					const bool is_selected = (current_resolution == resolutions[n]);
					if (ImGui::Selectable(resolutions[n].c_str(), is_selected))
					{
						current_resolution = resolutions[n];
						is_changed = true;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::TreePop();
		}

		if (is_changed)
		{
			RESOLUTION->SetResolution(to_screen_resolution(current_resolution));
		}
	}

	void IMGUImanager::clearcolor() const
	{
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	}

	void IMGUImanager::GenerateObject(ControllerType type, int * current_type)
	{
		if (type == ControllerType_NULL)
			return;

		ImGui::Button("Generate");
		if (ImGui::IsItemActive())
		{
			ImDrawList* draw_list = ImGui::GetWindowDrawList();
			draw_list->PushClipRectFullScreen();
			draw_list->AddCircle(ImGui::GetIO().MousePos, 10.f, ImGui::GetColorU32({ 0.8f, 0.7f, 0.95f, 0.5f }), 15, 10.0f);
			draw_list->PopClipRect();
		}
		else if (ImGui::IsItemDeactivated())
		{
			switch (type)
			{
			case ControllerType_TREE:
				controller = new TreeController;
				break;
			case ControllerType_SEED:
				controller = new SeedController;
				break;
			case ControllerType_BOX:
				controller = new BoxController;
				break;
			case ControllerType_RUSTKEY:
				controller = new RustKeyController;
				break;
			case ControllerType_LOG:
				controller = new LogController;
				break;
			case ControllerType_RIVER:
				controller = new RiverController;
				break;
			case ControllerType_AXE:
				controller = new AxeController;
				break;
			case ControllerType_PORTAL:
				controller = new Portal;
				break;
			case ControllerType_WALL:
				controller = new Wall;
				break;
			case ControllerType_SPIKE:
				controller = new SpikeController;
				break;
			case ControllerType_BLASTFURNACE:
				controller = new BlastFurnaceController;
				break;
			case ControllerType_POISONPLANT:
				controller = new PoisonplantController;
				break;
			case ControllerType_DOOR:
				controller = new DoorController;
				break;
            case ControllerType_VINE:
                controller = new VineController;
                break;
			case ControllerType_WOODBOARD:
				controller = new WoodBoardController;
				break;
			case ControllerType_TORCH:
				controller = new TorchController;
				break;
			case ControllerType_PUDDLE:
				controller = new PuddleController;
				break;
			case ControllerType_WALL1:
				controller = new Wall1;
				break;
			case ControllerType_WALL2:
				controller = new Wall2;
				break;
			case ControllerType_WALL3:
				controller = new Wall3;
				break;
			default:
				break;
			}

			static Camera * camera = GRAPHICS->GetCamera();
                        const glm::vec2 camera_pos = camera->GetPosition();
			ImVec2 mouse_pos = ImVec2(ImGui::GetIO().MousePos.x - (static_cast<float>(screen_width) / 2.0f) + camera_pos.x, (static_cast<float>(screen_height) / 2.0f) - ImGui::GetIO().MousePos.y + camera_pos.y);
			controller->Spawn(mouse_pos.x, mouse_pos.y, 0);
			OBJECT_CONTROLLER->AddController(controller);

			*current_type = 0;
		}
	}

	void IMGUImanager::SetName(int object_num) const
	{
		if (ImGui::TreeNode("Set Name"))
		{
			char name_char[TextBufferLength];
			strcpy_s(name_char, OBJECT_CONTROLLER->GetObject(object_num)->GetName().c_str());
			ImGui::InputText(" ", name_char, TextBufferLength);

			const std::string name_string(name_char);
			OBJECT_CONTROLLER->GetObject(object_num)->SetName(name_string);
			ImGui::TreePop();
		}
	}

	void IMGUImanager::SetTransform(int object_num) const
	{
		if (ImGui::TreeNode("Set Transform"))
		{
			Transform * transform = (OBJECT_CONTROLLER->GetObject(object_num)->transform);

			if (ImGui::TreeNode("Translation"))
			{
				ImGui::Button("By using mouse");
				if (ImGui::IsItemActive())
				{
					/* if you change the position of the camera, add camera position to mouse_pos */
				

                                    static Camera * camera = GRAPHICS->GetCamera();
                                    const glm::vec2 camera_pos = camera->GetPosition();

				    const ImVec2 mouse_pos = ImVec2(ImGui::GetIO().MousePos.x - (static_cast<float>(screen_width) / 2.0f) + camera_pos.x,
                                        (static_cast<float>(screen_height) / 2.0f) - ImGui::GetIO().MousePos.y+ camera_pos.y);


					transform->SetTranslation({ mouse_pos.x,mouse_pos.y, transform->GetTranslation().z });
				}

				float position[3] = { transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z };
				ImGui::DragFloat2("(x, y)", &position[0]);
				ImGui::SliderFloat("z", &position[2], Depth::range.x + 1.0f, Depth::range.y);
				transform->SetTranslation({ position[0], position[1], position[2] });
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Scale"))
			{
				float scale[2] = { transform->GetScale().x, transform->GetScale().y };
				ImGui::DragFloat2("W X H", &scale[0], 1.0f, 0.0f);
				transform->SetScale({ scale[0], scale[1] });
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rotation"))
			{
				int rotation = static_cast<int>(transform->GetRotation());
				ImGui::SliderInt("Degree", &rotation, 0, 360);
				transform->SetRotation(static_cast<float>(rotation));
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Direction(only poisonplant)"))
			{
				int dir[2] = { static_cast<int>(OBJECT_CONTROLLER->GetObject(object_num)->direction.x), static_cast<int>(OBJECT_CONTROLLER->GetObject(object_num)->direction.y) };
				ImGui::SliderInt2("X Y", &dir[0], -100, 100);
				OBJECT_CONTROLLER->GetObject(object_num)->direction.x = static_cast<glm::vec2::value_type>(dir[0]);
				OBJECT_CONTROLLER->GetObject(object_num)->direction.y = static_cast<glm::vec2::value_type>(dir[1]);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}

	void IMGUImanager::SetSprite(int object_num) const
	{
		if (ImGui::TreeNode("Set Sprite"))
		{
			Sprite *sprite = (OBJECT_CONTROLLER->GetObject(object_num)->sprite);

			ImGui::Checkbox("Is Hud", &sprite->isHud);
			ImGui::SameLine(); ShowHelpMarker("The position of the hud is relative to the position of the player (Assuming the player's position is (0, 0).");

			if (ImGui::TreeNode("Color"))
			{
				const glm::vec4 glm_color = sprite->GetMesh().GetColor(0).ColorToFloat();
				ImVec4 color(glm_color.x, glm_color.y, glm_color.z, glm_color.w);
				ImGui::ColorEdit4("", (float*)&color, ImGuiColorEditFlags_AlphaPreviewHalf);
				sprite->SetColor(glm::vec4{ color.x, color.y, color.z, color.w });
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Texture"))
			{
				std::string textures[] = { "texture/Item/tree.png", "texture/Item/sprout.png", "texture/Item/Box_Closed.png", "texture/Item/Key.png" ,"texture/Item/log.png","texture/Item/river.png","texture/Item/Axe.png","texture/Item/Portal.png", "texture/Item/Wall.png", "texture/Item/Spike_1.png", "texture/Item/bonfire.png","texture/Item/PoisonPlant.png","texture/Item/Door_Seed.png","texture/Item/Vine_1.png","texture/Item/Woodboard.png","texture/Item/torch.png","texture/Item/puddle.png", "texture/Item/Wall1.png", "texture/Item/Wall2.png", "texture/Item/Wall_1.png"/*add more*/ };

				static std::string current_texture = sprite->GetTexture()->GetFilePath();

				if (ImGui::BeginCombo(" ", current_texture.c_str()))
				{
					for (int n = 0; n < IM_ARRAYSIZE(textures); n++)
					{
						const bool is_selected = (current_texture == textures[n]);
						if (ImGui::Selectable(textures[n].c_str(), is_selected))
							current_texture = textures[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				sprite->SetTexture(current_texture);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Animation"))
			{
				Animation *animation = sprite->SetAnimation();

				bool isAnimationActive = animation->isAnimationActive();
				int frame_num[2] = { animation->GetFrameNumber().x, animation->GetFrameNumber().y };
				float speed = animation->GetSpeed();

				ImGui::Checkbox("Animation Active", &isAnimationActive);
				ImGui::InputInt2("(X, Y)", &frame_num[0]);
				ImGui::SliderFloat("Speed", &speed, AnimationSpeed::range.x, AnimationSpeed::range.y, "%.3f");

				animation->SetFrame(frame_num[0], frame_num[1]);
				animation->SetSpeed(speed);

				if (isAnimationActive)
				{
					animation->ActivateAnimation();
				}
				else
					animation->DeactivateAnimation();

				if (ImGui::Button("Reset Animation"))
				{
					animation->SetFrame(1, 1);
					animation->SetSpeed((AnimationSpeed::range.x + AnimationSpeed::range.y) / 2.0f);
				}

				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}

	void IMGUImanager::SetItemtype(int object_num) const
	{
		if (ImGui::TreeNode("Set Itemtype"))
		{
			std::string itemtypes[] = {
			"NULL",
			"ANYTHING",
			"PLAYER",
			"TREE",
			"SEED",
			"BOX",
			"RUSTKEY",
			"GHOST",
			"AXE",
			"LOG",
			"RIVER",
			"GHOSTRIVER",
			"PORTAL",
			"WALL",
			"SPIKE",
			"BLASTFURNACE",
			"POISONPLANT",
			"DOOR",
			"NUM"/*add more*/ };

			static std::string current_item = itemtypes[(OBJECT_CONTROLLER->GetObject(object_num)->item_type)];
			int current_item_index = (OBJECT_CONTROLLER->GetObject(object_num)->item_type);
			if (ImGui::BeginCombo(" ", current_item.c_str()))
			{
				for (int n = 0; n < IM_ARRAYSIZE(itemtypes); n++)
				{
					const bool is_selected = (current_item == itemtypes[n]);
					if (ImGui::Selectable(itemtypes[n].c_str(), is_selected))
					{
						current_item = itemtypes[n].c_str();
						current_item_index = n;
					}
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			OBJECT_CONTROLLER->GetObject(object_num)->item_type = static_cast<ControllerType>(current_item_index);
			ImGui::TreePop();
		}
	}

	void IMGUImanager::DebugDrawing() const
	{
		static bool do_draw = false;
		ImGui::Checkbox("Debug Drawing", &do_draw);

		if (do_draw)
		{
			const ImU32 color = ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f });

			const float zoom = GRAPHICS->GetCamera()->GetZoom();

			if (curr_screen_size.x != WINDOW_INFORMATION::GetWindowSize().x && curr_screen_size.y != WINDOW_INFORMATION::GetWindowSize().y)
			{
				prev_screen_size = { 1280, 720 };
				curr_screen_size = WINDOW_INFORMATION::GetWindowSize();
				ratio = curr_screen_size / prev_screen_size;
			}
			camera_for_debug = GRAPHICS->GetCamera()->GetPosition();
			camera_for_debug *= ratio;
			auto width = static_cast<int>((static_cast<float>(curr_screen_size.x) / 2.0f - camera_for_debug.x * zoom));
			auto height = static_cast<int>((static_cast<float>(curr_screen_size.y) / 2.0f + camera_for_debug.y * zoom));

			// PLAYER's Collision box
			if (PLAYER_CONTROLLER->GetObject() != nullptr)
			{
				Transform * transform = PLAYER_CONTROLLER->GetTransform();
				const glm::vec3 position = { transform->GetTranslation()*glm::vec3{ ratio.x, ratio.y, 1.f} };
				const glm::vec2 rect_size = PLAYER_CONTROLLER->GetObject()->rectangle->GetSize() *ratio;

				const ImVec2 pos1((position.x + rect_size.x / 2.f)*(zoom)+width, -(position.y + rect_size.y / 2.f)*(zoom)+height);
				const ImVec2 pos2((position.x - rect_size.x / 2.f)*(zoom)+width, -(position.y - rect_size.y / 2.f)*(zoom)+height);
				DrawRectangle(pos1, pos2, color);
			}


			// OBJECT's Collision box
			for (int n = 0; n < static_cast<int>(OBJECT_CONTROLLER->objects.size()); n++)
			{
				if (OBJECT_CONTROLLER->GetObject(n)->GetComponent(ComponentType_RECTANGLE) != nullptr
					&& OBJECT_CONTROLLER->GetObject(n)->GetComponent(ComponentType_TRANSFORM) != nullptr)
				{
					const Transform * transform = (OBJECT_CONTROLLER->GetObject(n)->transform);
					/*if (transform->GetRotation() == 0.0f || transform->GetRotation() == 360.0f)
					{*/
					const glm::vec2 rect_size = (OBJECT_CONTROLLER->GetObject(n)->rectangle)->GetSize()*ratio;
					const glm::vec3 position = transform->GetTranslation()*glm::vec3{ ratio.x, ratio.y, 1.f };
					const ImVec2 pos1((position.x + rect_size.x / 2.f)*(zoom)+width, -(position.y + rect_size.y / 2.f)*(zoom)+height);
					const ImVec2 pos2((position.x - rect_size.x / 2.f)*(zoom)+width, -(position.y - rect_size.y / 2.f)*(zoom)+height);
					DrawRectangle(pos1, pos2, color);
					//}
				}
			}
		}
	}

	void IMGUImanager::DrawRectangle(ImVec2 pos1, ImVec2 pos2, ImVec2 pos3, ImVec2 pos4, ImU32 color) const
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->PushClipRectFullScreen();
		draw_list->AddQuad(pos1, pos2, pos3, pos4, color);
		draw_list->PopClipRect();
	}

	void IMGUImanager::DrawRectangle(ImVec2 pos1, ImVec2 pos2, ImU32 color) const
	{
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->PushClipRectFullScreen();
		draw_list->AddRect(pos1, pos2, color);
		draw_list->PopClipRect();
	}
}
