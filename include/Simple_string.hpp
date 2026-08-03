#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

class Simple_string
{
  char *symbols;
  unsigned int all_size;
  unsigned int current_size;


  public:
  Simple_string(unsigned int _size);
  
  void upgrade_size(unsigned int new_size);

  void update_array(unsigned int _size);

  char* get_array();

  ~Simple_string();
};

#endif
