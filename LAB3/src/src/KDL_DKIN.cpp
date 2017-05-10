#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/frames.hpp>

using namespace std;
using namespace KDL;

float t1, t2, t3;
ros::Publisher pub; 

void jointCallback(const sensor_msgs::JointState & msg)
{
	ROS_INFO("poseX: [%f]", msg.position[0]);
	ROS_INFO("poseY: [%f]", msg.position[1]);
	ROS_INFO("poseZ: [%f]", msg.position[2]);
	ros::NodeHandle n;
	
	geometry_msgs::PoseStamped poseStamped;

//łańcuch KDL
	KDL::Chain chain;
	t1 = msg.position[0] ;
	t2 = msg.position[1] ;
	t3 = msg.position[2] ;	
	
	chain.addSegment(Segment(Joint(Joint::None),Frame(Frame::DH(0,0,0,0))));
	chain.addSegment(Segment(Joint(Joint::RotZ),Frame(Frame::DH(0,0,1.0,0))));
	chain.addSegment(Segment(Joint(Joint::None),Frame(Frame::DH(0,-M_PI/2.0,0,0))));
	chain.addSegment(Segment(Joint(Joint::RotZ),Frame(Frame::DH(1,0,0,-M_PI/2.0))));
	chain.addSegment(Segment(Joint(Joint::RotZ),Frame(Frame::DH(0,0,0,0))));

//solver
	ChainFkSolverPos_recursive solver(chain);
	JntArray q(chain.getNrOfJoints());
	KDL::Frame F_results;
	
	q(0)=t1;
	q(1)=t2;
	q(2)=t3;
       	
	solver.JntToCart(q,F_results);

	poseStamped.pose.position.x=F_results.p.data[0];
	poseStamped.pose.position.y=F_results.p.data[1];
	poseStamped.pose.position.z=F_results.p.data[2];

	double x, y, z, w;
	F_results.M.GetQuaternion(x, y, z, w);

	poseStamped.pose.orientation.x=x;
	poseStamped.pose.orientation.y=y;
	poseStamped.pose.orientation.z=z;
	poseStamped.pose.orientation.w=w; 
	pub.publish(poseStamped);
		
	poseStamped.header.frame_id="base_link";
	poseStamped.header.stamp = ros::Time::now();
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "KDL_DKIN");
	ros::NodeHandle s; 
	ros::Rate loop_rate(30);

			pub = s.advertise<geometry_msgs::PoseStamped>("kdl_pose",1);
	ros::Subscriber sub = s.subscribe("joint_states", 100, jointCallback);
	 
	ros::spin();

	return 0;
}
