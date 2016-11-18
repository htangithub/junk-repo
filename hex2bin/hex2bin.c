//
// This tool takes a text file containing hex values (representing a
// firmware application image) and converts it to a set of page-sized
// binary files
//

#include <stdio.h>

#define BL_CMD_DATA     1
#define PAGE_COUNT      20 //9
#define PAGE_SIZE       256

int main
(
  int   argc,
  char* argv[]
)
{
  FILE* pHexfile;
  FILE* pBinfile;
  int   iPage;
  int   iOffset;

  if (argc != 3)
  {
     printf("\nusage: %0 [hexfile] [binfile]\n", argv[0]);
     exit(1);
  }

  pHexfile = fopen(argv[1], "r");
  if (!pHexfile)
  {
     printf("\n%s open error\n", argv[1]);
     exit(1);
  }

  for (iPage = 0;
       iPage < PAGE_COUNT;
       iPage++)
  {
      char          sFile[256];
      unsigned char bByte;
      int           iResult;

      // create binfile name then open the file

      strcpy(sFile, argv[2]);
      sprintf(sFile+strlen(sFile), "%02X", iPage);

      pBinfile = fopen(sFile, "wb");
      if (!pBinfile)
      {
         printf("\n%s open error\n", sFile);
         exit(1);
      }

      printf("\nWriting %s...\n", sFile);

      // write bootloader command

      bByte = BL_CMD_DATA;
      iResult = fwrite(&bByte, sizeof(bByte), 1, pBinfile);
      if (iResult != 1)
      {
         printf("\n%s write error\n", sFile);
         exit(1);
      }

      // write page number of application data

      bByte = (unsigned char) iPage;
      iResult = fwrite(&bByte, sizeof(bByte), 1, pBinfile);
      if (iResult != 1)
      {
         printf("\n%s write error\n", sFile);
         exit(1);
      }

      // write application data

      for (iOffset = 0;
           iOffset < PAGE_SIZE;
           iOffset++)
      {
          unsigned int w;

          iResult = fscanf(pHexfile, "%x", &w);
          if (iResult != 1)
          {
             printf("\n%s read error\n", argv[1]);
             exit(1);
          }

          bByte = (unsigned char) w;
          iResult = fwrite(&bByte, sizeof(bByte), 1, pBinfile);
          if (iResult != 1)
          {
             printf("\n%s write error\n", sFile);
             exit(1);
          }
      }

      fclose(pBinfile);
  }

  fclose(pHexfile);
}
