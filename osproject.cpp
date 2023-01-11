#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#define LINE_MAX 1024

struct Process{
    int process_id, arrival_time, cpu_burst, reaming_time,
        waiting_time, turnaround_time, response_time, lastresponse_time;
};
struct Process process_queue[LINE_MAX];
struct Process CPU;
struct Process temp_process;
struct Node{
    struct Process process;
    struct Node *link;
}*head,*tail,*temp,*ptr,*min,*minLink;
struct node2  *readdata (void); 
struct node {
int process, arrival_time , burst_time, ct , waiting_time , turnaround_time ;
struct node *next;
};
struct node *start = NULL;
struct node2        
{
    int burstTime, arrivalTime, priority, pid;
    struct node2 *next;

};
struct node2 *header;


struct node2 *createNode(int bT,int aT,int pr,int pi){
	struct node2 * temp;
	temp=(struct node2 *) malloc (sizeof (struct node2));
	temp->burstTime=bT;
	temp->arrivalTime=aT;
	temp->priority=pr;
	temp->pid=pi;
	temp->next= NULL;
return temp;
	
}



struct node2 *insertBack(struct node2 *header, int b, int a, int p, int row)
{
    struct node2 *temp = createNode(b, a, p, row);
    struct node2 *datatemp;
    if (header == NULL)
    {
        header = temp;
        return header;
    }
    datatemp = header;
    while (datatemp->next != NULL)
        datatemp = datatemp->next;
    datatemp->next = temp;
    return header;
}


void MinProcess();
void queue(struct Process p);
void loadAvailableJobs(int var);
int n,t=0;
double sum=0,sum2=0;
double avg_time;

int preemptive=0;
int numberOfNodes(struct node2 *header);

// sort functions
void swapingNodes(struct node2 *z,struct node2 *y);
void sortJobs(struct node2 *header); 
void sortPriority(struct node2 *header);

char *input,*output,argument;

// Scheduling Function Declarations:
int FCFS(); // First come, First Serve.
int SJF(); // Shortest job first.
void sjnp(void); // Shortest job, Non-preemtive.

void simulationMenu(void);
void schedulingMethod(void);


int main(int argc,char **argv)
{
    

 readdata();	
 simulationMenu();

return 0;
}

struct node2 *readdata(){
	
	FILE *myFile;
char line[LINE_MAX];
 int num[3];
 int pid=0;

if ((myFile = fopen(input, "r")) == NULL){
printf("\n error opening the input file \n");
        return 0;}
while (fgets(line, LINE_MAX, myFile) != NULL) {
	++pid;
        sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
     
       header= insertBack(header,num[0],num[1],num[2],pid);
      
       
}

fclose(myFile);

    return header;


}


void sortJobs(struct node2 *header){
	
	 struct node2 *tempdata = header;
   
       
        while (tempdata->next != NULL)
        {
            if (tempdata->burstTime > tempdata->next->burstTime)
            {
                swapingNodes(tempdata, tempdata->next);
                
            }
           tempdata = tempdata->next;
        }
        header = tempdata;    
  
}

int numberOfNodes(struct node2 *header){
	int count=0;
	struct node2 *temp=header;
	while(temp!=NULL){
		count++;
		temp=temp->next;
	}
	return count;
}

void sortPriority(struct node2 *header){
	
	 struct node2 *tempdata = header;
   
       
        while (tempdata->next != NULL)
        {
            if (tempdata->priority > tempdata->next->priority)
            {
                swapingNodes
				(tempdata, tempdata->next);
                
            }
           tempdata = tempdata->next;
        }
        header = tempdata;    
  
}

void simulationMenu(){
	int option;
	printf("\t\t CPU Scheduler Simulator \n");
	printf("\n 1) Scheduling method");
	printf("\n 2) Preemptive Moode");
	printf("\n 3) Non-preemptive mode");
	printf("\n 4) Show Result");
	printf("\n 5) End Program");
   	printf("\n Option >:");

	scanf("%d", &option);
	switch(option){
		case 1:
			schedulingMethod();
			break;
		case 2:
			printf("This section was not completed. ");
			simulationMenu();
		case 3:
			printf("This section was not completed. ");
			simulationMenu();
		case 4:
			printf("This section was not completed. ");
			simulationMenu();
		case 5:
			printf("\n\n \t\t Press any key to terminate the program....");
			exit (1);
		default:
			printf("Please select an option between 1 and 5\n");
			simulationMenu();
		}
}
void schedulingMethod(void){

	int option;
		printf("\n \t\t\t\t  Scheduling Simulator\n");
	printf("\n 1) First Come, First-Served Scheduling");
   	printf("\n 2) Shortest-Job-first Scheduling");
   	printf("\n 3) Shortest-Job (Non-Preemptive)");
	printf("\n 4) Round-Robin Scheduling");
	printf("\n 5) Go back to main menu");
	printf("\n 6) End Program");
    printf("\n Option >");

	scanf("%d",&option);

	switch(option){
		case 1:
			FCFS();
			break;
		case 2:
			SJF();
			break;
		case 3:
			sjnp();
			break;
		case 4:
			printf("This section was not completed");
			simulationMenu();
		case 5:
			simulationMenu();
		case 6:
			printf("\n\n \t\t Press any key to terminate the program....");
			exit (1);
		default:
			printf("Please select an option between 1 and 5\n");
			simulationMenu();
			
			
	}	

}
	void swapingNodes(struct node2 *x, struct node2 *y){
	

	int temp_burstTime = x->burstTime;
    x->burstTime = y->burstTime;
    y->burstTime = temp_burstTime;

    int temp_arrivalTime = x->arrivalTime;
    x->arrivalTime = y->arrivalTime;
    y->arrivalTime = temp_arrivalTime;

    int temp_priority = x->priority;
    x->priority = y->priority;
    y->priority = temp_priority;

    int temp_pid = x->pid;
    x->pid = y->pid;
    y->pid = temp_pid;
}
int SJF(){

int i,j;
    int loop_time;


FILE *myFile;
char line[LINE_MAX];
unsigned int num[3];

if ((myFile = fopen(input, "r")) == NULL)
        return 0;


while (fgets(line, LINE_MAX, myFile) != NULL) {
        sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
        process_queue[i].arrival_time = num[1];
        process_queue[i].cpu_burst = num[0];
        process_queue[i].process_id=i+1;
        process_queue[i].reaming_time=process_queue[i].cpu_burst;
        t=t+process_queue[i].cpu_burst;
        i++;

    }
    n=i;
    fclose(myFile);
    for(j=0;j<t;j++){
        loadAvailableJobs(j);
        if(CPU.reaming_time==0){
            MinProcess();
            if(min==NULL){
                printf("|WAITING|");
            }else{
                CPU=min->process;
                CPU.lastresponse_time=j;
                if(CPU.cpu_burst==CPU.reaming_time){
                CPU.response_time=j;
                }
                if(min==head && min==tail){
                    head=NULL;
                    tail=NULL;
                    free(min);
                }else if(min==head && min!=tail){
                    head=min->link;
                    free(min);
                }else if(min==tail && min!=head){
                    minLink=head;
                    ptr=head;
                    while(ptr->link!=NULL){
                        minLink=ptr;
                        ptr=ptr->link;
                    }
                    tail=minLink;
                    minLink->link=NULL;
                    free(min);
                    minLink=NULL;
                }else if(min!=head && min!=tail){
                    minLink=head;
                    ptr=head;
                    while(ptr->link!=min){
                        minLink=ptr;
                        ptr=ptr->link;
                    }
                    minLink->link=min->link;
                    free(min);
                    minLink=NULL;
                }
                CPU.reaming_time--;


            }
        }else if(CPU.reaming_time>0){
            MinProcess();
            if(min!=NULL && min->process.reaming_time < CPU.reaming_time){
                    if(min==head && min==tail){
                        temp_process=CPU;
                        head=NULL;
                        tail=NULL;
                        CPU=min->process;
                        CPU.lastresponse_time=j;
                         if(CPU.cpu_burst==CPU.reaming_time){
                          CPU.response_time=j;
                           }
                        CPU.reaming_time--;

                        free(min);
                        queue(temp_process);
                    }else if(min==head && min!=tail){
                        temp_process=CPU;
                        head=min->link;
                        CPU=min->process;
                        CPU.lastresponse_time=j;
                           if(CPU.response_time==0){
                            CPU.response_time=j;
                             }
                        CPU.reaming_time--;

                        free(min);
                        queue(temp_process);
                    }else if(min!=head && min==tail){
                        minLink=head;
                        ptr=head;
                        while(ptr->link!=NULL){
                            minLink=ptr;
                            ptr=ptr->link;
                        }
                        temp_process=CPU;
                        CPU=min->process;
                        CPU.lastresponse_time=j;
                        if(CPU.cpu_burst==CPU.reaming_time){
                         CPU.response_time=j;
                         }
                        tail=minLink;
                        minLink->link=NULL;
                        CPU.reaming_time--;

                        free(min);
                        queue(temp_process);
                    }else{
                        minLink=head;
                        ptr=head;
                        while(ptr->link!=min){
                            minLink=ptr;
                            ptr=ptr->link;
                        }
                        temp_process=CPU;
                        CPU=min->process;
                        CPU.lastresponse_time=j;
                        if(CPU.cpu_burst==CPU.reaming_time){
                          CPU.response_time=j;
                          }
                        minLink->link=min->link;
                        CPU.reaming_time--;

                        free(min);
                        queue(temp_process);
                    }

            }else{
                CPU.reaming_time--;

            }

        }
        if(CPU.reaming_time==0){
            process_queue[CPU.process_id-1].turnaround_time=j-process_queue[CPU.process_id-1].arrival_time+1;
            process_queue[CPU.process_id-1].waiting_time=process_queue[CPU.process_id-1].turnaround_time-process_queue[CPU.process_id-1].cpu_burst;
            process_queue[CPU.process_id-1].response_time=CPU.response_time;
            process_queue[CPU.process_id-1].lastresponse_time=CPU.lastresponse_time;
        }

    }
    FILE * fp2;


   fp2 = fopen ("output.txt","w");
   printf ("Scheduling Method: Shortest-Job First (Preemitive)\n");
 printf ("Process Waiting Times:\n");
   fprintf (fp2, "Scheduling Method: Shortest-Job First (Preemitive)\n");
 fprintf (fp2, "Process Waiting Times:\n");

    for(i=0;i<n;i++){
        fprintf(fp2, "P%d:\t%d ms\n",process_queue[i].process_id,process_queue[i].waiting_time);
        printf("P%d:\t%d ms\n",process_queue[i].process_id,process_queue[i].waiting_time);
        sum=sum+process_queue[i].waiting_time;
        sum2=sum2+process_queue[i].turnaround_time;
    }
    avg_time=sum/n;
    

    fprintf(fp2, "Average waiting time: %lf\n",avg_time);
    printf( "Average waiting time: %lf\n",avg_time);
    fclose (fp2);
    printf("Simulation complete. Output printed in output1.txt\n");
    simulationMenu();
    return 0;
}





void queue(struct Process p){

    if(tail==NULL){
        temp=(struct Node *)malloc(1*sizeof(struct Node));
        temp->link=NULL;
        temp->process=p;
        head=temp;
        tail=head;
    }else{
        temp = (struct Node *)malloc(1*sizeof(struct Node));
        tail->link=temp;
        temp->process=p;
        temp->link=NULL;
        tail=temp;
    }
}

void MinProcess()
{
    ptr=head;

    if(ptr==NULL){
        min=NULL;
        return;
    }
      min = head;
    for (ptr=ptr->link;ptr!=NULL;ptr=ptr->link)
    {
        if(ptr->process.reaming_time < min->process.reaming_time){
            min=ptr;
        }else if(ptr->process.reaming_time==min->process.reaming_time){
            if(ptr->process.process_id < min->process.process_id){
                min=ptr;
            }
        }else {

        }
    }

}

void loadAvailableJobs(int var){
    int i;
    for(i=0;i<n;i++){
        if(process_queue[i].arrival_time==var){
            queue(process_queue[i]);
        }
    }


}
int FCFS(){

int i ,j , temp , c;
float avg_waiting_time = 0.0;
struct node *ptr , *newnode , *preptr ;
int x = 0;

FILE *myFile;
char line[LINE_MAX];
unsigned int num[3];

if ((myFile = fopen("input.txt", "r")) == NULL)
        return 0;

        
while (fgets(line, LINE_MAX, myFile) != NULL) {
        sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
       	newnode = (struct node*) malloc(sizeof(struct node));
		newnode->arrival_time = num[1];
		newnode->burst_time = num[0];
		newnode->next = NULL;

if(start == NULL){

start = newnode;

ptr = start;

}

else {

ptr->next = newnode;

ptr = ptr->next;

}
x++;
 		
}
fclose(myFile);


ptr = start;

i = 1;

while(ptr!=NULL){

ptr->process = i ;

ptr = ptr->next;

i++;

}

ptr = start;


while(ptr->next!=NULL){

preptr = ptr->next;

while(preptr!=NULL){

if (ptr->arrival_time > preptr->arrival_time){

temp = ptr->arrival_time;

ptr->arrival_time = preptr->arrival_time;

preptr->arrival_time = temp;

temp = ptr->burst_time;

ptr->burst_time = preptr->burst_time;

preptr->burst_time = temp;

temp = ptr->process;

ptr->process = preptr->process;

preptr->process= temp;

}

preptr = preptr ->next;

}

ptr = ptr->next;

}

ptr = start;





ptr = start;

c = ptr->arrival_time ;

while(ptr!=NULL){

ptr->ct = c + ptr->burst_time;

c = ptr->ct;

ptr->turnaround_time = ptr->ct - ptr->arrival_time;

ptr->waiting_time = ptr->turnaround_time - ptr->burst_time;

ptr = ptr->next;

}


ptr = start;

while(ptr != NULL){



avg_waiting_time = avg_waiting_time + ptr->waiting_time;

ptr = ptr->next;

}

FILE * fp2;
   
  
   fp2 = fopen ("input.txt ","r");
 printf("Scheduling Method: first come First serve (Non-Preemitive)\n");
	printf ("Process Waiting Times:\n");
   
   for(i=1;i<=x;i++){

ptr = start;

while(ptr!=NULL){

if(ptr->process == i)
 {
 	printf("P%d:\t%d ms\n",ptr->process,ptr->waiting_time);
 	fprintf(fp2, "P%d:\t%d ms\n",ptr->process,ptr->waiting_time);
 }


ptr = ptr->next;


}

}
	   printf ("Averge Waiting time %f",avg_waiting_time/x);
       fprintf (fp2, "Averge Waiting time %f",avg_waiting_time/x); 
          fclose (fp2);
   
   
   printf("Simulation complete. Output printed in output1.txt\n");

   simulationMenu();
}
void sjnp(void){
	FILE *fp2;
    fp2=fopen(output,"w");
	printf("Scheduling Method: Shortest-Job First (Non-Preemitive)\n");
	printf ("Process Waiting Times:");
   	fprintf(fp2,"Scheduling Method: Shortest-Job First (Non-Preemitive):\n");

	struct node2 *temp=header;
	struct node2 *temp2=temp;
    int count=numberOfNodes(temp);
    int k=0,i=0, j=0,burst[count],arrival[count],pid[count], waiting=0,tempburst=0,totalWaiting=0;
    
    while(temp!=NULL){
    sortJobs(temp2);
    temp=temp->next; 
		}
		
		temp=temp2;
    for(k;k<count;k++){
    burst[k]=temp->burstTime;
	arrival[k]=temp->arrivalTime;
	pid[k]=temp->pid;
	temp=temp->next;
    		}
    		
for(i;i<count;i++){
for(j=0;j<count;j++){
	if(waiting-arrival[j] >= 0 && burst[j] != 0){
		waiting=waiting-arrival[j];
		totalWaiting=totalWaiting+waiting;
		
		printf("\n p%d = %d ms.",pid[j],waiting);
		fprintf(fp2,"\n p%d = %d ms.",pid[j],waiting);

		waiting=waiting+burst[j]+arrival[j];
		burst[j]=0;
	}
}	
 }				
double averagewaiting=totalWaiting/(float)count;
 printf("\n Average Waiting Time: %0.2f  ms.",averagewaiting);
 fprintf(fp2,"\n Average Waiting Time: %0.2f  ms.",averagewaiting);
 fclose(fp2);
 
 simulationMenu();
       }

