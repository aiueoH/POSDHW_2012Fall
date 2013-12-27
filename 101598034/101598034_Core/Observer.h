#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer
{
public:
	Observer(void);
	virtual ~Observer(void);

	virtual void update();
};

#endif