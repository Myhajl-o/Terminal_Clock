#ifndef COLOR_OBJECT_HPP
#define COLOR_OBJECT_HPP

struct Color_object
{
  short back_color;
  short front_color;
  short main_back_color;
  short main_front_color;

  Color_object()
  {
    back_color = 0;
    front_color = 0;
    main_back_color = 0;
    main_front_color = 0;
  }

  Color_object(const short b,const short f,const short mb,const short mf)
  {
    back_color = b;
    front_color = f;
    main_back_color = mb;
    main_front_color = mf;
  }




};

#endif
