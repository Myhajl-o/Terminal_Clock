#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

/* The skip_to_next_line function searches for a newline character
 * in the provided character buffer, starting from the current index.
 *
 * This function is used in the parsing_conf function. */
void skip_to_next_line(char*buffer,int*i_buf,const int all_size)
{
  while(*i_buf < all_size)
  {
    if(buffer[*i_buf] == '\n'){(*i_buf)++;return;}
    (*i_buf)++;
  }
}

/* The move_to_int function converts a character array into an integer.
 * The number of characters processed depends on the provided size.
 *
 * This function is used in the parsing_conf function. */
void move_to_int(short*num,char*symbols,const short size)
{
  int i = 0;
  for(; i < size; i++)
  {
    *num = *num * 10 + (symbols[i] - '0');
  }
}

short check_size_symbol(const char c)
{
  if((c & 0x80) == 0x00)
  {
    return 1;
  }
  else if((c & 0xE0) == 0xC0)
  {
    return 2;
  }
  else if((c & 0xF0) == 0xE0)
  {
    return 3;
  }
  else if((c & 0xF8) == 0xF0)
  {
    return 4;
  }
  return 1;
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
  char*buffer_conf = (char*)malloc(size_buffer + 1);
  int i_buf = 0;

  FILE*conf_file = fopen(CONF_PATH,"r");
  int size_file = fread(buffer_conf,1,size_buffer,conf_file); 
  
  short i_num = 0;
  short i_sym = 0;

  short i = 0;
  char temp_num[4];

  short count_sym = 0;
  short add_bytes = 1;
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
        add_bytes = check_size_symbol(buffer_conf[i_buf]) + i;

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

/* The `comparisons` function compares two
 * `char` arrays passed to it. If at least one character
 * does not match, it returns 0. Conversely,
 * if the two arrays are identical, it returns 1.
 *
 * The function is used in the `parsing_main` function.*/
char comparisons(const char*arg1,const char*arg2)
{
  short i = 1;
  for(;arg1[i] != '\0' || arg2[i] != '\0';i++)
  {
    if(arg1[i] != arg2[i]) return 0;
  }
  return 1;
}

/* The `parsing_main` function checks the second element
 * of the second argument passed to the `main` function.
 * It checks, one by one, whether the passed
 * argument matches any of the program's flags. The function
 * returns 0 if the second element does not match
 * any flag, and 1 if it does match
 * at least one flag. The function writes to the `flag` pointer
 * the index of the flag to which the second element is equal.

 * The function is used in the `main.cpp` file.*/
char parsing_main(short *flag,const char* const*argv)
{
  const char*flags[6] = {"-static","-help","-name","-raw","-test","-version"};
  short i = 0;
  if(argv[1][0] == '-')
  {
    if(argv[1][1] >= 'h' && argv[1][1] <= 'v')
    {
      for(;i < 6; i++)
      {
        if(comparisons(flags[i],argv[1]))
        {
          *flag = i+1;
          return 1;
        }
      }
    }
  }
  return 0;
}
