#!/bin/sh

# wall following

export TURTLEBOT_GAZEBO_WORLD_FILE=$(rospack find home_service)/world/udx_world

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 5


xterm -e  "roslaunch turtlebot_gazebo gmapping_demo.launch" &

sleep 5

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &

sleep 5

xterm -e  "rosrun wall_follower wall_follower" &
