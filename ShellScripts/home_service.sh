

#!/bin/sh

# pick objects

export TURTLEBOT_GAZEBO_WORLD_FILE=$(rospack find home_service)/world/udx_world
export TURTLEBOT_GAZEBO_MAP_FILE=$(rospack find home_service)/world/udx_map.yaml



xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &

sleep 5


xterm -e  "roslaunch turtlebot_gazebo amcl_demo.launch" &

sleep 5

xterm -e "rosrun rviz rviz -d $(rospack find home_service)/Rvizconfig/marker_config.rviz" &

sleep 5

xterm -e  "rosrun add_markers add_markers" &


sleep 5

xterm -e  "rosrun pick_objects pick_objects" &
