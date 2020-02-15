#ifndef TIME_H
#define TIME_H
#include <string>
#include <sstream>

//TODO: Parametrar som inte modifieras ska vara const alt. const reference.
//TODO: Alla funktioner som inte modifierar objektet som kallar på den
//ska vara const.
//TODO: Hjälpfunktioner ska vara privata.

//DONE: Ändrat alla Parametrar som ska vara const till const alt const reference
//DONE: Ändrat funktioner till const på de funktioner som inte modifierar objektet
//DONE: Tagit bort onödiga funktioner & variabler
//DONE: Begränsat set funktionerna
//DONE: Flyttat ut hjälpfunktionen Valid_range till cc.filen, gjort om I/Ostream till friend
//DONE: Lagt till fler testfall för att testa då tiden som adderas/subtraheras är över ett dygn
//DONE: Fixat testfallen för pre inc/dec och lagt till ett testfall för chained input


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
  bool operator >(const Time& rhs)  const;
  bool operator ==(const Time& rhs) const;
  bool operator >=(const Time& rhs) const;
  bool operator <=(const Time& rhs) const;
  bool operator !=(const Time& rhs) const;

  friend std::ostream& operator<<(std::ostream& temp, const Time& t);
  friend std::istream& operator>>(std::istream& temp, Time & t);

private:
  int h;
  int m;
  int s;

  bool is_valid() const;

};

#endif
