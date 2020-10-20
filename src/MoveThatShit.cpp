#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/TeleportAbsolute.h>
#include <turtlesim/SetPen.h>
#include <iostream>
#include "stdlib.h"
#include "time.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "move_turtle");

    ros::NodeHandle nh;
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
    ros::Rate loop_rate(50);

    geometry_msgs::Twist cmd_vel_message;
    // int count = 0;
    int shapeInput = 1;
    std::cout << "What shape do you want? Type 1 = Circle, 2 = Square, 3 = Star ? ";
    
    float angularVel = 0;
    float linearVel = 2;
    bool negative = false;

   while(ros::ok() && shapeInput != 0){
    std::cin >> shapeInput;   
        switch (shapeInput){  
            case 1: 
                cmd_vel_message.angular.z=1.0;
                cmd_vel_message.linear.x=1.0;
                for(int i=0; i<55; i++){
                    cmd_vel_pub.publish(cmd_vel_message);
                    loop_rate.sleep();  
                }
            break;
            case 2:
                for(int x=0; x < 8; x++)
                {
                    cmd_vel_message.angular.z = angularVel;
                    cmd_vel_message.linear.x = linearVel;
                    for(int i=0; i<49; i++){
                        cmd_vel_pub.publish(cmd_vel_message);
                        loop_rate.sleep();  
                    }
                    if (angularVel == 0)
                    {
                        angularVel = 1.6; 
                        linearVel = 0;
                    }else if(linearVel == 0)
                    {
                        linearVel = 2;
                        angularVel = 0;
                    }
                }
            break;
            case 3:
                negative = true;
                angularVel = 0;
                linearVel = 1;
                for (int i = 0; i < 20; i++)
                {
                    cmd_vel_message.angular.z = angularVel;
                    cmd_vel_message.linear.x = linearVel;
                    for(int i=0; i<66; i++){
                        cmd_vel_pub.publish(cmd_vel_message);
                        loop_rate.sleep();
                    }

                    if (angularVel == 0 && negative)
                    {
                        angularVel = -2; 
                        linearVel = 0;
                        negative = false;
                    }else if(angularVel == 0 && !negative)
                    {
                        angularVel = 1;
                        linearVel = 0;
                        negative = true;
                    }else if(linearVel == 0)
                    {
                        linearVel = 1;
                        angularVel = 0;
                    }
                }
            break;


            break;
            default: ROS_INFO("enter '0' in order to exit"); break;
        }
  }

    return 0;
}