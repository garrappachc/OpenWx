#ifndef METARQUERYWINDOW_H
#define METARQUERYWINDOW_H

#include "window.h"
#include "httpclient.h"

class MetarQueryWindow: public Window {
public:
    MetarQueryWindow();

protected:
    void onWindowShown() override;

private:
    HttpClient m_http;

};

#endif // METARQUERYWINDOW_H
