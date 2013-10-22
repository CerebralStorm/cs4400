struct s1 {
  int f0;
  long long f1;
  unsigned int f2;
  int f3;
  long f4;
  int f5;
};

struct s2 {
  int f0;
  long long f1;
  unsigned char f2;
  signed char f3;
  unsigned long long f4;
  unsigned long long f5;
};

#pragma pack (1)
struct s2_packed {
  int f0;
  long long f1;
  unsigned char f2;
  signed char f3;
  unsigned long long f4;
  unsigned long long f5;
};
#pragma pack ()

struct s3 {
  short f0;
  short f1;
  unsigned short f2;
  unsigned int f3;
  long long f4;
  unsigned short f5;
};

struct s3_bitfield {
  short f0 : 8;
  short f1 : 3;
  unsigned short f2 : 12;
  unsigned int f3 : 8;
  long long f4 : 9;
  unsigned short f5 : 16;
};

