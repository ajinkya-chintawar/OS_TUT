#include <stdio.h>
#define MAX 20
typedef struct page
{
    int data;
    int hit;
} page;
void main()
{
    int i,j,k,flag,cnt=0,q=0,flag2=0,temp,max,mix=0,f3=0;
    page p[MAX];
    int frame[MAX];
    int fs,nr;
    printf("\nEnter number of references: ");
    scanf("%d",&nr);
    printf("\nEnter %d references: ",nr);
    for(i=0; i<nr; i++)
    {
        scanf("%d",&frame[i]);
    }

    printf("\nEnter frame size: ");
    scanf("%d",&fs);

    for(i=0; i<fs; i++)
    {
        p[i].data=-1;
        p[i].hit=0;
    }

    j=0;
    for(i=0; i<nr; i++)
    {
        for(k=0; k<fs; k++)
        {
            if(p[k].data!=-1)
                p[k].hit++;
        }

        flag=0;

        printf("\nREF: %d",frame[i]);
        for(k=0; k<fs; k++)
        {
            if(p[k].data==frame[i])
            {
                p[k].hit=1;
                flag=1;
                temp=k;
                break;
            }
        }

        if(flag!=1 && f3!=1)
        {
            p[j].data=frame[i];
            p[j].hit=1;
            temp=j;
            cnt++;
            j++;
        }

        if(f3==1 && flag!=1)
        {
            max=0;
            mix=0;
            for(k=0; k<fs; k++)
            {
                if(max < p[k].hit)
                {
                    max=p[k].hit;
                    mix=k;
                }
            }

            flag2=0;
            for(k=0; k<fs; k++)
            {
                if(flag2!=1)
                {
                    j=mix;
                    p[j].data=frame[i];
                    p[j].hit=1;
                    temp=j;
                    cnt++;
                    flag2=1;
                }
            }
        }
        if(j==fs)
        {
            j=0;
            f3=1;
        }

        for(k=0; k<fs; k++)
        {
            if(temp==k)
            {
                printf("\n->%d-%d",p[k].data,p[k].hit);
            }
            else
            {
                printf("\n%d-%d",p[k].data,p[k].hit);
            }
        }
        printf("\n-------\n");
    }
    printf("\nPage Fault: %d\n",cnt);
}
