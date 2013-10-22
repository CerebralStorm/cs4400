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

void test_pack_s2_value(struct s2_packed str2_packed, struct s2 str2){
  assert(str2_packed.f0 != 0xFFFFFFFF);
  assert(str2_packed.f1 != 0xEEEEEEEEEEEEEEEELL);
  assert(str2_packed.f2 != 0xD);
  assert(str2_packed.f3 != 0xC);
  assert(str2_packed.f4 != 0xBBBBBBBBBBBBBBBBULL);
  assert(str2_packed.f5 != 0xAAAAAAAAAAAAAAAAULL);

  char * str2_packed_p = (char *)(&str2_packed);
  char * str2_p = (char *)(&str2);   
  pack_s2(str2_packed_p, str2_p);

  assert(str2_packed.f0 == 0xFFFFFFFF);
  assert(str2_packed.f1 == 0xEEEEEEEEEEEEEEEELL);
  assert(str2_packed.f2 == 0xD);
  assert(str2_packed.f3 == 0xC);
  assert(str2_packed.f4 == 0xBBBBBBBBBBBBBBBBULL);
  assert(str2_packed.f5 == 0xAAAAAAAAAAAAAAAAULL);
}

void test_unpack_s2_value(struct s2_packed str2_packed, struct s2 str2){
  assert(str2.f0 != 0x11111111);
  assert(str2.f1 != 0x2222222222222222LL);
  assert(str2.f2 != 0x3);
  assert(str2.f3 != 0x4);
  assert(str2.f4 != 0x5555555555555555ULL);
  assert(str2.f5 != 0x6666666666666666ULL);

  char * str2_packed_p = (char *)(&str2_packed);
  char * str2_p = (char *)(&str2);   
  unpack_S2(str2_p, str2_packed_p);

  assert(str2.f0 == 0x11111111);
  assert(str2.f1 == 0x2222222222222222LL);
  assert(str2.f2 == 0x3);
  assert(str2.f3 == 0x4);
  assert(str2.f4 == 0x5555555555555555ULL);
  assert(str2.f5 == 0x6666666666666666ULL);
}

void test_pack_s2_size(struct s2_packed str2_packed, struct s2 str2){
  assert(sizeof(str2_packed) == 30);
  assert(sizeof(str2) == 32);
}

void test_pack_s2_against_unpack_S2( struct s2_packed str2_packed, struct s2 str2, 
                                  struct s2_packed blank_packed, struct s2 blank ){
  str2.f0 = 0xFFFFFFFF;
  str2.f1 = 0xEEEEEEEEEEEEEEEELL;
  str2.f2 = 0xD;
  str2.f3 = 0xC;
  str2.f4 = 0xBBBBBBBBBBBBBBBBULL;
  str2.f5 = 0xAAAAAAAAAAAAAAAAULL;
  str2_packed.f0 = 0xFFFFFFFF;
  str2_packed.f1 = 0xEEEEEEEEEEEEEEEELL;
  str2_packed.f2 = 0xD;
  str2_packed.f3 = 0xC;
  str2_packed.f4 = 0xBBBBBBBBBBBBBBBBULL;
  str2_packed.f5 = 0xAAAAAAAAAAAAAAAAULL;

  char * blank_packed_p = (char *)(&blank_packed);
  char * str2_p = (char *)(&str2);   
  pack_s2(blank_packed_p, str2_p);

  char * str2_packed_p = (char *)(&str2_packed);
  char * blank_p = (char *)(&blank);   
  unpack_S2(blank_p, str2_packed_p);

  assert(blank.f0 == blank_packed.f0);
  assert(blank.f1 == blank_packed.f1);
  assert(blank.f2 == blank_packed.f2);
  assert(blank.f3 == blank_packed.f3);
  assert(blank.f4 == blank_packed.f4);
  assert(blank.f5 == blank_packed.f5);
}

void test_pack_s2_then_upack_S2(struct s2_packed str2_packed, struct s2 str2){
  char * str2_packed_p = (char *)(&str2_packed);
  char * str2_p = (char *)(&str2);   
  pack_s2(str2_packed_p, str2_p); 

  assert(str2_packed.f0 == 0xFFFFFFFF);
  assert(str2_packed.f1 == 0xEEEEEEEEEEEEEEEELL);
  assert(str2_packed.f2 == 0xD);
  assert(str2_packed.f3 == 0xC);
  assert(str2_packed.f4 == 0xBBBBBBBBBBBBBBBBULL);
  assert(str2_packed.f5 == 0xAAAAAAAAAAAAAAAAULL);

  unpack_S2(str2_p, str2_packed_p);

  assert(str2.f0 == 0xFFFFFFFF);
  assert(str2.f1 == 0xEEEEEEEEEEEEEEEELL);
  assert(str2.f2 == 0xD);
  assert(str2.f3 == 0xC);
  assert(str2.f4 == 0xBBBBBBBBBBBBBBBBULL);
  assert(str2.f5 == 0xAAAAAAAAAAAAAAAAULL);
}

void test_pack_s3_overflow(){
  int i = 0;
  for(; i < 6; i++){
    struct s3_bitfield str3_bitfield;
    struct s3 str3;
    str3.f0 = 0;
    str3.f1 = 0;
    str3.f2 = 0;
    str3.f3 = 0;
    str3.f4 = 0;
    str3.f5 = 0;

    char * str3_bitfield_p = (char *)(&str3_bitfield);
    char * str3_p = (char *)(&str3);

    assert(pack_s3(str3_bitfield_p, str3_p) == 0);
    switch(i){
      case 0:        
        str3.f0 = 128;
        assert(pack_s3(str3_bitfield_p, str3_p) == -1);
        break;
      case 1:
        str3.f1 = 4;
        assert(pack_s3(str3_bitfield_p, str3_p) == -1);
        break;
      case 2:
        str3.f2 = 4096;
        assert(pack_s3(str3_bitfield_p, str3_p) == -1);
        break;
      case 3:
        str3.f3 = 129;
        assert(pack_s3(str3_bitfield_p, str3_p) == -1);
        break;
      case 4:
        str3.f4 = 512;
        assert(pack_s3(str3_bitfield_p, str3_p) == -1);
        break;
      case 5:
        str3.f5 = 65535;
        assert(pack_s3(str3_bitfield_p, str3_p) == 0);
        break;
    }   
  }
}

void test_pack_s3_value(){
  struct s3_bitfield str3_bitfield;
  struct s3 str3;

  str3.f0 = 1;
  str3.f1 = 2;
  str3.f2 = 3;
  str3.f3 = 4;
  str3.f4 = 5;
  str3.f5 = 6;

  char * str3_bitfield_p = (char *)(&str3_bitfield);
  char * str3_p = (char *)(&str3);
  pack_s3(str3_bitfield_p, str3_p); 

  assert(str3_bitfield.f0 == 1);
  assert(str3_bitfield.f1 == 2);
  //assert(str3_bitfield.f2 == 3);
  assert(str3_bitfield.f3 == 4);
  assert(str3_bitfield.f4 == 5);
  //assert(str3_bitfield.f5 == 6);
}

void test_unpack_s3_value(){
  struct s3_bitfield str3_bitfield;
  struct s3 str3;

  str3_bitfield.f0 = 1;
  str3_bitfield.f1 = 2;
  str3_bitfield.f2 = 3;
  str3_bitfield.f3 = 4;
  str3_bitfield.f4 = 5;
  str3_bitfield.f5 = 6;

  char * str3_bitfield_p = (char *)(&str3_bitfield);
  char * str3_p = (char *)(&str3);
  unpack_s3(str3_p, str3_bitfield_p); 

  assert(str3.f0 == 1);
  assert(str3.f1 == 2);
  assert(str3.f2 == 3);
  assert(str3.f3 == 4);
  assert(str3.f4 == 5);
  assert(str3.f5 == 6);
}

void test_pack_s3_then_unpack_s3(){
  struct s3_bitfield str3_bitfield;
  struct s3 str3;
  struct s3 str3_unpacked;

  str3.f0 = 1;
  str3.f1 = 2;
  str3.f2 = 3;
  str3.f3 = 4;
  str3.f4 = 5;
  str3.f5 = 6;

  char * str3_bitfield_p = (char *)(&str3_bitfield);
  char * str3_p = (char *)(&str3);
  pack_s3(str3_bitfield_p, str3_p); 

  char * str3_unpacked_p = (char *)(&str3_unpacked);
  unpack_s3(str3_unpacked_p, str3_bitfield_p);

  // assert(str3_unpacked.f0 == 1);
  // assert(str3_unpacked.f1 == 2);
  // assert(str3_unpacked.f2 == 3);
  // assert(str3_unpacked.f3 == 4);
  // assert(str3_unpacked.f4 == 5);
  // assert(str3_unpacked.f5 == 6);

}

void test_unpack_s3_then_pack_s3(){
  struct s3_bitfield str3_bitfield;
  struct s3 str3;
  struct s3_bitfield str3_packed;

  str3_bitfield.f0 = 1;
  str3_bitfield.f1 = 2;
  str3_bitfield.f2 = 3;
  str3_bitfield.f3 = 4;
  str3_bitfield.f4 = 5;
  str3_bitfield.f5 = 6;

  char * str3_bitfield_p = (char *)(&str3_bitfield);
  char * str3_p = (char *)(&str3);
  unpack_s3(str3_p, str3_bitfield_p); 

  char * str3_packed_p = (char *)(&str3_packed);
  pack_s3(str3_packed_p, str3_p);

  assert(str3_packed.f0 == 1);
  assert(str3_packed.f1 == 2);
  assert(str3_packed.f2 == 3);
  assert(str3_packed.f3 == 4);
  assert(str3_packed.f4 == 5);
  assert(str3_packed.f5 == 6);
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
  // pack_s2, unpack_S2
  struct s2_packed str2_packed;
  struct s2 str2;
  str2.f0 = 0xFFFFFFFF;
  str2.f1 = 0xEEEEEEEEEEEEEEEELL;
  str2.f2 = 0xD;
  str2.f3 = 0xC;
  str2.f4 = 0xBBBBBBBBBBBBBBBBULL;
  str2.f5 = 0xAAAAAAAAAAAAAAAAULL;

  str2_packed.f0 = 0x11111111;
  str2_packed.f1 = 0x2222222222222222LL;
  str2_packed.f2 = 0x3;
  str2_packed.f3 = 0x4;
  str2_packed.f4 = 0x5555555555555555ULL;
  str2_packed.f5 = 0x6666666666666666ULL;

  struct s2_packed str2_packed_2;
  struct s2 str2_2;

  test_pack_s2_value(str2_packed, str2);
  test_unpack_s2_value(str2_packed, str2);  
  test_pack_s2_against_unpack_S2(str2_packed_2, str2_2, str2_packed_2, str2_2);
  test_pack_s2_size(str2_packed, str2);
  test_pack_s2_then_upack_S2(str2_packed, str2);

  ////////////////////////////////////////////////////
  // pack_s3, upack_s3
  test_pack_s3_overflow();
  test_pack_s3_value();
  test_unpack_s3_value();
  test_pack_s3_then_unpack_s3();
  test_unpack_s3_then_pack_s3();

  return 0;
}

  // char * str3_bitfield_p = (char *)(&str3_bitfield);
  // char * str3_p = (char *)(&str3);   
  // pack_s3(str3_bitfield_p, str3_p); 

  // printf("%i\n", str3_bitfield.f0);
  // printf("%i\n", str3_bitfield.f1);
  // printf("%i\n", str3_bitfield.f2);
  // printf("%i\n", str3_bitfield.f3);
  // printf("%i\n", str3_bitfield.f4);
  // printf("%i\n", str3_bitfield.f5);

  // i = 0; 
  // example = (char *) & str3_bitfield; 
  // for (; i < sizeof(struct s3_bitfield); i++) { printf("bitfield[%i] = %x\n", i, example[i]); }

  // int i = 0; 
  // char * example = (char *) & str3_bitfield; 
  // for (; i < sizeof(struct s3_bitfield); i++) { printf("bitfield[%i] = %x\n", i, example[i]); }

  // printf("%i\n", str3_bitfield.f0);
  // printf("%i\n", str3_bitfield.f1);
  // printf("%i\n", str3_bitfield.f2);
  // printf("%i\n", str3_bitfield.f3);
  // printf("%i\n", str3_bitfield.f4);
  // printf("%i\n", str3_bitfield.f5);