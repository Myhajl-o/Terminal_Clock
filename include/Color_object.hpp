#ifndef COLOR_OBJECT_HPP
#define COLOR_OBJECT_HPP

struct Color_object
{
  short back;
  short front;
  short main_back;
  short main_front;

  Color_object()
  {
    back = 0;
    front = 0;
    main_back = 0;
    main_front = 0;
  }

  Color_object(const short b,const short f,const short mb,const short mf)
  {
    back = b;
    front = f;
    main_back = mb;
    main_front = mf;
  }




};

#endif
