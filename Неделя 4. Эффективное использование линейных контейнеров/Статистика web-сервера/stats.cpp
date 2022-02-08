#include "test_runner.h"
//#include "../../common/test_runner.h"

#include "http_request.h"
#include "stats.h"

#include <map>
#include <string_view>
#include <unordered_set>

using namespace std;

HttpRequest ParseRequest(string_view line) {
  if(!line.empty() && line.front() == ' ') {
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

Stats::Stats() {
  for(string_view x: supportedMethods) {
    methodStats[x] = 0;
  }
  methodStats["UNKNOWN"] = 0;

  for(string_view x: supportedUris) {
    uriStats[x] = 0;
  }
  uriStats["unknown"] = 0;
}
void Stats::AddMethod(string_view method) {
  if(supportedMethods.count(method) != 0) {
    methodStats[method] += 1;
  } else {
    methodStats["UNKNOWN"] += 1;
  }
}
void Stats::AddUri(string_view uri) {
  if(supportedUris.count(uri) != 0) {
    uriStats[uri] += 1;
  } else {
    uriStats["unknown"] += 1;
  }
}

const map<string_view, int>& Stats::GetMethodStats() const {
  return methodStats;
}
const map<string_view, int>& Stats::GetUriStats() const {
  return uriStats;
}

/*Stats ServeRequests(istream& input) {
  Stats result;
  for (string line; getline(input, line); ) {
    const HttpRequest req = ParseRequest(line);

//    cout << req.method << '\t' << req.uri << '\t' << req.protocol << endl;

    result.AddUri(req.uri);
    result.AddMethod(req.method);
  }
  return result;
}

void TestBasic() {
  const string input =
    R"(GET / HTTP/1.1
    POST /order HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    POST /product HTTP/1.1
    GET /order HTTP/1.1
    PUT /product HTTP/1.1
    GET /basket HTTP/1.1
    DELETE /product HTTP/1.1
    GET / HTTP/1.1
    GET / HTTP/1.1
    GET /help HTTP/1.1
    GET /upyachka HTTP/1.1
    GET /unexpected HTTP/1.1
    HEAD / HTTP/1.1)";

  const map<string_view, int> expected_method_count = {
    {"GET", 8},
    {"PUT", 1},
    {"POST", 4},
    {"DELETE", 1},
    {"UNKNOWN", 1},
  };
  const map<string_view, int> expected_url_count = {
    {"/", 4},
    {"/order", 2},
    {"/product", 5},
    {"/basket", 1},
    {"/help", 1},
    {"unknown", 2},
  };

  istringstream is(input);
  const Stats stats = ServeRequests(is);

  ASSERT_EQUAL(stats.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(stats.GetUriStats(), expected_url_count);
}

void TestAbsentParts() {
  // Методы GetMethodStats и GetUriStats должны возвращать словари
  // с полным набором ключей, даже если какой-то из них не встречался

  const map<string_view, int> expected_method_count = {
    {"GET", 0},
    {"PUT", 0},
    {"POST", 0},
    {"DELETE", 0},
    {"UNKNOWN", 0},
  };
  const map<string_view, int> expected_url_count = {
    {"/", 0},
    {"/order", 0},
    {"/product", 0},
    {"/basket", 0},
    {"/help", 0},
    {"unknown", 0},
  };
  const Stats default_constructed;

  ASSERT_EQUAL(default_constructed.GetMethodStats(), expected_method_count);
  ASSERT_EQUAL(default_constructed.GetUriStats(), expected_url_count);
}*/

int main() {
  /*TestRunner tr;
  RUN_TEST(tr, TestBasic);
  RUN_TEST(tr, TestAbsentParts);*/
}
