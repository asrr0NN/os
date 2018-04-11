#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


struct A{
	int pid;
	int status;
}obj[900];

 static int last=-1;
#define MIN_PID 100
#define MAX_PID 1000
int count=0;

int ran1(){
   int i;
   time_t t;
   srand((unsigned) time(&t));
     i=rand() % 5;
   return(i);
}


int allocate_pid(){
	
	last++;
	printf("\nlast %d",last);
	printf("\nobj[last].status = %d",obj[last].status);
	printf("\nobj[last].pid = %d",obj[last].pid);
	if(obj[last].status==0){
	//	printf("\n in function obj[last].pid = %d",obj[last].pid);
		obj[last].status=1;
	//	printf("\nin obj[last].status = %d\n",obj[last].status);
	//	printf("\n in function obj[last].pid = %d\n",obj[last].pid);
		return obj[last].pid;
	}
	else{
		printf("\n in else obj[last].status = %d\n",obj[last].status);
		return -1;
	}
	  
}

void release_pid(int pid){
	pid=pid-100;
	obj[pid].status=0;	
}
void allocate_map(){
	for(int i=0;i<(MAX_PID-MIN_PID);i++){
		obj[i].pid=i+100;
		obj[i].status=0;
	}
}

void *call(){
	//pthread_mutex_lock(&lock);
	int tpid_cl=0;
	tpid_cl=allocate_pid();
	printf("\n tpid_cl = %d\n",tpid_cl);
	if(tpid_cl==-1){
		printf("Pid not initilized");
		return;
	}
	else{
		printf("tpid is %d",tpid_cl);
		sleep(ran1());
		release_pid(tpid_cl);
		pthread_exit(NULL);
	}
	//pthread_mutex_unlock(&lock);
		
}
 
void *manager(){
	count=0;
	int c;
	//printf("enter c");
	//scanf("%d",&c);
	
	for(int i=0;i<(MAX_PID-MIN_PID);i++){
		if(obj[i].status==0){
			count=count+1;
		}
	}
printf("manager");
	
	pthread_exit((void*)count);
}



int main(){
	
	allocate_map();
	int size;
	printf("Enter the number of threads created ");
	scanf("%d",&size);
	pthread_t tpid[1000];
	
	
		int *t; 
	pthread_create(&tpid[0],NULL,manager,NULL);
	pthread_join(tpid[0],(void **)&t);
	
	for(int i=1;i<=size;i++){
		pthread_create(&tpid[i],NULL,call,NULL);
		pthread_join(tpid[i],NULL);
	}
	
	for(int i=1;i<=size;i++){
		pthread_join(tpid[i],NULL);
	}
	//pthread_join(tpid[0],(void **)&t);
	printf("\nt%d",t);
	
	return 0;
}
