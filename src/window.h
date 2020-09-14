#ifndef WINDOW_H
#define WINDOW_H

#include <XPLMDisplay.h>
#include <memory>
#include <string>

class WindowPrivate;

class Window {
public:
    Window(const std::string& title);
    virtual ~Window();

    bool isVisible() const;
    void setVisible(bool visible);
    void show() { setVisible(true); }
    void hide() { setVisible(false); }

    bool isCreated() const { return m_id != nullptr; }

protected:
    virtual void onWindowShown();

    virtual void draw(XPLMWindowID inWindowId);
    virtual int mouseClick(XPLMWindowID inWindowId, int x, int y, int isDown);
    virtual int rightClick(XPLMWindowID inWindowId, int x, int y, int isDown);
    virtual int mouseWheel(XPLMWindowID inWindowId, int x, int y, int wheel, int clicks);
    virtual void key(XPLMWindowID inWindowId, char key, XPLMKeyFlags flags, char virtualKey, int losingFocus);
    virtual XPLMCursorStatus cursor(XPLMWindowID inWindowId, int x, int y);

private:
    void create();

    static void derefDrawWindow(XPLMWindowID inWindowId, void *inRefcon);
    static int derefMouseClick(XPLMWindowID inWindowId, int x, int y, int isDown, void *inRefcon);
    static int derefRightClick(XPLMWindowID inWindowId, int x, int y, int isDown, void *inRefcon);
    static int derefMouseWheel(XPLMWindowID inWindowId, int x, int y, int wheel, int clicks, void *inRefcon);
    static void derefKey(XPLMWindowID inWindowId, char key, XPLMKeyFlags flags, char virtualKey, void *inRefcon, int losingFocus);
    static XPLMCursorStatus derefCursor(XPLMWindowID inWindowId, int x, int y, void *inRefcon);

    XPLMWindowID m_id;
    std::string m_title;

};

#endif // WINDOW_H
