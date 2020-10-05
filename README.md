# visy_user_interface_pkg

Qt based user interface for vision system (visy) display on backside. Controls apps and shows live and manipulated images.

![CI](https://github.com/deltarobotone/visy_user_interface_pkg/workflows/CI/badge.svg?branch=master)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/be05858eeff6450380d40f157e511fc9)](https://www.codacy.com/gh/deltarobotone/visy_user_interface_pkg?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=deltarobotone/visy_user_interface_pkg&amp;utm_campaign=Badge_Grade)

## Nodes

### data_exchange_thread

Ros node connects ROS communication mechanisms via qt signals/slots. Implemented as seperate thread to support a non blocking user interface.

#### Service Clients

##### start_sorting (visy_sorting_app_pkg/StartSorting)

Client to start sorting application for metal chips including Delta-Robot One, conveyor system and vision system.

##### stop_sorting (visy_sorting_app_pkg/StopSorting)

Client to stop sorting application.

##### select_image (visy_detector_pkg/SelectImage)

Client to change image at processing state via buttons on user interface to select displayed image processing state.

#### Subscribed topics

##### visy_image (sensor_msgs/CompressedImage)

Subscribe image at the end of a detection loop published by conveyor detector or metal chip detetctor.

##### grasp_data (visy_sorting_app_pkg/GraspData)

Subscribe grasp data including the time until grasp, colour of chip, number of detetcted chips, latency, velocity, last chip position, etc.

