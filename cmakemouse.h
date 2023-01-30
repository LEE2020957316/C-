#include <iostream>

struct Mousecallback {
public:
	virtual void hasData(int x, int y, bool left, bool middle, bool right) = 0;
};

struct MyMouseCallback : Mousecallback {
public:
	void hasData(int x, int y, bool left, bool middle, bool right);
};


class Mouse {
public:
	int x;
	int y;
	bool left;
	bool middle;
	bool right;
public:
	Mousecallback* mc;
public:
	void registerCallback(Mousecallback* mc);
	void start();
	void stop();
};
