#include "addition_functional.hpp"
#include "output.h"
#include "timedate.hpp"


void help()
{
  const char*msg_help = "\n======  all_flags  ======\n      -help :    show all flags\n      -static :  static version\n      -name :    name progect\n      -raw :     raw output time and date\n      -version : version progect\n";
  output_symbols(msg_help,stdout);
}

void name()
{
  const char*msg_name = NAME"\n\0";
  output_symbols(msg_name,stdout);
}

void time_and_date()
{
  char msg[60];
  short i = 0;
  move_to_time_format(cur_hour(),msg,&i);
  msg[i] = ':';i++;

  move_to_time_format(cur_minute(),msg,&i);
  msg[i] = ':';i++;

  move_to_time_format(cur_second(),msg,&i);
  msg[i] = '\n';i++;

  move_to_time_format(cur_day(),msg,&i);
  msg[i] = '/';i++;

  move_to_time_format(cur_month(),msg,&i);
  msg[i] = '/';i++;

  move_to_time_format(cur_year(),msg,&i);
  msg[i] = '\n';i++;msg[i] = '\0';i++;
  output_symbols(msg,stdout);
}

void test()
{
  char msg[10];
  short i = 0;
  move_to_time_format(0,msg,&i);
  msg[i] = ' ';i++;
  move_to_char(8,msg,&i);
  msg[i] = '\n';i++;msg[i] = '\0';
  output_symbols(msg,stdout);
  char num[20];
  short j = 0;
  move_to_char(msg[0],num,&j);
  move_to_char(msg[1],num,&j);
  move_to_char(msg[2],num,&j);
  move_to_char(msg[3],num,&j);
  output_symbols(num,stdout);
}

void version()
{
  const char*msg_version = VERSION"\n\0";
  output_symbols(msg_version,stdout);
}

void addition_functional(const short flag)
{
  switch(flag)
  {
    case 2:
      help();
      return;

    case 3:
      name();
      return;

    case 4:
      time_and_date();
      return;

    case 5:
      test();
      return;

    case 6:
      version();
      return;

    default:
      return;
  }
}
