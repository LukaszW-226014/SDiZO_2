#include "Time.h"

Time::Time() {
	PCFreq = 0.0;
	counter = 0;
	tmp = 0;
	kru = false;
	bel = false;
}

Time::~Time() {

}

void Time::timeStart() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "Error!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	counter = li.QuadPart;
}

void Time::timeTake() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	//tmp = (li.QuadPart - counter) / PCFreq;
	if ( kru = true) {
		tmp = 0.75*(li.QuadPart - counter) / PCFreq;
	}
	else if (bel = true) {
		tmp = 1.5*(li.QuadPart - counter) / PCFreq;
	}
	else {
		tmp = (li.QuadPart - counter) / PCFreq;
	}
	cout << "############################################" << endl
		<< "Operacja zajela: " << tmp << " jednostek czasu" << endl;
}