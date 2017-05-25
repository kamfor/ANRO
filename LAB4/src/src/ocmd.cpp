#include "ros/ros.h"
#include "lab4/oint_control_srv.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  double x, y, z, rx, ry, rz, t;
  string type;
  ros::init(argc, argv, "oint_server");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<lab4::oint_control_srv>("oint_control_srv");
  while(ros::ok())
  {
    lab4::oint_control_srv srv;

    ROS_INFO("Enter joint values, time and interpolation type: [double double double double string(linear or poly)] and press enter");
    
    cin>>x>>y>>z>>rx>>ry>>rz>>t>>type;
    srv.request.x = x;
    srv.request.y = y;
    srv.request.z = z;
    srv.request.rx = rx;
    srv.request.ry = ry;
    srv.request.rz = rz;
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