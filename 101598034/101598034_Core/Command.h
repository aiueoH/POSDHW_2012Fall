#ifndef COMMAND_H_
#define COMMAND_H_

class Command
{
public:
	Command(void);
	virtual ~Command(void) = 0;

	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

#endif
