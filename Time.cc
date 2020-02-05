// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"
#include <iomanip>
#include <sstream>
#include <string>

bool Time::is_valid()
{
  return  !(set_range(23, 0, hour())
          ||set_range(59, 0, minute())
          ||set_range(59, 0, second()));
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
  return !set_range(11, 0, hour());
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
  return (x<min || x>max);
}

//omvandlar sekunder till 24h format
Time Time::sec_to_time(int second)
{
  Time t{};

  second = second % (3600*24);
  t.set_hour((second / 3600) % 24);
  second = second % 3600;
  t.set_minute(second / 60);
  second = second % 60;
  t.set_second(second);

  return t;
}

//objekt på vänstra sidan av operatorn, rhs = right hand side
Time Time::operator +(const int& rhs)
{
  Time t{};
  int add{};

  add = rhs + this->get_time_in_sec();
  t = sec_to_time(add);

  return t;
}

//objekt på vänstra sidan av operatorn, rhs = right hand side
Time Time::operator -(const int& rhs)
{
  Time t{};
  int sub{};

  sub = this->get_time_in_sec() - rhs;
  t = sec_to_time(sub);

  return t;
}

//*this = an object of the class, this = pointer of the object
Time& Time::operator ++()
{
  *this = *this + 1;
  return *this;
}

Time& Time::operator --()
{
  *this = *this - 1;
  return *this;
}

Time Time::operator ++(int)
{
  Time t{*this};
  *this = *this + 1;
  return t;
}

Time Time::operator --(int)
{
  Time t{*this};
  *this = *this - 1;
  return t;
}

bool Time::operator <(const Time& rhs)
{
  return (this->get_time_in_sec() < rhs.get_time_in_sec());
}

bool Time::operator >(Time& rhs)
{
  return rhs < *this;
}

bool Time::operator ==(const Time& rhs)
{
  return this->get_time_in_sec() == rhs.get_time_in_sec();
}

bool Time::operator >=(Time& rhs)
{
  return (*this == rhs || *this > rhs);
}

bool Time::operator <=(Time& rhs)
{
  return (*this == rhs || *this < rhs);
}

bool Time::operator !=(Time& rhs)
{
  return !(*this == rhs);
}

std::ostream& operator<<(std::ostream& lhs,const Time& rhs)
{
  lhs << rhs.get_time_str();

  return lhs;
}

std::istream& operator>>(std::istream& lhs, Time& rhs)
{
  int x{};
  int y{};
  int z{};

  lhs >> x;
  if(set_range(23, 0, x))
  {
    lhs.setstate(std::ios::failbit);
  }
  lhs.ignore(1);
  lhs >> y;
  if(set_range(59, 0, y))
  {
    lhs.setstate(std::ios::failbit);
  }
  lhs.ignore(1);
  lhs >> z;
  if(set_range(59, 0, z))
  {
    lhs.setstate(std::ios::failbit);
  }

  if(!lhs.fail())
  {
    rhs.set_hour(x);
    rhs.set_minute(y);
    rhs.set_second(z);
  }

  return lhs;
}
