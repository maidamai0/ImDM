#include "GLFW/glfw3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "stb/stb_image.h"

#include "assets/droid_sans.h"
#include "assets/icon.png.h"
#include "log.h"
#include "window.h"

int main(int argc, char** argv) {
  make_singleton<Log>();
  if (glfwInit() == GL_FALSE) {
    LOGE("Failed to initialize GLFW");
    return EXIT_FAILURE;
  }

  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  auto* window = glfwCreateWindow(1080, 720, APP_NAME, nullptr, nullptr);
  if (window == nullptr) {
    LOGE("Failed to create GLFW window");
    glfwTerminate();
    return EXIT_FAILURE;
  }

  //  set window icon
  GLFWimage icon;
  icon.pixels = stbi_load_from_memory(icon_png, sizeof(icon_png), &icon.width, &icon.height, nullptr, 4);
  glfwSetWindowIcon(window, 1, &icon);
  stbi_image_free(icon.pixels);

  glfwMakeContextCurrent(window);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsLight();
  ImGuiStyle& style = ImGui::GetStyle();
  style.FrameRounding = 5.0f;
  style.ChildRounding = 5.0f;
  style.GrabRounding = 5.0f;
  style.PopupRounding = 5.0f;
  style.ScrollbarRounding = 5.0f;
  style.TabRounding = 5.0f;
  style.WindowRounding = 5.0f;
  style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->Clear();
  io.Fonts->AddFontFromMemoryCompressedTTF(droid_sans_compressed_data, droid_sans_compressed_size, 16);

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  while (glfwWindowShouldClose(window) == GLFW_FALSE) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // background
    ImGuiWindowFlags background_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                                        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs |
                                        ImGuiWindowFlags_AlwaysAutoResize;
    const auto size = ImGui::GetMainViewport()->WorkSize;
    ImGui::SetNextWindowSize(size);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::Begin(APP_NAME, nullptr, background_flags);
    ImGui::End();
    ImGui::PopStyleVar(3);

    // custom UI from here
    make_singleton<Window>().Show();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}