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

JSONCommand::JSONCommand(const char* str_json)
{
	command.Parse(str_json);
}

rapidjson::Document* JSONCommand::getCommand()
{
	return &command;
}

std::string JSONCommand::getCommandType()
{
	return command["CommandType"].GetString();
}

std::string JSONCommand::getMoveType()
{
	return command["MoveType"].GetString();
}


double JSONCommand::getAngle()
{
	return command["Angle"].GetDouble();
}

double JSONCommand::getDistance()
{
	return command["Distance"].GetDouble();
}
