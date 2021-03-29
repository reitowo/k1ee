#include "k1ee/time.h"

time_t k1ee::getTimestampMillisecond()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
