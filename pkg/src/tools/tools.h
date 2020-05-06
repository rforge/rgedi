#pragma once

#ifdef _WIN32
	#define strncasecmp _strnicmp
	#define strcasecmp _stricmp
	#define fseeko _fseeki64
	typedef long int off_t;
#endif

#define TIDY(arr) if((arr)){free((arr));(arr)=NULL;}  /*free an array*/

/*Define macros for error handling*/
#define ISINTRETINT(x)   if((x==-1)) return((-1))
#define ISINTRETNULL(x)  if((x==-1)) return((NULL))
#define ISINTRETFLT(x) if((x==-1)) return((-FLT_MAX))
#define ISINTRETONE(x)   if((x==-1)) return((1))
#define ISNULLRETINT(x)  if((x==NULL)) return((-1))
#define ISNULLRETNULL(x) if((x==NULL)) return((NULL))
#define ISNULLRETONE(x)   if((x==NULL)) return((1))
#define NOT0RETNULL(x)   if((x==-1)) return((NULL))
#define NOT0RETINT(x)    if((x==-1)) return((-1))
#define ASSIGN_CHECKNULL_RETNULL(x,y) (x)=(y);if((x==NULL)) return(NULL)
#define ASSIGN_CHECKNULL_RETINT(x,y) (x)=(y);if((x==NULL)) return(-1)
#define ASSIGN_CHECKNULL_RETFLT(x,y) (x)=(y);if((x==NULL)) return(-FLT_MAX)
#define ASSIGN_CHECKNULL_RETONE(x,y) (x)=(y);if((x==NULL)) return(1)
#define ASSIGN_CHECKNULL_RETDBL(x,y) (x)=(y);if((x==NULL)) return(-DBL_MAX)
#define ASSIGN_CHECKINT_RETNULL(x,y) (x)=(y);if((x==-1)) return(NULL)
#define ASSIGN_CHECKINT_RETINT(x,y)  (x)=(y);if((x==-1)) return(-1)
#define ASSIGN_CHECKFLT_RETONE(x,y)  (x)=(y);if((x==-FLT_MAX)) return(1)
#define ASSIGN_CHECKFLT_RETNULL(x,y) (x)=(y);if((x==-FLT_MAX)) return(NULL)
#define ASSIGN_CHECKFLT_RETINT(x,y)  (x)=(y);if((x==-FLT_MAX)) return(-1)
#define ASSIGN_CHECKDBL_RETINT(x,y)  (x)=(y);if((x==-DBL_MAX)) return(-1)

double *dalloc(int,char *,int);
float *falloc(uint64_t,char *,int);
char *challoc(uint64_t,char *,int);
unsigned char *uchalloc(uint64_t,char *,int);
int *ialloc(int,char *,int);
short int *shalloc(int,char *,int);
int *intSwap(int *,uint64_t);
uint64_t *uint64Swap(uint64_t *,uint64_t);
float *floSwap(float *,uint64_t);
long int *lintSwap(long int *,uint64_t);
double *doSwap(double *,uint64_t);
double doOneSwap(double);
float floOneSwap(float);
uint32_t u32OneSwap(uint32_t);
int16_t *int16Swap(int16_t *,uint64_t);
double gaussian(double,double,double);
double logNormal(double,double,double);
char *markChar(int,char *,char);
unsigned char *markUchar(int,unsigned char *,unsigned char);
float singleMedian(float*, int);

unsigned char **uchChalloc(int,char *,int);
char **chChalloc(int,char *,int);
int **iIalloc(int,char *,int);
float **fFalloc(int,char *,int);
short int **shIalloc(int,char *,int);
double **dDalloc(int,char *,int);


int checkArguments(int,int,int,char *);
void TTIDY(void **,int); 


