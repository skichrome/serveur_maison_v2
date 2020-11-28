#ifndef _RUNNABLE_h
#define _RUNNABLE_h

class Runnable
{
private:
	static Runnable* headRunnable;
	Runnable* nextRunnable;

protected:
	virtual void setup() = 0;
	virtual void loop() = 0;

public:
	Runnable() {
		nextRunnable = headRunnable;
		headRunnable = this;
	}

	static void setupAll();
	static void loopAll();
};

#endif