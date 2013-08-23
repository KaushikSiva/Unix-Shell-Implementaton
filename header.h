#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX_ARG 256
#define TOKEN 512

int y=1;

void cl(int *p)
{
	if ( p[0] != -1 ) {
		close(p[0]);
		p[0] = -1;
	}

	if ( p[1] != -1 ) {
		close(p[1]);
		p[1] = -1;
	}

}
int indirect(char *fileName,char * tmp, FILE **fp,int yn)
{
char *point;
if ( (point = strchr(tmp,'\074')) != NULL ) {
point++;
if ( yn != 0 ) {
fprintf(stderr, "\nINVALID INPUT");
return -1;
}
int l=0;
for ( l = 0 ; point[l] == ' ' && point[l] != '\0' ; l++ )
{
if ( point[l] == '\074' || point[l] == '\076' ) {
fprintf(stderr, "\nInvalid input");
return -1;
}
}
if ( point[l] == '\0' ) {
fprintf(stderr, "\nInvalid input");
return -1;
}
int vb=0;
for (  ; point[l] != '\0' && point[l] != ' ' && point[l] !='\074' && point[l] != '\076'; l++ )
{
fileName[vb] = point[l];	vb++;
}
fileName[vb]='\0';
*fp = fopen(fileName,"r");
return 1;
}else
return 0;
}

int outdirect(char * fileName, char *inp, FILE**fp, int yn)
{
char *point;
char a[5] = "w";
if ( (point = strchr(inp,'\076')) != NULL ) {
if ( point[1] == '\076')
{
strcpy(a,"a");
point++;
}
if ( yn != y ) {
fprintf(stderr, "\nInvalid input");
return -1;
}
int l=0;
for ( l =1 ; point[l] == ' ' && point[l] != '\0' ; l++ )
{
if ( point[l] == '\074' || point[l] == '\076' ) {
fprintf(stderr, "\nInvalid input");
return -1;
}
}
if ( point[l] == '\0' ) {
fprintf(stderr, "\nInvalid input");
return -1;}

int m=0;
for (  ; point[l] != '\0' && point[l] != ' ' && point[l] !='\074' && point[l] != '\76'; l++ )
{
fileName[m] = point[l];m++;
		}

fileName[m]='\0';
*fp = fopen(fileName,a);
return 1;
}else
return 0;
}

