#include <iostream>
#include <opencv2/opencv.hpp>

enum EState
{
    EWork,
    EMove,
    ERotate,
    EForward,
    EFill,
    ESendPush,
    EGive
};

class Detector
{
public:
    bool has_client_exists();
    bool has_delta_distance(float det);
    bool has_delta_angle(float det);
    int get_angle_to_target(float det);
    void update_image();
    void draw_image();
};

class Drink
{
public:
    void fill();
    bool isReady()
    {
        return true;
    }
};

class Order
{
public:

    bool Order::order_exist()
    {
        return true;
    }
    void Order::send_push() {}
    bool Order::glass_is_given()
    {
        return true;
    }
};

class Robot
{
    Detector *det;
    EState state;
    Robot *robot;
    Drink *drink;
    Order *ord;
    bool flag_filling_glass = false;
    void left();
    void right();
    void forward();

public:
    Robot(Robot *r, Order *o, Drink *dr)
    {
        state = EWork;
    }
void Robot::processEvents()
        {
            switch (state)
            {
            case EWork:
                if (ord->order_exist())
                {
                    this->state = EFill;
                }
                break;
            case EFill:
                if (flag_filling_glass)
                {
                    if (drink->isReady())
                    {
                        flag_filling_glass = false;
                        this->state = EMove;
                    }
                }
                else
                {
                    drink->fill();
                    flag_filling_glass = true;
                }
                break;
            case EMove:
                if (det->has_delta_angle(5))
                {
                    this->state = ERotate;
                    break;
                }

                if (det->has_delta_distance(160))
                    this->state = EForward;
                else
                    this->state = ESendPush;

                break;
            case ERotate:
                if (det->get_angle_to_target(5) > 0)
                    robot->left();
                else
                    robot->right();

                this->state = EMove;
                break;
            case EForward:
                robot->forward();
                this->state = EMove;
                break;
            case ESendPush:
                ord->send_push();
                this->state = EGive;
                break;
            case EGive:
                if (ord->glass_is_given())
                    this->state = EWork;
                break;
            }
        }

void Robot::run()
    {
        while (1)
        {
            this->det->update_image();
            this->det->draw_image();
            std::cout << this->state << "\n";

            this->processEvents();

        }
    }
};

int main(int argc, char** argv )
{

}
