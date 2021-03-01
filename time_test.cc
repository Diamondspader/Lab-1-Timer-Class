#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Time.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut

TEST_CASE ("Default constructor")
{
    Time t;
    CHECK(t.hour() == 0);
    CHECK(t.minute() == 0);
    CHECK(t.second() == 0);
}

// the following line will halt the compilation process. Move it
// one test case at the time and then start creating your own test
// cases

TEST_CASE ( "Constructor with numeric arguments" )
{
    Time t{12,13,14};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 13);
    CHECK(t.second() == 14);

}

TEST_CASE ("Constructor with faulty argument")
{
    CHECK_THROWS( Time{41,0,0} );
    CHECK_THROWS( Time{0,99,0} );
    CHECK_THROWS( Time{0,0,99} );
}

TEST_CASE ("String constructor")
{
    Time t{"12:23:12"};
    CHECK(t.hour() == 12);
    CHECK(t.minute() == 23);
    CHECK(t.second() == 12);

    SECTION ("Throws as well")
    {
        CHECK_THROWS( Time{"02:11:74"} );
    }
}

TEST_CASE ("am or pm")
{
    Time t{12,12,31};
    CHECK_FALSE(t.is_am());
    Time t2{1,2,3};
    CHECK(t2.is_am());
}

TEST_CASE ("Convert to string" )
{
    CHECK( Time{12,12,12}.to_string()     ==    "12:12:12" );
    CHECK( Time{12, 1, 2}.to_string()     ==    "12:01:02" );
    CHECK( Time{14,33,12}.to_string(true) == "02:33:12 pm" );
}



TEST_CASE ("Conversion to string" )
{
    CHECK( string(Time{2,4,1}) == "02:04:01" );
}

//*DONE?* TODO: Testa också chained input.
TEST_CASE ("Output operator" )
{
    stringstream ss;
    SECTION("Simple output")
    {
        ss << Time{2,5,1};
        CHECK(ss.str() == "02:05:01");
    }

    SECTION("Chained output")
    {
        ss << Time{23,10,32} << "---";
        CHECK(ss.str() == "23:10:32---");
    }

    SECTION("Const time")
    {
        Time const t{23,23,23};
        ss << t;
        CHECK(ss.str() == "23:23:23");
    }
    SECTION("simple input")
    {
      ss.str("23:32:12");
      Time t{};
      ss >> t;
      CHECK(t.to_string() == "23:32:12");
      CHECK_FALSE(ss.fail());
    }
    SECTION("Chained input")
    {
      ss.str("23:12:12 22:13:13");
      Time t1{};
      Time t2{};
      ss >> t1 >> t2;
      CHECK(t1.to_string()=="23:12:12");
      CHECK(t2.to_string()=="22:13:13");
    }
    SECTION("failed input")
    {
      ss.str("23:60:12");
      Time t{};
      ss >> t;
      CHECK(t.to_string() == "00:00:00");
      CHECK(ss.fail());
    }
}

//*DONE* TODO: Ni testar inte om pre delen av inc/dec funkar.
// TODO: Testa också så att +/- operatorn klarar sekunder > 86400 (över en dag)
TEST_CASE ("arithmetic operators")
{
  //ADDITION
  Time t1{23,59,59};
  Time t2{};
  t2 = t1 + 3;
  CHECK(t2.to_string() == "00:00:02");

  t2 = t2 + 86403;
  CHECK(t2.to_string() == "00:00:05");

  //Subtraction
  Time t3{0,0,0};
  t2 = t3 - 3;
  CHECK(t2.to_string() == "23:59:57");

//86400*20 = 1 728 000.   DVS -20 dagar + (- 1 sec)
  t2 = t2 - 1728001;
  CHECK(t2.to_string() == "23:59:56");

  //PREINCREMENT
  Time t9{23,59,57};
  Time t4{++t9};
  CHECK(t4.to_string() == "23:59:58");

  //POSTINCREMENT
  Time t5{23,59,57};
  t1 = t5++;
  CHECK(t1.to_string() == "23:59:57");
  CHECK(t5.to_string() == "23:59:58");

  //PREDECREMENT
  Time t6{23,59,57};
  Time t8{--t6};
  CHECK(t8.to_string() == "23:59:56");

  //POSTDECREMENT
  Time t7{23,59,56};
  t1 = t7--;
  CHECK(t1.to_string() == "23:59:56");
  CHECK(t7.to_string() == "23:59:55");
}

TEST_CASE (" Relational Operators")
{


  Time a{22,59,56};
  Time b{22,59,57};
  Time c{22,59,56};

  CHECK(( a < b));
  CHECK((b > a));
  CHECK((a >= c));
  CHECK((a <= c));
  CHECK((a == c));
  CHECK((a != b));

  CHECK_FALSE(( a > b));
  CHECK_FALSE((b < a));
  CHECK_FALSE((a >= b));
  CHECK_FALSE((b <= a));
  CHECK_FALSE((a == b));
  CHECK_FALSE((a != c));


}


#if 0

#endif
