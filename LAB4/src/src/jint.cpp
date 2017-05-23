#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <csignal>
#include <cstring>

using namespace std;
using namespace KDL;

volatile int exitFlag = 0;

void sigintHandler(int) {
	exitFlag = 1;
}

double calculate_poly(double x,double ox, double ta, double t){
	
	double result; 
	result  = ((-2*(x-ox))/(ta*ta*ta))*(t*t*t) + ((3*(x-ox))/(ta*ta))*(t*t) + ox; 
	return result; 
}
 
//publishTrajectoryPath

int main(int argc, char **argv){
	
	double x,y,z,t;
	double ox, oy, oz; 
	double dx, dy, dz; 
	string type; 
	
	ros::init(argc, argv, "jint");
	ros::NodeHandle s; 
	ros::Rate loop_rate(10);
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
	ox=0; 
	oy=0; 
	oz=0; 

	robotState.header.stamp = ros::Time::now(); 	
	robotState.position[0] = ox;
	robotState.position[1] = oy;
	robotState.position[2] = oz;
	joint.publish(robotState); 
	
	while(ros::ok()|| !exitFlag){

		
		ROS_INFO("enter position and move time and type x y z t");  
		std::cin>>x>>y>>z>>t>>type;
		if(x>d1 || x<0 || y>d2 || y<0 || z>d3 || z<0 || t<0)
		{
			ROS_INFO("one of parameters is out of limits, enter again");
			continue;
		}
		else
			ROS_INFO("entered data: x=%f, y=%f, z=%f, t=%f",x,y,z,t); 


		if(!type.compare("linear")){

			dx = (x-ox)/(10*t); 
			dy = (y-oy)/(10*t); 
			dz = (z-oz)/(10*t); 

			for(int i=0; i<(int)10*t; i++){
				robotState.header.stamp = ros::Time::now(); 
		
				robotState.position[0] +=dx;
				robotState.position[1] +=dy;
				robotState.position[2] +=dz;

				joint.publish(robotState); 
				loop_rate.sleep();
			}
		
			ox = robotState.position[0]; 
			oy = robotState.position[1];
			oz = robotState.position[2];
		}else{

			for(int i=0; i<(int)100*t; i++){ //optimize using dt 
				robotState.header.stamp = ros::Time::now(); 
		
				robotState.position[0] =calculate_poly(x, ox, (double)(i/100), t);
				robotState.position[1] =calculate_poly(y, oy, (double)(i/100), t);
				robotState.position[2] =calculate_poly(z, oz, (double)(i/100), t);

				joint.publish(robotState); 
				loop_rate.sleep();
			}
		
			ox = robotState.position[0]; 
			oy = robotState.position[1];
			oz = robotState.position[2];
		}
	
		loop_rate.sleep();
	}
	
	ros::spin();

	return 0;
}
