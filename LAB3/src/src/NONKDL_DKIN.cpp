#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>

float finalX, finalY, finalZ;
ros::Publisher pub; 

void jointCallback(const sensor_msgs::JointState & msg)
{
	ROS_INFO("poseX: [%f]", msg.position[0]);
	ROS_INFO("poseY: [%f]", msg.position[1]);
	ROS_INFO("poseZ: [%f]", msg.position[2]);
	ros::NodeHandle n;
	
	geometry_msgs::PoseStamped poseStamped;

	
		
	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();
	

	finalX = msg.position[0] ;
	finalY = msg.position[1] ;
	finalZ = msg.position[2] ;
	
	poseStamped.pose.position.x=finalZ;
	poseStamped.pose.position.y=finalY;
	poseStamped.pose.position.z=finalX;

	poseStamped.pose.orientation.x=0;
	poseStamped.pose.orientation.y=0;
	poseStamped.pose.orientation.z=0;
	poseStamped.pose.orientation.w=0; 
	pub.publish(poseStamped);
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "NONKDL_DKIN");
	ros::NodeHandle s; 
	ros::Rate loop_rate(30);
	pub = s.advertise<geometry_msgs::PoseStamped>("nonkdl_pose",1);
	ros::Subscriber sub=s.subscribe("joint_states", 100, jointCallback);
	
	ros::spin();

	return 0;
}
