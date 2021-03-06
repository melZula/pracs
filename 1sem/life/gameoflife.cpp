#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
#pragma pack(push)  // push current alignment to stack
#pragma pack(1)     // set alignment to 1 byte boundary


typedef struct {
  short int   bfType;         // 0x4d42 | 0x4349 | 0x5450
  int    bfSize;         // размер файла
  int    bfReserved;     // 0
  int    bfOffBits;      // смещение до поля данных,
  // обычно 54 = 16 + biSize
  int    biSize;         // размер струкуры в байтах:
  // 40(BITMAPINFOHEADER) или 108(BITMAPV4HEADER)
  // или 124(BITMAPV5HEADER)
  int    biWidth;        // ширина в точках
  int    biHeight;       // высота в точках
  short int   biPlanes;       // всегда должно быть 1
  short int   biBitCount;     // 0 | 1 | 4 | 8 | 16 | 24 | 32
  int    biCompression;  // BI_RGB | BI_RLE8 | BI_RLE4 |
  // BI_BITFIELDS | BI_JPEG | BI_PNG
  // реально используется лишь BI_RGB
  int    biSizeImage;    // Количество байт в поле данных
  // Обычно устанавливается в 0
  int    biXPelsPerMeter;// горизонтальное разрешение, точек на дюйм
  int    biYPelsPerMeter;// вертикальное разрешение, точек на дюйм
  int    biClrUsed;      // Количество используемых цветов
  // (если есть таблица цветов)
  int    biClrImportant; // Количество существенных цветов.
  // Можно считать, просто 0
} BMPheader;

int *loadBMP( const char *fname, int &mx, int &my ) // чтение bmp
{
  mx = -1;
  my = -1;
  FILE *f = fopen( fname, "rb" );
  if( !f ) {return NULL;}
  BMPheader bh;    // File header sizeof(BMPheader) = 56
  size_t res;

  // читаем заголовок
  res = fread( &bh, 1, sizeof(BMPheader), f );
  if( res != sizeof(BMPheader) ) { fclose(f); return NULL; }

  // проверяем сигнатуру
  if( bh.bfType!=0x4d42 && bh.bfType!=0x4349 && bh.bfType!=0x5450 ) { fclose(f);  return NULL; }

  // проверка размера файла
  fseek( f, 0, SEEK_END);
  int filesize = ftell(f);

  // восстановим указатель в файле:
  fseek( f, sizeof(BMPheader), SEEK_SET);
  // проверим условия
  if( bh.bfSize != filesize ||
    bh.bfReserved != 0    ||
    bh.biPlanes   != 1    ||
    (bh.biSize!=40 && bh.biSize!=108 && bh.biSize!=124)||
    bh.bfOffBits != 14+bh.biSize ||

    bh.biWidth <1 || bh.biWidth >10000 ||
    bh.biHeight<1 || bh.biHeight>10000 ||
    bh.biBitCount    != 24 ||             // пока рассматриваем только полноцветные изображения
    bh.biCompression !=  0                // пока рассматриваем только несжатие изображения
  )
  {
    fclose(f);
    return NULL;
  }
  // Заголовок прочитан и проверен, тип - верный (BGR-24), размеры (mx,my) найдены
  mx = bh.biWidth;
  my = bh.biHeight;
  int mx3 = (3*mx+3) & (-4);    // Compute row width in file, including padding to 4-byte boundary
  unsigned char *tmp_buf = new unsigned  char[mx3*my];    // читаем данные
  res = fread( tmp_buf, 1, mx3*my, f);
  if( (int)res != mx3*my ) { delete []tmp_buf; fclose(f); return NULL; }
  // данные прочитаны
  fclose(f);

  // выделим память для результата
  int *v = new int[mx*my];

  // Перенос данных (не забудем про BGR->RGB)
  unsigned char *ptr = (unsigned char *) v;
  for(int y = my-1; y >= 0; y--) {
    unsigned char *pRow = tmp_buf + mx3*y;
    for(int x=0; x< mx; x++) {
      *ptr++ = *(pRow + 2);
      *ptr++ = *(pRow + 1);
      *ptr++ = *pRow;
      pRow+=3;
      ptr ++;
    }
  }
  delete []tmp_buf;
  return v;    // OK
}

int saveBMP( const char *fname, int *v, int mx, int my )    // В каждом элементе упаковано все три RGB-байта
{
  BMPheader bh; // Заголовок файла, sizeof(BMPheader) = 56
  memset( &bh, 0, sizeof(bh) );
  bh.bfType =0x4d42;    // 'BM'
  // Найдем длину строки в файле, включая округление вверх до кратного 4:
  int mx3 = (3*mx+3) & (-4);
  int filesize = 54 + my*mx3;
  bh.bfSize = filesize;
  bh.bfReserved =  0;
  bh.biPlanes   =  1;
  bh.biSize     = 40;
  bh.bfOffBits  = 14 + bh.biSize;
  bh.biWidth    = mx;
  bh.biHeight   = my;
  bh.biBitCount = 24;
  bh.biCompression= 0;

  FILE *f = fopen( fname, "wb" );
  if( !f ) return -1;
  size_t res;

  // пишем заголовок
  res = fwrite( &bh, 1, sizeof(BMPheader), f );
  if( res != sizeof(BMPheader) ) { fclose(f); return -1; }

  // приготовим временный буфер
  unsigned char *tmp_buf = new unsigned char[mx3*my];
  // Перенос данных (не забудем про RGB->BGR)
  unsigned char *ptr = (unsigned char *) v;
  for(int y = my-1; y >= 0; y--) {
    unsigned char *pRow = tmp_buf + mx3*y;
    for(int x=0; x< mx; x++) {
      *(pRow + 2) = *ptr++;
      *(pRow + 1) = *ptr++;
      *pRow       = *ptr++;
      pRow+=3;
      ptr++;
    }
  }
  // сбросим в файл
  fwrite( tmp_buf, 1, mx3*my, f );
  fclose(f);
  delete []tmp_buf;
  return 0; // OK
}

char *itoa(int a){
  char *ss;   //create empty string
  while(a)
  {
    int x=a%10;
    a/=10;
    char i='0';
    i=i+x;
    ss=i+ss;      //append new character at the front of the string!
  }
  return ss;
}

int main(int argc, char * argv[]){
  int mx, my;
  int i, j;
  char *inputFile, *outputFile;
  int max_iter = 5;        // infinity
  int dump_freq = 0;

  for (i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--input")) {
      inputFile = argv[i+1];
    } else if (!strcmp(argv[i], "--output")) {
      outputFile = argv[i+1];
    } else if (!strcmp(argv[i], "--max_iter")) {
      max_iter = atoi(argv[i+1]);
    } else if (!strcmp(argv[i], "--dump_freq")) {
      dump_freq = atoi(argv[i+1]);
      printf("dump_freq = %d\n", dump_freq);
    }
  }


  int *firstgen = loadBMP(inputFile, mx, my);
  printf("SIZE %d %d\n", mx, my);

  if (firstgen != NULL){
    for (i = 0; i < my; i++) {
      for (j = 0; j < mx; j++) {
        firstgen[i*mx +j] = firstgen[i*mx + j] & 16777215;
        printf("%x  ", firstgen[i*mx +j]);
      }
      printf("\n");
    }

    int neighb[mx*my];
    int currNeighbours = 0;
    int iter;

    for (iter = 1; iter < max_iter+1; iter++){
      printf("________________\n");
      currNeighbours = 0;

      for (i = 0; i < my; i++) {      // creating neighbours matrix
        for (j = 0; j < mx; j++) {
          currNeighbours = 0;
          if (firstgen[ ((i-1 +my) % my)*mx+(j-1+mx % mx)] == 0) currNeighbours++;
          if (firstgen[ ((i-1 + my) % my)*mx+j] == 0) currNeighbours++;
          if (firstgen[ ((i-1 + my) % my)*mx+(j+1+mx % mx)] == 0) currNeighbours++;

          if (firstgen[ i+(j-1+my % my)] == 0) currNeighbours++;
          if (firstgen[ i+(j+1+my % my)] == 0) currNeighbours++;

          if (firstgen[ ((i+1+my) % my)*mx+(j-1+mx % mx)] == 0) currNeighbours++;
          if (firstgen[ ((i+1+my) % my)*mx+j] == 0) currNeighbours++;
          if (firstgen[ ((i+1+my) % my)*mx+(j+1+mx % mx)] == 0) currNeighbours++;

          neighb[i*mx + j] = currNeighbours;
          printf("%d  ", neighb[i*mx +j]);
        }
        printf("\n");
      }

      for (i = 0; i < my-1; i++) {    // change case
        for (j = 0; j < mx-1; j++) {
          if (firstgen[mx*i+j] == 0){ //living
            if ((neighb[mx*i+j] != 2)&&(neighb[mx*i+j] != 3)){
              firstgen[mx*i+j] = 16777215;
              //printf("kill  ");
            }
          } else if (firstgen[mx*i+j] == 16777215){ //dead
            if (neighb[mx*i+j] == 3){
              firstgen[mx*i+j] = 0;
              //printf("alive ");
            }
          }

        }
        //printf("\n");
      }

      char c = '1';

      printf("%s\n", strcat(outputFile, &c));

      saveBMP(outputFile, firstgen, mx, my);
      /*if (iter % dump_freq == 0) {
        c = c+1;
        saveBMP(outputFile+c, firstgen, mx, my);
      }*/
      printf("END\n" );
    }
  } else printf("ERROR\n" );







}
