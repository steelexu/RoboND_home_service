#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


#define PICKUP_X 2.5
#define PICKUP_Y -2.48

#define DROPOFF_X -0.2
#define DROPOFF_Y -0.9


typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pick_objects");
    // Spin a thread
    MoveBaseClient ac("move_base", true);

    // Wait for the action server to come up
    ROS_INFO("Waiting for the move_base action server");
    ac.waitForServer(ros::Duration(5));

    ROS_INFO("Connected to move_base server");

    move_base_msgs::MoveBaseGoal goal;

    // Send goal pose
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = PICKUP_X;
    goal.target_pose.pose.position.y = PICKUP_Y;

    goal.target_pose.pose.orientation.x = 0.0;
    goal.target_pose.pose.orientation.y = 0.0;
    goal.target_pose.pose.orientation.z = 0.0;
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending pickup goal");
    ac.sendGoal(goal);

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Excellent! Your robot has reached the pickup position.");
        ros::Duration(5.0).sleep();
        //TODO reach the second goal
        }
    else
        ROS_INFO("The robot failed to reach the pickup position");

    
    
    ros::Duration(5.0).sleep();
    // Wait for the action server to come up
    ROS_INFO("Waiting for the move_base action server");
    ac.waitForServer(ros::Duration(5));

    //--------------------drop off goal
    move_base_msgs::MoveBaseGoal goal_drop;
    // Send goal pose
    goal_drop.target_pose.header.frame_id = "map";
    goal_drop.target_pose.header.stamp = ros::Time::now();

    // Define a position and orientation for the robot to reach
    goal_drop.target_pose.pose.position.x = DROPOFF_X;
    goal_drop.target_pose.pose.position.y = DROPOFF_Y;

    goal_drop.target_pose.pose.orientation.x = 0.0;
    goal_drop.target_pose.pose.orientation.y = 0.0;
    goal_drop.target_pose.pose.orientation.z = 0.0;
    goal_drop.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending drop off goal");
    ac.sendGoal(goal_drop);

    ac.waitForResult();

    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Excellent! Your robot has reached the drop off goal position.");
        ros::Duration(5.0).sleep();
        //TODO reach the second goal
        }
    else
        ROS_INFO("The robot failed to reach the drop off goal position");


    return 0;
}
