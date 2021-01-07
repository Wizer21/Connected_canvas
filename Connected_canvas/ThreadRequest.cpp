#include "ThreadRequest.h"
#include <iostream>
#include <sstream>

#define CURL_STATICLIB
#include <curl.h>

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
  std::string data((const char*)ptr, (size_t)size * nmemb);
  *((std::stringstream*)stream) << data << std::endl;
  return size * nmemb;
}

ThreadRequest::ThreadRequest(const std::string newUrl, QWidget* parent)
  : QThread(parent)
  , myUrl(newUrl)
  , curl(curl_easy_init())
{
}

void ThreadRequest::run()
{
  emit resultRequest(QString::fromStdString(this->download()));
}

std::string ThreadRequest::download()
{
  // Basic fetching setup
  curl_easy_setopt(curl, CURLOPT_URL, this->myUrl.c_str());
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");

  // Output setup
  std::stringstream out;
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

  // Perform the request and get the return code
  CURLcode res{curl_easy_perform(curl)};

  if (res != CURLE_OK)
  {
    //fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    return "fetch_error";
  }

  return out.str();
}

ThreadRequest::~ThreadRequest()
{
  curl_easy_cleanup(curl);
}