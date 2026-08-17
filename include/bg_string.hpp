#ifndef BG_STRING_HPP
#define BG_STRING_HPP

class bg_string
{
  char *spaces;
  short all_size;
  short past_size;

  void upgrade_size(const short new_size);

  public:
  bg_string(const short size);

  void update_size_spaces(const short size);

  char* get_spaces();

  ~bg_string();
};

#endif
