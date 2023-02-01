
#include <iostream>
#include <thread>

struct Mousecallback {
public:
	virtual void hasData(int x, int y, bool left, bool middle, bool right) = 0;
};

class Mouse {
private:
	int x;
	int y;
	bool left;
	bool middle;
	bool right;
    	bool isStop;
	std::thread t;
	void ReadMouse(Mouse* mouse);
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
