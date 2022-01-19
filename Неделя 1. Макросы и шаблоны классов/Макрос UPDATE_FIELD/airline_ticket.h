#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Date {
  int year, month, day;
  friend bool operator==(const Date& lhs, const Date& rhs);
  friend std::istream& operator>>(std::istream& stream, Date& lhs);
  friend std::ostream& operator<<(std::ostream& stream, const Date& lhs);
};

struct Time {
  int hours, minutes;
  friend bool operator==(const Time& lhs, const Time& rhs);
  friend std::istream& operator>>(std::istream& stream, Time& lhs);
  friend std::ostream& operator<<(std::ostream& stream, const Time& lhs);
};

struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};