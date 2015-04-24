#include<stdio.h>

int head,arr[30];
float avg2,avg3,avg4,avg1;
float seek1=0,seek2=0,seek3=0,seek4=0;

int greater2[30],greater3[30],greater4[30];
int less2[30],less3[30],less4[30];

int g2=0,g3=0,g4=0,l2=0,l3=0,l4=0;
int current1[30],current2[30],current3[30],current4[30];

int next1[30],next2[30],next3[30],next4[30];
int total1[30],total2[30],total3[30],total4[30];

int i,j,n=0,n1,temp,ch,cnt=0;

void FCFS();
void SSTF();
void SCAN();
void CSCAN();

void main()
{

  clrscr();
  printf("\nEnter Head:\n");
  scanf("%d",&head);
  printf("Enter total track requests\n");
  scanf("%d",&cnt);
  printf("\nEnter tracks\n");
  for(n=0;n<cnt;n++)
  scanf("%d",&arr[n]);
  do
	 {
		printf("\n----------MENU-----------\n");
		printf("\n1-FCFS\n2-SSTF\n3-SCAN\n4-CSCAN\n5-exit\n");
		printf("\n ENTER YOUR CHOICE:");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:
					 FCFS();
					  break;
			case 2:
					  SSTF();
					  break;
			case 3:
					  SCAN();
					  break;

			case 4:
					  CSCAN();
					  break;

			case 5:
					  break;;

		}
	  }while(ch<5);
	  getch();
}

void FCFS()
{


  current1[0]=head;

  for(i=0;i<n;i++)
  {
	 current1[i+1]=arr[i];
  }

  for(i=0;i<n;i++)
  {
	 next1[i]=arr[i];
  }

  for(i=0;i<n;i++)
	{
	  if(current1[i]>next1[i])
	  {
	  total1[i]=current1[i]-next1[i];
	  }
	  else
	  {
		total1[i]=next1[i]-current1[i];
	  }
	}

	for(i=0;i<n;i++)
	{
		seek1=total1[i]+seek1;
	}
	 avg1=seek1/n;

  printf("\n-----CURRENT----NEXT--------traverse-----\n");
  for(i=0;i<n;i++)
  {
	  printf("\t%d\t",current1[i]);
	  printf("%d\t",next1[i]);
	  printf("\t%d\n",total1[i]);
  }
  printf("\nAverage Seek Length [FCFS]:%f\n",avg1);
 }


void SSTF()
{


  current2[0]=head;

for(i=0;i<n;i++)
  {
	 if(arr[i]>head)
	 {
		greater2[g2]=arr[i];
		g2++;
	 }
	 else
	 {
		 less2[l2]=arr[i];
		 l2++;
	 }
  }

	for(i=0;i<g2;i++)
	{
	  for(j=i+1;j<g2;j++)
	  {
		 if(greater2[i]>greater2[j])
		 {
			  temp=greater2[i];
			 greater2[i]=greater2[j];
			 greater2[j]=temp;
		 }
	 }
	}
	for(i=0;i<l2;i++)
	{
	  for(j=i+1;j<l2;j++)
	  {
		 if(less2[i]<less2[j])
		 {
			  temp=less2[i];
			 less2[i]=less2[j];
			 less2[j]=temp;
		 }
	  }
	}

	n1=g2+l2;
  for(i=0;i<l2;i++)
  {
	 next2[i]=less2[i];
  }
  for(i=l2,j=0;i<n1,j<g2;i++,j++)
  {
	  next2[i]=greater2[j];
  }

  for(i=0;i<n;i++)
  {
	  current2[i+1]=next2[i];
  }

  for(i=0;i<n;i++)
	{
	  if(current2[i]>next2[i])
	  {
	  total2[i]=current2[i]-next2[i];
	  }
	  else
	  {
		total2[i]=next2[i]-current2[i];
	  }
	}

	for(i=0;i<n;i++)
	{
		seek2=total2[i]+seek2;
	}
	 avg2=seek2/n;

  printf("\n-----CURRENT----NEXT--------traverse-----\n");
  for(i=0;i<n;i++)
  {
	  printf("\t%d\t",current2[i]);
	  printf("%d\t",next2[i]);
	  printf("\t%d\n",total2[i]);
  }
  printf("\nAverage Seek Length [SSTF]:%f\n",avg2);
}

void SCAN()
{

  current3[0]=head;

  for(i=0;i<n;i++)
  {
	 if(arr[i]>head)
	 {
		greater3[g3]=arr[i];
		g3++;
	 }
	 else
	 {
		 less3[l3]=arr[i];
		 l3++;
	 }
  }

 for(i=0;i<g3;i++)
	{
	  for(j=i+1;j<g3;j++)
	  {
		 if(greater3[i]>greater3[j])
		 {
			  temp=greater3[i];
			 greater3[i]=greater3[j];
			 greater3[j]=temp;
		 }
	 }
	}
	for(i=0;i<l3;i++)
	{
	  for(j=i+1;j<l3;j++)
	  {
		 if(less3[i]<less3[j])
		 {
			  temp=less3[i];
			 less3[i]=less3[j];
			 less3[j]=temp;
		 }
	  }
	}

  n1=g3+l3;
  for(i=0;i<g3;i++)
  {
	 next3[i]=greater3[i];
  }
  for(i=g3,j=0;i<n1,j<l3;i++,j++)
  {
	  next3[i]=less3[j];
  }

  for(i=0;i<n;i++)
  {
	  current3[i+1]=next3[i];
  }

  for(i=0;i<n;i++)
	{
	  if(current3[i]>next3[i])
	  {
	  total3[i]=current3[i]-next3[i];
	  }
	  else
	  {
		total3[i]=next3[i]-current3[i];
	  }
	}

	for(i=0;i<n;i++)
	{
		seek3=total3[i]+seek3;
	}
	 avg3=seek3/n;

  printf("\n-----CURRENT----NEXT--------traverse-----\n");
  for(i=0;i<n;i++)
  {
	  printf("\t%d\t",current3[i]);
	  printf("%d\t",next3[i]);
	  printf("\t%d\n",total3[i]);
  }
  printf("\nAverage Seek Length [SCAN]:%f\n",avg3);
}

void CSCAN()
{

  current4[0]=head;


  for(i=0;i<n;i++)
  {
	 if(arr[i]>head)
	 {
		greater4[g4]=arr[i];
		g4++;
	 }
	 else
	 {
		 less4[l4]=arr[i];
		 l4++;
	 }
  }

 for(i=0;i<g4;i++)
	{
	  for(j=i+1;j<g4;j++)
	  {
		 if(greater4[i]>greater4[j])
		 {
			  temp=greater4[j];
			 greater4[j]=greater4[i];
			 greater4[i]=temp;
		 }
	 }
	}

 for(i=0;i<l4;i++)
	{
	  for(j=i+1;j<l4;j++)
	  {
		 if(less4[i]>less4[j])
		 {
			  temp=less4[i];
			 less4[i]=less4[j];
			 less4[j]=temp;
		 }
	  }
	}

 n1=g4+l4;
  for(i=0;i<g4;i++)
  {
	 next4[i]=greater4[i];
  }
  for(i=g4,j=0;i<n1,j<l4;i++,j++)
  {
	  next4[i]=less4[j];
  }

  for(i=0;i<n;i++)
  {
	  current4[i+1]=next4[i];
  }

  for(i=0;i<n;i++)
	{
	  if(current4[i]>next4[i])
	  {
	  total4[i]=current4[i]-next4[i];
	  }
	  else
	  {
		total4[i]=next4[i]-current4[i];
	  }
	}

	for(i=0;i<n;i++)
	{
		seek4=total4[i]+seek4;
	}
	 avg4=seek4/n;

  printf("\n-----CURRENT----NEXT--------traverse-----\n");
  for(i=0;i<n;i++)
  {
	  printf("\t%d\t",current4[i]);
	  printf("%d\t",next4[i]);
	  printf("\t%d\n",total4[i]);
  }
  printf("\nAverage Seek Length [C-SCAN]:%f\n",avg4);

}

