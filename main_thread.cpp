//
//  main.cpp
//  COSC3360_Hw3
//
//  Created by Hien Nguyen on 4/6/19.
//  Copyright © 2019 Hien Nguyen. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;
//worked with Jeremy Bayangos

pthread_t threading_id[10];
static int sgroup;
int groupie[2] = {0,0};
int groupie2[2] = {0,0};
static bool foundation[10] = {false};  //database
static int occupy[10];
static int wait_g; //wait based on group
static int wait_p; //wait based on position
bool flag_s = false;


struct keep
{
    int id, pos, start, end, group;
    
    keep (int ngroup, int npos, int sstart, int nend, int nid){
        id = nid;
        pos = npos;
        start = sstart;
        end = nend;
        group = ngroup;
    }
};

static pthread_mutex_t pos_lock[10];                    //position lock
static pthread_mutex_t group_lock = PTHREAD_MUTEX_INITIALIZER; //group lock
static pthread_cond_t grouper = PTHREAD_COND_INITIALIZER;     //group condition
static pthread_cond_t poser[10];                                //position condition

void *data(void *data_ptr)     //condition variable 
{
    keep a=*(keep *)data_ptr;
    cout<<"User "<<a.id;
    cout <<" from group "<<a.group;
    cout <<" arives to the DBMS"<<endl;
    
    pthread_mutex_lock(&group_lock);
    if(a.group!=sgroup){
        cout<<"User "<<a.id;
        cout <<" is waiting due to its group "<<endl;
        pthread_cond_wait(&grouper, &group_lock);
        wait_g++;
    }
    pthread_mutex_unlock(&group_lock);                 //unlock group lock
    
    pthread_mutex_lock(&pos_lock[a.pos]);
    
    if(foundation[a.pos]!=false)
    {
        cout<<"User "<<a.id;
        cout <<" is waiting: position "<<a.pos;
        cout <<" is being used by user ";
        cout<<occupy[a.pos]<<endl;
        wait_p++;
        pthread_cond_wait(&poser[a.pos], &pos_lock[a.pos]);
    }
    pthread_mutex_unlock(&pos_lock[a.pos]);              //unlock position lock
    
    cout<<"User "<<a.id;
    cout <<" is accesing the position "<<a.pos;
    cout <<" of the database for "<<a.end;
    cout <<" secound(s)"<<endl;
    occupy[a.pos]=a.id;
    foundation[a.pos]=true;
    
    sleep(a.end);
    
    cout<<"User "<<a.id;
    cout<<" finished its execution"<<endl;
    pthread_mutex_lock(&pos_lock[a.pos]);
    pthread_cond_signal(&poser[a.pos]);
    foundation[a.pos]=false;
    groupie[a.group-1]--;
    pthread_mutex_unlock(&pos_lock[a.pos]);              //unlock position lock again
    
    pthread_mutex_lock(&group_lock);
    if(groupie[sgroup-1]==0){
        if(!flag_s){
            cout<<"All users from Group " <<sgroup;
            cout << " finished their execution"<<endl;
            int b=sgroup==1?2:1;
            cout<<"The users from Group "<<b;
            cout <<" start their execution\n"<<endl;
            flag_s=true;
        }
        pthread_cond_signal(&grouper);
        
    }
    pthread_mutex_unlock(&group_lock);
    
    return 0;
}

int main(int argc, const char * argv[]) {
    
    for (int i =0; i<10; i++){
        pos_lock[i] = PTHREAD_MUTEX_INITIALIZER;
        poser[i] = PTHREAD_COND_INITIALIZER;
    }
    
    int pos, start, end, group;
    int set = 1;
    int i = 0;
    
    cin >>sgroup;
    while(cin >> group >> pos >> start >> end)
    {
        sleep(start);
        
        //totaling
        groupie[group-1]++;
        
        //for copyer number 2
        groupie2[group-1]++;
        
        keep temp(group, pos, start, end, set);
        if(pthread_create(&threading_id[i], NULL, data,(void*)&temp)) //used the sample file
        {
            cerr<< "Error creating thread" << endl;
            return 1;
        }set++; i++;
        
    }
    for(int i = 0; i<set;i++)
    {
        pthread_join(threading_id[i], NULL);
    }
    
    cout <<"Total request:"<<endl;
    cout <<"                Group 1: "<<groupie2[0]<<endl;
    cout <<"                Group 2: "<<groupie2[1]<<endl;
    cout <<"Requests that waited:"<<endl;
    cout <<"                Due to its group: "<< wait_g <<endl;
    cout <<"                Due to locked position: "<<wait_g<<endl;
    
    return 0;
    
}
