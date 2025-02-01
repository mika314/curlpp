#pragma once
#include <curl/curl.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

class Curl
{
public:
  Curl();
  ~Curl();
  auto getResponseCode() -> long;
  auto perform() -> CURLcode;
  auto setFollowLocations(long) -> void;
  auto setHeaders(const std::vector<std::string> &) -> void;
  auto setMaxRedirs(long) -> void;
  auto setPostFields(const std::string &) -> void;
  auto setUrl(const std::string &) -> void;

  using WriteFunc = std::function<auto(const char *content, size_t size)->size_t>;
  auto setWriteFunc(WriteFunc) -> void;

private:
  CURL *curl;
  std::unique_ptr<WriteFunc> writeFunc;
  struct curl_slist *headers = nullptr;
  static auto staticWriteFunc(void *content, size_t size, size_t nmemb, void *userp) -> size_t;
};
