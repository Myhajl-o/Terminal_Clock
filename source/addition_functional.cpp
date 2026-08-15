#include "addition_functional.hpp"
#include "output.h"

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

      return;

    case 5:
      version();
      return;

    default:
      return;
  }
}
