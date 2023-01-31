#include "mouse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
using namespace std;


static const int nt = 1;
thread t;


Mouse::Mouse(bool isStop){
    this->isStop = false;
}


int ReadMouse(Mouse* mouse) {
    int fd, bytes;
    unsigned char data[3];
    const char* pDevice = "/dev/input/mice";
    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if (fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }
    int left, middle, right;
    signed char x, y;
    while (1)
    {
        if(mouse->isStop){
            cout << "Mouse Listening thread exit." << endl;
            return 0;
        }
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));
        if (bytes > 0)
        {
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;
            x = data[1];
            y = data[2];
            mouse->x = x;
            mouse->y = y;
            mouse->left = left > 0 ? true : false;
            mouse->middle = middle > 0 ? true : false;
            mouse->right = right > 0 ? true : false;
            mouse->mc->hasData(x,y,left,middle,right);
        }
    }
}

// a demo derived from Mousecallback which prints out the coordinates.
void MyMouseCallback::hasData(int x, int y, bool left, bool middle, bool right) {
	if (x == 0 && y == 0 && !left && !middle && !right)return;
	cout << "x=" << x << "  y=" << y << endl;
	cout << "left=" << left << "  middle="<< middle << "  right=" << right << endl;
}

void Mouse::registerCallback(Mousecallback* mc){
	this->mc = mc;
}
void Mouse::start(){
	t = thread(ReadMouse, this);
}

void Mouse::stop(){
    this->isStop = true;
	
}


