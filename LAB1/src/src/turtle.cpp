#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }

class RobotDriver
{
private:
  //! The node handle we'll be using
  ros::NodeHandle nh_;
  //! We will be publishing to the "/base_controller/command" topic to issue commands
  ros::Publisher cmd_vel_pub_;
  bool loop; 

public:
  //! ROS node initialization
  RobotDriver(ros::NodeHandle &nh)
  {
    nh_ = nh;
    //set up the publisher for the cmd_vel topic
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
  }

  //! Loop forever while sending drive commands based on keyboard input
  bool driveKeyboard()
  {
    std::cout << "Type a command and then press enter.  "
      "Use 'w' to move forward, 'a' to turn left, "
      "'d' to turn right, 's' to turn back,";
      "'p' to exit.\n";
      
    //we will be sending commands of type "twist"
    geometry_msgs::Twist base_cmd;

    loop  = true; 
    char c;
    base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;
    while(nh_.ok()&&loop){

      c = getch();
    
      switch (c){
		case 'w':
			base_cmd.linear.x = 1.0;
			base_cmd.angular.z = 0;
		break;
		case 'a':
			base_cmd.angular.z = 0.75;
			base_cmd.linear.x = 0; 
		break;
		case 's':
			base_cmd.linear.x = -0.25;
			base_cmd.angular.z = 0;
		break;
		case 'd':
			base_cmd.angular.z = -0.75;
			base_cmd.linear.x = 0;  
		break;
		case 'p':
			loop  = false; 
		break; 
		default:
			base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;
		break; 
	}
	
	c='x'; 


      //publish the assembled command
      cmd_vel_pub_.publish(base_cmd);
    }
    return true;
  }

};

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "turtle");
  ros::NodeHandle nh;

  RobotDriver driver(nh);
  driver.driveKeyboard();
}
