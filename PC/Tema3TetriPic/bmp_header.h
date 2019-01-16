#ifndef BMP_HEADER_H
#define BMP_HEADER_H
#pragma pack(1)

/*
 *  Pentru File Header si Info Header nu am modificat structurile date in enun-
 *  tul temei.
 */
typedef struct {
  unsigned char fileMarker1; /* 'B' */
  unsigned char fileMarker2; /* 'M' */
  unsigned int bfSize;       /* File's size */
  unsigned short unused1;
  unsigned short unused2;
  unsigned int imageDataOffset; /* Offset to the start of image data */
} bmpFileHeader;

typedef struct {
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

/*
 *  Am creat o structura reprezentand un pixel. Folosesc unsigned char pentru
 *  fiecare din R, G si B pentru ca ocupa un singur bit.
 */
typedef struct {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} bmpPixel;

/*
 *  Am creat si o structura pentru pixelii de padding, adica cei care sunt adau-
 *  gati la finalul unei linii astfel incat latimea sa fie divizibila cu 4.
 *  Folosesc unsigned short pentru ca ocupa 2 biti.
 */
typedef struct {
  unsigned short p;
} bmpPaddingPixel;

#pragma pack()
#endif
