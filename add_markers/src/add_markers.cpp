#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


#include <cmath>

#define PICKUP_X 2.5
#define PICKUP_Y -2.48

#define DROPOFF_X -0.2
#define DROPOFF_Y -0.9

#define TOLERANCE 0.6

#define TO_PICKUP 0
#define TO_DROPOFF 1
#define DONE 2

int turtle_status = 0;


ros::Publisher marker_pub;
visualization_msgs::Marker marker;




void odom_callback(const nav_msgs::Odometry::ConstPtr& nav_msg) {
  float turtle_x = nav_msg->pose.pose.position.x;
  float turtle_y = nav_msg->pose.pose.position.y;
  

  
  if (turtle_status==TO_PICKUP) {
    float dx = turtle_x - PICKUP_X;
    float dy = turtle_y - PICKUP_Y;
    float maker_dist = std::sqrt(dx*dx+dy*dy);
    if (maker_dist < TOLERANCE ) {
		ROS_INFO("Picking up object");
		//hide it
		marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);

        ros::Duration(5.0).sleep();
        turtle_status=TO_DROPOFF;
        return;
    }
  } else if (turtle_status==TO_DROPOFF) {
    float dx = turtle_x - DROPOFF_X;
    float dy = turtle_y - DROPOFF_Y;
    float maker_dist = std::sqrt(dx*dx+dy*dy);
    //ROS_INFO("Dropping off far dist = %f", maker_dist);
    if (maker_dist < TOLERANCE ) {
		ROS_INFO("Drop Off object");
		//show it
        marker.pose.position.x = DROPOFF_X;
        marker.pose.position.y = DROPOFF_Y;
        
		marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);

        ros::Duration(5.0).sleep();
        turtle_status=DONE;
        return;
    }
  }

}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;


  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);




    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;
    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = PICKUP_X;
    marker.pose.position.y = PICKUP_Y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
    
    sleep(1);
    //ros::Duration(1.0).sleep();
    marker_pub.publish(marker);
    
    ros::Subscriber odom_subscriber = n.subscribe("/odom", 10, odom_callback);
    
  ros::Rate r(1);
  while (ros::ok())
  {
    ros::spinOnce();

    r.sleep();
  }
  
  return 0;
  
}
