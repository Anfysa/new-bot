#include <string.h>
#include "../rapidjson/include/rapidjson/document.h"

void print(const char* msg);

class JSONCommand
{
private:
	rapidjson::Document command;
	
public:
	JSONCommand(const char* str_json);
	rapidjson::Document* getCommand();
	std::string getCommandType();
	double getAngle();
	double getDistance();
};
