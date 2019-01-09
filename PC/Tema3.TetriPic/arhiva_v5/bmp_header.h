/* Tells the compiler not to add padding for these structs. This may
   be useful when reading/writing to binary files.
   http://stackoverflow.com/questions/3318410/pragma-pack-effect
*/
#pragma pack(1)

typedef struct  {
  unsigned char fileMarker1; /* 'B' */
  unsigned char fileMarker2; /* 'M' */
  unsigned int bfSize;       /* File's size */
  unsigned short unused1;
  unsigned short unused2;
  unsigned int imageDataOffset; /* Offset to the start of image data */
} bmpFileHeader;

typedef struct  {
  unsigned int biSize; /* Size of the info header - 40 bytes */
  signed int width;    /* Width of the image */
  signed int height;   /* Height of the image */
  unsigned short planes;
  unsigned short bitPix;
  unsigned int biCompression;
  unsigned int biSizeImage; /* Size of the image data */
  int biXPelsPerMeter;
  int biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
} bmpInfoHeader;

typedef struct {
<<<<<<< HEAD
   unsigned char b;
   unsigned char g;
   unsigned char r;
=======
  unsigned char b;
  unsigned char g;
  unsigned char r;
>>>>>>> 658ad79b07536f815853140947a2efefddf68a97
} bmpPixel;

typedef struct {
  unsigned short p;
} bmpPaddingPixel;

#pragma pack()
