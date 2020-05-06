
/*############################################*/
/*# Some general functions for doing usefull #*/
/*# non-specific things.    20th April 2007  #*/
/*############################################*/

#include <functionWrappers.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <inttypes.h>
#include "tools.h"
#include "functionWrappers.h"


/*binary buffers*/    
typedef union{
  char buff[sizeof(int)];
  int x;
}intBuff; /*integers*/
typedef union{
  char buff[sizeof(float)];
  float x;
}floBuff; /*floats*/  
typedef union{
  char buff[sizeof(double)];
  double x;
}doBuff;  /*doubles*/    
typedef union{
  char buff[sizeof(long int)];
  long int x;
}lintBuff; /*long integers*/
typedef union{
  char buff[sizeof(int16_t)];
  int16_t x;
}int16Buff;  /*int16_t*/
typedef union{
  char buff[sizeof(uint32_t)];
  uint32_t x;
}u32Buff;    /*uint32_t*/


/*#########################################################################*/
/*check the number of command line arguments*/

int checkArguments(int numberOfArguments,int thisarg,int argc,char *option)
{
  int i=0;

  for(i=0;i<numberOfArguments;i++){
    if(thisarg+1+i>=argc){
      errorf("error in number of arguments for %s option: %d required\n",option,numberOfArguments);
      return(-1);
    }
  }

  return(0);
}/*checkArguments*/


/*#########################################################*/
/*return y for a normailised Gaussian given other parameters*/

double gaussian(double x,double sigma,double offset)
{
  double y=0;

  y=exp(-1.0*(x-offset)*(x-offset)/(2.0*sigma*sigma))/(sigma*sqrt(2.0*M_PI));

  return(y);
}/*gaussian*/

/*######################################################*/
/*return the gradient at x of a Gaussian*/

double gaussdiff(double x,double sigma,double offset)
{
  double dydx=0;   /*the differential of a gaussian*/

  dydx=-(x-offset)/(sigma*sigma)*exp(-1.0*(x-offset)*(x-offset)/(2.0*sigma*sigma))/(sigma*sqrt(2.0*M_PI));

  return(dydx);
}

/*######################################################*/
/*return the second differential at x of a Gaussian*/

double gaussecond(double x,double sigma,double offset)
{
  double d2y;  /*the second differential of a gaussian*/

  d2y=exp(-1.0*(x-offset)*(x-offset)/(2.0*sigma*sigma))/(sigma*sqrt(2.0*M_PI))/(sigma*sigma)*((x-offset)*(x-offset)/(sigma*sigma)-1.0);

  return(d2y);
}

/*#########################################################*/
/*return y for a lognormal*/

double logNormal(double x,double sigma,double offset)
{
  double y=0;
  double norm=1.0;

  x/=sigma;  /*modify x for computational efficiency*/
  x+=1.0;
  norm=x*x*x;

  y=(log(x-offset)/norm-0.002)/(1.31*sigma);
  if(y<0.0)y=0.0;

  return(y);
}/*logNormal*/

/*#########################################################*/
/*byte swap floats, if big endian*/

float *floSwap(float *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(float),i=0;
  floBuff *ibuff=NULL,*obuff=NULL;
  float *buff=NULL;   /*the pointer to pass back*/

  if(numb<1)return(buff);

  if(!(ibuff=(floBuff *)calloc(numb,sizeof(floBuff)))){
    errorf("error in float buffer allocation.\n");
    return(NULL);
  }
  if(!(obuff=(floBuff *)calloc(numb,sizeof(floBuff)))){
    errorf("error in float buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(float *)calloc(numb,sizeof(float)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    ibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      obuff[j].buff[i]=ibuff[j].buff[nBytes-1-i];
    }
    buff[j]=obuff[j].x;
  }
  TIDY(ibuff);
  TIDY(obuff);
  TIDY(bytes);
  return(buff);
}

/*##############################################################################*/
/*byte swap integers, if big endian*/

int *intSwap(int *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(int),i=0;
  intBuff *iibuff=NULL,*oibuff=NULL;
  int *buff=NULL;   /*the pointer to pass back*/

  if(!bytes){msgf("Something is wrong\n");return(NULL);}

  if(numb<1)return(buff);

  if(!(iibuff=(intBuff *)calloc(numb,sizeof(intBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(oibuff=(intBuff *)calloc(numb,sizeof(intBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(int *)calloc(numb,sizeof(int)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    iibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      oibuff[j].buff[i]=iibuff[j].buff[nBytes-1-i];
    }
    buff[j]=oibuff[j].x;
  }
  TIDY(iibuff);
  TIDY(oibuff);
  TIDY(bytes);
  return(buff);
}


/*##############################################################################*/
/*byte swap uint64_t, if big endian*/

uint64_t *uint64Swap(uint64_t *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(uint64_t),i=0;
  intBuff *iibuff=NULL,*oibuff=NULL;
  uint64_t *buff=NULL;   /*the pointer to pass back*/

  if(!bytes){msgf("Something is wrong\n");return(NULL);}

  if(numb<1)return(buff);

  if(!(iibuff=(intBuff *)calloc(numb,sizeof(intBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(oibuff=(intBuff *)calloc(numb,sizeof(intBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(uint64_t *)calloc(numb,sizeof(uint64_t)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    iibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      oibuff[j].buff[i]=iibuff[j].buff[nBytes-1-i];
    }
    buff[j]=oibuff[j].x;
  }
  TIDY(iibuff);
  TIDY(oibuff);
  TIDY(bytes);
  return(buff);
}


/*############################################################################*/
/*byte swap long integers*/

long int *lintSwap(long int *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(long int),i=0;
  lintBuff *iibuff=NULL,*oibuff=NULL;
  long int *buff=NULL;   /*the pointer to pass back*/

  if(numb<1)return(buff);

  if(!(iibuff=(lintBuff *)calloc(numb,sizeof(lintBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(oibuff=(lintBuff *)calloc(numb,sizeof(lintBuff)))){
    errorf("error in int buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(long int *)calloc(numb,sizeof(long int)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    iibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      oibuff[j].buff[i]=iibuff[j].buff[nBytes-1-i];
    }
    buff[j]=oibuff[j].x;
  }
  TIDY(iibuff);
  TIDY(oibuff);
  TIDY(bytes);
  return(buff);
}

/*##############################################################################*/
/*byte swap arrays of doubles*/

double *doSwap(double *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(double),i=0;
  doBuff *ibuff=NULL,*obuff=NULL;
  double *buff=NULL;   /*the pointer to pass back*/

  if(numb<1)return(buff);

  if(!(ibuff=(doBuff *)calloc(numb,sizeof(doBuff)))){
    errorf("error in double buffer allocation.\n");
    return(NULL);
  }
  if(!(obuff=(doBuff *)calloc(numb,sizeof(doBuff)))){
    errorf("error in double buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(double *)calloc(numb,sizeof(double)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    ibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      obuff[j].buff[i]=ibuff[j].buff[nBytes-1-i];
    }
    buff[j]=obuff[j].x;
  }
  TIDY(ibuff);
  TIDY(obuff);
  TIDY(bytes);

  return(buff);
}


/*##############################################################################*/
/*byte swap arrays of int16_t*/

int16_t *int16Swap(int16_t *bytes,uint64_t numb)
{
  uint64_t j=0;
  register int nBytes=sizeof(int16_t),i=0;
  int16Buff *ibuff=NULL,*obuff=NULL;
  int16_t *buff=NULL;   /*the pointer to pass back*/

  if(numb<1)return(buff);

  if(!(ibuff=(int16Buff *)calloc(numb,sizeof(int16Buff)))){
    errorf("error in double buffer allocation.\n");
    return(NULL);
  }
  if(!(obuff=(int16Buff *)calloc(numb,sizeof(int16Buff)))){
    errorf("error in double buffer allocation.\n");
    return(NULL);
  }
  if(!(buff=(int16_t *)calloc(numb,sizeof(int16_t)))){
    errorf("error in output buffer allocation.\n");
    return(NULL);
  }
  for(j=0;j<numb;j++){
    ibuff[j].x=bytes[j];
    for(i=0;i<nBytes;i++){
      obuff[j].buff[i]=ibuff[j].buff[nBytes-1-i];
    }
    buff[j]=obuff[j].x;
  }
  TIDY(ibuff);
  TIDY(obuff);
  TIDY(bytes);

  return(buff);
}/*int16Swap*/


/*############################################################################*/
/*Byte swap a single double*/

uint32_t u32OneSwap(uint32_t bytes)
{
  register int nBytes=sizeof(uint32_t),i=0;
  u32Buff ibuff,obuff;
  uint32_t buff;   /*the pointer to pass back*/

  ibuff.x=bytes;
  for(i=0;i<nBytes;i++){
    obuff.buff[i]=ibuff.buff[nBytes-1-i];
  }
  buff=obuff.x;
  return(buff);
}


/*############################################################################*/
/*Byte swap a single double*/

double doOneSwap(double bytes)
{
  register int nBytes=sizeof(double),i=0;
  doBuff ibuff,obuff;
  double buff;   /*the pointer to pass back*/

  ibuff.x=bytes;
  for(i=0;i<nBytes;i++){
    obuff.buff[i]=ibuff.buff[nBytes-1-i];
  }
  buff=obuff.x;
  return(buff);
}

/*############################################################################*/
/*Byte swap a single float*/

float floOneSwap(float bytes)
{
  register int nBytes=sizeof(float),i=0;
  floBuff ibuff,obuff;
  float buff;   /*the pointer to pass back*/

  ibuff.x=bytes;
  for(i=0;i<nBytes;i++){
    obuff.buff[i]=ibuff.buff[nBytes-1-i];
  }
  buff=obuff.x;
  return(buff);
}


/*######################################################################*/
/*To measure byte order and set swapping control*/
/*stolen from T Quaife's check_endian in 2006*/

char byteOrder()
{
  long l=1;
  void *vp=&l;       /*a pointer to the first byte of the long integer*/
  char c=*(char*)vp; /*an array of bytes made up of the long int*/
  char byteord=0;

  if(sizeof(char)!=1){msgf("Oh no, chars are not one byte.\n");return(-1);}
  if( c == 1 ) byteord=0;
  else if( c == 0 ) byteord=1;
  else {
    msgf("Errrr, this shouldn't happen\nproblem in byte order\n");
    return(-1);
  }
  return(byteord);

}/*byteOrder*/

/*##########################################################################*/
/*reverse an array of floats*/

float *reverseArr(float *arr,int length)
{
  int i=0;
  float *jimlad=NULL;

  if(!(jimlad=(float *)calloc(length,sizeof(float)))){
    errorf("error in array reverseing array\n");
    return(NULL);
  }
  for(i=0;i<length;i++)jimlad[i]=arr[length-(i+1)];

  TIDY(arr);

  return(jimlad);
}

/*#########################################################################*/
/*allocate a double arrays, checking for errors*/

double *dalloc(int length,char *namen,int n)
{
  double *jimlad=NULL;
  if(!(jimlad=(double *)calloc(length,sizeof(double)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d\n",length);
    return(NULL);
  }
  return(jimlad);
}/*dalloc*/

/*#########################################################################*/
/*allocate an int arrays, checking for errors*/

int *ialloc(int length,char *namen,int n)
{
  int *jimlad=NULL;
  if(!(jimlad=(int *)calloc(length,sizeof(int)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d\n",length);
    return(NULL);
  }
  return(jimlad);
}/*ialloc*/

/*#########################################################################*/
/*allocate a char arrays, checking for errors*/

char *challoc(uint64_t length,char *namen,int n)
{
  char *jimlad=NULL;
  if(!(jimlad=(char *)calloc(length,sizeof(char)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %" PRIu64 "\n",((uint64_t)length));
    return(NULL);
  }
  return(jimlad);
}/*challoc*/


/*#########################################################################*/
/*allocate an unsigned char arrays, checking for errors*/

unsigned char *uchalloc(uint64_t length,char *namen,int n)
{
  unsigned char *jimlad=NULL;
  if(!(jimlad=(unsigned char *)calloc(length,sizeof(unsigned char)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %" PRIu64 "\n",(uint64_t)length);
    return(NULL);
  }
  return(jimlad);
}/*uchalloc*/


/*########################################################################*/
/*allocate a float array, checking for errors*/

float *falloc(uint64_t length,char *namen,int n)
{
  float *jimlad=NULL;
  if(!(jimlad=(float *)calloc(length,sizeof(float)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %" PRIu64 "\n",length);
    return(NULL);
  }
  return(jimlad);
}/*falloc*/

/*########################################################################*/
/*allocate a short int array, checking for errors*/

short int *shalloc(int length,char *namen,int n)
{
  short int *jimlad=NULL;
  if(!(jimlad=(short int *)calloc(length,sizeof(short int)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d\n",length);
    return(NULL);
  }
  return(jimlad);
}/*shalloc*/

/*#########################################################################*/
/*allocate an array of int arrays, checking for errors*/

int **iIalloc(int length,char *namen,int n)
{
  int **jimlad=NULL;
  if(!(jimlad=(int **)calloc(length,sizeof(int *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d int pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*iIalloc*/

/*#########################################################################*/
/*allocate a pointer to a pointer to chars*/

char **chChalloc(int length,char *namen,int n)
{
  char **jimlad=NULL;
  if(!(jimlad=(char **)calloc(length,sizeof(char *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d char pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*chChalloc*/


/*#########################################################################*/
/*allocate a pointer to a pointer to unsigned chars*/

unsigned char **uchChalloc(int length,char *namen,int n)
{
  unsigned char **jimlad=NULL;
  if(!(jimlad=(unsigned char **)calloc(length,sizeof(unsigned char *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d char pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*chChalloc*/


/*########################################################################*/
/*allocate a pointer to an array of float pointers, checking for errors*/

float **fFalloc(int length,char *namen,int n)
{
  float **jimlad=NULL;
  if(!(jimlad=(float **)calloc(length,sizeof(float *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d float pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*fFalloc*/

/*########################################################################*/
/*allocate a pointer to an array of double pointers, checking for errors*/

double **dDalloc(int length,char *namen,int n)
{
  double **jimlad=NULL;
  if(!(jimlad=(double **)calloc(length,sizeof(double *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d float pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*dDalloc*/


/*#########################################################################*/
/*allocate an array of short int arrays, checking for errors*/

short int **shIalloc(int length,char *namen,int n)
{
  short int **jimlad=NULL;
  if(!(jimlad=(short int **)calloc(length,sizeof(short int *)))){
    errorf("error in %s array allocation %d\n",namen,n);
    errorf("allocating %d int pointers\n",length);
    return(NULL);
  }
  return(jimlad);
}/*iIalloc*/


/*###################################################################*/
/*add one integer to the end of an array of integers more efficiently*/

int *markInt(int length,int *jimlad,int new)
{
  if(length>0){
    if(!(jimlad=(int *)realloc(jimlad,(length+1)*sizeof(int)))){
      errorf("Error in int reallocation within markInt, allocating %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(int));
      return(NULL);
    }
  }else{ASSIGN_CHECKNULL_RETNULL(jimlad,ialloc(length+1,"int",0));}
  jimlad[length]=new;
  return(jimlad);
}/*markIntNew*/


/*###################################################################*/
/*add one integer to the end of an array of integers*/

int *markIntOld(int length,int *jimlad,int new)
{
  int i=0,*temparr=NULL;

  ASSIGN_CHECKNULL_RETNULL(temparr,ialloc(length+1,"integer transfer",length));
  for(i=0;i<length;i++)temparr[i]=jimlad[i];
  temparr[length]=new;
  TIDY(jimlad);

  return(temparr);
}/*markInt*/


/*###################################################################*/
/*add one integer to the end of an array of integers more efficiently*/

uint32_t *markUint32(int length,uint32_t *jimlad,uint32_t new)
{
  if(length>0){
    if(!(jimlad=(uint32_t *)realloc(jimlad,(length+1)*sizeof(uint32_t)))){
      errorf("Error in uint32 reallocation, allocaing %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(uint32_t));
      return(NULL);
    }
  }else{
    if(!(jimlad=(uint32_t *)calloc(length+1,sizeof(uint32_t)))){
      errorf("error tls allocation.\n");
      return(NULL);
    }
  }
  jimlad[length]=new;
  return(jimlad);
}/*markUint32*/


/*###################################################################*/
/*add one integer to the end of an array of integers more efficiently*/

float *markFloat(int length,float *jimlad,float new)
{
  if(length>0){
    if(!(jimlad=(float *)realloc(jimlad,(length+1)*sizeof(float)))){
      errorf("Error in float reallocation, %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(float));
      return(NULL);
    }
  }else{ASSIGN_CHECKNULL_RETNULL(jimlad,falloc((uint64_t)length+1,"int",0));}
  jimlad[length]=new;
  return(jimlad);
}/*markFloat*/


/*###################################################################*/
/*add one to the end of an array of floats*/

float *markFloatOld(int length,float *jimlad,float new)
{
  int i=0;
  float *temparr=NULL;

  ASSIGN_CHECKNULL_RETNULL(temparr,falloc((uint64_t)length+1,"integer transfer",length));
  for(i=0;i<length;i++)temparr[i]=jimlad[i];
  temparr[length]=new;
  TIDY(jimlad);

  return(temparr);
}/*markFloat*/


/*#############################################################*/

double *markDo(int length,double *jimlad,double new)
{
  if(length>0){
    if(!(jimlad=(double *)realloc(jimlad,(length+1)*sizeof(double)))){
      errorf("Error in double reallocation %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(double));
      return(NULL);
    }
  }else{ASSIGN_CHECKNULL_RETNULL(jimlad,dalloc(length+1,"int",0));}
  jimlad[length]=new;
  return(jimlad);
}/*markDo*/


/*#############################################################*/

char *markChar(int length,char *jimlad,char new)
{
  if(length>0){
    if(!(jimlad=(char*)realloc(jimlad,(length+1)*sizeof(char)))){
      errorf("Error in char reallocation %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(char));
      return(NULL);
    }
  }else{ASSIGN_CHECKNULL_RETNULL(jimlad,challoc((uint64_t)length+1,"int",0));}
  jimlad[length]=new;
  return(jimlad);
}/*markChar*/


/*#############################################################*/

unsigned char *markUchar(int length,unsigned char *jimlad,unsigned char new)
{
  if(length>0){
    if(!(jimlad=(unsigned char *)realloc(jimlad,(length+1)*sizeof(unsigned char)))){
      errorf("Error in uchar allocation, %" PRIu64 "\n",(uint64_t)(length+1)*sizeof(unsigned char));
      return(NULL);
    }
  }else{ASSIGN_CHECKNULL_RETNULL(jimlad,uchalloc((uint64_t)length+1,"int",0));}
  jimlad[length]=new;
  return(jimlad);
}/*markChar*/


/*##############################################################*/
/*delete one float from an array*/


float *deleteFloat(int length,float *jimlad,int point)
{
  int i=0,k=0;
  float *temparr=NULL;

  ASSIGN_CHECKNULL_RETNULL(temparr,falloc((uint64_t)length-1,"float deletion",point));
  for(i=0;i<length;i++){
    if(i!=point)temparr[k++]=jimlad[i];
  }
  TIDY(jimlad);

  return(temparr);
}/*deleteFloat*/

/*##############################################################*/
/*delete one int from an array*/

int *deleteInt(int length,int *jimlad,int point)
{
  int i=0,k=0;
  int *temparr=NULL;

  ASSIGN_CHECKNULL_RETNULL(temparr,ialloc(length-1,"int deletion",point));
  for(i=0;i<length;i++){
    if(i!=point)temparr[k++]=jimlad[i];
  }

  TIDY(jimlad);
  return(temparr);
}/*deleteInt*/


/*#############################################################*/
/* Modulus in the style of % for doubles*/

double decimalMod(double num,double denom)
{
  double x=0;

  x=num/denom;
  return((x-floor(x))*denom);
}/*decimalMod*/


/*#############################################################*/
/*tidy an array of arrays*/

void TTIDY(void **jimlad,int length)
{
  int i=0;

  if(jimlad){
    for(i=0;i<length;i++)TIDY(jimlad[i]);
    free(jimlad);
    jimlad=NULL;
  }
  return;
}/*TTIDY*/


/*#############################################################*/
/*find median point*/

float singleMedian(float *jimlad,int numb)
{
  float median=0;
  int compFloat(const void *x,const void *y);  /*function needed by qsort()*/

  qsort(jimlad,numb,sizeof(float),compFloat);  /*put the contents of temp in order*/
  if(numb>0){
    median=jimlad[(int)(numb/2)];
  }else{
    errorf("No data points for median?\n");
    return(-FLT_MAX);
  }

  return(median);
}/*singleMedian*/


/*#############################################################*/
/*A median filter for floats*/

float *medianFloat(float *jimlad,int width,int length)
{
  int i=0,j=0,place=0;
  int halfLength=0,nIn=0;
  float *filtered=NULL,*temp=NULL;
  int compFloat(const void *x,const void *y);  /*function needed by qsort()*/

  if(width<3){
    errorf("Median filter won't work with a width of %d for float\n",width);
    return(NULL);
  }

  ASSIGN_CHECKNULL_RETNULL(filtered,falloc((uint64_t)length,"median filter",0));
  ASSIGN_CHECKNULL_RETNULL(temp,falloc((uint64_t)width,"temporary median",0));

  halfLength=width/2;
  for(i=0;i<length;i++){
    nIn=0;
    for(j=0;j<width;j++){
      place=i+j-halfLength;
      if((place>0)&&(place<length)){
        temp[nIn++]=jimlad[place];
      }
    }/*median loop*/
    for(j=nIn;j<width;j++)temp[j]=9999.0;    /*pad end if needed so that they get put to the back during re-ordering*/
    qsort(temp,width,sizeof(float),compFloat);  /*put the contents of temp in order*/
    if(nIn>0){
      filtered[i]=temp[(int)(nIn/2)];
    }else{
      errorf("That didn't work, number in %d for bin %d of %d\n",nIn,i,length);
      return(NULL);
    }
  }  /*array loop*/

  TIDY(temp);
  return(filtered);
}/*medianFloat*/


/*#############################################################*/
/*A median filter for unsigned char*/

unsigned char *medianUchar(unsigned char *jimlad,int width,int length)
{
  int i=0,j=0,place=0;
  int halfLength=0,nIn=0;
  unsigned char *filtered=NULL,*temp=NULL;
  int compUchar(const void *x,const void *y);  /*function needed by qsort()*/

  if(width<3){
    errorf("Median filter won't work with a width of %d for uchar\n",width);
    return(NULL);
  }

  ASSIGN_CHECKNULL_RETNULL(filtered,uchalloc((uint64_t)length,"median filter",0));
  ASSIGN_CHECKNULL_RETNULL(temp,uchalloc((uint64_t)width,"temporary median",0));

  halfLength=width/2;
  for(i=0;i<length;i++){
    nIn=0;
    for(j=0;j<width;j++){
      place=i+j-halfLength;
      if((place>0)&&(place<length)){
        temp[nIn++]=jimlad[place];
      }
    }/*median loop*/
    for(j=nIn;j<width;j++)temp[j]=255;    /*pad end if needed so that they get put to the back during re-ordering*/
    qsort(temp,width,sizeof(unsigned char),compUchar);  /*put the contents of temp in order*/
    if(nIn>0){
      filtered[i]=temp[(int)(nIn/2)];
    }else{
      errorf("That didn't work, number in %d for bin %d of %d\n",nIn,i,length);
      return(NULL);
    }
  }  /*array loop*/

  TIDY(temp);
  return(filtered);
}/*medianUchar*/


/*#############################################################*/
/*A median filter for doubles*/

double *medianDouble(double *jimlad,int width,int length)
{
  int i=0,j=0,place=0;
  int halfLength=0,nIn=0;
  double *filtered=NULL,*temp=NULL;
  int comp(const void *x,const void *y);  /*function needed by qsort()*/

  if(width<3){
    errorf("Median filter won't work with a width of %d for double\n",width);
    return(NULL);
  }

  ASSIGN_CHECKNULL_RETNULL(filtered,dalloc(length,"median filter",0));
  ASSIGN_CHECKNULL_RETNULL(temp,dalloc(width,"temporary median",0));

  halfLength=width/2;
  for(i=0;i<length;i++){
    nIn=0;
    for(j=0;j<width;j++){
      place=i+j-halfLength;
      if((place>0)&&(place<length)){
        temp[nIn++]=jimlad[place];
      }
    }/*median loop*/
    for(j=nIn;j<width;j++)temp[j]=9999.0;    /*pad end if needed so that they get put to the back during re-ordering*/
    qsort(temp,width,sizeof(double),comp);  /*put the contents of temp in order*/
    if(nIn>0){
      filtered[i]=temp[(int)(nIn/2)];
    }else{
      errorf("That didn't work, number in %d for bin %d of %d\n",nIn,i,length);
      return(NULL);
    }
  }  /*array loop*/

  TIDY(temp);
  return(filtered);
}/*medianDouble*/


/*########################################################################*/
/*comparison function for qsort(), doubles*/

int comp(const void *x,const void *y)
{
  int returning=0;

  if((*(double *)x)<(*(double *)y))     returning=-1;
  else if((*(double *)x)>(*(double *)y))returning=1;
  else                                  returning=0;

  return(returning);
}/*comp*/


/*########################################################################*/
/*comparison function for qsort(), floats*/

int compFloat(const void *x,const void *y)
{
  int returning=0;

  if((*(float *)x)<(*(float *)y))     returning=-1;
  else if((*(float *)x)>(*(float *)y))returning=1;
  else                                returning=0;

  return(returning);
}/*compFloat*/


/*########################################################################*/
/*comparison function for qsort(), unsigned char*/

int compUchar(const void *x,const void *y)
{
  int returning=0;

  if((*(unsigned char *)x)<(*(unsigned char *)y))     returning=-1;
  else if((*(unsigned char *)x)>(*(unsigned char *)y))returning=1;
  else                                                returning=0;

  return(returning);
}/*compUchar*/


/*The end*/
/*################################################################################*/
