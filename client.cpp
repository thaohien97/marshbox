// Please note this is a C program
// It compiles without warnings with gcc
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/wait.h>

using namespace std;

void error(string msg)
{
    cout << msg;
    exit(0);
}

int *encode(int arr[], int num){
    int *p;
    return p;
}

int main(int argc, char *argv[])
{
    int w1[4] = {-1, 1, -1, 1};
    int w2[4] = {-1, -1, 1, 1};
    int w3[4] = {-1, 1, 1, -1};
    string wArr[3] = {"-1 1 -1 1", "-1 -1 1 1", "-1 1 1 -1"};
    
    pid_t pid;
    
    int sockfd, portno, n, x;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    
    int process1[2] = {0};
    int process2[2] = {0};
    int process3[2] = {0};
    
    int proc, val;
    int i = 1;
    
    while (cin>>proc>>val){
        if (i == 1){
            process1[0] = proc;
            process1[1] = val;
        }
        else if (i == 2){
            process2[0] = proc;
            process2[1] = val;
        }
        else if(i == 3){
            process3[0] = proc;
            process3[1] = val;
        } i++;
    }
    
    for (x = 0; x<3; x++){
        if ((pid = fork() == 0)){
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0)
                error("ERROR opening socket");
            server = gethostbyname(argv[1]);
            if (server == NULL) {
                fprintf(stderr,"ERROR, no such host\n");
                exit(0);
            }
            bzero((char *) &serv_addr, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            bcopy((char *)server->h_addr,
                  (char *)&serv_addr.sin_addr.s_addr,
                  server->h_length);
            serv_addr.sin_port = htons(portno);
            if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
                error("ERROR connecting");
            
            if (x == 0){
                //sending child 1
                cout << "Child 1, sending value: " << process1[1] << " to child process "<< process1[0]
                << endl;
                n = write(sockfd, (char*)&process1, sizeof(process1));
                if (n < 0)
                    error("ERROR reading from socket");
            }
            else if(x==1){
                //sending child 2
                cout << "Child 2, sending value: " << process2[1] << " to child process "<< process2[0]
                << endl;
                n = write(sockfd, (char*)&process2, sizeof(process2));
                if (n < 0)
                    error("ERROR reading from socket");
            }
            else{
                //sending child 3
                cout << "Child 3, sending value: " << process3[1] << " to child process "<< process3[0]
                << endl;
                n = write(sockfd, (char*)&process3, sizeof(process3));
                if (n < 0)
                    error("ERROR reading from socket");
            }
        }
    }
    
    for (x = 0; x<3; x++){
        wait(0);
    }
    
    return 0;
}
