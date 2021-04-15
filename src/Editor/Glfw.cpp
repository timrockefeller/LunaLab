#include <glad/glad.h>
// static
#include <Common/Common.h>
#include <Core/OpenGL/Common.h>
#include <Editor/Glfw.h>
#include <Editor/UI/UIManager.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>
#include <Core/Runtime/GlobalStorage.h>
using namespace std;
using namespace LUNA;

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

bool Glfw::Init(size_t width, size_t height, const string &title)
{
    glfwSetErrorCallback(glfw_error_callback);

    /* init */
    if (!glfwInit())
        return false;
#ifdef __APPLE__
    // GL 3.2 + GLSL 150
    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    /* genWindow */
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        Terminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
    bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
    bool err = false;
    glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
    bool err = false;
    glbinding::initialize([](const char *name) { return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
    glfwSetFramebufferSizeCallback(window, updateViewport);

    // =================================================
    // Input Events
    glfwSetCursorPosCallback(
        window, [](GLFWwindow *window, double xpos, double ypos) {
            static float lastX = (float)xpos;
            static float lastY = (float)ypos;

            static float xoffset;
            static float yoffset;
            _GS<float>::getInstance()->Register(strMousePosX, xoffset);
            _GS<float>::getInstance()->Register(strMousePosY, yoffset);
            xoffset = (float)xpos - lastX;
            yoffset = lastY - (float)ypos;
            lastX = (float)xpos;
            lastY = (float)ypos;
            KTKR::EventListener::getInstance()->response(
                KTKR::EventListener::Event_Type::MOUSE_MOVE);
        });
    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        if(action == GLFW_PRESS){
            KTKR::EventListener::getInstance()->response(
                KTKR::EventListener::Event_Type::MOUSE_PRESS | button);
                // GLFW_MOUSE_BUTTON_LEFT
                
        }else if(action == GLFW_RELEASE){
            KTKR::EventListener::getInstance()->response(
                KTKR::EventListener::Event_Type::MOUSE_RELEASE | button);
        }
    });
    glfwSetScrollCallback(
        window, [](GLFWwindow *window, double xoffset, double yoffset) {
            _GS<float>::getInstance()->Register(strMouseScrollX,
                                                (float)xoffset);
            _GS<float>::getInstance()->Register(strMouseScrollY,
                                                (float)yoffset);
            KTKR::EventListener::getInstance()->response(
                KTKR::EventListener::Event_Type::MOUSE_SCROLL);
        });
    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scanCode,
                                  int state, int mods) {
        size_t kbState =
            (state == GLFW_PRESS ? KTKR::EventListener::KEYBOARD_PRESS
                                 : (state == GLFW_REPEAT
                                        ? KTKR::EventListener::KEYBOARD_REPEAT
                                        : (state == GLFW_RELEASE
                                               ? KTKR::EventListener::KEYBOARD_RELEASE
                                               : 0)));
        if (kbState != 0)
            KTKR::EventListener::getInstance()->response(key | kbState);
        KTKR::EventListener::getInstance()->response(key | KTKR::EventListener::KEYBOARD);
    });

    // =================================================
    // Update Processes
    _startOp = [&]() {
        int display_w, display_h;
        glfwGetFramebufferSize(Glfw::getInstance()->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        auto clear_color = _GS<ImVec4>::getInstance()->getPtr("clear_color");
        if (clear_color)
            glClearColor(clear_color->x, clear_color->y, clear_color->z, clear_color->w);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        float ct = (float)glfwGetTime();
        deltaTime = ct - lastTime;
        lastTime = ct;
    };
    _endOp = [&]() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    return true;
}
void Glfw::CloseWindow()
{
    glfwSetWindowShouldClose(window, true);
}
void Glfw::Terminate()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(Glfw::getInstance()->getWindow());
    glfwTerminate();
}
GLFWwindow *Glfw::getWindow()
{
    return window;
}

void Glfw::RunDemo()
{
    Editor::UIManager::getInstance()->InitDemo();
    // Loop
    while (!glfwWindowShouldClose(Glfw::getInstance()->getWindow()))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

        Editor::UIManager::getInstance()->RunDemo();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(Glfw::getInstance()->getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        auto clear_color = _GS<ImVec4>::getInstance()->getPtr("clear_color");
        if (clear_color)
            glClearColor(clear_color->x, clear_color->y, clear_color->z, clear_color->w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(Glfw::getInstance()->getWindow());
    }

    Terminate();
}

void Glfw::Run(KTKR::OpQueue *opList)
{
    while (opList->isHold() && !glfwWindowShouldClose(window))
    {
        _startOp();
        opList->Run();
        _endOp();
    }
    Terminate();
}

void Glfw::Run(KTKR::Ptr<KTKR::OpQueue> &opList)
{
    while (opList->isHold() && !glfwWindowShouldClose(window))
    {
        _startOp();
        opList->Run();
        _endOp();
    }
    Terminate();
}

void Glfw::updateViewport(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    // KTKR::EventListener::getInstance()->response(KTKR::EventListener::WINDOW_ZOOM);
}
