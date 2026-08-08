#include "parsing.hpp"
#include <cstdio>

void skip_to_next_line(char*buffer,std::size_t&i_buf,const std::size_t&all_size)
{
  while(i_buf < all_size)
  {
    if(buffer[i_buf] == '\n')
    {
      i_buf++;
      return;
    }
    else
    {
      i_buf++;
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
  const short size_buffer = 16384;
  char*buffer_conf = new char[size_buffer];
  std::size_t i_buf = 0;

  FILE*conf_file = fopen(CONF_PATH,"r");
  std::size_t size_file = fread(buffer_conf,1,size_buffer,conf_file); 
  if(size_file < 50)
  {
    delete[] buffer_conf;
    return false;
  }
  fclose(conf_file);

  short i_num = 0;
  short i_sym = 0;

  while((i_buf < size_file) && (i_num < size_num || i_sym < size_sym))
  {
    if(buffer_conf[i_buf] == '=')
    {

      short i = 0;
      char temp_num[4];

      while((i_buf++,i_buf < size_file) && buffer_conf[i_buf] != '\n' && i < 3)
      {
        if(buffer_conf[i_buf] >= '0' && buffer_conf[i_buf] <= '9')
        {
          temp_num[i] = buffer_conf[i_buf];
          i++;
        }
        else
        {
          delete[] buffer_conf;
          return false;
        }
      }

      if(i == 0)
      {
        delete[] buffer_conf;
        return false;
      }

      move_to_int(numbers[i_num],temp_num,i);
      i_num++;

      skip_to_next_line(buffer_conf,i_buf,size_file);

    }
    else if(buffer_conf[i_buf] == '-')
    {
      short i = 0;
      short count_sym = 0;
      i_buf++;

      while(i_buf < size_file && buffer_conf[i_buf] != '\n' && count_sym < 2)
      {
        short add_bytes = 1;
        if((buffer_conf[i_buf] & 0x80) == 0x00)
        {
          add_bytes = 1;
        }
        else if((buffer_conf[i_buf] & 0xE0) == 0xC0)
        {
          add_bytes = 2;
        }
        else if((buffer_conf[i_buf] & 0xF0) == 0xE0)
        {
          add_bytes = 3;
        }
        else if((buffer_conf[i_buf] & 0xF8) == 0xF0)
        {
          add_bytes = 4;
        }

        add_bytes += i;

        while(i < add_bytes)
        {
          symbols[i_sym][i] = buffer_conf[i_buf];
          i_buf++;
          i++;
        }
        count_sym++;
      }

      if(count_sym == 0)
      {
        delete[] buffer_conf;
        return false;
      }

      symbols[i_sym][i] = '\0';
      i_sym++;

      skip_to_next_line(buffer_conf,i_buf,size_file);

    }
    else if(buffer_conf[i_buf] == '#')
    {
      skip_to_next_line(buffer_conf,i_buf,size_file);
    }
    else if(buffer_conf[i_buf] == ' ' || buffer_conf[i_buf] == '\n')
    {
      i_buf++;
    }
    else
    {
      delete[] buffer_conf;
      return false;
    }
  }

  if(i_num == size_num && i_sym == size_sym)
  {
    delete[] buffer_conf;
    return true;
  }
  else
  {
    delete[] buffer_conf;
    return false;
  }

}

