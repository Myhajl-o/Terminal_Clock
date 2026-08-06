#include "parsing.hpp"
#include <cstdio>

void skip_to_next_line(FILE*conf_file,char&c)
{
  while(c != '\n')
  {
    if(fscanf(conf_file,"%c",&c) != 1)
    {
      return;
    }
  }
}

void move_to_int(short*num,char*symbols,const short size)
{
  for(int i = 0; i < size; i++)
  {
    *num = *num * 10 + (symbols[i] - '0');
  }
}

bool parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym)
{
  FILE*conf_file = fopen(CONF_PATH,"r");
  if(conf_file == NULL)
  {
    return false;
  }

  short i_num = 0;
  short i_sym = 0;
  char c = 0;

  while((fscanf(conf_file,"%c",&c) == 1) && i_num < size_num && i_sym < size_sym)
  {
    if(c == '=')
    {
      
      short i = 0;
      char temp_num[4];

      while((fscanf(conf_file,"%c",&c) == 1) && i < 3)
      {
        if(c >= '0' && c <= '9')
        {
          temp_num[i] = c;
          i++;
        }
        else
        {
          return false;
        }
      }

      if(i == 0)
      {
        return false;
      }

      move_to_int(numbers[i_num],temp_num,i);
      i_num++;

      skip_to_next_line(conf_file,c);

    }
    else if(c == '-')
    {

      short i = 0;
      short count_sym = 0;

      while((fscanf(conf_file,"%c",&symbols[i_sym][i]) == 1) && symbols[i_sym][i] != '\n' && count_sym < 2)
      {
        short add_bytes = 0;
        if((symbols[i_sym][i] & 0x80) == 0x00)
        {
          add_bytes = 0;
        }
        else if((symbols[i_sym][i] & 0xE0) == 0xC0)
        {
          add_bytes = 1;
        }
        else if((symbols[i_sym][i] & 0xF0) == 0xE0)
        {
          add_bytes = 2;
        }
        else if((symbols[i_sym][i] & 0xF8) == 0xF0)
        {
          add_bytes = 3;
        }

        add_bytes += i;

        while(i < add_bytes)
        {
          i++;
          fscanf(conf_file,"%c",&symbols[i_sym][i]);
        }

        i++;
        count_sym++;
      }

      if(count_sym == 0)
      {
        return false;
      }

      symbols[i_sym][i] = '\0';
      i_sym++;

      skip_to_next_line(conf_file,c);

    }
    else if(c == '#')
    {
      skip_to_next_line(conf_file,c);
    }
    else if(c != ' ' && c != '\n')
    {
      return false;
    }
  }

  if(i_num == size_num && i_sym == size_sym)
  {
    return true;
  }
  else
  {
    return false;
  }

}

