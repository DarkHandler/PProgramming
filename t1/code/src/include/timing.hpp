#ifndef __TIMING_CLASS__
#define __TIMING_CLASS__ 

#include <chrono>

class timing
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;

public:
	timing();

	void start();
	void stop();
	double elapsed();

};

timing::timing()
{

}

void timing::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}
void timing::stop()
{
	endTime = std::chrono::high_resolution_clock::now();
}

double timing::elapsed()
{
	auto e = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	return(e.count());
}


#endif
