#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include<pthread.h>

typedef struct process_canal{
	int* flag;
	char* comand;
}canal_t;
int str_len(char* str){
	int i=0;
	while ((str[i]!='\0')&&(str[i]!='\n')){
		i++;
	}
	return i;
}
char* Directoryname(char* gitname){
	char* Dirname;
	int i=0,j;
	while(gitname[i]!='\0')
		i++;
	while(gitname[i-1]!='/')
		i--;
	Dirname=malloc(sizeof(char)*(str_len(&gitname[i])));
	for(j=0;j<str_len(&gitname[i]);j++){
		Dirname[j]=gitname[j+i];
	}
	return Dirname;
}
char* bash_comand(char flag,char* argname){
	char* comand;
	int i;
	switch (flag){
	case('g'):
		comand=malloc(sizeof(char)*(10+str_len(argname)));
		strcpy(comand,"git clone ");
		for(i=0;i<str_len(argname);i++){
			comand[10+i]=argname[i];
		}
		break;
	case('c'):
		comand=malloc(sizeof(char)*(4+str_len(argname)));
		strcpy(comand,"cd ");
		for(i=0;i<str_len(argname);i++){
			comand[3+i]=argname[i];
		}
		break;
	case('m'):
		comand=malloc(sizeof(char)*(18+str_len(argname)));
		strcpy(comand,"make -f ");
		for(i=0;i<str_len(argname);i++){
			comand[8+i]=argname[i];
		}
		comand=strncat(comand,"/Makefile",9);
		break;
	}
	printf("%s\n",comand);
	return comand;
}
void *load(void* arg){
	canal_t* canal=arg;
	system(canal->comand);
	*canal->flag=0;
}
int load_git(char* gitname){
	int i,cd=1;
	pthread_t load_worker;
	canal_t canal;
	canal.flag=&cd;
	canal.comand=bash_comand('g',gitname);
	pthread_create(&load_worker, NULL, load, &canal);
	sleep(7);
	pthread_cancel(load_worker);
	if(cd)
		return 1;
	else
		return 0;
	free(canal.comand);
}
void print_make_result(FILE* fp,char* gitname){
	int cd;
	char* Dirname;
	char* comand;
	cd=load_git(gitname);
	if (cd){
		fprintf(fp,"Git clone EROR\n");
		exit(-1);
	}
	Dirname=Directoryname(gitname);
	comand=bash_comand('m',Dirname);
	printf("%s\n",comand);
	cd=system(comand);
	free(Dirname);
	if (cd)
		fprintf(fp,"makefile -\n");
	else
		fprintf(fp,"makefile +\n");
	free(comand);
}
