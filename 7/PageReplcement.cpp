#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<queue>
using namespace std;

void FIFO(int num_of_frames,int num_of_pages,int pages[],int time[],int cnt)
{
    int i,j,k,m,n,memory[num_of_frames],num_of_pf = 0,no_pf = 0, valid_pf = 0;
    queue< int > mem;

    for(j=0; j<num_of_frames; ++j)
        memory[j] = 0;

    for(j=0; j<cnt; ++j)
    {
        for(k=0; k<num_of_frames; ++k)
        {
            if(memory[k] == pages[j])
            {
                no_pf = 1;
                break;
            }
            else
                continue;
        }
        if(no_pf == 1)
        {
            cout<<"j : "<<j<<" no pf"<<endl;
            no_pf = 0;
            continue;
        }
        else
        {
            num_of_pf++;
            cout<<"j : "<<j<<" pf : "<<num_of_pf<<endl;

            for(m=0; m<num_of_frames; ++m)
            {
                if(memory[m] == 0)
                {
                    valid_pf = 1;
                    break;
                }
            }
            if(valid_pf == 1)
            {
                memory[m] = pages[j];
                mem.push(pages[j]);
                valid_pf = 0;
                continue;
            }
            else
            {
                int replace_page = mem.front();
                mem.pop();
                mem.push(pages[j]);
                for(n=0; n<num_of_frames; ++n)
                {
                    if(memory[n] == replace_page)
                    {
                        memory[n] = pages[j];
                        break;
                    }
                }
            }
        }
    }
    cout<<"number of page faults : "<<num_of_pf<<endl;
}

void Optimal(int pages[],int time[],int num_of_frames,int num_of_pages)
{

}

int main()
{
    int num_of_frames,num_of_pages,i=0,j,k,cnt=0;
    cout<<"Enter no. of frames : ";
    cin>>num_of_frames;
    cout<<"Enter no. of pages : ";
    cin>>num_of_pages;
    int pages[num_of_pages],time[num_of_pages],choice;

    cout<<"Enter the Reference String : ";
    while(1)
    {
        cin>>pages[cnt];
        if(pages[cnt] == 0)
            break;
        cnt++;
    }

    cout<<"Enter your choice : "<<endl;
    cout<<"1] FIFO"<<endl<<"2] Optimal"<<endl<<"3] LRU"<<endl;
    cin>>choice;

    switch(choice)
    {
    case 1:
        FIFO(num_of_frames,num_of_pages,pages,time,cnt);
        break;

    case 2:
        Optimal(pages,time,num_of_frames,num_of_pages);
        break;

    case 3:
        //LRU(pages,time,num_of_frames,num_of_pages);
        break;

    case 4:
        exit(0);
    }

    return 0;
}
