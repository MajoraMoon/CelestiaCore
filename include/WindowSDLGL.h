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

    // inner enum class, so it does not conflict with global on/off values
    // somewhere else. idk how c++ works honestly, I know object oriented design
    // but c++ is something else lol
    enum class FullscreenMode
    {
        Windowed,
        Fullscreen,
        Borderless
    };

    enum class VsyncMode
    {
        Off = 0,
        On = 1
    };

    void publishCurrentWindowSize();

    void setFullscreenMode(FullscreenMode mode);

    void setVsyncMode(VsyncMode mode);

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

    FullscreenMode getFullscreenMode() const
    {
        return windowState.currentMode;
    }

    VsyncMode getVsyncMode() const
    {
        return m_VsyncMode;
    }

  private:
    EventBus &eventBus;
    SDL_Window *window;
    SDL_GLContext glContext;

    int m_width;
    int m_height;

    bool m_mouseVisible;
    bool m_windowIsMaximized;

    const char *videoDriver;

    void handleMouseVisibity(unsigned int width, unsigned int height);
    void handleWindowResize(unsigned int width, unsigned int height);
    void handleMaximizeWindow();

    void setupEventSubscriptions();

    struct WindowState
    {
        FullscreenMode currentMode = FullscreenMode::Windowed;
        int prevWidth = 0;
        int prevHeight = 0;
        int prevX = 0;
        int prevY = 0;
    };

    VsyncMode m_VsyncMode = VsyncMode::Off;

    WindowState windowState;
};

} // namespace Celestia
