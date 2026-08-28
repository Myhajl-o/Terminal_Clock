/*
 * This library implements absolutely everything related to output.
 * Even features that are only indirectly related to output. For example, functions for converting
 * numbers to characters and filling an array with characters. The functions in this library
 * allow you to set the position and specify the color of
 * the characters being output.
 *
 * The library is very flexible, so to output data, you need to pass a pointer to
 * the file where the code should be written, which allows you to output not only to the terminal, 
 * but essentially anywhere.*/ 




#include "output.h"
#include "Colors.h"
#include <stdio.h>

/* The move_to_char function converts an integer
 * into an array of characters. It takes as its last
 * argument a pointer to the array index where
 * the characters should be written. This allows for flexible appending
 * of characters to an array that already contains characters.
 *
 * The function is used in the set_cursor and
 * set_color functions, as well as in the addition_functional.cpp file. */
void move_to_char(short num, char*msg,short*i_msg)
{
  char s[6];
  short i = 5;
  short j = 0;
  char sub = 0;
  if(num < 0)
  {
    sub = !sub;
    num = -num;
  }
  if(!num)
  {
    s[i--] = '0';
  }
  else
  {
    for(;num;num/=10)s[i--] = num%10 + '0';
  }
  if(sub)s[i--] = '-';
  for(; j < (5 - i); j++)msg[(*i_msg)++] = s[i + j + 1];
}

/* The move_to_time_format function converts an integer
 * into a character array. It takes as its last
 * argument a pointer to the array index where
 * the characters should be written. This allows for flexible appending
 * of characters to an array that already contains characters. It also
 * adds a zero if the number has an odd number of digits.
 *
 * The function is used in the addition_functional.cpp and
 * Date_window.cpp files.*/
void move_to_time_format(short num, char*msg,short*i_msg)
{
  char s[7];
  short i = 6;
  short j = 0;
  char zero = 0;
  char sub = 0;
  if(num < 0)
  {
    sub = !sub;
    num = -num;
  }
  if(!num)
  {
    s[i--] = '0';
    zero = !zero;
  }
  else
  {
    for(;num;num/=10,zero = !zero)s[i--] = num%10 + '0';
  }
  if(zero)s[i--] = '0';
  if(sub)s[i--] = '-';
  for(; j < (6 - i); j++)msg[(*i_msg)++] = s[i + j + 1];
}

/*
 * The filling_space function fills an array of characters with a specific
 * character and appends a null terminator at the end. It is
 * necessary because characters do not always occupy 1 byte.
 *
 * The function is used in the files watch_face.cpp and Hour-hand.cpp*/
short filling_space(char*space,const char*symbol,const short count)
{
  short size_sym = symbol[5];
  short all_size = count * size_sym;
  short i = 0, j = 0;
  for(; i < all_size; i++, j++)
  {
    if(j == size_sym) j = 0 ;
    space[i] = symbol[j];
  }
  space[all_size] = '\0';
  return size_sym;
}


/*
 * The `output_error` function outputs the code and description of an error that occurred while
 * reading the configuration file. It writes the message to the `error_conf` file, which
 * is located in the same directory as `clock.conf`.
 *
 * The function is used in the `Settings_clock.cpp` file.*/
void output_error(const short error)
{
  FILE*err_f = fopen(ERROR_CONF,"w");
  char const*msg_error[11] = {"No errors, everything was read correctly.\n",
                              "Error code : 1\nThe file was either not read or is too small.\n",
                              "Error code : 2\nThe loop successfully read the ‘=’ character,\nbut was unable to find a digit after it\nor encountered an invalid character.\n",
                              "Error code : 3\nAn invalid character was encountered while reading the digits.\n",
                              "Error code : 4\nAfter the digits were read, an invalid character was found.\n",
                              "Error code : 5\nAfter reading the character ‘-’,\nthe quotation mark was not found,\nor an invalid character was read.\n",
                              "Error code : 6\nAn invalid character was read during character reading.\n",
                              "Error code : 7\nNo characters were read during the character read operation.\n",
                              "Error code : 8\nAn invalid character was found after the characters were read.\n",
                              "Error code : 9\nInvalid character in the main loop.\n",
                              "Error code : 10\nInsufficient data to populate the arrays.\n"};
  if(err_f == NULL)return;

  output_symbols(msg_error[error],err_f);

  fclose(err_f);
}


/*The clear_term function clears the terminal of all other
 * colors and sets the colors to their
 * default values in the terminal.
 *
 * This function is used within the full_clear_term function
 * and is defined in the heart_clock.cpp file.*/
void clear_term()
{
  static const char*esc_clear = "\033[0m\0";
  output_symbols(esc_clear,stdout);
}

/* The full_clear_term function resets all escape codes
 * that were previously output, clears the terminal
 * of characters, and moves the cursor to the beginning
 * of the terminal, using escape codes.
 *
 * The function is used in the heart_clock.cpp file. */
void full_clear_term(const short y,const char*spaces)
{
  short i = 1;
  clear_term();
  for(;i <= y; i++)
  {
    set_cursor(0,i);
    output_symbols(spaces,stdout);
  }
  set_cursor(0,1);
}

/* The hide_cursor function hides the terminal cursor
 * using escape codes.
 *
 * The function is used in the heart_clock.cpp file. */
void hide_cursor(const char hide)
{
  static char esc_cursor[8] = "\033[?25l\0";
  if (hide)
  {
    esc_cursor[5] = 'l';
  }
  else
  {
    esc_cursor[5] = 'h';
  }
  output_symbols(esc_cursor,stdout);
}


void set_cursor(const short x,const short y)
{
  char esc_pos[20] = "\033[";
  short i = 2;
  move_to_char(y,esc_pos,&i);
  esc_pos[i++] = ';';
  move_to_char(x,esc_pos,&i);
  esc_pos[i++] = 'H';esc_pos[i] = '\0';
  output_symbols(esc_pos,stdout);
}

void set_color(const Colors color)
{
  char esc_color[20] = "\033[";
  short i = 2;
  move_to_char(color.back,esc_color,&i);
  esc_color[i++] = ';';
  move_to_char(color.front,esc_color,&i);
  esc_color[i++] = 'm';esc_color[i] = '\0';
  output_symbols(esc_color,stdout);
}

/* The output_object is the primary
 * output function for this utility. The function prints elements from
 * a char array to specific terminal locations using specific colors.
 *
 * It is used in the following files: background.cpp, watch_face.cpp, 
 * Second-hand.cpp, Minute-hand.cpp, Hour-hand.cpp and Date_window.cpp. */
void output_object(const short x,const short y, const char *symbols,const Colors color)
{
  set_cursor(x,y);
  set_color(color);
  output_symbols(symbols,stdout);
}

/*The output_symbols function is highly optimized.
 * It uses a simple C function that is very straightforward
 * and highly optimized. Essentially, it is simply a function that
 * outputs symbols to the terminal.
 *
 * The function is used in the functions full_clear_term, hide_cursor,
 * set_cursor, set_color, and output_object, as well as in the file 
 * addition_functional.cpp.*/
void output_symbols(const char*symbols,FILE*out)
{
  fputs(symbols,out);
  fflush(out);
}


