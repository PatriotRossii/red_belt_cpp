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
  Stats() {
    for(string_view x: supportedMethods) {
      methodStats[x] = 0;
    }
    methodStats["UNKNOWN"] = 0;

    for(string_view x: supportedUris) {
      uriStats[x] = 0;
    }
    uriStats["unknown"] = 0;
  }
  void AddMethod(string_view method) {
    if(supportedMethods.count(method) != 0) {
      methodStats[method] += 1;
    } else {
      methodStats["UNKNOWN"] += 1;
    }
  }
  void AddUri(string_view uri) {
    if(supportedUris.count(uri) != 0) {
      uriStats[uri] += 1;
    } else {
      uriStats["unknown"] += 1;
    }
  }

  const map<string_view, int>& GetMethodStats() const {
    return methodStats;
  }
  const map<string_view, int>& GetUriStats() const {
    return uriStats;
  }
};

HttpRequest ParseRequest(string_view line) {
  if(line.starts_with(' ')) {
    line = line.substr(line.find_first_not_of(' '));
  }

  auto first_delim = line.find(' ');
  auto second_delim = line.find(' ', first_delim + 1);

  return HttpRequest{
    line.substr(0, first_delim),
    line.substr(first_delim + 1, second_delim - (first_delim + 1)),
    line.substr(second_delim + 1)
  };
}