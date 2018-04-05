//
//
//

#ifndef HUNTER_REFERENCE_H
#define HUNTER_REFERENCE_H

struct GLFWwindow;

namespace gfx
{
    /*!
     Crossplatform window that plays a OpenGL < 2.0 demo
     */
    class DemoGLWindow
    {
        GLFWwindow *const pWindow;

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
