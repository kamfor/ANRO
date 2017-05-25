#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Quaternion.h>
#include "lab5/oint_control_srv.h"
#include <math.h>
#include <tf/LinearMath/Matrix3x3.h>
#include <iostream>

#define LOOP_RATE 10

using namespace std;

double x, y, z, ox, oy, oz, t;

ros::Publisher oint_pub;
ros::Publisher path_pub;

double calculatePoly(double x,double ox, double ta, double t){
  
  double result; 
  result  = ((-2*(x-ox))/(t*t*t))*(ta*ta*ta) + ((3*(x-ox))/(t*t))*(ta*ta) + ox; 
  return result; 
}

bool interpolatePose(lab5::oint_control_srv::Request& request, lab5::oint_control_srv::Response& response){

    ROS_INFO("Params position: x=%f, y=%f, z=%f, time=%f ", (double)request.x, (double)request.y, (double)request.z, (double)request.time);
    ROS_INFO("interpolation type: %s", request.type.c_str());

    ros::Rate loop_rate(LOOP_RATE);

    int steps; 

    geometry_msgs::PoseStamped oint_pose;
    geometry_msgs::PoseStamped pose_stamped;
    oint_pose.header.frame_id="base_link";

    nav_msgs::Path path; 
    path.header.frame_id="base_link";

	if(request.time <= 0){
		response.status = "Wrong time";
        return false;
    }

    x = request.x;
    y = request.y; 
    z = request.z;
    t = request.time; 

    steps = (int)(t*10); 

    if(request.type == "linear"){

      ROS_INFO("linear interpolation started");

      oint_pose.pose.position.x=ox;
      oint_pose.pose.position.y=oy;
      oint_pose.pose.position.z=oz;


      for(int i=0; i<steps; i++){

        oint_pose.header.stamp = ros::Time::now();
        path.header.stamp = ros::Time::now(); 
    
        oint_pose.pose.position.x += (x-ox)/(10.0*t);
        oint_pose.pose.position.y += (y-oy)/(10.0*t);
        oint_pose.pose.position.z += (z-oz)/(10.0*t);

        pose_stamped.header.stamp = ros::Time::now();
        pose_stamped.pose.position.x = oint_pose.pose.position.x;
        pose_stamped.pose.position.y = oint_pose.pose.position.y;
        pose_stamped.pose.position.z = oint_pose.pose.position.z;
        path.poses.push_back(pose_stamped);

        oint_pub.publish(oint_pose);
        path_pub.publish(path);
        loop_rate.sleep();

      }
    
      ox = oint_pose.pose.position.x; 
      oy = oint_pose.pose.position.y;
      oz = oint_pose.pose.position.z;

      response.status = "Sucess";

      ROS_INFO("linear interpolation done");

      return true; 

    }else if(request.type == "poly"){

      ROS_INFO("polynomian interpolation started");

      double dt = t/steps; 
      double t_act = 0; 

      for(int i=0; i<steps; i++){ 

        oint_pose.header.stamp = ros::Time::now();
        path.header.stamp = ros::Time::now(); 
    
        oint_pose.pose.position.x =calculatePoly(x, ox, t_act, t);
        oint_pose.pose.position.y =calculatePoly(y, oy, t_act, t);
        oint_pose.pose.position.z =calculatePoly(z, oz, t_act, t);

        t_act+=dt; 

        pose_stamped.header.stamp = ros::Time::now();
        pose_stamped.pose.position.x = oint_pose.pose.position.x;
        pose_stamped.pose.position.y = oint_pose.pose.position.y;
        pose_stamped.pose.position.z = oint_pose.pose.position.z;
        path.poses.push_back(pose_stamped);

        oint_pub.publish(oint_pose);
        path_pub.publish(path);
        loop_rate.sleep();
      }

      response.status = "Sucess";
    
      ox = oint_pose.pose.position.x; 
      oy = oint_pose.pose.position.y;
      oz = oint_pose.pose.position.z;

      ROS_INFO("polynomian interpolation done");

      return true; 
    }
    else{

      response.status = "Wrong type";
      return false;
    }
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "oint");
  ros::NodeHandle n;
  
  oint_pub=n.advertise<geometry_msgs::PoseStamped>("pose_stamped", 1);
  path_pub=n.advertise<nav_msgs::Path>("path",1);
  
  geometry_msgs::PoseStamped oint_pose;
  oint_pose.header.frame_id="base_link";
  oint_pose.header.stamp = ros::Time::now();
  oint_pose.pose.position.x = 1;
  oint_pose.pose.position.y = 1;
  oint_pose.pose.position.z = 1;

  oint_pub.publish(oint_pose);

  ros::ServiceServer service = n.advertiseService("oint_control_srv", interpolatePose);

  ROS_INFO("READY :)");
  ros::spin();
  return 0;
}
