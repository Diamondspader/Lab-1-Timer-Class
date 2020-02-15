// I denna fil läggs definitionerna (implementationen) av de funktioner
// som deklarerats i Time.h
#include "Time.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

bool valid_range(const int& max, const int& min, const int& x)
{
  return (x>=min && x<=max);
}

bool Time::is_valid() const
{
  return  (valid_range(23, 0, hour())
          && valid_range(59, 0, minute())
          && valid_range(59, 0, second()));
}

Time::Time():
      h{0}, m{0}, s{0}
{
}

Time::Time(int hour,int minute,int second):
      h{hour}, m{minute}, s{second}
{
  if(!is_valid())
  {
    throw std::invalid_argument("invalid argument");
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
    throw std::invalid_argument("invalid argument");
  }
}

void Time::set_hour  (const int& hour)
{
  if(valid_range(23,0, hour))
  {
    h = hour;
  }
  else
  {
    throw std::invalid_argument("invalid argument");
  }
}

void Time::set_minute(const int& minute)
{
  if(valid_range(59,0, minute))
  {
    m = minute;
  }
  else
  {
    throw std::invalid_argument("invalid argument");
  }
}

void Time::set_second(const int& second)
{
  if(valid_range(59,0, second))
  {
    s = second;
  }
  else
  {
    throw std::invalid_argument("invalid argument");
  }
}


bool Time::is_am() const
{
  return valid_range(11, 0, hour());
}

std::string Time::to_string(bool am_pm) const
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

//omvandlar sekunder till 24h format
Time Time::sec_to_time(int second)
{
  Time t{};
  if(second < 0)
  {
    second = ((second % 86400) + 86400);
  }

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

  add = rhs + get_time_in_sec();
  t = sec_to_time(add);

  return t;
}

//objekt på vänstra sidan av operatorn, rhs = right hand side
Time Time::operator -(const int& rhs)
{
  Time t{};
  int sub{};

  sub = get_time_in_sec() - rhs;
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

bool Time::operator <(const Time& rhs) const
{
  return (this->get_time_in_sec() < rhs.get_time_in_sec());
}

bool Time::operator >(const Time& rhs) const
{
  return rhs < *this;
}

bool Time::operator ==(const Time& rhs) const
{
  return this->get_time_in_sec() == rhs.get_time_in_sec();
}

bool Time::operator >=(const Time& rhs) const
{
  return (*this == rhs || *this > rhs);
}

bool Time::operator <=(const Time& rhs) const
{
  return (*this == rhs || *this < rhs);
}

bool Time::operator !=(const Time& rhs) const
{
  return !(*this == rhs);
}

//TODO: Använd to_string istället så borde ni inte behöva get_time_str().
//DONE
std::ostream& operator<<(std::ostream& lhs, const Time& rhs)
{
  Time t{rhs};
  lhs << t.to_string();

  return lhs;
}

std::istream& operator>>(std::istream& lhs, Time& rhs)
{
  int x{};
  int y{};
  int z{};

  lhs >> x;
  if(!valid_range(23, 0, x))
  {
    lhs.setstate(std::ios::failbit);
  }
  lhs.ignore(1);
  lhs >> y;
  if(!valid_range(59, 0, y))
  {
    lhs.setstate(std::ios::failbit);
  }
  lhs.ignore(1);
  lhs >> z;
  if(!valid_range(59, 0, z))
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
