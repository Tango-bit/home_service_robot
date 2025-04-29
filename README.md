# home_service_robot

This project implements autonomous mapping, localization, and navigation for a TurtleBot in a simulated environment using Gazebo and ROS Kinetic. It integrates several core ROS packages to allow the robot to map unknown environments, localize itself within the map, and navigate to goal positions.

## Project Overview

The system includes:

- **Simulated Environment** using Gazebo
- **SLAM (Simultaneous Localization and Mapping)** with `gmapping`
- **Localization** with AMCL
- **Path Planning and Navigation** using the ROS Navigation Stack
- **User Interaction Tools** via `turtlebot_interaction`

---

## Packages Used

### `turtlebot`
Provides the base TurtleBot model, control nodes, and sensor configurations. This package is essential for both real and simulated robots.

### `gmapping`
Used for building 2D maps of the environment in real-time. It processes LIDAR data to construct occupancy grids while estimating the robot's position.

###  `turtlebot_interaction`
Includes tools like interactive markers and visual interfaces in RViz for user interaction with the robot. Useful for setting navigation goals and teleoperation.

###  `turtlebot_gazebo`
Enables simulation of the TurtleBot in various virtual environments. It integrates Gazebo with the robot’s sensors and actuators.

### `my_robot`
Custom package containing launch files, robot configurations, and an environment used for the project.

---

## Features

- **Localization**: Using AMCL to estimate the robot’s position on a pre-built map.
- **Mapping**: SLAM implementation with `gmapping` for real-time map creation.
- **Navigation**: The robot plans paths, avoids obstacles, and navigates to user-defined goals.
- **Simulation**: Entire setup runs in Gazebo for testing without hardware.
- **Interaction**: Goal setting and robot monitoring via RViz interactive tools.

---

## Launch Instructions

1. **Test SLAM**
   ```bash
   ./src/scripts/test_slam.sh

2. **Test navigation**
  ```bash
   -/src/scripts/test_navigation.sh

3. **Simulate robot pick and drop**
  ```bash
   -/src/scripts/pick_objects.sh

4. **Add markers to pick and drop location**
  ```bash
   -/src/scripts/add_markers.sh

5. **Simulate virtual object pick and drop**
  ```bash
   -/src/scripts/home_service.sh



