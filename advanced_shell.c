#include"header.h"
int main(int argc, char *argv[])
{
int x; int z;
char input[TOKEN];int i = 0;
while(1)
{printf("SHELL:");fflush(stdin);  fgets(input,TOKEN,stdin);x=strlen(input);
z=x-1;
input[z]='\0';
										for (  i = 0 ; input[i] != '\0' && (input[i] == ' '  || input[i] == '\t') ; i++ );
if ( input[i] == '\0' )
continue;
if ( feof(stdin) )exit(0);
int fd[2]= {-1,-1};
	int pd[2]= { -1,-1};
	pid_t pid1;
	int *inp;
	int *out;
	char subInput[25][TOKEN];

	char *tmp1 = input-1;
	y=0;

	while ( (tmp1 = strchr(tmp1+1,'\174')) != NULL)
		y++;

        out = fd;
	inp = pd;
	int j= 0;
	char *piper = strtok(input,"\174");
	int i = 0;

	char *arg[35];
	while( piper != NULL )
	{
		strcpy(subInput[i],piper);
		i++;
		piper = strtok(NULL,"\174");
	}


	for ( i = 0 ;  i < y+1 ; i++ )
	{


		char *args[100];
		char tmp[TOKEN];
		strcpy(tmp,subInput[i]);
		int k = 0;
		char *p;
		FILE *r = NULL;
		FILE *w = NULL;

		char *fileName = malloc(200);

		int stat = indirect(fileName,tmp,&r,i);

		if ( stat == -1)
			return;
		stat = outdirect(fileName,tmp,&w,i);
		if ( stat == -1)
			return;


		tmp1 = strchr(tmp,'\076');
		char * tmp2 = strchr(tmp,'\074');

		if ( tmp1)
			*tmp1='\0';
		if ( tmp2)
			*tmp2='\0';



		piper = strtok(tmp," ");

		while ( piper != NULL )
		{
			arg[k] = piper;
			k++;
			piper = strtok(NULL," ");
		}

		arg[k]=NULL;

		pipe(out);
		if ( fork() == 0 ) {



			if ( i != 0 )
				dup2(inp[0],0);
			if ( r != NULL  ) {
			  
				dup2(fileno(r),0);
				fclose(r);
			}

			if ( i != y ) {

				dup2(out[1],1);
				if ( w != NULL ){
					fprintf(stderr,"\nAMBIGUOUS ");
					return;
				}

			}
			else
			{
				if ( w != NULL )
					dup2(fileno(w),1);
			}


			cl(inp);
			cl(out);
			
			if ( execvp(*arg,arg) < 0 ) {
				fprintf(stderr,"\nCOMMAND NOT FOUND %s",*arg);
				exit(-1);
			}

		}
		cl(inp);
		pipe(inp);
		int *new = inp;
		inp = out;
		out = new;

		arg[j] = strtok(NULL,"\174");
		j++;

	}
	cl(fd);
	cl(pd);


	for ( i = 0 ; i < y+1; i++ ) {
		wait(NULL);
	}

}
}

