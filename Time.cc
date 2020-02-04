// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"

#include <iomanip>

bool Time::is_valid()
{
  return  !(set_range(23, 0, hour())||
          set_range(59, 0, minute())||
          set_range(59, 0, second()));
}

Time::Time():
      h{0}, m{0}, s{0}
{
}

Time::Time(int hour, int minute, int second):
      h{hour}, m{minute}, s{second}
{
  if(!is_valid())
  {
    throw invalid();
  }
}

Time::Time(std::string str):
      h{}, m{}, s{}
{
  std::stringstream ss(str);
  ss >> h;
  ss.ignore(1);
  ss >> m;
  ss.ignore(1);
  ss >> s;
  if(!is_valid())
  {
    throw invalid();
  }
}

bool Time::is_am()
{
  return !(set_range(11, 0, hour()));
}

std::string Time::to_string(bool am_pm)
{
  int h {hour()};
  std::string am_or_pm;
  std::string str;
  std::stringstream ss;
  if(am_pm)
  {
    if(!is_am())
    {
      am_or_pm = " pm";
      h -= 12;
    }
    else
    {
      am_or_pm = " am";
    }
  }
  ss << std::setw(2) << std::setfill('0') << h<< ":"
  << std::setw(2) << std::setfill('0') << minute()<< ":"
  << std::setw(2) << std::setfill('0') << second();

  str = ss.str() + am_or_pm;
  ss.str(std::string());
  return str;
}

Time::operator std::string()
{
  return to_string();
}

bool set_range(const int& max, const int& min, const int& x)
{
  return (x>max || x<min);
}



std::ostream& operator<<(std::ostream& temp,const Time& t)
{
  temp << t.get_time_str();
  return temp;
}

std::istream& operator>>(std::istream& temp, Time& t)
{
  int x{},y{},z{};
  temp >> x;
  if(set_range(23, 0, x))
  {
    temp.setstate(std::ios::failbit);
  }
  temp.ignore(1);
  temp >> y;
  if(set_range(59, 0, y))
  {
    temp.setstate(std::ios::failbit);
  }
  temp.ignore(1);
  temp >> z;
  if(set_range(59, 0, z))
  {
    temp.setstate(std::ios::failbit);
  }
  if(!temp.fail())
  {
    t.set_hour(x);
    t.set_minute(y);
    t.set_second(z);
  }
  return temp;
}
