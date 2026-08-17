#include "addition_functional.hpp"
#include "output.h"
#include "timedate.hpp"

void move_to_char(short num, char*msg,char spec_sym)
{
  char s[10];
  short i = 7;
  s[9] = '\0';
  s[8] = spec_sym;
  for(;num;num/=10,i--)s[i] = num%10 + '0';
  if((i%2) == 0){s[i] = '0';i--;}
  i++;
  for(short j = 0; j <= (9 - i); j++){msg[j] = s[i + j];}
}

void help()
{
  const char*msg_help = "\n======  all_flags  ======\n      -help :    show all flags\n      -static :  static version\n      -name :    name progect\n      -raw :     raw output time and date\n      -version : version progect\n";
  output_message(msg_help);
}

void name()
{
  const char*msg_name = NAME"\n\0";
  output_message(msg_name);
}

void time_and_date()
{
  char msg[10];
  move_to_char(cur_hour(),msg,':');
  output_message(msg);

  move_to_char(cur_minute(),msg,':');
  output_message(msg);

  move_to_char(cur_second(),msg,'\n');
  output_message(msg);

  move_to_char(cur_day(),msg,'/');
  output_message(msg);

  move_to_char(cur_month(),msg,'/');
  output_message(msg);

  move_to_char(cur_year(),msg,'\n');
  output_message(msg);
}

void test()
{
  char msg[10];
  move_to_char(9,msg,'\n');
  output_number(msg[0]);
  output_number(msg[1]);
  output_number(msg[2]);
  output_number(msg[3]);
}

void version()
{
  const char*msg_version = VERSION"\n\0";
  output_message(msg_version);
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
