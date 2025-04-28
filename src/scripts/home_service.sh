#!/bin/sh
xterm  -e  "source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 5
xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(pwd)/src/worlds/apartment.world" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(pwd)/src/maps/map.yaml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 10
xterm -e "roslaunch pick_objects pick_objects.launch" &
sleep 2
xterm -e "roslaunch add_markers add_markers_odom.launch" &

