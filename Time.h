// Denna fil ska innehålla deklarationer för de typer och funktioner
// som behövs
#ifndef TIME_H
#define TIME_H
#include <string>
#include <sstream>
class Time
{
public:
  class invalid{};

  Time();
  Time(int hour, int minute, int second);
  Time(std::string str);

  int hour()const  { return h; }
  int minute()const{ return m; }
  int second()const{ return s; }

  void set_hour  (int hour)  {h = hour;}
  void set_minute(int minute){m = minute;}
  void set_second(int second){s = second;}

  std::string get_time_str()const{return time_str;}

  bool is_am();
  std::string to_string(bool am_pm = false);

  operator std::string();
  //operator +(){}

private:
  int h;
  int m;
  int s;

  std::string time_str{to_string()};

  bool is_valid();
};

std::ostream& operator<<(std::ostream& temp,const Time& t);
std::istream& operator>>(std::istream& temp, Time & t);

bool set_range(const int& max, const int& min,const int& x);

#endif
