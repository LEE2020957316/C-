#include "mouse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
using namespace std;


void Mouse::ReadMouse(Mouse* mouse) {
    int fd, bytes;
    unsigned char data[3];
    const char* pDevice = "/dev/input/mice";
    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if (fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return;
    }
    int left, middle, right;
    signed char x, y;
    while (!(mouse->isStop))
    {
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

Mouse::Mouse(bool isStop){
	isStop = false;
    
}

void Mouse::registerCallback(Mousecallback* _mc){
	mc = _mc;
}

void Mouse::start(){
	t = thread([this](Mouse* m){ReadMouse(m);}, this);
}

void Mouse::stop(){
	isStop = true;
	t.join();
}
