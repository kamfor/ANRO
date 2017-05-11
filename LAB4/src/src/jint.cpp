#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <csignal>

using namespace std;
using namespace KDL;

volatile int exitFlag = 0;

void sigintHandler(int) {
	exitFlag = 1;
}
 
//publishTrajectoryPath

int main(int argc, char **argv){
	
	double x,y,z,t;
	
	ros::init(argc, argv, "jint");
	ros::NodeHandle s; 
	ros::Rate loop_rate(30);
	ros::Publisher pub = s.advertise<geometry_msgs::PoseStamped>("kdl_pose",1);
	ros::Publisher joint = s.advertise<sensor_msgs::JointState>("joint_states",1);  

	double d1,d2,d3;

	s.param<double>("d1",d1,3);
    s.param<double>("d2",d2,3);
	s.param<double>("d3",d3,3);

	sensor_msgs::JointState robotState; 
	robotState.name.push_back("joint1");
	robotState.name.push_back("joint2");
	robotState.name.push_back("joint3");
	robotState.position.resize(robotState.name.size());
	

	d1 = 3;
	d2 = 3;
	d3 = 3;
	
	while(ros::ok()|| !exitFlag){
		
		std::cout<<"enter position and move time x y z t"<<std::endl;  
		std::cin>>x>>y>>z>>t;
		if(x>d1 || x<0 || y>d2 || y<0 || z>d3 || z<0 || t<0)
		{
			std::cout<<"one of parameters is out of limits, enter again"<<std::endl;
			continue;
		}
		else
			std::cout<<"entered data: "<<x<<" "<<y<<" "<<z<<" "<<t<<std::endl; 
		

		robotState.header.stamp = ros::Time::now(); 
		
		robotState.position[0] = x;
		robotState.position[1] = y;
		robotState.position[2] = z;
		
		joint.publish(robotState); 
		loop_rate.sleep();
	}
	
	ros::spin();

	return 0;
}
