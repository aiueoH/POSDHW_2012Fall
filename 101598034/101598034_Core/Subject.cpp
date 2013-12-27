#include "Subject.h"

Subject::Subject(void)
{
	_observer = NULL;
}

Subject::~Subject(void)
{
}

void Subject::notify()
{
	if (_observer != NULL)
		_observer->update();
}

void Subject::setObserver(Observer *observer)
{
	_observer = observer;
}