#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

/* The skip_to_next_line function searches for a newline character
 * in the provided character buffer, starting from the current index.
 *
 * This function is used in the parsing_conf function. */
void skip_to_next_line(char*buffer,size_t*i_buf,const size_t all_size)
{
  while(*i_buf < all_size)
  {
    if(buffer[*i_buf] == '\n')
    {
      (*i_buf)++;
      return;
    }
    else
    {
      (*i_buf)++;
    }
  }
}

/* The move_to_int function converts a character array into an integer.
 * The number of characters processed depends on the provided size.
 *
 * This function is used in the parsing_conf function. */
void move_to_int(short*num,char*symbols,const short size)
{
  int i = 0;
  for(i = 0; i < size; i++)
  {
    *num = *num * 10 + (symbols[i] - '0');
  }
}

/* The parsing_conf function is written entirely in C. It allocates heap memory 
 * to store bytes from the configuration file. The function iterates through 
 * each byte and populates the passed arrays according to their size. 
 * While the underlying parsing logic is quite trivial, it is highly optimized.
 *
 * This function is used in the main.cpp file. */
char parsing_conf(short**numbers,char**symbols,const short size_num,const short size_sym)
{
  const short size_buffer = 16384;
  char*buffer_conf = (char*)malloc(size_buffer);
  size_t i_buf = 0;

  FILE*conf_file = fopen(CONF_PATH,"r");
  size_t size_file = fread(buffer_conf,1,size_buffer,conf_file); 
  
  short i_num = 0;
  short i_sym = 0;

  short i = 0;
  char temp_num[4];

  short count_sym = 0;

  if(size_file < 50)
  {
    free(buffer_conf);
    return 0;
  }
  fclose(conf_file);

  while((i_buf < size_file) && (i_num < size_num || i_sym < size_sym))
  {
    if(buffer_conf[i_buf] == '=')
    {
      i = 0;
      while((i_buf++,i_buf < size_file) && buffer_conf[i_buf] != '\n' && i < 3)
      {
        if(buffer_conf[i_buf] >= '0' && buffer_conf[i_buf] <= '9')
        {
          temp_num[i] = buffer_conf[i_buf];
          i++;
        }
        else
        {
          free(buffer_conf);
          return 0;
        }
      }

      if(i == 0)
      {
        free(buffer_conf);
        return 0;
      }

      move_to_int(numbers[i_num],temp_num,i);
      i_num++;

      skip_to_next_line(buffer_conf,&i_buf,size_file);

    }
    else if(buffer_conf[i_buf] == '-')
    {
      i = 0;
      count_sym = 0;
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
        free(buffer_conf);
        return 0;
      }

      symbols[i_sym][i] = '\0';
      i_sym++;

      skip_to_next_line(buffer_conf,&i_buf,size_file);

    }
    else if(buffer_conf[i_buf] == '#')
    {
      skip_to_next_line(buffer_conf,&i_buf,size_file);
    }
    else if(buffer_conf[i_buf] == ' ' || buffer_conf[i_buf] == '\n')
    {
      i_buf++;
    }
    else
    {
      free(buffer_conf);
      return 0;
    }
  }

  if(i_num == size_num && i_sym == size_sym)
  {
    free(buffer_conf);
    return 1;
  }
  else
  {
    free(buffer_conf);
    return 0;
  }

}



char parsing_main(short *flag,const char* const*argv)
{
  const char*flags = "shnrv";
  short i = 0;
  if(argv[1][0] == '-')
  {
    if(argv[1][1] >= 'h' && argv[1][1] <= 'v')
    {
      do
      {
        if(flags[i] == argv[1][1])
        {
          *flag = i+1;
          return 1;
        }
      }while(i++,i < 5);
    }
  }
  return 0;
}
