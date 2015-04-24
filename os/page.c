#include<stdio.h>

int page[20],memo[3],num_page;
int a=0;
void accept_data()
{
	int i;
	printf("\nEnter how many pages require by the process:");
	scanf("%d",&num_page);
	
	printf("Enter the page numbers:\n");
	for(i=0;i<num_page;i++)
	{
		scanf("%d",&page[i]);
	}

	for(a=0;a<3;a++)
	{
	memo[a]=100;
	printf("Memo %d",memo[a]);
	}

}

int check_avail(int curr)
{
	int i;
	for(i=0;i<3;i++)
	{
		if(curr==memo[i])
			return i;
	}
	return -1;
	
}

int find_max1(int curr[3],int pos)
{
	printf("Curr %d",curr[3]);
	int i,j,k,max=-1,dist;
	for(j=0;j<3;j++)
	{
	printf("Value of pos --%d\n",pos);
		for(i=pos;i>=0;i--)
		{
			printf("Value of i --%d\n",i);
printf("Value of curr of j --%d\n",curr[j]);
			if(curr[j]==page[i])
			  break;
		}
		dist=pos-i;
printf("Value of dist--%d\n",dist);
		if(max<dist)
		{
			printf("Value of max --%d\n",max);
			max=dist;
			k=j;
			printf("Value of k --%d\n",k);
		}
	}
printf(“Returned value of k is : ”,k)
	return k;
}

int find_max(int curr[3],int pos)
{
	int i,j,k,max=-1,dist;
	for(j=0;j<3;j++)
	{
		for(i=pos;i<num_page;i++)
		{
			if(curr[j]==page[i])
			  break;
		}
		dist=i-pos;
		if(max<dist)
		{
			max=dist;
			k=j;
		}
	}
	return k;
}




void fifo()
{
	int i=0,present,loc=0,cnt=0;

	while(i<num_page)
	{
		present=check_avail(page[i]);
		//printf("Value of present --%d\n",present);
		if(present==-1)
		{
			memo[loc]=page[i];
			loc++;
                        //printf("Value of loc --%d\n",loc);
			if(loc==3)
				loc=0;
			printf("\nPage [%d]--> Fault    : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
			cnt++;
                       //printf("Value of count --%d\n",cnt);
		}	
		else
			printf("\nPage [%d]--> No Fault : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
		i++;
	}
	printf("\n\nTotal Page Faults:%d",cnt);
}

void optimal()
{
	int empty=0,present,max,cnt=0,i=0;
	while(i<num_page)
	{
		present=check_avail(page[i]);
		if(present==-1)
		{
			if(empty==3)
			{
				max=find_max(memo,i);
				memo[max]=page[i];
				printf("\nPage [%d]--> Fault    : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
			}
			else
			{
				memo[empty]=page[i];
				empty++;
				printf("\nPage [%d]--> Fault    : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
			}
			cnt++;
		}
		else
			printf("\nPage [%d]--> No Fault : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
		i++;
	}
	
	printf("\nTotal page fault:%d",cnt);
	
}

void LRU()
{
	int empty=0,present,max,cnt=0,i=0;
	while(i<num_page)
	{
		present=check_avail(page[i]);
printf("Value of present *********%d\n",present);
		if(present==-1)
		{
			if(empty==3)
			{
printf("Value of memo --%d\n",memo);printf("Value of i --%d\n",i);
				max=find_max1(memo,i);
printf("Value of max --%d\n",max);
				memo[max]=page[i];
				printf("\nPage [%d]--> Fault    : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
			}
			else
			{
				memo[empty]=page[i];
				empty++;
				printf("\nPage [%d]--> Fault    : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
			}
			cnt++;
		}
		else
			printf("\nPage [%d]--> No Fault : [%d %d %d]",page[i],memo[0],memo[1],memo[2]);
		i++;
	}
	
	printf("\nTotal page fault:%d",cnt);
	
}

void main()
{
	int i;	
	accept_data();
	printf("------------FIFO------------");
	fifo();
	for(i=0;i<3;i++)
		memo[i]=100;
	printf("\n------------OPTIMAL----------");
	optimal();	
	for(i=0;i<3;i++)
		memo[i]=100;
	printf("\n------------LRU----------");
	LRU();	
	printf("\n");
}