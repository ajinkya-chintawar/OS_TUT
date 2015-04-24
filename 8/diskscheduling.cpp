#include<stdio.h>
#include<queue>
#include<iostream>
#include<algorithm>
using namespace std;

void fcfs(int num, int req[], int current)
{
    int i,seek=0;
    for(i=0; i<num; ++i)
    {
        if(current <= req[i])
            seek = seek + (req[i] - current);

        if(current > req[i])
            seek = seek + (current - req[i]);

        current = req[i];
    }
    cout<<"total seek time : "<<seek<<endl;
}

int find_min(int num, int current, int req[], int done[])
{
    int temp,i,j,arr[num];
    for(i=0; i<num; ++i)
    {
        temp = current - req[i];
        if(temp < 0)
            temp = temp - (2 * temp);
        arr[i] = temp;
    }
    int min_req = 10000,min_index;
    for(i=0; i<num; ++i)
    {
        if(min_req > arr[i] && done[i] == 0)
        {
            min_req = arr[i];
            min_index = i;
        }
    }
    return min_index;
}

void sstf(int num, int req[], int current)
{
    int i,j,done[num],next,seek = 0;
    for(i=0; i<num; ++i)
        done[i] = 0;

    for(i=0; i<num; ++i)
    {
        next = find_min(num,current,req,done);
        if(current > req[next])
            seek = seek + (current - req[next]);

        else if(current <= req[next])
            seek = seek + (req[next] - current);

        current = req[next];
        done[next] = 1;
    }
    cout<<seek;
}

void scan(int num, int req[], int current)
{
    int i,j,newreq[num+1],cur_index;
    for(i=0; i<num; ++i)
    {
        newreq[i] = req[i];
    }
    newreq[num] = current;
    sort(newreq,(newreq+num+1));
    for(i=0; i<(num+1); ++i)
    {
        if(newreq[i] == current)
        {
            cur_index = i;
            break;
        }
    }
    cout<<"current at : "<<cur_index<<endl;
    int seek = 0,next = cur_index;
    for(i=0; i<(num-cur_index); ++i)
    {
        seek = seek + (newreq[next+1] - newreq[next]);
        next++;
    }
    next = cur_index-1;
    seek = seek + (newreq[num] - newreq[next]);
    for(i=1; i<cur_index; ++i)
    {
        seek = seek + (newreq[next] - newreq[next-1]);
        next--;
    }
    cout<<"final : "<<seek<<endl;
}

int main()
{
    int i,num,cur;
    cout<<"enter current head position : ";
    cin>>cur;
    cout<<"enter number of requests : ";
    cin>>num;
    int req[num];
    cout<<"enter requests : ";
    for(i=0; i<num; ++i)
        cin>>req[i];
    //fcfs(num,req,cur);
    //sstf(num,req,cur);
    scan(num,req,cur);
    return 0;
}
