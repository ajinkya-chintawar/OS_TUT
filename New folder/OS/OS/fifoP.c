#include<stdio.h>
#include<string.h>

void main()
{	
      int pno,i=0,j=0,PF=0,fno,rpnt,pfcnt=0,k;
      int seq[15],frame[10];

      for(j=0;j<10;j++)
	 		frame[j]=-1;

      printf("Enter no of Pages : ");
      scanf("%d",&pno);
      printf("Enter page sequence : ");
      for(i=0;i<pno;i++)
      {
	   	scanf("%d",&seq[i]);
      }

      printf("Enter no of frames : ");
      scanf("%d",&fno);
      rpnt=0;
      j=0;
      for(i=0;i<pno;i++)
      {
	  		j=0;PF=0;
	  		while(j<fno)
	  		{
	       	if(seq[i]==frame[j])
	       	{
		    		PF=1;      //no page fault
		    		break;
	       	}
	       	j++;
  			}
	  		if(PF==0)            //page fault
	  		{
				pfcnt++;
				frame[rpnt]=seq[i];
				rpnt=(rpnt+1)%fno;
				printf("\nPageFault   :\t");
				for(k=0;k<fno;k++)
		   		printf("%d\t",frame[k]);
	  		}
	  		else
	  		{
				printf("\nNOPageFault :\t");
				for(k=0;k<fno;k++)
					printf("%d\t",frame[k]);
	  		}
      }
      printf("\n Page faults=%d\n",pfcnt);
}
