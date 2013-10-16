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

char *longLong2Bin(long long a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    int i = 63;
    for (; i >= 0; i--) {
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
  // Setup Variables
  char buffer[BUF_SIZE];
  buffer[BUF_SIZE - 1] = '\0';
  char longBuffer[LONG_BUF_SIZE];
  longBuffer[LONG_BUF_SIZE-1] = '\0';

  struct s1 str;  
  str.f0 = 0xF0E0D0C0;
  str.f1 = 0xF0E0D0C0B0A09080LL;
  str.f2 = 0xF0E0D0C0;
  str.f3 = 0xF0E0D0C0;
  str.f4 = 0xF0E0D0C0;
  str.f5 = 0xF0E0D0C0;

  struct s1 result;

  result = endian_swap_s1_ptr(str);

  ll2bin(str.f1, longBuffer, LONG_BUF_SIZE - 1);
  printf("orgnal = %s\n", longBuffer);
  ll2bin(result.f1, longBuffer, LONG_BUF_SIZE - 1);
  printf("result = %s\n", longBuffer);

  test_endian_swap_s1_shift(str);
  test_endian_swap_s1_shift_identity(str);
  //test_endian_swap_s1_ptr(str);
  //test_endian_swap_s1_ptr_identity(str);
  //test_endian_swap_are_equal(str);

  return 0;
}
