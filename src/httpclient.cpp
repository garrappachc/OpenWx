#include "httpclient.h"
#include <XPLMProcessing.h>
#include <curl/curl.h>
#include <algorithm>
#include <iostream>

namespace {

constexpr auto UserAgent = "OpenWx/1.0";

struct HttpClientRequestData {
    HttpClientRequestData(CURL* curl, std::function<void (std::string)> callback) :
        callback(callback),
        curl(curl)
    { }

    std::function<void (std::string)> callback;
    CURL* curl;
    std::string data;
};

size_t curlWrite(void *contents, size_t size, size_t nmemb, void *userp)
{
    HttpClientRequestData* requestData = reinterpret_cast<HttpClientRequestData*>(userp);
    requestData->data.append(reinterpret_cast<const char*>(contents), size * nmemb);
    return size * nmemb;
}

} // namespace

HttpClient::HttpClient()
{
    m_curl = curl_multi_init();
    XPLMRegisterFlightLoopCallback(&HttpClient::flightLoop, -1.0, this);
}

HttpClient::~HttpClient()
{
    curl_multi_cleanup(m_curl);
    XPLMUnregisterFlightLoopCallback(&HttpClient::flightLoop, this);
}

void HttpClient::get(const std::string& url, std::function<void (std::string)> callback)
{
    HttpClientRequestData* requestData = new HttpClientRequestData(curl_easy_init(), callback);

    curl_easy_setopt(requestData->curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(requestData->curl, CURLOPT_USERAGENT, UserAgent);
    curl_easy_setopt(requestData->curl, CURLOPT_WRITEFUNCTION, &::curlWrite);
    curl_easy_setopt(requestData->curl, CURLOPT_WRITEDATA, requestData);
    curl_easy_setopt(requestData->curl, CURLOPT_PRIVATE, requestData);
    curl_multi_add_handle(m_curl, requestData->curl);
}

void HttpClient::perform()
{
    curl_multi_perform(m_curl, &m_handleCount);

    CURLMsg *msg;
    int messagesLeft;

    while ((msg = curl_multi_info_read(m_curl, &messagesLeft))) {
        if (msg->msg == CURLMSG_DONE) {
            HttpClientRequestData* requestData;
            curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &requestData);
            requestData->callback(requestData->data);
            delete requestData;
        }
    }
}

float HttpClient::flightLoop(float /*inElapsedSinceLastCall*/, float /*inElapsedTimeSinceLastFlightLoop*/, int /*inCounter*/, void* self)
{
    HttpClient* instance = reinterpret_cast<HttpClient*>(self);
    instance->perform();

    return -1.0f;
}
