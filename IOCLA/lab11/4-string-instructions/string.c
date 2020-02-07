#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<stdint.h>

#define N 10000000

extern unsigned int computeLength1(char* str);
extern unsigned int computeLength2(char* str);


char a[N]; 

void main()
{
  uint32_t rng = 11; 
  for(int i = 0; i < N-1; i++){
    rng = (rng * 48271u) % 0x7fffffff;
    a[i] = 65 + (rng & 0x1f);
  }
  a[N-1] = 0;
  
  struct timeval t0, t1;

  gettimeofday(&t0, NULL);
  int len = computeLength1(a);
  gettimeofday(&t1, NULL);
  long elapsed = (t1.tv_sec - t0.tv_sec)*1000000 + t1.tv_usec - t0.tv_usec;
  printf("len = %u\n", len);
  printf("Time1 = %ld us\n", elapsed);

  struct timeval t3, t4;
  gettimeofday(&t3, NULL);
  int len2 = computeLength2(a);
  gettimeofday(&t4, NULL);
  long elapsed2 = (t4.tv_sec - t3.tv_sec)*1000000 + t4.tv_usec - t3.tv_usec;
  printf("len = %u\n", len2);
  printf("Time2 = %ld us\n", elapsed2);
  /* 
     Doubt the results? Check Agner Fog "Optimizing subroutines in
     assembly language An optimization guide for x86 platform" section
     16.10 
     https://www.agner.org/optimize/optimizing_assembly.pdf
   */
}
