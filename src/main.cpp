#include "datarefstore.h"
#include "dataref.h"
#include "httpclient.h"
#include "metarquerywindow.h"
#include <XPLMPlugin.h>
#include <XPLMDataAccess.h>
#include <XPLMProcessing.h>
#include <XPLMMenus.h>
#include <iostream>
#include <cstring>

float flightLoop(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);
void handleMenu(void *inMenuRef, void *inItemRef);

static int menuContainerId;
static XPLMMenuID menuId;
static std::unique_ptr<MetarQueryWindow> window;
static std::unique_ptr<HttpClient> httpClient;

static constexpr auto MetarWindow = "MetarWindow";

PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc)
{
    std::strcpy(outName, "OpenWx");
    std::strcpy(outSig, "pl.garapich.openwx");
    std::strcpy(outDesc, "An open-source weather engine");

    httpClient.reset(new HttpClient);

    // menu
    menuContainerId = XPLMAppendMenuItem(XPLMFindPluginsMenu(), "OpenWX", nullptr, 0);
    menuId = XPLMCreateMenu("OpenWX", XPLMFindPluginsMenu(), menuContainerId, handleMenu, nullptr);
    XPLMAppendMenuItem(menuId, "METAR query", const_cast<void*>(reinterpret_cast<const void*>(&MetarWindow)), 1);

    // cache datarefs
    DataRef<double> latitude("sim/flightmodel/position/latitude");
    DataRef<double> longitude("sim/flightmodel/position/longitude");

//    XPLMRegisterFlightLoopCallback(&flightLoop, 1.0, nullptr);

    window.reset(new MetarQueryWindow);
    return window->isCreated();
}

PLUGIN_API int XPluginEnable()
{
    return 1;
}

PLUGIN_API void XPluginDisable()
{

} 

PLUGIN_API void XPluginStop()
{
//    XPLMUnregisterFlightLoopCallback(&flightLoop, nullptr);
    XPLMDestroyMenu(menuId);
    httpClient.reset(nullptr);
    window.reset(nullptr);
    DataRefStore::clear();
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID /*inFrom*/, int /*inMsg*/, void* /*inParam*/)
{

}

float flightLoop(float /*inElapsedSinceLastCall*/, float /*inElapsedTimeSinceLastFlightLoop*/, int /*inCounter*/, void */*inRefcon*/)
{
    DataRef<double> latitude("sim/flightmodel/position/latitude");
    DataRef<double> longitude("sim/flightmodel/position/longitude");

    std::cout << "latitude=" << latitude.get() << ", longitude=" << longitude.get() << std::endl;

    return 1.0f;
}

void handleMenu(void *inMenuRef, void *inItemRef)
{
    if (reinterpret_cast<decltype(&MetarWindow)>(inItemRef) == &MetarWindow) {
        window->show();
    }
}
