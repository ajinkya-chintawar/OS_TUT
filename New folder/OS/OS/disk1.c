#include<stdio.h>
void fcfs(void) ;
void cscan(void);
void display(void);
int queue[10][2],track[10][2];
int i,avg_seek,task,hand,ptr,seek=0;

void main()
{
	printf("Enter The no. of tasks per cylinder :");
	scanf("%d",&task);
	printf("Enter the current head position: ");
	scanf("%d",&hand);
	for(i=0;i<task;i++)
	{
		printf("Enter the track no. %d: ",(i+1));
		scanf("%d",&track[i][0]);
	}
	//fcfs();
	cscan();
}

void fcfs()
{
	for(i=0;i<task;i++)
		queue[i][0]=track[i][0];
	ptr=hand;
	for(i=0;i<task;i++)
	{
		if(ptr>queue[i][0])
			queue[i][1]=ptr-queue[i][0];
		else if(ptr<queue[i][0])
			queue[i][1]=queue[i][0]-ptr;
		else if(ptr==queue[i][0])
			queue[i][1]=0;
		ptr=queue[i][0];
		seek=seek+queue[i][1];
	}
	avg_seek=seek/(task);
	printf("\nFCFS ALGORITHM\n");
	display();
}

void cscan()
{
	int temp[10][3],j=0,tmp;
	seek=0;
	for(i=0;i<task;i++)
	{
		queue[i][0]=track[i][0];
		temp[i][0]=track[i][0];
		temp[i][2]=-1;
	}
	ptr=hand;
	for(i=0;i<task;i++)
		for(j=1;j<task;j++)
		{
			if(temp[j-1][0]> temp[j][0])
	  		{
	     		tmp=temp[j-1][0];
	     		temp[j-1][0]=temp[j][0];
	     		temp[j][0]=tmp;
	  		}
		}

	for(i=0;i<task;i++)
		printf("\n%d",temp[i][0]);
	for(i=0;i<task;i++)
	{
		if(temp[i][0]>ptr)
		{
			printf("\n%d\t%d\n",temp[i][0],ptr);
			for(j=i;j<task;j++)
			{
				if(ptr<temp[j][0])
				{
					temp[j][1]=temp[j][0]-ptr;
					temp[j][2]=0;
				}
				else if(ptr==temp[j][0])
				{
					temp[j][1]=0;
					temp[j][2]=0;
				}
				ptr=temp[j][0];
				printf("\n%d",ptr);
			}
			printf("\n%d",ptr);
			temp[0][1]=ptr-temp[0][0];
			printf("\t%d\t%d\t%d",ptr,temp[0][0],temp[0][1]);
			ptr=temp[0][0];
			temp[j][2]=0;
			break;
		}
	}
	for(j=1;j<i;j++)
		if(temp[j][2]==-1)
		{
			temp[j][1]=temp[j][0]-ptr;
			temp[j][2]=0;
			ptr=temp[j][0];
		}

	for(i=0;i<task;i++)
		for(j=0;j<task;j++)
			if(queue[i][0]==temp[j][0])
			{
				queue[i][1]=temp[j][1];
	 			seek=seek+queue[i][1];
			}
	avg_seek=seek/(task);
	printf("\nC-SCAN ALGORITHM\n");
	display();
}

void display()
{
	printf("Track Visited\tNo.of tracks traversed\n");
	printf("_______________________________________\n");
	for(i=0;i<task;i++)
		printf("%d\t\t%d\n",queue[i][0],queue[i][1]);
	printf("_______________________________________\n");
	printf("Total Seek Length=%d\n",seek);
	printf("Average Seek Length=%d\n",avg_seek);
}
