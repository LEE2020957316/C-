#include "mouse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
using namespace std;


void Mouse::ReadMouse() {
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
    while (!(isStop))
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
		    x = x;
		    y = y;
		    left = left > 0 ? true : false;
		    middle = middle > 0 ? true : false;
		    right = right > 0 ? true : false;
		    mc->hasData(x,y,left,middle,right);
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
	t = thread([this](){ReadMouse();});
}

void Mouse::stop(){
	isStop = true;
	t.join();
}
