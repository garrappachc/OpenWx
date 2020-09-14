#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <functional>
#include <list>
#include <string>

typedef void CURLM;

class HttpClient {
public:
    HttpClient();
    virtual ~HttpClient();

    void get(const std::string& url, std::function<void(std::string)> callback);

private:
    void perform();

    static float flightLoop(float inElapsedSinceLastCall, float inElapsedTimeSinceLastFlightLoop, int inCounter, void *inRefcon);

    CURLM* m_curl = nullptr;
    int m_handleCount = 0;

};

#endif // HTTPCLIENT_H
