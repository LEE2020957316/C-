#include <iostream>

struct Mousecallback {
public:
	virtual void hasData(int x, int y, bool left, bool middle, bool right) = 0;
};


class Mouse {
public:
	int x;
	int y;
	bool left;
	bool middle;
	bool right;
    	bool isStop; 
public:
	Mousecallback* mc;
public:
    	Mouse(/* args */) {}
    	Mouse(bool isStop);
	void registerCallback(Mousecallback* mc);
	void start();
	void stop();
   	 ~Mouse() {}
};
