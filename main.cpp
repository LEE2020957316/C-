#include "mouse.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>
#include <thread>
using namespace std;

static const int nt = 1;
thread t;



int main()
{
	Mousecallback* callback = new MyMouseCallback;
	Mouse mouse(false);
	mouse.registerCallback(callback);
	mouse.start();

	t.detach();


	cout << "Mouse Listening started. input 'q' to stop Listening thread." << endl;
    char s1,s2;
    while (cin >> s1) {
        if (s1 == 'q' || s1 == 'Q') {
            mouse.stop();
            cout << "input any char to exit Main thread..." << endl;
            cin >> s2;
            if (s2 != '\0')break;
        }else{
            
        }
    }


    cout << "Main thread exit." << endl;
	return 0;
}
