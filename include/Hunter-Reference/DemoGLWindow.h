//
//
//

#ifndef HUNTER_REFERENCE_H
#define HUNTER_REFERENCE_H

#include <memory>

struct GLFWwindow;

namespace gfx
{
    /*!
     Crossplatform window that plays a OpenGL < 2.0 demo
     */
    class DemoGLWindow final
    {
        std::unique_ptr<GLFWwindow, void(*)(GLFWwindow *const)> m_pWindow;

    public:
        /// Indicates whether the window should close or not
        bool shouldClose() const;

        /// Steps and draws the demo
        void update() const;

        DemoGLWindow();

        ~DemoGLWindow();
    };
}

#endif
