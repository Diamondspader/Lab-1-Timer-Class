#ifndef TIME_H
#define TIME_H
#include <string>
#include <sstream>

//TODO: Parametrar som inte modifieras ska vara const alt. const reference.
//TODO: Alla funktioner som inte modifierar objektet som kallar på den
//ska vara const.

//TODO: Hjälpfunktioner ska vara privata.
class Time
{
public:
  Time();
  Time(int hour,int minute, int second);
  Time(std::string str);

  int hour()  const{ return h; }
  int minute()const{ return m; }
  int second()const{ return s; }

  //TODO: Finns inga begränsningar på era set funktioner.
  void set_hour  (const int& hour  );
  void set_minute(const int& minute);
  void set_second(const int& second);

  int get_time_in_sec() const { return (h*3600 + m*60 + s); }

  bool is_am() const;
  std::string to_string(bool am_pm = false) const;
  Time sec_to_time(int second);

  operator std::string();
  Time operator +(const int& lhs);
  Time operator -(const int& lhs);

  Time& operator ++();
  Time& operator --();

  Time operator ++(int);
  Time operator --(int);

  bool operator <(const Time& rhs)  const;
  bool operator >(Time& rhs)        const;
  bool operator ==(const Time& rhs) const;
  bool operator >=(Time& rhs)       const;
  bool operator <=(Time& rhs)       const;
  bool operator !=(Time& rhs)       const;

private:
  int h;
  int m;
  int s;

//TODO: Värdet på denna sätts bara en gång?
//Så fort användaren ändrar datumet så visar den fel värde.
    // int time_in_sec{h*3600 + m*60 + s};

//TODO: Värdet på denna sätts bara en gång?
// (Se även kommentaren till output operatorn)
//Så fort användaren ändrar datumet så visar den fel värde.

  bool is_valid();

};

std::ostream& operator<<(std::ostream& temp, const Time& t);
std::istream& operator>>(std::istream& temp, Time & t);



#endif
