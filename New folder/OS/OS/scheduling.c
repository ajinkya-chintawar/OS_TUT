#include<stdio.h>
//Definition of structure for process
struct process
{
	char name[20];
	int flag,arrival,burst,initburst,prio;
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
//Normal enqueue(used in FCFS and Round Robin)
void enqueue(struct queue *q,struct process d)
{
	if(empty(*q))
		q->r=q->f=0;
	else q->r=q->r+1;
	q->data[q->r]=d;
}
/*Enqueue for sjf scheduling. In this, we maintain a priority based queue
where priority is given to the shortest job, i.e, the job with min. burst time is
always at the front of the queue*/
void sjfenqueue(struct queue *q, struct process d)
{
	int x,y;
	if(empty(*q))
	{
		q->r=q->f=0;
		q->data[q->r]=d;
	}
	else
	{
		x=q->f;
		y=q->r;
		//Go through the queue to find position of new process d
		while(q->data[x].burst<=d.burst&&x<=y)
			x++;
		//Shift elements one place to the right to make space for d
		while(y>=x)
		{
			q->data[y+1]=q->data[y];
			y--;
		}
		q->data[x]=d;
		q->r=q->r+1;
	}
}
/*Enqueue for priority scheduling. Same as above except the priority is now
using process priority instead of burst time*/
void prioenqueue(struct queue *q, struct process d)
{
        int x,y;
        if(empty(*q))
        {
                q->r=q->f=0;
                q->data[q->r]=d;
        }
        else
        {
                x=q->f;
                y=q->r;
                //Go through the queue to find position of new process d
                while(q->data[x].prio<=d.prio&&x<=y)
                        x++;
                //Shift elements one place to the right to make space for d
                while(y>=x)
                {
                        q->data[y+1]=q->data[y];
                        y--;
					}
					q->data[x]=d;
					q->r=q->r+1;
		}
}
struct process dequeue(struct queue *q)
{
	struct process d;
	d=q->data[q->f];
	if(q->f==q->r)
		q->f=q->r=-1;
	else q->f=q->f+1;
	return(d);
}
void accept(struct process p[20],int n);
void fcfs(struct process p[20],int n);
void sjf(struct process p[20],int n);
void prio(struct process p[20],int n);
void sjfpre(struct process p[20],int n);
void priopre(struct process p[20],int n);
void rr(struct process p[20],int n);
void main()
{
	int ch,n,i;
	struct process p[20];
	printf("\nEnter number of processes: ");
	scanf("%d",&n);	
	accept(p,n);
	do
	{
	for(i=0;i<n;i++)
		p[i].flag=0;
	printf("\nMENU:\n1.FCFS\n2.SJF\n3.SJF-preemptive\n4.Priority\n5.Priority-preemptive\n6.Round Robin\n7.Re-enter processes\n8.Exit\n\n\tEnter your choice: ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: fcfs(p,n);
			break;
		case 2: sjf(p,n);
			break;
		case 3: sjfpre(p,n);
			break;
		case 4: prio(p,n);
			break;
		case 5: priopre(p,n);
			break;
		case 6: rr(p,n);
			break;		
		case 7: printf("\nEnter number of processes: ");
			scanf("%d",&n);
			accept(p,n);
			break;
		case 8: break;		
		default:printf("\nWrong choice entered\n");
			break;
	}
	}while(ch!=8);
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
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when i=1. The loop will run until completed processes(comp) equals no. of proceses*/
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				enqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
/*Decrement burst time to indicate completion of one burst */
		pc.burst--;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}

//Exactly the same as FCFS, except we use sjfenqueue function instead of enqueue function
void sjf(struct process p[20],int n)
{
	int i,j,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when 	i=1. The loop will run until completed processes(comp) equals no. of proceses
	*/
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				sjfenqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
/*Decrement burst time to indicate completion of one burst */
		pc.burst--;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}

//Exactly the same as sjf,but with preemption
void sjfpre(struct process p[20],int n)
{
	int i,j,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when 	i=1. The loop will run until completed processes(comp) equals no. of proceses
	*/
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				sjfenqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
//The following 'else if' gives the condition for pre-emption. If the process at the front of the queue has smaller burst time than the current process, then current process is enqueued and the new process is dequeued into pc
		else if(q.f!=-1 && pc.burst > q.data[q.f].burst)
		{
			printf("%s|",pc.name);
			pretime[cnt++]=i;
			sjfenqueue(&q,pc);
			pc=dequeue(&q);
		}
/*Decrement burst time to indicate completion of one burst */
		pc.burst--;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}


//Exactly the same as FCFS, except we use prioenqueue function instead of enqueue function
void prio(struct process p[20],int n)
{
	int i,j,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
	//Accept the priority for the processes
	for(i=0;i<n;i++)
	{	
		printf("\nEnter priority for process %d: ",i+1);
		scanf("%d",&p[i].prio);
	}	
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when 	i=1. The loop will run until completed processes(comp) equals no. of proceses
	*/
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				prioenqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
/*Decrement burst time to indicate completion of one burst */
		pc.burst--;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}

//Exactly the same as prio,but with preemption
void priopre(struct process p[20],int n)
{
	int i,j,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
	//Accept the priority for the processes
	for(i=0;i<n;i++)
	{	
		printf("\nEnter priority for process %d: ",i+1);
		scanf("%d",&p[i].prio);
	}	
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when 	i=1. The loop will run until completed processes(comp) equals no. of proceses
	*/
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				prioenqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
				flag1=1;
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
	//The following 'else if' gives the condition for pre-emption. If the process at the front of the queue has higher priority than the current process, then current process is enqueued and the new process is dequeued into pc
		else if(q.f!=-1 && pc.prio > q.data[q.f].prio)
		{
			printf("%s|",pc.name);
			pretime[cnt++]=i;
			prioenqueue(&q,pc);
			pc=dequeue(&q);
		}
/*Decrement burst time to indicate completion of one burst */
		pc.burst--;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}

//Procedure for Round Robin
void rr(struct process p[20],int n)
{
	int i,j,qt,tr=0,turnaround,waiting,pretime[30],cnt=0,flag1=0,comp=0;
	float avgta=0,avgwt=0;	
	struct queue q;
	init(&q);
	struct process pc;
	/* pc is the current process. Since initially, there is no process in
	pc, we set its flag to -1*/
	pc.flag=-1;
//Obtain quantum time for Round Robin
	printf("\nEnter quantum time: ");
	scanf("%d",&qt);
	printf("\nGANTT CHART\n\n\t|");
	/*In this loop, i signifies the moment in time. A process with arrival time 1 will be said to have arrived when i=1. The loop will run until completed processes(comp) equals no. of proceses*/
//Slight modification in the loop for RR. Since the same process will run for qt moments, we increment i by qt instead of by 1	
	for(i=0;comp<n;i++)
	{
/*In this loop, we find the processes that have arrived and place them in the queue. A process has arrived if its arrival time is less than the current moment (i)
flag is used to signify whether the process has been enqueued or not. If it has already been enqueued, it does not need to be enqueued again.
*/
		for(j=0;j<n;j++)
		{
			if(p[j].arrival<=i && p[j].flag==0)
			{
				p[j].flag=1;
				enqueue(&q,p[j]);
			}
		}
/*If pc.flag=-1, it means no process has arrived upto the current moment or all arrived processes have completed execution*/
		if(pc.flag==-1)
		{
/*flag1 is used to indicate a gap between process execution. Eg: if p1 finishes execution at 2 and p2 begins execution at 4, we will need to show a gap in the gantt chart*/
			if(empty(q) && flag1==0)
			{
				flag1=1;
				continue;
			}
			else if(empty(q) && flag1==1)
				continue;
			else if(!empty(q) && flag1==1)
			{
				printf("  |");
/*Variable pretime is used to keep track of the times that will be required when displaying the Gantt chart,such as process preemption or completion. Variable cnt is the count of these times */				
				pretime[cnt++]=i;
				flag1=0;
				pc=dequeue(&q);
			}
			else pc=dequeue(&q);
		}
/*If queue is not empty and the current process has already run for qt moments, then we replace the current process by the new process*/
		else if(!empty(q) && tr==qt)
		{
			pretime[cnt++]=i;
			printf("%s|",pc.name);
			enqueue(&q,pc);
			pc=dequeue(&q);
			tr=0;	//Reset time-run.
		}
//Decrement burst time
		pc.burst--;
//tr is time-run. It is required to keep track of whether a process has run for the given quantum time.
		tr++;
/* If burst time is zero, process is completed. So we calculate its turnaround time and waiting time, which will later be used to calculate the average TA and WT. We print the process name in Gantt Chart and put pc.flag=-1 to indicate that there is no current process */
		if(pc.burst==0)
		{
			turnaround=(i+1)-pc.arrival;
			waiting=turnaround-pc.initburst;
			avgta+=turnaround;
			avgwt+=waiting;
			pretime[cnt++]=i+1;
			comp++;
			printf("%s|",pc.name);
			pc.flag=-1;
			tr=0;	//Reset time-run
		}
	}
//Display the times below the Gantt Chart
	printf("\n\t0 ");
	for(i=0;i<cnt;i++)
	{	
		if(pretime[i]>9)
			printf("%d ",pretime[i]);
		else	printf (" %d ",pretime[i]);
	}
//Calculate avg. TA and WT
	avgta=avgta/n;
	avgwt=avgwt/n;
	printf("\n\nAvg. TA time: %.2f",avgta);
	printf("\n\nAvg. WT time: %.2f",avgwt);
}
