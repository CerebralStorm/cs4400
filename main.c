#include <stdio.h>
#include <assert.h>
#include "struct.h"
#include "funcs.h"
#define BUF_SIZE 33
#define LONG_BUF_SIZE 65

char *int2bin(int a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    int i = buf_size-1;
    for (;i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer;
}

char *ll2bin(long long a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    int i = buf_size-1;
    for (;i >= 0; i--) {
        *buffer-- = (a & 1) + '0';

        a >>= 1;
    }

    return buffer;
}

void test_endian_swap_s1_shift(struct s1 str){
  struct s1 result;

  result = endian_swap_s1_shift(str);
  assert(result.f0 == 0xC0D0E0F0);
  assert(result.f1 == 0x8090A0B0C0D0E0F0LL);
  assert(result.f2 == 0xC0D0E0F0);
  assert(result.f3 == 0xC0D0E0F0);
  assert(result.f4 == 0xC0D0E0F0);
  assert(result.f5 == 0xC0D0E0F0);
}

void test_endian_swap_s1_shift_identity(struct s1 str){
  struct s1 result1;
  struct s1 result2;

  result1 = endian_swap_s1_shift(str);
  result2 = endian_swap_s1_shift(result1);
  assert(result2.f0 == str.f0);
  assert(result2.f1 == str.f1);
  assert(result2.f2 == str.f2);
  assert(result2.f3 == str.f3);
  assert(result2.f4 == str.f4);
  assert(result2.f5 == str.f5);
}

void test_endian_swap_s1_ptr(struct s1 str){
  struct s1 result;

  result = endian_swap_s1_ptr(str);
  assert(result.f0 == 0xC0D0E0F0);
  assert(result.f1 == 0x8090A0B0C0D0E0F0LL);
  assert(result.f2 == 0xC0D0E0F0);
  assert(result.f3 == 0xC0D0E0F0);
  assert(result.f4 == 0xC0D0E0F0);
  assert(result.f5 == 0xC0D0E0F0);
}

void test_endian_swap_s1_ptr_identity(struct s1 str){
  struct s1 result1;
  struct s1 result2;

  result1 = endian_swap_s1_ptr(str);
  result2 = endian_swap_s1_ptr(result1);
  assert(result2.f0 == str.f0);
  assert(result2.f1 == str.f1);
  assert(result2.f2 == str.f2);
  assert(result2.f3 == str.f3);
  assert(result2.f4 == str.f4);
  assert(result2.f5 == str.f5);
}

void test_endian_swap_are_equal(struct s1 str){
  struct s1 result1;
  struct s1 result2;

  result1 = endian_swap_s1_shift(str);
  result2 = endian_swap_s1_ptr(str);

  assert(result1.f0 == result2.f0);
  assert(result1.f1 == result2.f1);
  assert(result1.f2 == result2.f2);
  assert(result1.f3 == result2.f3);
  assert(result1.f4 == result2.f4);
  assert(result1.f5 == result2.f5);
}

int main (void)
{
  ////////////////////////////////////////////////////
  // endian_swap_s1_shift, endian_swap_s1_ptr
  struct s1 str;  
  str.f0 = 0xF0E0D0C0;
  str.f1 = 0xF0E0D0C0B0A09080LL;
  str.f2 = 0xF0E0D0C0;
  str.f3 = 0xF0E0D0C0;
  str.f4 = 0xF0E0D0C0;
  str.f5 = 0xF0E0D0C0;

  struct s1 result;
  result = endian_swap_s1_ptr(str);

  test_endian_swap_s1_shift(str);
  test_endian_swap_s1_shift_identity(str);
  test_endian_swap_s1_ptr(str);
  test_endian_swap_s1_ptr_identity(str);
  test_endian_swap_are_equal(str);

  ////////////////////////////////////////////////////
  // pack_s2
  struct s2 str2_packed;
  struct s2 str2;
  str2.f0 = 0xFFFFFFFF;
  str2.f1 = 0xEEEEEEEEEEEEEEEELL;
  str2.f2 = 0xD;
  str2.f3 = 0xC;
  str2.f4 = 0xBBBBBBBBBBBBBBBBULL;
  str2.f5 = 0xAAAAAAAAAAAAAAAAULL;

  // // Setup Variables
  char buffer[LONG_BUF_SIZE];
  buffer[LONG_BUF_SIZE-1] = '\0';

  printf( "Memory size occupied by str2_packed : %d\n", sizeof(struct s2_packed));
  printf( "Memory size occupied by str2 : %d\n", sizeof(struct s2));

  char * str2_packed_p = (char *)(&str2_packed);
  char * str2_p = (char *)(&str2);  
  
  pack_s2(str2_packed_p, str2_p);

  printf("first int: %i\n", str2_packed.f0);
  printf("first int: %lld\n", str2_packed.f1);

  

  ll2bin(str2.f1, buffer, LONG_BUF_SIZE - 1);
  printf("origin = %s\n", buffer);
  ll2bin(str2.f1, buffer, LONG_BUF_SIZE - 1);
  printf("result = %s\n", buffer);

  // #pragma pack (1)
  // struct s2_packed {
  //   int f0;
  //   long long f1;
  //   unsigned char f2;
  //   signed char f3;
  //   unsigned long long f4;
  //   unsigned long long f5;
  // };
  // #pragma pack ()

  return 0;
}
