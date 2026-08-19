#ifndef BG_STRING_HPP
#define BG_STRING_HPP

class bg_string
{
  char *spaces;
  short all_size;
  short past_size;
  const char*symbol;
  short size_sym;

  void upgrade_size();
  void fill_array_1b(short index);
  void fill_array_234b(short intdex);

  public:
  bg_string(const short size,const char*sym);

  void update_size_spaces(short size);

  char* get_spaces();

  ~bg_string();
};

#endif
