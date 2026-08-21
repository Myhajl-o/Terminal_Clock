#include "parsing.h"
#include <iostream>

int main ()
{
  const short size_num = 33,size_sym = 19;
  short*array_num[size_num];
  short numbers[size_num];
  char s0[10],s1[10],s2[10],s3[10],s4[10],s5[10],s6[10],s7[10],s8[10],s9[10],s10[10],s11[10],s12[10],s13[10],s14[10],s15[10],s16[10],s17[10],s18[10];
  short error;

  char*array_sym[19] = {s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18};

  for(short i = 0 ; i < size_num ; i++){numbers[i] = 0;array_num[i] = &numbers[i];}

  if(!parsing_conf(array_num,array_sym,size_num,size_sym,&error))
  {
    std::cout<<error<<"\n";
  }
  std::cout<<"\n";
  for(short i = 0 ; i < size_num ; i++) std::cout<<*(array_num[i])<<"    ";
  std::cout<<"\n";
  for(short i = 0 ; i < size_sym ; i++) std::cout<<array_sym[i]<<"\n";
  
  return 0;
}
