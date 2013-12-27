#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "Observer.h"

#include <string>

using namespace std;

class Subject
{
private:
	Observer *_observer;

protected:
	void notify();

public:
	Subject(void);
	virtual ~Subject(void);

	void setObserver(Observer *observer);
};

#endif