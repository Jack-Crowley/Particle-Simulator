#include <vector>
#include "circle.h"
#include "renderer.h"
#include "color.h"
#include "physics.h"
#include "sceneManager.h"
#include "staticManager.h"
#include <cstdlib>
#include <ctime>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Circle *clickedCircle = nullptr;

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
        return;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        float xValue = 2*((xPos-(getWidth(window)-getHeight(window))/2)/(getHeight(window))*1000-500);
        Component comp = Component(xValue*calculateAspectRatio(window), -4/3*(yPos-360));
        // printf("Click at: (%f, %f)\n",comp.x , comp.y);
        if (clickAdds){
            Circle circ = Circle(comp, getRandomColor());
            addCircles(circ);
        }
        if (clickAttracts){
            // printf("Attracts at: (%f, %f)\n",comp.x , comp.y);
            summonForceTowards(comp);
        }
        for (Circle& c : getCircles())
        {
            if (c.getDistance(comp) <= c.radius)
            {
                clickedCircle = &c;
                return;
            }
        }
        clickedCircle = nullptr;
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        circles.push_back(Circle(Component(0, 0), getRandomColor()));
    }
}

int main(int, char **)
{
    const uint32_t frame_rate = 60;

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);

    loadMaps();

    while (!glfwWindowShouldClose(window))
    {
        // Figure out how t
        if (!pause)
        {
            update_physics_sub_steps(1, 8);
        }
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static float f = 250.0f;

        static float size = 10.0f;
        static float scale = 10.0f;
        static bool showGrid = false;

        {

            // Your main window content
            ImGui::Begin("Particle Simulator!");

            ImGui::Checkbox("Add", &clickAdds);
            ImGui::Checkbox("Attract", &clickAttracts);

            ImGui::NewLine();        

            ImGui::SliderFloat("Size", &size, 1.0f, 250.0f);
            ImGui::SliderFloat("Speed", &fallSpeed, -.5f, .5f);
            ImGui::Checkbox("Repel?", &circlesRepel);
            ImGui::SliderFloat("RepelMagnitude", &repel_magnitude, -50.0f, 50.0f);

            ImGui::NewLine();

            ImGui::Checkbox("Show Grid", &showGrid);
            ImGui::Checkbox("Debug Mode", &debug);
            ImGui::Checkbox("Pause", &pause);
            

            if (ImGui::Button("Move Physics"))
            {
                update_physics_sub_steps(1, 8);
            }

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            ImGui::End();
        }

        if (clickedCircle != nullptr)
        {
            ImGui::Begin("Clicked Particle");

            ImGui::Text("Current Position");
            ImGui::InputFloat("Curr-X", &clickedCircle->position_cur.x);
            ImGui::InputFloat("Curr-Y", &clickedCircle->position_cur.y);

            ImGui::NewLine();

            ImGui::Text("Old Position");
            ImGui::InputFloat("Old-X", &clickedCircle->position_old.x);
            ImGui::InputFloat("Old-Y", &clickedCircle->position_old.y);

            ImGui::NewLine();

            ImGui::Text("Velocity");
            ImGui::InputFloat("Vel-X", &clickedCircle->velocity.x);
            ImGui::InputFloat("Vel-Y", &clickedCircle->velocity.y);

            ImGui::NewLine();

            ImGui::Text("Acceleration");
            ImGui::InputFloat("Acc-X", &clickedCircle->acceleration.x);
            ImGui::InputFloat("Acc-Y", &clickedCircle->acceleration.y);

            ImGui::NewLine();

            ImGui::Text("Jerk");
            ImGui::InputFloat("Jer-X", &clickedCircle->jerk.x);
            ImGui::InputFloat("Jer-Y", &clickedCircle->jerk.y);

            ImGui::NewLine();

            ImGui::Text("Radius");
            ImGui::InputFloat("Radius", &clickedCircle->radius);

            ImGui::NewLine();

            ImGui::Text("Enabled");
            ImGui::Checkbox("Enabled", &clickedCircle->enabled);

            ImGui::End();
        }

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::BeginMenu("Examples")) // Begin submenu
                {
                    if (ImGui::MenuItem("Circle"))
                    {
                        loadCircle();
                    }
                    if (ImGui::MenuItem("Parabula"))
                    {
                        loadParabola();
                    }
                    if (ImGui::MenuItem("Nothing"))
                    {
                        loadNothing();
                    }
                    ImGui::EndMenu(); // End submenu
                }

                ImGui::EndMenu(); // End "File" menu
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // All of stuff here
        if (showGrid)
        {
            drawGrid(window, size);
        }

        drawMap(window);

        drawCircles(window);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
