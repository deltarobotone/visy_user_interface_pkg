#!/bin/bash

echo -e "\e[1mupdate vision systen \e[39m \e[0m"

echo -e "\e[32mstep 1/7: update one-easy-protocol \e[39m"
pip3 install --upgrade pip
pip3 install one-easy-protocol

echo -e "\e[32mstep 2/7: update one_easy_protocol_pkg \e[39m"
echo "pull one_easy_protocol_pkg"
cd /home/ubuntu/catkin_ws/src/one_easy_protocol_pkg
git fetch origin
git reset --hard origin/master
git pull

echo -e "\e[32mstep 3/7: update visy_detector_pkg \e[39m"
echo "pull visy_detector_pkg"
cd /home/ubuntu/catkin_ws/src/visy_detector_pkg
git fetch origin
git reset --hard origin/master
git pull

echo -e "\e[32mstep 4/7: update visy_neopixel_pkg \e[39m"
echo "pull visy_neopixel_protocol_pkg"
cd /home/ubuntu/catkin_ws/src/visy_neopixel_pkg
git fetch origin
git reset --hard origin/master
git pull

echo -e "\e[32mstep 5/7: update visy_sorting_app_pkg \e[39m"
echo "pull visy_sorting_app_pkg"
cd /home/ubuntu/catkin_ws/src/visy_sorting_app_pkg
git fetch origin
git reset --hard origin/master
git pull

echo -e "\e[32mstep 6/7: update visy_user_interface_pkg \e[39m"
echo "pull visy_user_interface_pkg"
cd /home/ubuntu/catkin_ws/src/visy_user_interface_pkg
git fetch origin
git reset --hard origin/master
git pull

echo -e "\e[32mstep 7/7: build workspace \e[39m"
cd /home/ubuntu/catkin_ws
catkin build -j1
sleep  3


