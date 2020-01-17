#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <queue>
#include <vector>

using namespace std;

class car {
public:
    string license_plate;
    char direct;
    int time_;
    
    car(string a, char b, int c) {
        license_plate = a;
        direct = b;
        time_ = c;
    }
};

int check(vector<car> &vect, char direction) { //check if the direction in the vector or not
    for (size_t i = 0; i < vect.size(); i++) {
        if (vect.at(i).direct == direction)
            return true;
    }
    return false;
}


char change_direction(char s) {
    if (s == 'N')
        return 'E';
    if (s == 'E')
        return 'S';
    if (s == 'S')
        return 'W';
    else if (s == 'W')
        return 'N';
    else
        return '\0';
}
int dir_count(vector<car> &vect, char direction_){   //count how many time each direction appears in the vector
    int count = 0;
    for(size_t i = 0; i < vect.size(); i++){
        if(vect.at(i).direct == direction_)
            count = count + 1;
    }
    return count;
}

int main()
{
    //initializes variables
    vector<car> vect;
    queue<car> que;
    char initial_dir, current_dir, dir;
    pid_t pid;
    int max_cars, rem_cars = 0, numcar = 0, time_;
    string license_plate;
    int n = 0;
    int e = 0;
    int s = 0;
    int w = 0;
    
    
    cin >> initial_dir;
    cin >> max_cars;
    
    while (cin >> license_plate >> dir >> time_) {
        
        car c = car(license_plate, dir, time_);
        
        vect.push_back(c);
        
        // if (dir == 'N')
        //     n++;
        // else if (dir == 'E')
        //     e++;
        // else if (dir == 'S')
        //     s++;
        // else
        //     w++;
        
        rem_cars++;
        
    }
    // for(auto i =0; i<vect.size(); i++){
    //     cout << vect.at(i).license << endl;
    // }
    
    current_dir = initial_dir;
    
    while (!vect.empty()) {
        for (auto i = 0; i < vect.size(); i++) {
        comeToFront:
            if (check(vect, current_dir)) {
                
                if (vect.at(i).direct == current_dir) {
                    //cout << dir_count(vect, current_dir) <<endl;
                    if (max_cars == 1 || dir_count(vect, current_dir) == 1) {   //if max car = 1 or direction count = 1
                        //pushing all the variables in the vector into to the queue
                        que.push(vect.at(i));
                        vect.erase(vect.begin() + i);
                        current_dir = change_direction(current_dir);
                        numcar = 0;
                        //n--;
                        break;
                        
                    }
                    else if (max_cars > 1) {
                        que.push(vect.at(i));
                        vect.erase(vect.begin() + i);
                        numcar++;
                        if (numcar == max_cars) {
                            current_dir = change_direction(current_dir);
                            numcar = 0;
                            break;
                        }
                        else {
                            goto comeToFront;
                        }
                    }
                }
            }
            else {
                current_dir = change_direction(current_dir);
                goto comeToFront;    //going back to the beginning of the loop and run it until vector is empty
            }
        }
        
    }
    
    
    char d1 = que.front().direct;
    char d2;
    while (!que.empty()) {
        if (d1 != d2) {
            char d1 = que.front().direct;
            
            if (d1 == 'E') {
                cout << "Current direction: Eastbound" << endl;
            }
            else if (d1 == 'S') {
                cout << "Current direction: Southbound" << endl;
            }
            else if (d1 == 'N') {
                cout << "Current direction: Northbound" << endl;
            }
            else if (d1 == 'W') {
                cout << "Current direction: Westbound" << endl;
            }
        }
        
        if ((pid = fork()) == 0) {
            cout << "Car " << que.front().license_plate << " is using the intersection for " <<
            que.front().time_ << "sec(s)." << endl;
            sleep(que.front().time_);
            _exit(0);
            //break;
        }
        else {
            d1 = que.front().direct;
            wait(0);
            que.pop();
            if (!que.empty())
                d2 = que.front().direct;
        }
        
    }
    
    return 0;
}

