#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include "./libs/glm/glm.hpp"
#include "./libs/glm/gtc/matrix_transform.hpp"
#include "./libs/glm/gtc/type_ptr.hpp"
#include "./libs/GLFW/glfw3.h"

namespace RenderSpace {
    class RenderWindow {
    public:
        RenderWindow() = default;
        RenderWindow(unsigned int width, unsigned int height);
        ~RenderWindow();

        void init(unsigned int width, unsigned int height);
    public:
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput();

    public:
        GLFWwindow* m_window;
        unsigned int m_scr_width = 800;
        unsigned int m_scr_height = 600;

        // camera
        glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

        bool firstMouse = true;
        float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
        float pitch =  0.0f;
        float lastX =  800.0f / 2.0;
        float lastY =  600.0 / 2.0;
        float fov   =  45.0f;

        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;
    };
}

#endif