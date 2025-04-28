#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <cmath>

// Global variable to store latest odometry
nav_msgs::Odometry latest_odom;
bool odom_received = false;

// Callback function to update global odometry
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    latest_odom = *msg;
    odom_received = true;
}

// Function to check if robot has reached target
uint8_t is_target_reached(double target_x, double target_y)
{	
    if (!odom_received) return 0;
    double dx = std::abs(latest_odom.pose.pose.position.x - target_x);
    double dy = std::abs(latest_odom.pose.pose.position.y - target_y);
    ROS_INFO("dx = %f", dx);
    ROS_INFO("dy = %f", dy);
    return (dx < 1 && dy < 1) ? 1 : 0;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "add_markers");
    ros::NodeHandle n;
    ros::Rate r(1);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    ros::Subscriber odom_sub = n.subscribe("odom", 10, odomCallback);

    double x_pickup = 4.0;
    double y_pickup = 3.0;
    double x_dropoff = 7.0;
    double y_dropoff = -4.0;

    visualization_msgs::Marker marker;
    marker.header.frame_id = "/map"; // More typical than "/my_frame"
    marker.ns = "basic_shapes";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration();

    // Publish pickup marker
    marker.pose.position.x = x_pickup;
    marker.pose.position.y = y_pickup;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.header.stamp = ros::Time::now();
    while(marker_pub.getNumSubscribers()<1)
    {
      if(!ros::ok())
      {
	return 0;
      } 
      ROS_WARN_ONCE("Please create a subscriber to marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    ROS_INFO("Published pickup marker");

    //Wait until pickup reached
    while (ros::ok() && !is_target_reached(x_pickup, y_pickup))
    {
        ros::spinOnce();
       r.sleep();
     }

    ROS_INFO("Pickup location reached!");
    ros::Duration(5.0).sleep();

    // Delete pickup marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Deleted pickup marker");

    ros::Duration(1.0).sleep();

    // Publish dropoff marker
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = x_dropoff;
    marker.pose.position.y = y_dropoff;
    marker.header.stamp = ros::Time::now();
    marker_pub.publish(marker);
    ROS_INFO("Published dropoff marker");

    // Wait until dropoff reached
    while (ros::ok() && !is_target_reached(x_dropoff, y_dropoff))
     {
        ros::spinOnce();
        r.sleep();
     }

    ROS_INFO("Dropoff location reached!");
    ros::Duration(5.0).sleep();

    // Delete dropoff marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Deleted dropoff marker");

    return 0;
}

