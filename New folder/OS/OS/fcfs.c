//FCFS-CPU Scheduling

#include<stdio.h>
//Definition of structure for process
struct process
{
	char name[3];
	int flag,arrival,burst,initburst,finishTime,turnAroundTime,waitingTime;
};

//Queue Definition along with queue functions
struct queue
{
	struct process data[20];
	int r,f;
};

void init(struct queue *q)
{
	q->r=q->f=-1;
}

int empty(struct queue q)
{
	if(q.r==-1)
		return(1);
	return(0);
}

void enqueue(struct queue *q,struct process d)
{
	if(empty(*q))
		q->r=q->f=0;
	else 
		q->r=q->r+1;
	q->data[q->r]=d;
}

struct process dequeue(struct queue *q)
{
	struct process d;
	d=q->data[q->f];
	if(q->f==q->r)
		q->f=q->r=-1;
	else 
		q->f=q->f+1;
	return(d);
}

void accept(struct process p[20],int n);
void fcfs(struct process p[20],int n);

void main()
{
	int ch,n,i;
	struct process p[20];
	printf("\nEnter number of processes: ");
	scanf("%d",&n);	
	accept(p,n);
	for(i=0;i<n;i++)
		p[i].flag=0;
	fcfs(p,n);	
}

void accept(struct process p[20],int n)
{
	int i;
	char s[2];	
	for(i=0;i<n;i++)
	{
		printf("\nProcess %d: ",i+1);
		//We use sprintf to give thee processes names like 'P1','P2',etc.
		sprintf(p[i].name,"P%d",i+1);
		printf("\nEnter arrival time: ");
		scanf("%d",&p[i].arrival);
		printf("\nEnter burst time: ");
		scanf("%d",&p[i].initburst);
		//initburst is the initial burst time, and 'burst' is current burst time
		p[i].burst=p[i].initburst;
	}
}

void fcfs(struct process p[20],int n)
{
	int i,j,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	
	pc.flag=-1;
	printf("\nGANTT CHART\n\n\t|");
	
	for(i=0;comp<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				enqueue(&q,p[j]);
			}
		}

		if(pc.flag==-1)
		{
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("   |");
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else 
				pc=dequeue(&q);
		}
		//printf("%d %d %d %s ",pc.burst,flag1,empty(q),pc.name);
		pc.burst--;

		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			
			pretime[cnt++]=i+1;
			comp++;
			printf("%s  |",pc.name);
			pc.flag=-1;
		}
	}
printf("--------------%d",cnt);
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{
		p[i].finishTime=pretime[i];
		p[i].turnAroundTime=p[i].finishTime-p[i].arrival;
		p[i].waitingTime=p[i].turnAroundTime-p[i].initburst;	
		if(pretime[i]>9)
			printf("  %2d ",pretime[i]);
		else	printf ("   %d ",pretime[i]);
	}
	
	printf("\n\nProcess\tAT\tBT\tFT\tTT\tWT\n");
	for(i=0;i<n;i++)
	{
		printf("P%d\t%d\t%d\t%d\t%d\t%d",i+1,p[i].arrival,p[i].initburst,p[i].finishTime,p[i].turnAroundTime,p[i].waitingTime);
		printf("\n");
	}

	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAverage Turnaround time: %.2f",avgta);
	printf("\n\nAverage Waiting time: %.2f\n",avgwt);
}

/*
Output:-
administrator@ubuntu:~/Desktop/OSPrograms$ gcc fcfs.c
administrator@ubuntu:~/Desktop/OSPrograms$ ./a.out

Enter number of processes: 5

Process 1: 
Enter arrival time: 0

Enter burst time: 8

Process 2: 
Enter arrival time: 1

Enter burst time: 1

Process 3: 
Enter arrival time: 2

Enter burst time: 3

Process 4: 
Enter arrival time: 3

Enter burst time: 2

Process 5: 
Enter arrival time: 4

Enter burst time: 6

GANTT CHART

	|P1  |P2  |P3  |P4  |P5  |
	0    8    9   12   14   20 

Process	AT	BT	FT	TT	WT
P1	0	8	8	8	0
P2	1	1	9	8	7
P3	2	3	12	10	7
P4	3	2	14	11	9
P5	4	6	20	16	10


Average Turnaround time: 10.60

Average Waiting time: 6.60

*/
