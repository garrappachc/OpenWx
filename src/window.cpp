#include "window.h"
#include <XPLMDisplay.h>

class WindowPrivate {
public:
    XPLMCreateWindow_t params();
};

Window::Window(const std::string& title) :
    m_title(title)
{
    create();
}

Window::~Window()
{
    XPLMDestroyWindow(m_id);
    m_id = nullptr;
}

bool Window::isVisible() const
{
    return XPLMGetWindowIsVisible(m_id);
}

void Window::setVisible(bool visible)
{
    XPLMSetWindowIsVisible(m_id, visible);

    if (visible)
        onWindowShown();
}

void Window::onWindowShown()
{

}

void Window::draw(XPLMWindowID /*inWindowId*/)
{

}

int Window::mouseClick(XPLMWindowID /*inWindowId*/, int /*x*/, int /*y*/, int /*isDown*/)
{
    return 0;
}

int Window::rightClick(XPLMWindowID /*inWindowId*/, int /*x*/, int /*y*/, int /*isDown*/)
{
    return 0;
}

int Window::mouseWheel(XPLMWindowID /*inWindowId*/, int /*x*/, int /*y*/, int /*wheel*/, int /*clicks*/)
{
    return 0;
}

void Window::key(XPLMWindowID /*inWindowId*/, char /*key*/, XPLMKeyFlags /*flags*/, char /*virtualKey*/, int /*losingFocus*/)
{

}

XPLMCursorStatus Window::cursor(XPLMWindowID /*inWindowId*/, int /*x*/, int /*y*/)
{
    return xplm_CursorDefault;
}

void Window::derefDrawWindow(XPLMWindowID inWindowId, void *inRefcon)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    self->draw(inWindowId);
}

int Window::derefMouseClick(XPLMWindowID inWindowId, int x, int y, int isDown, void* inRefcon)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    return self->mouseClick(inWindowId, x, y, isDown);
}

int Window::derefRightClick(XPLMWindowID inWindowId, int x, int y, int isDown, void* inRefcon)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    return self->rightClick(inWindowId, x, y, isDown);
}

int Window::derefMouseWheel(XPLMWindowID inWindowId, int x, int y, int wheel, int clicks, void* inRefcon)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    return self->mouseWheel(inWindowId, x, y, wheel, clicks);
}

void Window::derefKey(XPLMWindowID inWindowId, char key, XPLMKeyFlags flags, char virtualKey, void* inRefcon, int losingFocus)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    self->key(inWindowId, key, flags, virtualKey, losingFocus);
}

XPLMCursorStatus Window::derefCursor(XPLMWindowID inWindowId, int x, int y, void* inRefcon)
{
    Window* self = reinterpret_cast<Window*>(inRefcon);
    return self->cursor(inWindowId, x, y);
}

void Window::create()
{
    XPLMCreateWindow_t params;
    params.structSize = sizeof(params);
    params.visible = 0;

    params.drawWindowFunc = &Window::derefDrawWindow;
    params.handleMouseClickFunc = &Window::derefMouseClick;
    params.handleRightClickFunc = &Window::derefRightClick;
    params.handleMouseWheelFunc = &Window::derefMouseWheel;
    params.handleKeyFunc = &Window::derefKey;
    params.handleCursorFunc = &Window::derefCursor;
    params.refcon = reinterpret_cast<void*>(this);
    params.layer = xplm_WindowLayerFloatingWindows;
    params.decorateAsFloatingWindow = xplm_WindowDecorationRoundRectangle;

    int left, bottom, right, top;
    XPLMGetScreenBoundsGlobal(&left, &top, &right, &bottom);
    params.left = left + 50;
    params.top = top - 50;
    params.right = params.left + 200;
    params.bottom = params.top - 100;

    m_id = XPLMCreateWindowEx(&params);
    XPLMSetWindowPositioningMode(m_id, xplm_WindowPositionFree, -1);
    XPLMSetWindowResizingLimits(m_id, 100, 100, 500, 300);
    XPLMSetWindowTitle(m_id, m_title.c_str());
}
