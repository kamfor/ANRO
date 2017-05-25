#include "ros/ros.h"
#include "lab5/oint_control_srv.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  double x, y, z, t;
  string type;
  ros::init(argc, argv, "oint_server");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<lab5::oint_control_srv>("oint_control_srv");
  int mode; 
  while(ros::ok())
  {
    lab5::oint_control_srv srv;


    
    ROS_INFO("Select mode: 1 - position, 2 - trajectory");
    
    cin>>mode; 
    
    if(mode==1){
		
		ROS_INFO("Enter joint values, time and interpolation type: [double double double double string(linear or poly)] and press enter");
    
		cin>>x>>y>>z>>t>>type;
		srv.request.x = x;
		srv.request.y = y;
		srv.request.z = z;
		srv.request.time = t;
		srv.request.type = type;
		if(client.call(srv)){
		  ROS_INFO("Service called, %s", srv.response.status.c_str());
		}else{
		  ROS_ERROR("Failed to call service.");
		}
	}
	else if(mode==2){
		
		ROS_INFO("Enter corner values, time and interpolation type: [double double double double string(linear or poly)] and press enter");
		
		cin>>x>>y>>z>>t>>type;
				
		srv.request.x = x;
		srv.request.y = y;
		srv.request.z = 0;
		srv.request.time = t/4;
		srv.request.type = type;
		if(client.call(srv)){
		  ROS_INFO("Service called, %s", srv.response.status.c_str());
		}else{
		  ROS_ERROR("Failed to call service.");
		}
		
		srv.request.x = x;
		srv.request.y = y;
		srv.request.z = z;
		srv.request.time = t/4;
		srv.request.type = type;
		if(client.call(srv)){
		  ROS_INFO("Service called, %s", srv.response.status.c_str());
		}else{
		  ROS_ERROR("Failed to call service.");
		}
		
		srv.request.x = 0;
		srv.request.y = 0;
		srv.request.z = z;
		srv.request.time = t/4;
		srv.request.type = type;
		if(client.call(srv)){
		  ROS_INFO("Service called, %s", srv.response.status.c_str());
		}else{
		  ROS_ERROR("Failed to call service.");
		}
		
		srv.request.x = 0;
		srv.request.y = 0;
		srv.request.z = 0;
		srv.request.time = t/4;
		srv.request.type = type;
		if(client.call(srv)){
		  ROS_INFO("Service called, %s", srv.response.status.c_str());
		}else{
		  ROS_ERROR("Failed to call service.");
		}
	}
    ros::spinOnce();
  }
  return 0;
}
