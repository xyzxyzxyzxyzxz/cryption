#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getcfromn (int inn,char* otch)
{
  int i=0,j=0,cl=0;
  char cht;
  while (inn/93!=0)
  {
    otch[i]=inn%93+34;
    inn=inn/93;
    i++;
  }
  otch[i]=inn+34;
  cl=i;

  while (i>j)
  {
    cht=otch[i];
    otch[i]=otch[j];
    otch[j]=cht;
    i--;
    j++;
  }

  cl++;
  while (cl<4)
  {
    otch[cl]=33;
    cl++;
  }

  return 0;
}

int encryption (FILE* fpin,int passwd,char* fot)
{
  int buf=0;
  char bufc[5]={"\0"};
  FILE* fpot;
  fpot=fopen(fot,"w");
  if (fpot==NULL)
  {
    printf("output file creation error");
    return 1;
  }
  fseek(fpin,0,SEEK_SET);

  while (!feof(fpin))
  {
    buf=0;
    fread(&buf,3,1,fpin);
//    if (feof(fpin))
//      break;
//    printf("%x\n",buf);
    buf=buf+passwd;
    getcfromn(buf,bufc);
    fprintf(fpot,"%s",bufc);
  }

  fclose(fpot);
  return 0;
}

int decryption (FILE* fpin,int passwd,char* fot)
{
  int i=0;
  char bufc;
  int buf=0;
  FILE* fpot;
  fpot=fopen(fot,"w");
  if (fpot==NULL)
  {
    printf("output file creation error");
    return 1;
  }
  fseek(fpin,0,SEEK_SET);

  while (!feof(fpin))
  {
    i=0;
    buf=0;
    while (i<4)
    {
      bufc=fgetc(fpin);
      if (bufc==EOF)
        break;
//      printf("%d ",bufc);
      if (bufc==33)
      {
        i++;
        continue;
      }
      buf=buf*93+bufc-34;
      i++;
    }
    if (buf!=0)
    {
      buf=buf-passwd;
//      printf("%x\n",buf);
      fwrite(&buf,3,1,fpot);
    }
  }
  fclose(fpot);
}

int main (int argc,char* argv[])
{
  int i;
  char otnm[100];
  FILE* fpin;
  if (!strcmp(argv[1],"-e"))
  {
    strcpy(otnm,"encryption_");
    strcat(otnm,argv[3]);
    fpin=fopen(argv[3],"r");
    if (fpin==NULL)
    {
      printf("open file error");
      return 2;
    }
    encryption(fpin,atoi(argv[2]),otnm);
    fclose(fpin);
  }

  if (!strcmp(argv[1],"-d"))
  {
    strcpy(otnm,"decryption_");
    strcat(otnm,argv[3]);
    fpin=fopen(argv[3],"r");
    if (fpin==NULL)
    {
      printf("open file error");
      return 2;
    }
    decryption(fpin,atoi(argv[2]),otnm);
    fclose(fpin);
  }
}
