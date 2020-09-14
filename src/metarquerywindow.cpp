#include "metarquerywindow.h"
#include "dataref.h"
#include "httpclient.h"
#include <XPLMNavigation.h>
#include <iostream>

MetarQueryWindow::MetarQueryWindow() : Window("METAR query")
{

}

void MetarQueryWindow::onWindowShown()
{
    float latitude = static_cast<float>(DataRef<double>("sim/flightmodel/position/latitude").get());
    float longitude = static_cast<float>(DataRef<double>("sim/flightmodel/position/longitude").get());

    XPLMNavRef apRef = XPLMFindNavAid(nullptr, nullptr, &latitude, &longitude, nullptr, xplm_Nav_Airport);
    if (apRef == XPLM_NAV_NOT_FOUND) {
        return;
    }

    char id[32], name[256];
    XPLMGetNavAidInfo(apRef, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, id, name, nullptr);

    std::cout << "Fetching weather for " << id << std::endl;

    m_http.get("http://metar.vatsim.net/metar.php?id=" + std::string(id), [](std::string metar) {
        std::cout << "metar=" << metar << std::endl;
    });
}
