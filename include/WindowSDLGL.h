#pragma once

/**
 *
 * This class is responible for creating a window context, as well the
 * openGL/glad context. It also stores width/height information. So the
 * dimensions
 */

namespace Celestia
{

// forward declarations
class EventBus;

class WindowSDLGL
{

  public:
    WindowSDLGL(const std::string &title, const std::string &version, EventBus &eventBus,
                unsigned int initialWidth = 1920, unsigned int initialHeight = 1080);
    ~WindowSDLGL();

    void publishCurrentWindowSize();

    SDL_Window *getSDLGLWindow() const
    {
        return window;
    }
    SDL_GLContext getGLContext() const
    {
        return glContext;
    }

    int getWidth() const
    {
        return m_width;
    }
    int getHeight() const
    {
        return m_height;
    }

  private:
    EventBus &eventBus;
    SDL_Window *window;
    SDL_GLContext glContext;

    int m_width;
    int m_height;

    bool m_mouseVisible;
    bool m_windowIsMaximized;
    bool m_windowFullscreen;
    bool m_vsyncMode;

    const char *m_videoDriver;

    // Fullscreen mode member variables
    int m_prevWidth = 0;
    int m_prevHeight = 0;
    int m_prevX = 0;
    int m_prevY = 0;

    void handleMouseVisibity(unsigned int width, unsigned int height);
    void handleWindowResize(unsigned int width, unsigned int height);
    void handleMaximizeWindow();
    void handleFullscreenMode();
    void handleVsyncMode();

    void setupEventSubscriptions();
};

} // namespace Celestia
