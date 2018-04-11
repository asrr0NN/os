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
     i=rand() % 5; // this gives maximum 4 output range[0,4]
   return(i);
}

//complexity of allocate_pid=1(constant)

int allocate_pid(){
	
aa:	last++;
	//printf("\n\nlast %d",last);
	//printf("\nobj[last].status = %d",obj[last].status);
	//printf("\nobj[last].pid = %d",obj[last].pid);
	if(obj[last].status==0 && last<900){
	//	printf("\n in function obj[last].pid = %d",obj[last].pid);
		obj[last].status=1;
		printf("\nin obj[last].status = %d",obj[last].status);
		printf("\nin function obj[last].pid = %d\n",obj[last].pid);
		return obj[last].pid;
	}
	if(last==900){
		last=-1;
		goto aa;
	}
	else{
	//	printf("\n in else obj[last].status = %d\n",obj[last].status);
		return -1;
	}
	  
}

//complexity of release_pid=1(constant)

void release_pid(int pid){
	pid=pid-100;
	obj[pid].status=0;	//if we remove the it shows the pids not released correctly 
}

//complexity of allocate_map=o(n)

void allocate_map(){
	for(int i=0;i<(MAX_PID-MIN_PID);i++){
		obj[i].pid=i+100;
		obj[i].status=0;
	}
}

void *call(){
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
	
}
// complexity of manager=o(n)

void *manager(){
//	for(int j=0;j<10;j++){
		count=0;
		for(int i=0;i<(MAX_PID-MIN_PID);i++){
			if(obj[i].status==0){
				count=count+1;
			}
		}
//	printf("\ncount %d",count);
	
//	}
	pthread_exit((void*)count);
}


// o(n) overall complexity
int main(){
	pid_t pid;
	allocate_map();
	int *t=0; 
	int size;
	printf("Enter the number of threads created ");
	scanf("%d",&size);
	pthread_t tpid[10000];
	
	
	//printf("PARENT");
//	pthread_create(&tpid[0],NULL,manager,NULL);
//	pthread_join(tpid[0],(void **)&t);
//	printf("\nNUMBER OF THREADS VACENT %d",t);
		
	
		for(int i=0,c=3;i<=size;i++){
			if(c==3)
			{	pthread_create(&tpid[0],NULL,manager,NULL);
				pthread_join(tpid[0],(void **)&t);
				printf("\n\nNUMBER OF THREADS VACENT %d",t);
				c=0;
			}
			if(i!=0)
			{	
				pthread_create(&tpid[i],NULL,call,NULL);
				c=c+1;
			}
			pthread_join(tpid[i],NULL);
		}
	
		for(int i=1;i<=size;i++){
			pthread_join(tpid[i],NULL);
		}	
		
	return 0;
}
