#include "struct.h"
#include "funcs.h"
#include <stdio.h>

/* your six struct manipulation functions go here */

/* DO NOT put a main() function in this file */


int endian_swap_int_shift(int x){
	x = (x & 0x0000FFFF) << 16 | (x & 0xFFFF0000) >> 16;
	x = (x & 0x00FF00FF) << 8 | (x & 0xFF00FF00) >> 8;
	return x;
}

long long endian_swap_long_long_shift(long long x){
	long long temp = x;
	temp = (temp >> 32) & 0xFFFFFFFF;
	temp = endian_swap_int_shift((int) temp) & 0xFFFFFFFF;
	x = endian_swap_int_shift((int) x) & 0xFFFFFFFF;
	x = x << 32;
	return x | temp;
}

struct s1 endian_swap_s1_shift (struct s1 str){
	struct s1 result;
	result.f0 = endian_swap_int_shift(str.f0);
	result.f1 = endian_swap_long_long_shift(str.f1);
	result.f2 = endian_swap_int_shift(str.f2);
	result.f3 = endian_swap_int_shift(str.f3);
	result.f4 = endian_swap_int_shift(str.f4);
	result.f5 = endian_swap_int_shift(str.f5);
	
	return result;
}


/*-------------------------------------------------------*/


int endian_swap_int_ptr(int x){
  unsigned char * startx = (unsigned char *)(&x);
  unsigned char * endx = startx + sizeof(x)-1;
  int result = 0;
  unsigned char * startr = (unsigned char *)(&result);
  
  while(startx <= endx){
  	*startr = *endx;
  	startr++;
    endx--;
  }
	return result;
}

long long endian_swap_long_long_ptr(long long x){
	unsigned char * startx = (unsigned char *)(&x);
  unsigned char * endx = startx + sizeof(x)-1;
  long long result = 0;
  unsigned char * startr = (unsigned char *)(&result);

  while(startx <= endx){
  	*startr = *endx;
  	startr++;
    endx--;
  }
	return result;
}

struct s1 endian_swap_s1_ptr (struct s1 str){
	struct s1 result;
	result.f0 = endian_swap_int_ptr(str.f0);
	result.f1 = endian_swap_long_long_ptr(str.f1);
	result.f2 = endian_swap_int_ptr(str.f2);
	result.f3 = endian_swap_int_ptr(str.f3);
	result.f4 = endian_swap_int_ptr(str.f4);
	result.f5 = endian_swap_int_ptr(str.f5);
	return result;
}


/*-------------------------------------------------------*/


void pack_s2 (char *c1, char *c2){	 
	int i = 0;   

  for (;i < 32; ++i){
  	c1[0] = c2[0];

  	if(i == 13) {
  		c2 += 2;
  	}

    c1 += 1;
    c2 += 1;
  }
}

void unpack_S2 (char *c1, char *c2){
	int i = 0;   

  for (;i < 32; ++i){
  	c1[0] = c2[0];

  	if(i == 13) {
  		c1 += 2;
  	}
  	
    c1 += 1;
    c2 += 1;
  }
}

int pack_s3 (char *c1, char *c2){
  int result = 0;

  // check bounds
  short * f0 = (short *) c2;
  short * f1 = (short *) (c2+2);
  unsigned short * f2 = (unsigned short *) (c2+4);
  unsigned int * f3 = (unsigned int *) (c2+8);
  long long * f4 = (long long *) (c2+12);
  unsigned short * f5 = (unsigned short *) (c2+20);

  if(*f0 > 127 || *f0 < -128)
    result = -1;  
  else if(*f1 > 3 || *f1 < -4)
    result = -1;  
  else if(*f2 > 4095)
    result = -1;
  else if(*f3 > 128)
    result = -1;
  else if(*f4 > 511 || *f4 < -512)
    result = -1;
  else if(*f5 > 65536)
    result = -1;

  // copy bits
  c1[0] = *f0;
  c1[1] = *f1;
  c1[2] = *f2;
  c1[4] = *f3;
  c1[5] = *f4;
  c1[8] = *f5;

	return result;
}

void unpack_s3 (char *c1, char *c2){
  short * f0 = (short *) c2;
  short * f1 = (short *) (c2+2);
  unsigned short * f2 = (unsigned short *) (c2+4);
  unsigned int * f3 = (unsigned int *) (c2+8);
  long long * f4 = (long long *) (c2+12);

  *f0 = c1[0];
  *f1 = c1[2];
  *f2 = c1[4];
  *f3 = c1[8];
  *f4 = c1[12];
}


