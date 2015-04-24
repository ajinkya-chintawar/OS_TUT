#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

void FCFS(int num_proc, int arrival_time[], int burst_time[])
{
    int time_cntr = 0,next = 0,j,i,finish_time[num_proc],turnaround_time[num_proc],waiting_time[num_proc],done[num_proc+1];

    for(i=0; i<=num_proc; ++i)
    {
        done[i] = 0;
    }
    for(i=0; i<num_proc; ++i)
    {
        next = num_proc;
        for(j=0; j<=num_proc; ++j)
        {
            if(arrival_time[j] < arrival_time[next] && done[j] == 0)
            {
                //cout<<"next changed"<<endl<<endl;
                next = j;
            }
        }
        cout<<"next : "<<next<<endl;
        done[next] = 1;
        time_cntr = time_cntr + burst_time[next];
        finish_time[next] = time_cntr;
        cout<<"FT : "<<finish_time[next]<<endl;
        turnaround_time[next] = finish_time[next] - arrival_time[next];
        cout<<"TT : "<<turnaround_time[next]<<endl;
        waiting_time[next] = turnaround_time[next] - burst_time[next];
        cout<<"WT : "<<waiting_time[next]<<endl<<endl;
    }
    return;
}

void FCFS_new(int num_proc, int arrival_time[], int burst_time[])
{
    int time_cntr=0,i,j,k,min_proc = 100,next,ft,wt,tt,done[num_proc];
    queue< int > ready_q;

    for(i=0; i<=num_proc; ++i)
    {
        done[i] = 0;
    }

    for(i=0; i<num_proc; ++i)
    {
        min_proc = 100;
        for(j=0; j<num_proc; ++j)
        {
            if(arrival_time[j] < min_proc && done[j] == 0)
            {
                min_proc = arrival_time[j];
                next = j;
            }
        }
        ready_q.push(next);
        done[next] = 1;
    }
    for(k=0; k<num_proc; ++k)
    {
        cout<<endl<<endl;
        next = ready_q.front();
        ready_q.pop();
        cout<<"next proc : "<<next;
        time_cntr = time_cntr + burst_time[next];
        ft  = time_cntr;
        cout<<"finish time : "<<ft<<endl;
        tt = ft - arrival_time[next];
        cout<<"turnaround time : "<<tt<<endl;
        wt = tt - burst_time[next];
        cout<<"waiting time : "<<wt<<endl;
    }
    return;
}

void SJF_nonP(int num_proc, int arrival_time[], int burst_time[])
{
    int i,j,k,done[num_proc],next,min_proc = 100,time_cntr = 0,ft,wt,tt;

    for(i=0; i<num_proc; ++i)
    {
        done[i] = 0;
        if(arrival_time[i] == 0)
        {
            done[i] = 1;
            next = i;
        }
    }

    time_cntr = burst_time[next];
    ft = time_cntr;
    cout<<"Finish time : "<<ft<<endl;
    tt = ft - arrival_time[next];
    cout<<"Turnaround time : "<<tt<<endl;
    wt = tt - burst_time[next];
    cout<<"Waiting time : "<<wt<<endl;

    for(i=1; i<num_proc; ++i)
    {
        min_proc = 100;
        for(j=0; j<num_proc; ++j)
        {
            if(arrival_time[j] < time_cntr)
            {
                if(burst_time[j] < min_proc && done[j] == 0)
                {
                    min_proc = burst_time[j];
                    next = j;
                }
            }
        }
        time_cntr = time_cntr + burst_time[next];
        ft = time_cntr;
        cout<<endl<<"Finish time : "<<ft<<endl;
        cout<<"Turnaround time : "<<tt<<endl;
        cout<<"Waiting time : "<<wt<<endl;
        
    }

    return;
}
void print_job(int ft,int tt,int wt)
{
    cout<<endl<<"Finish time : "<<ft<<endl;
    cout<<"Turnaround time : "<<tt<<endl;
    cout<<"Waiting time : "<<wt<<endl;
}   
void SJF_P(int num_proc, int arrival_time[], int burst_time[])
{
    int i,j,k,done[num_proc],next,min_proc = 100,time_cntr = 0,ft,wt,tt;
    int bt1[100];
    for(i=0; i<num_proc; ++i)
    {
        done[i] = 0;
        bt1[i] = burst_time[i];
        // if(arrival_time[i] == 0)
        // {
        // 	if(burst_time[i] == 1)
        //     	done[i] = 1;
        //     next = i;
        // }
    }
    int counter = 0;
    	
    while(1)
    {
    	min_proc = 100;
    	for(i = 0;i < num_proc;i++)
    	{
    		if(burst_time[i] < min_proc && done[i] == 0 && arrival_time[i] <= counter)
    		{

    			min_proc = burst_time[i];
    			next = i;
    		}
    	}
    	counter++;
    	time_cntr++;
    	cout<<"selected "<<min_proc<<endl;
		if(min_proc == 100)
			break;
		
		if(burst_time[next] == 1)
		{
			done[next] = 1;
			//next = i;
			//time_cntr = time_cntr + bt1[next];
			ft = time_cntr;
			tt = ft - arrival_time[next];
			wt = tt - bt1[next];
			print_job(ft,tt,wt);
			burst_time[next]--;
		}
		else
			burst_time[next]--;
		// for(int i = 0;i < num_proc;i++)
		// 	cout<<burst_time[i]<<"\t"<<done[i]<<endl;	
    }

    return;
}

void Priority_nonP(int num_proc, int arrival_time[], int burst_time[], int priority[])
{
    int i,j,k,done[num_proc],next,min_proc = 100,time_cntr = 0,ft,wt,tt;

    for(i=0; i<num_proc; ++i)
    {
        done[i] = 0;
        if(arrival_time[i] == 0)
        {
            done[i] = 1;
            next = i;
        }
    }

    time_cntr = time_cntr + burst_time[next];
    ft = time_cntr;
    cout<<"Finish time : "<<ft<<endl;
    tt = ft - arrival_time[next];
    cout<<"Turnaround time : "<<tt<<endl;
    wt = tt - burst_time[next];
    cout<<"Waiting time : "<<wt<<endl;

    for(i=1; i<num_proc; ++i)
    {
        int max_priority = 100;
        for(j=0; j<num_proc; ++j)
        {
            if(arrival_time[j] < time_cntr)
            {
                if(priority[j] < max_priority && done[j] == 0)
                {
                    max_priority = priority[j];
                    next = j;
                }
            }
        }
        time_cntr = time_cntr + burst_time[next];
        ft = time_cntr;
        cout<<"Finish time : "<<ft<<endl;
        tt = ft - arrival_time[next];
        cout<<"Turnaround time : "<<tt<<endl;
        wt = tt - burst_time[next];
        cout<<"Waiting time : "<<wt<<endl;
        done[next] = 1;
    }

    return;
}

void Priority_P(int num_proc, int arrival_time[], int burst_time[], int priority[])
{
	int i,j,k,done[num_proc],next,min_proc = 100,time_cntr = 0,ft,wt,tt;
	int bt1[num_proc];
    for(i=0; i<num_proc; ++i)
    {
        done[i] = 0;
        bt1[i] = burst_time[i];
        // if(arrival_time[i] == 0)
        // {
        //     done[i] = 1;
        //     next = i;
        // }
    }

    // time_cntr = time_cntr + burst_time[next];
    // ft = time_cntr;
    // cout<<"Finish time : "<<ft<<endl;
    // tt = ft - arrival_time[next];
    // cout<<"Turnaround time : "<<tt<<endl;
    // wt = tt - burst_time[next];
    // cout<<"Waiting time : "<<wt<<endl;

    while(1)
    {
        int max_priority = 100;
        for(j=0; j<num_proc; ++j)
        {
            if(arrival_time[j] <= time_cntr)
            {
                if(priority[j] < max_priority && done[j] == 0)
                {
                    max_priority = priority[j];
                    next = j;
                }
            }
        }
        time_cntr++;
    	//cout<<"selected "<<max_priority<<endl;
		if(max_priority == 100)
			break;
		
		if(burst_time[next] == 1)
		{
			done[next] = 1;
			//next = i;
			//time_cntr = time_cntr + bt1[next];
			ft = time_cntr;
			tt = ft - arrival_time[next];
			wt = tt - bt1[next];
			print_job(ft,tt,wt);
			burst_time[next]--;
		}
		else
			burst_time[next]--;
        // ft = time_cntr;
        // tt = ft - arrival_time[next];
        // wt = tt - burst_time[next];
        //done[next] = 1;
    }
    return;
}

void RR(int num_proc, int arrival_time[], int burst_time[], int priority[])
{
    return;
}

int main()
{
    int i,j,k,num_proc,choice;

    while(1)
    {
        cout<<"Enter your choice :"<<endl;
        cout<<"1] FCFS"<<endl<<"2] SJF(Non-Preemptive)"<<endl<<"3] SJF(Preemptive)"<<endl<<"4] Priority(Non-Preemptive)"<<endl<<"5] Priority(Preemptive)"<<endl<<"6] Round-Robin"<<endl<<"7] EXIT"<<endl<<endl;
        cin>>choice;

        if(choice == 7)
            break;

        cout<<"Enter number of processes :"<<endl<<endl;
        cin>>num_proc;

        int arrival_time[num_proc+1],burst_time[num_proc],priority[num_proc];

        cout<<"Enter Arrival Times, Burst Times and Priority of processes :"<<endl<<endl;
        for(i=0; i<num_proc; i++)
        {
            cin>>arrival_time[i];
            cin>>burst_time[i];
            cin>>priority[i];
        }
        arrival_time[num_proc] = 10000;

        switch(choice)
        {
        case 1:
            FCFS_new(num_proc, arrival_time, burst_time);
            break;

        case 2:
            SJF_nonP(num_proc, arrival_time, burst_time);
            break;

        case 3:
            SJF_P(num_proc, arrival_time, burst_time);
            break;

        case 4:
            Priority_nonP(num_proc, arrival_time, burst_time, priority);
            break;

        case 5:
            Priority_P(num_proc, arrival_time, burst_time, priority);
            break;

        case 6:
            RR(num_proc, arrival_time, burst_time, priority);
            break;
        }
    }
    return 0;
}


/*
int time_cntr=0,i,j,k,min_proc = 100,next,ft,wt,tt,done[num_proc];
    list< int > ready_q;

    for(i=0; i<=num_proc; ++i)
    {
        done[i] = 0;
    }

    for(i=0; i<num_proc; ++i)
    {
        min_proc = 100;
        for(j=0; j<num_proc; ++j)
        {
            if(arrival_time[j] < min_proc && done[j] == 0)
            {
                min_proc = arrival_time[j];
                next = j;
            }
        }
        ready_q.push(next);
        done[next] = 1;
    }

    cout<<endl<<endl;
    next = ready_q.front();
    ready_q.pop_front();
    cout<<"next proc : "<<next;
    time_cntr = time_cntr + burst_time[next];
    ft  = time_cntr;
    cout<<"finish time : "<<ft<<endl;
    tt = ft - arrival_time[next];
    cout<<"turnaround time : "<<tt<<endl;
    wt = tt - burst_time[next];
    cout<<"waiting time : "<<wt<<endl;

    for(k=0;k<(num_proc - 1);++k)
    {
        min_proc = 100;
        for(int m=0;m<(num_proc - 1);++m)
        {

        }
    }

*/
