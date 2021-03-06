#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <nav_msgs/Path.h>
#include <visualization_msgs/Marker.h>
#include "lab4/jint_control_srv.h"
#include <math.h>
#include <kdl/chain.hpp>
#include <iostream>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>
#include <csignal>
#include <cstring>


#define LOOP_RATE 10

volatile int exitFlag = 0;

using namespace std; 

ros::Publisher joint;
ros::Publisher pub;

double x,y,z,t;
double ox, oy, oz; 
double dx, dy, dz; 
int steps; 
string type; 

uint path_no = 0;


void sigintHandler(int) {
	exitFlag = 1;
}

double calculatePoly(double x,double ox, double ta, double t){
	
	double result; 
	result  = ((-2*(x-ox))/(t*t*t))*(ta*ta*ta) + ((3*(x-ox))/(t*t))*(ta*ta) + ox; 
	return result; 
}


bool interoplateJoints(lab4::jint_control_srv::Request& request, lab4::jint_control_srv::Response& response){

	  	ROS_INFO("Params: x=%f, y=%f, z=%f, time=%f ", (double)request.x, (double)request.y, (double)request.z, (double)request.time);
		ROS_INFO("interpolation type: %s", request.type.c_str());

		ros::Rate loop_rate(LOOP_RATE);

		sensor_msgs::JointState robotState; 
		robotState.name.push_back("joint1");
		robotState.name.push_back("joint2");
		robotState.name.push_back("joint3");
		robotState.position.resize(robotState.name.size());

		geometry_msgs::PoseStamped pose_stamped;
		pose_stamped.header.frame_id="base_link";

		nav_msgs::Path path;
		path.header.frame_id="base_link";


		if(request.x>3 || request.x<0 || request.y>3 || request.y<0 || request.z>3 || request.z<0){
			response.status = "Wrong joints";
			return true;		
		}

	  	if(request.time <= 0){
		    response.status = "Wrong time";
		    return true;
		}

		x = request.x;
		y = request.y; 
		z = request.z;
		t = request.time; 

		steps = (int)(t*10); 

		if(request.type == "linear"){

			ROS_INFO("linear interpolation started");

			robotState.position[0] = ox; 
			robotState.position[1] = oy; 
			robotState.position[2] = oz; 

			for(int i=0; i<steps; i++){
				robotState.header.stamp = ros::Time::now();
				path.header.stamp = ros::Time::now(); 
		
				robotState.position[0] += (x-ox)/(10.0*t);
				robotState.position[1] += (y-oy)/(10.0*t);
				robotState.position[2] += (z-oz)/(10.0*t);

				pose_stamped.header.stamp = ros::Time::now();
				pose_stamped.pose.position.z = robotState.position[0];
  				pose_stamped.pose.position.y = robotState.position[1];
				pose_stamped.pose.position.x = robotState.position[2];
				path.poses.push_back(pose_stamped);

				joint.publish(robotState);
				pub.publish(path);
				loop_rate.sleep();
			}
		
			ox = robotState.position[0]; 
			oy = robotState.position[1];
			oz = robotState.position[2];

			response.status = "Sucess";

			ROS_INFO("linear interpolation done");

			return true; 

		}else if(request.type == "poly"){

			ROS_INFO("polynomian interpolation started");

			double dt = t/steps; 
			double t_act = 0; 

			for(int i=0; i<steps; i++){ 
				robotState.header.stamp = ros::Time::now();
				path.header.stamp = ros::Time::now(); 
		
				robotState.position[0] =calculatePoly(x, ox, t_act, t);
				robotState.position[1] =calculatePoly(y, oy, t_act, t);
				robotState.position[2] =calculatePoly(z, oz, t_act, t);
				t_act+=dt; 

				pose_stamped.header.stamp = ros::Time::now();
				pose_stamped.pose.position.z = robotState.position[0];
  				pose_stamped.pose.position.y = robotState.position[1];
				pose_stamped.pose.position.x = robotState.position[2];
				path.poses.push_back(pose_stamped);


				joint.publish(robotState); 
				pub.publish(path);
				loop_rate.sleep();
			}

			response.status = "Sucess";
		
			ox = robotState.position[0]; 
			oy = robotState.position[1];
			oz = robotState.position[2];

			ROS_INFO("polynomian interpolation done");

			return true; 
		}
		else{

			response.status = "Wrong type";
			return true;
		}
	
}
 

int main(int argc, char **argv){
	

	ros::init(argc, argv, "jint");
	ros::NodeHandle s; 
	pub = s.advertise<nav_msgs::Path>("path",1);
	joint = s.advertise<sensor_msgs::JointState>("joint_states",1);  

	sensor_msgs::JointState robotState; 
	robotState.name.push_back("joint1");
	robotState.name.push_back("joint2");
	robotState.name.push_back("joint3");
	robotState.position.resize(robotState.name.size());
	robotState.header.stamp = ros::Time::now(); 
	robotState.position[0] = 0;
	robotState.position[1] = 0;
	robotState.position[2] = 0;
	joint.publish(robotState);


	ros::ServiceServer service = s.advertiseService("jint_control_srv", interoplateJoints);

	ROS_INFO("READY :)");

	ros::spin();	

	return 0;
}
