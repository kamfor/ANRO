#include "ros/ros.h"
#include "lab4/jint_control_srv.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  double x, y, z, t;
  string type;
  ros::init(argc, argv, "jint_server");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<lab4::jint_control_srv>("jint_control_srv");
  while(ros::ok())
  {
    lab4::jint_control_srv srv;

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
    ros::spinOnce();
  }
  return 0;
}