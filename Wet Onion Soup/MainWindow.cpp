#include "Bridge.h"
#include "MainWindow.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

#include <sstream>
#include <stdexcept>

MainWindow::MainWindow()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
    {
        std::stringstream ss;
        ss << "Error: SDL_Init(): " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
    m_Window = SDL_CreateWindow("Wet Onion Soup", (int)(925 * main_scale), (int)(400 * main_scale), window_flags);
    if (m_Window == nullptr)
    {
        std::stringstream ss;
        ss << "Error: SDL_CreateWindow(): " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    m_GLContext = SDL_GL_CreateContext(m_Window);
    if (m_GLContext == nullptr)
    {
        std::stringstream ss;
        ss << "Error: SDL_GL_CreateContext(): " << SDL_GetError();
        throw std::runtime_error(ss.str());
    }

    SDL_GL_MakeCurrent(m_Window, m_GLContext);
    SDL_GL_SetSwapInterval(1);
    SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(m_Window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_IO = &ImGui::GetIO(); (void)m_IO;
    m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); 
    style.FontScaleDpi = main_scale;

    ImGui_ImplSDL3_InitForOpenGL(m_Window, m_GLContext);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bridge = new Bridge{};
}

MainWindow::~MainWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DestroyContext(m_GLContext);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
    delete bridge;
}

void MainWindow::Show()
{
    m_GuildList.push_back({ "WoS", "We owe Samsyn (ten bucks)", "Member", 1, false });
    m_GuildList.push_back({ "MWGA", "Make WoS Great Again", "President of the HOA", 2, false });
    m_GuildList.push_back({ "KoE", "Kings (and queens) of Evergreen", "Propane Master", 0, true });

    ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool done = false;
    int selectedRowIndex = -1;
    char* characterName = bridge->GetCharacterName();
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
                done = true;
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(m_Window))
                done = true;
        }

        if (SDL_GetWindowFlags(m_Window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(1250, 400), ImGuiCond_Once);
        ImGui::Begin("Available Guild Uniforms");
        ImGui::Text("\n%s belongs to these guilds. Pick the one you wish to champion today.\n\n", characterName);
        if (ImGui::BeginTable("Guilds", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable, ImVec2(1200.f, 0.f))) {
            ImGui::TableSetupColumn("Uniform", ImGuiTableColumnFlags_WidthFixed, 100.f);
            ImGui::TableSetupColumn("Guild Name", ImGuiTableColumnFlags_WidthStretch, 650.f);
            ImGui::TableSetupColumn("Rank", ImGuiTableColumnFlags_WidthFixed, 300.f);
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 50.f);
            ImGui::TableSetupColumn("Exclusive", ImGuiTableColumnFlags_WidthFixed, 100.f);
            ImGui::TableHeadersRow();

            for (int i = 0; i < m_GuildList.size(); i++) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();

                ImGui::PushID(i);
                bool isSelected = (i == selectedRowIndex);
                if (ImGui::Selectable((m_GuildList[i].uniform + "##" + std::to_string(i)).c_str(), isSelected, ImGuiSelectableFlags_SpanAllColumns)) {
                    selectedRowIndex = i;
                }
                ImGui::PopID();

                ImGui::TableNextColumn();
                ImGui::Text("%s", m_GuildList[i].guildName.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%s", m_GuildList[i].rank.c_str());

                ImGui::TableNextColumn();
                ImGui::Text("%d", m_GuildList[i].id);

                ImGui::TableNextColumn();
                if (m_GuildList[i].exclusive) 
                    ImGui::Text("Yes");
                else 
                    ImGui::Text("No");
            }
            ImGui::EndTable();
        }

        if (ImGui::Button("Put On Uniform")) {
            if (selectedRowIndex != -1) {
                bridge->PutOnUniform(m_GuildList[selectedRowIndex].uniform.c_str());
            }
            selectedRowIndex = -1;
        }

        ImGui::SameLine();
        if (ImGui::Button("Remove Uniform")) {
            bridge->PutOnUniform("");
        }

        ImGui::SameLine();
        if (ImGui::Button("Quit Guild")) {
            
        }

        ImGui::SameLine();
        if (ImGui::Button("Refresh")) {
            selectedRowIndex = -1;
            delete characterName;
            characterName = bridge->GetCharacterName();
        }

        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, (int)m_IO->DisplaySize.x, (int)m_IO->DisplaySize.y);
        glClearColor(clearColor.x * clearColor.w, clearColor.y * clearColor.w, clearColor.z * clearColor.w, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(m_Window);
    }
}