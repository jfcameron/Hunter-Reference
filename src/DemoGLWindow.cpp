#include "DemoGLWindow.h"

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>

using namespace gfx;

namespace 
{
    long int INSTANCE_COUNT = 0;

    void tryInitializeLibGLFW()
    {
        if (INSTANCE_COUNT == 0)
        {
            if (!glfwInit()) throw std::runtime_error("Could not initialize lib GLFW");

            ++INSTANCE_COUNT;
        }
    }
}

DemoGLWindow::DemoGLWindow()
: pWindow([]()
{
    tryInitializeLibGLFW();

    if (GLFWwindow *const pWindow = glfwCreateWindow(640, 480, "OpenGL < 2.0 demo", NULL, NULL))
    {
        glfwMakeContextCurrent(pWindow);
        glfwSwapInterval(1);

        glfwSetErrorCallback([](const int error, const char *const description) 
        {
            std::cerr << description << std::endl;
        });

        glfwSetKeyCallback(pWindow, [](GLFWwindow *const pWindow, const int key, const int scancode, const int action, const int mods) 
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(pWindow, GL_TRUE);
        });

        return pWindow;
    }
    else throw std::runtime_error("Could not create a window!");
}())
{}

DemoGLWindow::~DemoGLWindow()
{
    glfwDestroyWindow(pWindow);

    if (!INSTANCE_COUNT--) glfwTerminate();
}

bool DemoGLWindow::shouldClose() const
{
    return glfwWindowShouldClose(pWindow);
}

void DemoGLWindow::update() const
{
    int width, height;
    glfwGetFramebufferSize(pWindow, &width, &height);
            
    const float ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
}
