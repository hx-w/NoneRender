#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "./libs/glm/glm.hpp"
#include "./libs/glm/gtc/matrix_transform.hpp"
#include "./libs/glm/gtc/type_ptr.hpp"
#include "./libs/GLFW/glfw3.h"
#include "service.h"
#include "libs/imgui/imgui.h"

namespace RenderSpace {
    class RenderService;
    class RenderWindowWidget {
    public:
        RenderWindowWidget() = default;
        RenderWindowWidget(unsigned int width, unsigned int height, std::shared_ptr<RenderService> service);
        ~RenderWindowWidget();

        void init(unsigned int width, unsigned int height, std::shared_ptr<RenderService> service);

    public:
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput(GLFWwindow* window);

        void pickingRay(glm::vec2 screen_pos, glm::vec3& direction);
        void screen2world(glm::vec2 screen_pos, glm::vec3& world_pos);
    public:
        unsigned int m_scr_width = 800;
        unsigned int m_scr_height = 600;

        // camera
        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 10.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
        float cameraSpeed = 8.f;

        bool leftMousePressed = false;
        bool firstMouse = true;
        float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch =  0.0f;
        float lastX =  800.0f / 2.0;
        float lastY =  600.0 / 2.0;
        float fov   =  45.0f;

        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;

        GLenum shade_mode = GL_LINE;
        std::shared_ptr<RenderService> m_service;
        bool all_visible = true;
        ImVec4 clear_color = ImVec4(0.8f, 0.8f, 0.8f, 1.00f);

        float realX = 0.0f;
        float realY = 0.0f;
    private:
        bool T_down = false;
        bool H_down = false;
        bool R_down = false;
        bool CTRL_down = false;
    
    private:
        void T_EventHandler();
        void H_EventHandler();
    };
}

#endif
