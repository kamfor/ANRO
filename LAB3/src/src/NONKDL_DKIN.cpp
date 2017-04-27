#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>

float finalX, finalY, finalZ;

void jointCallback(const sensor_msgs::JointState & msg)
{
	ROS_INFO("pose: [%f]", msg.position[1]);
	

	
	/*finalX = 2 - msg.position[0];
	finalY = 2 - msg.position[1];
	finalZ = 2 - msg.position[2];
	
	poseStamped.pose.position.x=finalX;
	poseStamped.pose.position.y=finalY;
	poseStamped.pose.position.z=finalZ;

	poseStamped.pose.orientation.x=1;
	poseStamped.pose.orientation.y=1;
	poseStamped.pose.orientation.z=1;*/
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "NONKDL_DKIN");
	ros::NodeHandle s; 

	ros::Subscriber sub=s.subscribe("joint_states", 100, jointCallback);
	
	ros::Rate loop_rate(30);
	ros::NodeHandle n;
	ros::Publisher pub=n.advertise<geometry_msgs::PoseStamped>("base_link",1);
	geometry_msgs::PoseStamped poseStamped;

	
		while(ros::ok()){
		poseStamped.header.frame_id="/frame";
		poseStamped.header.stamp = ros::Time::now();
	
		poseStamped.pose.position.x=2;
		poseStamped.pose.position.y=3;
		poseStamped.pose.position.z=4;
	
		poseStamped.pose.orientation.x=1;
		poseStamped.pose.orientation.y=1;
		poseStamped.pose.orientation.z=1;
		poseStamped.pose.orientation.w=1;

	
		pub.publish(poseStamped);

		loop_rate.sleep();
		}
	

	ros::spin();

	return 0;
}
