#ifndef UNITTEST_H_
#define UNITTEST_H_

#include "Daemon.h"

class UnitTest : public Daemon
{
	public:
		virtual void activity();

	protected:
		cXMLElement *config;
		cXMLElement *outp;
		void output(std::string s);
		void output(std::stringstream& s);
		virtual void execute() = 0;
		virtual void finish();

	private:
		std::vector<std::string> outMessage;
};

#define	UNIT_TEST(unit)	class unit : public UnitTest\
{\
	public:\
		virtual void execute();\
};\
\
Define_Module_Like(unit, UnitTest);\
\
void unit::execute()

std::string createMessage(int size);
int checkMessage(const char *s, int size);

#endif
