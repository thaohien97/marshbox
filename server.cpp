//
//  main.cpp
//  COSC3360_hw2
//
//  Created by Hien Nguyen on 3/27/19.
//  Copyright © 2019 Hien Nguyen. All rights reserved.
//

// A simple server in the internet domain using TCP
// The port n1mber is passed as an argument

// Please note this is a C program
// It compiles without warnings with gcc
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bitset>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

void error(string msg)
{
    cout << msg;
    exit(1);
}

struct info
{
    int EM[12];
    int walsh[4];
};

int main(int argc, char *argv[])
{
    info storing[3];
    int w1[4] = {-1, 1, -1, 1};
    int w2[4] = {-1, -1, 1, 1};
    int w3[4] = {-1, 1, 1, -1};
    string WalshArr[3] = {"-1 1 -1 1", "-1 -1 1 1", "-1 1 1 -1"};
    
    int sockfd, newsockfd, portno, clilen;
    
    struct sockaddr_in serv_addr, cli_addr;
    
    int n;
    
    int process1[2] = {0};
    int process2[2] = {0};
    int process3[2] = {0};
    int sockArr[3];
    
    string bi1, bi2, bi3;
    int arr1[3], arr2[3], arr3[3];
    int EM1[12] = {0};
    int EM2[12] = {0};
    int EM3[12] = {0};
    int EM[12] = {0};
    // int process_arr[3] = {0};
    int processArr[3];
    
    if (argc < 2)
    {
        cout << "ERROR, no port provided\n";
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    int k;
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    
    for (int i = 0; i < 3; i++)
    {
        
        if (i == 0)
        {
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
            sockArr[i] = newsockfd;
            if (newsockfd < 0)
                error("ERROR on accept");
            bzero((int *)&process1, sizeof(process1));
            n = read(newsockfd, (int *)&process1, sizeof(process1));
            processArr[i] = process1[0];
            if (n < 0)
                error("ERROR reading from socket");
            cout << "Here is the value from child 1: Value = " << process1[0] << ", Destination = " << process1[1] << endl;
        }
        
        if (i == 1)
        {
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
            sockArr[i] = newsockfd;
            
            if (newsockfd < 0)
                error("ERROR on accept");
            bzero((int *)process2, sizeof(process2));
            n = read(newsockfd, (int *)&process2, sizeof(process2));
            processArr[i] = process2[0];
            if (n < 0)
                error("ERROR reading from socket");
            
            cout << "Here is the value from child 2: Value = " << process2[0] << ", Destination = " << process2[1] << endl;
        }
        else if (i == 2)
        {
            newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
            sockArr[i] = newsockfd;
            
            if (newsockfd < 0)
                error("ERROR on accept");
            bzero((int *)process3, sizeof(process3));
            n = read(newsockfd, (int *)&process3, sizeof(process3));
            processArr[i] = process3[0];
            if (n < 0)
                error("ERROR reading from socket");
            
            cout << "Here is the value from child 3: Value = " << process3[0] << ", Destination = " << process3[1] << endl;
        }
        
        // n = write(newsockfd,"I got your message",18);
        //if (n < 0) error("ERROR writing to socket");
        // return 0;
    }
    
    bi1 = bitset<3>(process1[1]).to_string();
    bi2 = bitset<3>(process2[1]).to_string();
    bi3 = bitset<3>(process3[1]).to_string();
    
    for (int i = 0; i < 3; i++)
    {
        if (bi1[i] == '0')
            arr1[i] = -1;
        else
            arr1[i] = 1;
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (bi2[i] == '0')
            arr2[i] = -1;
        else
            arr2[i] = 1;
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (bi3[i] == '0')
            arr3[i] = -1;
        else
            arr3[i] = 1;
    }
    
    int indx1 = 0;
    int indx2 = 0;
    int indx3 = 0;
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            EM1[indx1] = arr1[i] * w1[j];
            indx1++;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            EM2[indx2] = arr2[i] * w2[j];
            indx2++;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            EM3[indx3] = arr3[i] * w3[j];
            indx3++;
        }
    }
    
    for (int i = 0; i < 12; i++)
    {
        EM[i] = EM1[i] + EM2[i] + EM3[i];
    }
    
    //storing walsh code in struct info
    for (int i = 0; i < 3; i++)
    {
        for (int a = 0; a < 4; a++)
        {
            if (i == 0)
                storing[i].walsh[a] = w1[a];
            else if (i == 1)
                storing[i].walsh[a] = w2[a];
            else
                storing[i].walsh[a] = w3[a];
        }
    }
    
    //storing EM in struct info
    for (int i = 0; i < 3; i++)
    {
        for (int b = 0; b < 12; b++)
        {
            if (i == 0)
                storing[i].EM[b] = EM1[b];
            else if (i == 1)
                storing[i].EM[b] = EM2[b];
            else
                storing[i].EM[b] = EM3[b];
        }
    }
    
    int key, j;
    string wKey;
    for (int i = 1; i < 3; i++)
    {
        key = processArr[i];
        wKey = WalshArr[i];
        j = i - 1;
        while (j >= 0 && processArr[j] > key)
        {
            processArr[j + 1] = processArr[j];
            WalshArr[j + 1] = WalshArr[j];
            j--;
        }
        processArr[j + 1] = key;
        WalshArr[j + 1] = wKey;
    }
    // for (auto h : WalshArr)
    // {
    //     cout << h << " ";
    // }
    // cout << endl;
    int send1[16] = {0};
    int send2[16] = {0};
    int send3[16] = {0};
    stringstream ss;
    int a, b, c, d;
    for (int i = 0; i < 3; i++)
    {
        string w = WalshArr[i];
        stringstream ss(w);
        ss >> a >> b >> c >> d;
        for (int j = 0; j < 4; j++)
        {
            if (i == 0)
            {
                send1[0] = a;
                send1[1] = b;
                send1[2] = c;
                send1[3] = d;
            }
            else if (i == 1)
            {
                send2[0] = a;
                send2[1] = b;
                send2[2] = c;
                send2[3] = d;
            }
            else if (i == 2)
            {
                send3[0] = a;
                send3[1] = b;
                send3[2] = c;
                send3[3] = d;
            }
        }
    }
    
    // for (auto h : send1)
    // {
    //     cout << h << " ";
    // }
    // cout << endl;
    int o = 0;
    for (int j = 4; j < 16 && o < 12; j++, o++)
    {
        send1[j] = EM[o];
        send2[j] = EM[o];
        send3[j] = EM[o];
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            n = write(sockArr[i], (int *)&send1, sizeof(send1));
            sleep(1);
        }
        if (i == 1)
        {
            n = write(sockArr[i], (int *)&send2, sizeof(send2));
            sleep(1);
        }
        if (i == 2)
        {
            n = write(sockArr[i], (int *)&send3, sizeof(send3));
            sleep(1);
        }
        close(sockfd);
    }
    return 0;
}
