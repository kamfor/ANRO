#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <math.h>
#include <iostream>
#include <csignal>
#include <cstring>


#define LOOP_RATE 10

volatile int exitFlag = 0;

using namespace std; 

ros::Publisher joint;
ros::Subscriber pose;

double d1,d2,d3;

void sigintHandler(int) {
	exitFlag = 1;
}


void jointCallback(const geometry_msgs::PoseStamped & msg){
	
	if(msg.pose.position.x>d1 || msg.pose.position.x<0 || msg.pose.position.y>d2 || msg.pose.position.y<0 || msg.pose.position.z>d3 || msg.pose.position.z<0){
      ROS_INFO("Wrong joints - position unreachable");
      return;    
    }
	
	sensor_msgs::JointState robotState; 
	robotState.name.push_back("joint1");
	robotState.name.push_back("joint2");
	robotState.name.push_back("joint3");
	robotState.position.resize(robotState.name.size());
	robotState.header.stamp = ros::Time::now(); 
	robotState.position[0] = msg.pose.position.z;
	robotState.position[1] = msg.pose.position.y;
	robotState.position[2] = msg.pose.position.x;
	ROS_INFO("linear interpolation started %f %f %f",msg.pose.position.x, msg.pose.position.y, msg.pose.position.z);
	joint.publish(robotState);
}
 

int main(int argc, char **argv){
	
	ros::init(argc, argv, "jint");
	ros::NodeHandle s; 
	joint = s.advertise<sensor_msgs::JointState>("joint_states",1);  
	pose = s.subscribe("pose_stamped", 100, jointCallback);
	
	s.param<double>("d1",d1,3);
	s.param<double>("d2",d2,3);
	s.param<double>("d3",d3,3);

	ros::spin();	

	return 0;
}
