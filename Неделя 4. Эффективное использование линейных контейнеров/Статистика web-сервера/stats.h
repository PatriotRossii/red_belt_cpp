#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <unordered_set>

using namespace std;

class Stats {
  unordered_set<string_view> supportedMethods = {
    "GET", "POST", "PUT", "DELETE"
  };
  unordered_set<string_view> supportedUris = {
    "/", "/order", "/product", "/basket", "/help"
  };

  map<string_view, int> methodStats;
  map<string_view, int> uriStats;
public:
  Stats();
  void AddMethod(string_view method);
  void AddUri(string_view uri);

  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);