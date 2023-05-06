#include "TCP.h"
#include "GPIO.h"
#include "JSON.h"

class Robot
{
private:
	Motor* motorA;
	Motor* motorB;
	
	JSONCommand* cmd;
	
	
public:
	Robot(Motor* ma, Motor* mb);
	
	int run();
	
	void forward(const double& val);
	void backward(const double& val);
	void turn_left(const double& val);
	void turn_right(const double& val);
};

Robot::Robot(Motor* ma, Motor* mb) : cmdrcv(te), motorA(ma), motorB(mb)
{
	print("Подключено");
}

int Robot::run()
{
	int exit_code = 0;
	
	print("Жду команды");
	exit_code += cmdrcv->Receive(cmd);
	
	if (exit_code == 0)
	{
		print("Выполняю команду");

		if (cmd->getCommandType() == "movement")
		{
			std::string mt = cmd->getMoveType(); 
			if (mt == "forward") forward(cmd->getDistance());
			else if (mt == "backward") backward(cmd->getDistance());
			else if (mt == "left") turn_left(cmd->getAngle());
			else if (mt == "right") turn_right(cmd->getAngle());
			else print("Не знаю такой команды");
		}
	}
	else print("Что-то пошло не так...");
	
	char tmp_code = static_cast<char>('0' + exit_code);
	cmdrcv->Send(&tmp_code);
	return exit_code;
}

void Robot::forward(const double& val)
{
	print("Вперед");
	motorA->run(0);
	motorB->run(0);
	usleep(static_cast<useconds_t>(1000*val));
	motorA->stop();
	motorB->stop();
	
	usleep(static_cast<useconds_t>(1000*200));
}

void Robot::backward(const double& val)
{
	print("Назад");
	motorA->run(1);
	motorB->run(1);
	usleep(static_cast<useconds_t>(1000*val));
	motorA->stop();
	motorB->stop();
	
	usleep(static_cast<useconds_t>(1000*200));
}

void Robot::turn_left(const double& val)
{
	print("Налево");
	motorA->run(0);
	motorB->run(1);
	usleep(static_cast<useconds_t>(1000*val));
	motorA->stop();
	motorB->stop();
	
	usleep(static_cast<useconds_t>(1000*200));
}

void Robot::turn_right(const double& val)
{
	print("Направо");
	motorA->run(1);
	motorB->run(0);
	usleep(static_cast<useconds_t>(1000*val));
	motorA->stop();
	motorB->stop();
	
	usleep(static_cast<useconds_t>(1000*200));
}

