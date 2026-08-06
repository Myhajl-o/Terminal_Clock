#include "parsing.hpp"
#include <cstdio>

int main()
{
  const short size_n = 17;
  const short size_s = 18;

  short numbers[size_n] = {0};
  short*point_to_num[size_n];

  short error = 0;

  char symbols0[10];
  char symbols1[10];
  char symbols2[10];
  char symbols3[10];
  char symbols4[10];
  char symbols5[10];
  char symbols6[10];
  char symbols7[10];
  char symbols8[10];
  char symbols9[10];
  char symbols10[10];
  char symbols11[10];
  char symbols12[10];
  char symbols13[10];
  char symbols14[10];
  char symbols15[10];
  char symbols16[10];
  char symbols17[10];


  char*point_to_sym[size_s];

  for(int i = 0; i < size_n; i++)
  {
    point_to_num[i] = &numbers[i];
  }

  point_to_sym[0] = symbols0;
  point_to_sym[1] = symbols1;
  point_to_sym[2] = symbols2;
  point_to_sym[3] = symbols3;
  point_to_sym[4] = symbols4;
  point_to_sym[5] = symbols5;
  point_to_sym[6] = symbols6;
  point_to_sym[7] = symbols7;
  point_to_sym[8] = symbols8;
  point_to_sym[9] = symbols9;
  point_to_sym[10] = symbols10;
  point_to_sym[11] = symbols11;
  point_to_sym[12] = symbols12;
  point_to_sym[13] = symbols13;
  point_to_sym[14] = symbols14;
  point_to_sym[15] = symbols15;
  point_to_sym[16] = symbols16;
  point_to_sym[17] = symbols17;

  bool read = parsing_conf(point_to_num,point_to_sym,size_n,size_s,error);

  if(read)
  {
     printf("\ncorrent reading conf file\n");
  }
  else
  {
    printf("\nerror reading conf file\n");
  }

  printf("\n%d\n",error);

  for(int i = 0; i < size_n; i++ )
  {
    printf("%d\n",numbers[i]);
  }

  for(int i = 0; i < size_s; i++)
  {
    printf("%s\n",point_to_sym[i]);
  }

  return 0;
}
