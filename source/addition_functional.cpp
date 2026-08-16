#include "addition_functional.hpp"
#include "output.h"
#include "timedate.hpp"

void move_to_char(short num, char*msg,char spec_sym)
{
  char s[10],*c = s + 9;
  short i = 0;
  for(i = 0;num;num/=10,i++)*--c = num%10 + '0';
  if((i%2) == 1){*--c = '0';i++;}
  while(i>0){*msg++ = *c++;i--;}
  *++msg = spec_sym;*++msg = '\0';
}

void help()
{
  const char*msg_help = "\n======  all_flags  ======\n      -h\n      -s : static version\n      -n : name progect\n      -r : raw output time and date\n      -v : version progect\n";
  output_message(msg_help);
}

void name()
{
  const char*msg_name = NAME;
  output_message(msg_name);
}

void time_and_date()
{
  char msg[10],*temp = msg;
  move_to_char(cur_second(),temp,':');
  output_message(msg);

  move_to_char(cur_minute(),temp,':');
  output_message(msg);

  move_to_char(cur_hour(),temp,'\n');
  output_message(msg);

  move_to_char(cur_day(),temp,'/');
  output_message(msg);

  move_to_char(cur_month(),temp,'/');
  output_message(msg);

  move_to_char(cur_year(),temp,'\n');
  output_message(msg);
}

void version()
{
  const char*msg_version = VERSION;
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
      version();
      return;

    default:
      return;
  }
}
