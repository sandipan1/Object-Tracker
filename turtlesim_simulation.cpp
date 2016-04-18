# include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>
using namespace std;

ros::Publisher velocity_publisher;
ros::Subscriber pose_subscriber;
ros::Subscriber pose1_subscriber;
turtlesim::Pose turtlesim_pose;
turtlesim::Pose goal_pose;

void move(double speed,double distance,bool isForward);
void poseCallback(const turtlesim::Pose::ConstPtr &pose_message);
//void poseCallback2(const turtlesim::Pose::ConstPtr &pose_message);
void rotate(double theta ,double angvel,bool anticl);
void setDesiredOrientation(double theta);
void movegoal(turtlesim::Pose goal_pose,double distance_tolerance);
void goaldet(double x,double y);



int main(int argc,char **argv){

	ros::init(argc,argv,"robot_cleaner");
	ros::NodeHandle n;
	
	velocity_publisher=n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
	pose_subscriber=n.subscribe("/turtle1/pose",10,poseCallback);
	//pose1_subscriber=n.subscribe("pose",10,poseCallback2);
	cout<<"enter x";
	cin>> goal_pose.x;
	cout << "enter y";
	cin >> goal_pose.y;
	goal_pose.theta=0;
	//move(speed,distance,1); 
//	rotate(2.0,5.0,1);
	//ros::Rate loop_rate(0.5);*/
	movegoal(goal_pose,0.01);
	//loop_rate.sleep();
	//goaldet(x,y);
	//cout <<"\n"<<turtlesim_pose.x<<"\n"<<turtlesim_pose.y<<"\n";
	 ros::spin();
	

 



}

void poseCallback(const turtlesim::Pose::ConstPtr &pose_message){
	turtlesim_pose.x=pose_message->x;
	turtlesim_pose.y=pose_message->y;
	turtlesim_pose.theta=pose_message->theta;
}




/*void move(double speed,double distance,bool isForward){


	geometry_msgs::Twist vel_msg;

	if(isForward)
	vel_msg.linear.x=speed;
	/*else
	vel_msg.linear.x=-abs(speed);*/
/*
	vel_msg.linear.y=0;
	vel_msg.linear.z=0;


	vel_msg.angular.x=0;
	vel_msg.angular.y=0;
	vel_msg.angular.z=0;
	
	//current time
	double t0=ros::Time::now().toSec();
	double current_distance=0;
	ros::Rate loop_rate(10);

	// loop
	do{
	  velocity_publisher.publish(vel_msg);
	  double t1=ros::Time::now().toSec();
	current_distance=speed*(t1-t0);
	ros::spinOnce();	
	loop_rate.sleep();
	}while(current_distance<distance);

	vel_msg.linear.x=0;
	velocity_publisher.publish(vel_msg);
	

}*/
/*void rotate(double theta ,double angvel,bool anticl){
	geometry_msgs::Twist vel_msg;

	vel_msg.angular.x=0;
	vel_msg.angular.y=0;
	if(anticl)
	vel_msg.angular.z=abs(angvel);
	
	vel_msg.linear.y=0;
	vel_msg.linear.z=0;
	vel_msg.linear.x=0;

	double t0=ros::Time::now().toSec();
	double current_theta=0;
	ros::Rate loop_rate(10);
	do{
	  velocity_publisher.publish(vel_msg);
	  double t1=ros::Time::now().toSec();
	current_theta=angvel*(t1-t0);
	ros::spinOnce();	
	loop_rate.sleep();
	}while(current_theta<theta);

	vel_msg.angular.z=0;
	velocity_publisher.publish(vel_msg);}
*/
/*void goaldet(double x,double y){
	double alpha=atan2(y-turtlesim_pose.y,x-turtlesim_pose.x);
		rotate(	alpha-turtlesim_pose.theta,5,1);
		move(5,sqrt((x-turtlesim_pose.x)*(x-turtlesim_pose.x)+(y-turtlesim_pose.y)*(y-turtlesim_pose.y)),1);}

*/


void movegoal(turtlesim::Pose goal_pose,double distance_tolerance){
	
	geometry_msgs::Twist vel_msg;
	
	ros::Rate loop_rate(10);
	do{

	vel_msg.linear.x=2*sqrt((goal_pose.x-turtlesim_pose.x)*(goal_pose.x-turtlesim_pose.x)+(goal_pose.y-turtlesim_pose.y)*(goal_pose.y-turtlesim_pose.y));;
	

	vel_msg.linear.y=0;
	vel_msg.linear.z=0;

	cout<<vel_msg.angular.z;
	vel_msg.angular.x=0;
	vel_msg.angular.y=0;
	vel_msg.angular.z=4*(atan2(goal_pose.y-turtlesim_pose.y,goal_pose.x-turtlesim_pose.x)-turtlesim_pose.theta);
	velocity_publisher.publish(vel_msg);
	
	
	ros::spinOnce();	
	loop_rate.sleep();

}while(sqrt((goal_pose.x-turtlesim_pose.x)*(goal_pose.x-turtlesim_pose.x)+(goal_pose.y-turtlesim_pose.y)*(goal_pose.y-turtlesim_pose.y))>0.1);
	
	vel_msg.linear.x=0;
	vel_msg.angular.z=0;
	velocity_publisher.publish(vel_msg);
	
	
}

/*void poseCallback2(const turtlesim::Pose::ConstPtr &pose_message){
	goal_pose.x=pose_message->x;
	goal_pose.y=pose_message->y;
	goal_pose.theta=pose_message->theta;}

*/







	

	



