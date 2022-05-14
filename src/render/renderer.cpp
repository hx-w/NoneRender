﻿#include "renderer.h"
#include "./mesh/elements.h"

using namespace std;
using namespace fundamental;

namespace RenderSpace {
    Renderer::Renderer(RenderEngine& engine, unsigned int _width, unsigned int _height):
        m_engine(engine) {
        setup(_width, _height);
        // service 中维护了 shader，需要在renderer setup之后初始化
        m_service = std::make_shared<RenderService>();
        m_win_widget.init(_width, _height, m_service);
    }

    void Renderer::setup(unsigned int w, unsigned int h) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw m_window creation
        // --------------------
        m_window = glfwCreateWindow(w, h, "NURBS Render System", NULL, NULL);
        if (m_window == NULL) {
            std::cout << "Failed to create GLFW m_window" << std::endl;
            glfwTerminate();
            return;
        }
        glfwMakeContextCurrent(m_window);
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        glfwSetWindowUserPointer(m_window, &m_win_widget);

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, double xpos, double ypos) {
            static_cast<RenderWindowWidget*>(glfwGetWindowUserPointer(w))->mouse_callback(w, xpos, ypos);
        });
        glfwSetScrollCallback(m_window, [](GLFWwindow* w, double xoffset, double yoffset) {
            static_cast<RenderWindowWidget*>(glfwGetWindowUserPointer(w))->scroll_callback(w, xoffset, yoffset);
        });
        glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* w, int width, int height) {
            static_cast<RenderWindowWidget*>(glfwGetWindowUserPointer(w))->framebuffer_size_callback(w, width, height);
        });
        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* w, int button, int action, int modes) {
            static_cast<RenderWindowWidget*>(glfwGetWindowUserPointer(w))->mouse_button_callback(w, button, action, modes);
        });
        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return;
        }
    
        glEnable(GL_DEPTH_TEST);
        // 启用阴影平滑
        glShadeModel(GL_SMOOTH);
    } 

    Renderer::~Renderer() {
        glfwTerminate();
        m_service.reset();
    }

    int Renderer::exec() {
        while (!glfwWindowShouldClose(m_window)) {
            // clear
            // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

            // shade mode
            glPolygonMode(GL_FRONT_AND_BACK, m_win_widget.shade_mode);

            // input
            m_win_widget.processInput(m_window);

            update_transform();

            draw();

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }

    void Renderer::draw() {
        m_service->update();
        m_service->draw_all();
    }

    void Renderer::update_transform() {
        auto& m_shader = m_service->get_shader();
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        m_win_widget.deltaTime = currentFrame - m_win_widget.lastFrame;
        m_win_widget.lastFrame = currentFrame;

        // activate shader
        m_shader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(m_win_widget.fov), (float)m_win_widget.m_scr_width / (float)m_win_widget.m_scr_height, 0.1f, 100.0f);
        m_shader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = glm::lookAt(m_win_widget.cameraPos, m_win_widget.cameraPos + m_win_widget.cameraFront, m_win_widget.cameraUp);
        m_shader.setMat4("view", view);

        m_shader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
        m_shader.setVec3("lightPos", 0.0, 0.0, 0.0);
        m_shader.setVec3("viewPos", m_win_widget.cameraPos);
    }
}
