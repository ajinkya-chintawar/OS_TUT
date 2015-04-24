
#include<stdio.h>

void FCFS();
void nonSJF();
void preSJF();
void nonPrio();
void prePrio();
void RR();
void main()
{
    int choice;
    do
    {
        printf("\nEnter your choice\n");
        printf("1.FCFS\n2.SJF(non-premptive)\n3.SJF(premptive)\n4.Priority(non-premptive)\n");
        printf("5.Priority(pre-emptive)\n6.Round Robin\n7.Quit\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            FCFS();
            break;
        case 2:
            nonSJF();
            break;
        case 3:
            preSJF();
            break;
        case 4:
            nonPrio();
            break;
        case 5:
            prePrio();
            break;
        case 6:
            RR();
            break;
        }
    }
    while(choice!=7);
}
void FCFS()
{
    int i,pro,arr[11],bur[11],fin[11];
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&bur[i]);
    fin[0]=arr[0]+bur[0];
    printf("Finish time is %d",fin[0]);
    for(i=1; i<pro; i++)
    {
        fin[i]=fin[i-1]+bur[i]; //calculating finish time of each process
        printf("Finish time is %d",fin[i]);
        printf("\nP.Id\tArival\tBurst\tFinish\tTurn\tWaiting\n");
    }
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],bur[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-bur[i]);
}
void nonSJF()
{
    int i,k,flag,min=999,pro,arr[11],bur[11],fin[11],status[11]= {0},T=0;
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&bur[i]);
    while(1)
    {
        for(i=0; i<pro; i++)
        {
            if(arr[i]<=T&&(status[i]!=-1||status[i]==0))
            {
                status[i]=1;
            }
        }
        min=999;
        for(i=0; i<pro; i++)
        {
            if(status[i]==1&&bur[i]<min)
            {
                min=bur[i];
                k=i;
            }
        }
        fin[k]=T+bur[k];
        status[k]=-1;
        T+=bur[k];
        flag=0;
        for(i=0; i<pro; i++)
            if(status[i]==-1)
                flag=1;
            else
            {
                flag=0;
                break;
            }
        if(flag==1)
            break;
    }
    printf("\nP.Id\tArival\tBurst\tFinish\tTurn\tWaiting\n");
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],bur[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-bur[i]);
}
void preSJF()
{
    int tp,min=999;
    int i,k,swp,j=-1,l,flag,s,t,pro,arr[11],bur[11],que[11],temp[11],fin[11],status[11]= {0},T=0;
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
    {
        scanf("%d",&bur[i]);
        temp[i]=bur[i];
    }
    printf("Enter the time slab\n");
    scanf("%d",&t);
    for(i=0; i<pro; i++)
    {
        if(arr[i]==T)
        {
            j++;
            status[i]=1;
            que[j]=i;
        }
    }
    for(l=0; l<pro; l++)
    {
        if(bur[l]<min&&status[l]==1)
        {
            min=bur[que[l]];
            k=que[l];
        }
    }
    while(1)
    {
        if(bur[que[k]]>t)
        {
            for(tp=0; tp<t; tp++)
            {
                bur[que[k]]--;
                T++;
                for(l=0; l<pro; l++)
                {
                    if(arr[l]==T&&status[l]==0)
                    {
                        j++;
                        que[j]=l;
                        status[l]=1;
                    }
                }
            }
        }
        else
        {
            while(bur[que[k]]!=0)
            {
                bur[que[k]]--;
                T++;
                for(l=0; l<pro; l++)
                    if(arr[l]==T&&status[l]==0)
                    {
                        j++;
                        que[j]=l;
                        status[l]=1;
                    }
            }
            fin[que[k]]=T;
            status[que[k]]=-1;
        }
        min=999;
        for(l=0; l<=j; l++)
        {
            if(bur[que[l]]<min&&status[que[l]]!=-1)
            {
                min=bur[que[l]];
                k=que[l];
            }
        }
        for(l=0; l<pro; l++)
        {
            if(bur[l]==0)
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
        if(flag==1)break;
    }
    printf("\nP.Id\tArival\tBurst\tFinish\tTurn\tWaiting\n");
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],temp[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-temp[i]);
}
void nonPrio()
{
    int i,k,flag,min=999,pro,arr[11],bur[11],pri[11],fin[11],status[11]= {0},T=0;
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&bur[i]);
    printf("Enter the priorities\n");
    for(i=0; i<pro; i++)
        scanf("%d",&pri[i]);
    while(1)
    {
        for(i=0; i<pro; i++)
        {
            if(arr[i]<=T&&(status[i]!=-1||status[i]==0))
            {
                status[i]=1;
            }
        }
        min=999;
        for(i=0; i<pro; i++)
        {
            if(status[i]==1&&pri[i]<min)
            {
                min=pri[i];
                k=i;
            }
        }
        fin[k]=T+bur[k];
        status[k]=-1;
        T+=bur[k];
        flag=0;
        for(i=0; i<pro; i++)
            if(status[i]==-1)
                flag=1;
            else
            {
                flag=0;
                break;
            }
        if(flag==1)break;
    }
    printf("\nP.Id\tArrival\tBurst\tPrio\tFinish\tTurn\tWaiting\n");
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],bur[i],pri[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-bur[i]);
}
void prePrio()
{
    int tp,min=999;
    int i,k,swp,j=-1,l,flag,s,t,pro,arr[11],pri[11],bur[11],temp[11],que[11],fin[11],status[11]= {0},T=0;
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
    {
        scanf("%d",&bur[i]);
        temp[i]=bur[i];
    }
    printf("Enter the priorities times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&pri[i]);
    printf("Enter the time slab\n");
    scanf("%d",&t);
    for(i=0; i<pro; i++)
    {
        if(arr[i]==T)
        {
            j++;
            status[i]=1;
            que[j]=i;
        }
    }
    for(l=0; l<pro; l++)
    {
        if(pri[l]<min&&status[l]==1)
        {
            min=pri[que[l]];
            k=que[l];
        }
    }
    while(1)
    {
        if(bur[que[k]]>t)
        {
            for(tp=0; tp<t; tp++)
            {
                bur[que[k]]--;
                T++;
                for(l=0; l<pro; l++)
                {
                    if(arr[l]==T&&status[l]==0)
                    {
                        j++;
                        que[j]=l;
                        status[l]=1;
                    }
                }
            }
        }
        else
        {
            while(bur[que[k]]!=0)
            {
                bur[que[k]]--;
                T++;
                for(l=0; l<pro; l++)
                    if(arr[l]==T&&status[l]==0)
                    {
                        j++;
                        que[j]=l;
                        status[l]=1;
                    }
            }
            fin[que[k]]=T;
            status[que[k]]=-1;
        }
        min=999;
        for(l=0; l<=j; l++)
        {
            if(pri[que[l]]<min&&status[que[l]]!=-1)
            {
                min=pri[que[l]];
                k=que[l];
            }
        }
        for(l=0; l<pro; l++)
        {
            if(bur[l]==0)
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
        if(flag==1)break;
    }
    printf("\nP.Id\tArrival\tBurst\tPrio\tFinish\tTurn\tWaiting\n");
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],temp[i],pri[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-temp[i]);
}
void RR()
{
    int tp;
    int i,k,swp,j=-1,flag,s,t,pro,arr[11],bur[11],que[11],temp[11],fin[11],status[11]= {0},T=0;
    printf("Enter the number of processes\n");
    scanf("%d",&pro);
    printf("Enter the arrival times\n");
    for(i=0; i<pro; i++)
        scanf("%d",&arr[i]);
    printf("Enter the burst times\n");
    for(i=0; i<pro; i++)
    {
        scanf("%d",&bur[i]);
        temp[i]=bur[i];
    }
    printf("Enter the time slab\n");
    scanf("%d",&t);
    for(i=0; i<pro; i++)
    {
        if(arr[i]==T)
        {
            j++;
            status[i]=1;
            que[j]=i;
        }
    }
    while(1)
    {
        if(bur[que[0]]>t)
        {
            swp=1;
            for(tp=0; tp<t; tp++)
            {
                bur[que[0]]--;
                T++;
                for(k=0; k<pro; k++)
                {
                    if(arr[k]==T&&status[k]==0)
                    {
                        j++;
                        que[j]=k;
                        status[k]=1;
                    }
                }
            }
        }
        else
        {
            swp=0;
            while(bur[que[0]]!=0)
            {
                bur[que[0]]--;
                T++;
                for(k=0; k<pro; k++)
                    if(arr[k]==T&&status[k]==0)
                    {
                        j++;
                        que[j]=k;
                        status[k]=1;
                    }
            }
            fin[que[0]]=T;
            for(k=0; k<j; k++)
            {
                que[k]=que[k+1];
            }
            j--;
        }
        if(swp==1)
        {
            s=que[0];
            for(k=0; k<j; k++)
            {
                que[k]=que[k+1];
            }
            que[j]=s;
        }
        for(k=0; k<pro; k++)
        {
            if(bur[k]==0)
                flag=1;
            else
            {
                flag=0;
                break;
            }
        }
        if(flag==1)break;
    }
    printf("\nP.Id\tArival\tBurst\tFinish\tTurn\tWaiting\n");
    for(i=0; i<pro; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,arr[i],temp[i],fin[i],fin[i]-arr[i],fin[i]-arr[i]-temp[i]);
}
/*_____________________Output____________________
Enter the number of processes
5
Enter the arrival times
0 1 3 9 12
Enter the burst times
3 5 2 5 5
Enter the priorities times
2 1 3 4 4
Enter the time slab
2
FCFS:
P.Id	Arival	Burst	Finish	Turn	Waiting
P1	0	        3	  3	        3	  0
P2	1	        5	  8	        7	  2
P3	3	        2	  10	        7	  5
P4	9	        5	  15	        6	  1
P5	12	        5	  20	        8	  3

SJF(non-premptive):
P.Id	Arival	Burst	Finish	Turn	Waiting
P1	0	       3	  3	       3	  0
P2	1	       5	  10	       9	  4
P3	3	       2	  5	       2	  0
P4	9	       5	  15	       6	  1
P5	12	       5	  20	       8	  3

SJF(premptive):
P.Id	Arival	Burst	Finish	Turn	Waiting
P1	0	3	3	3	0
P2	1	5	10	9	4
P3	3	2	5	2	0
P4	9	5	15	6	1
P5	12	5	20	8	3
Priority(non-premtive):
P.Id	Arrival	Burst	Prio	Finish	Turn	Waiting
P1	0	3	2	3	3	0
P2	1	5	1	8	7	2
P3	3	2	3	10	7	5
P4	9	5	4	15	6	1
P5	12	5	4	20	8	3
Priority(premtive):
P.Id	Arrival	Burst	Prio	Finish	Turn	Waiting
P1	0	3	2	8	8	5
P2	1	5	1	6	5	0
P3	3	2	3	10	7	5
P4	9	5	4	15	6	1
P5	12	5	4	20	8	3
Round Robin:
P.Id	Arival	Burst	Finish	Turn	Waiting
P1	0	3	5	5	2
P2	1	5	12	11	6
P3	3	2	7	4	2
P4	9	5	17	8	3
P5	12	5	20	8	3
*/

