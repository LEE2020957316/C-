#include "mouse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
using namespace std;


struct MyMouseCallback : Mousecallback {
public:
	void hasData(int x, int y, bool left, bool middle, bool right) {
		if (x == 0 && y == 0 && !left && !middle && !right)return;
		cout << "x=" << x << "  y=" << y << endl;
		cout << "left=" << left << "  middle="<< middle << "  right=" << right << endl;
	}
};

int main()
{
	MyMouseCallback callback;
	Mouse mouse(false);
	mouse.registerCallback(&callback);
	mouse.start();

	cout << "Mouse Listening started. input 'q' to stop Listening thread." << endl;

	while (getc(stdin) != 'q');

	mouse.stop();
	cout << "Main thread exit." << endl;
	return 0;
}
