#!/bin/bash
echo -e "\e[1mupdate vision systen \e[39m \e[0m"
echo -e "\e[32mstep 1: update one-easy-protocol \e[39m"
pip3 install --upgrade pip
pip3 install one-easy-protocol
echo -e "\e[32mstep 2: update one_easy_protocol_pkg \e[39m"
echo -e "\e[32mstep 3: update visy_detector_pkg \e[39m"
echo -e "\e[32mstep 4: update visy_neopixel_pkg \e[39m"
echo -e "\e[32mstep 5: update visy_sorting_app_pkg \e[39m"
echo -e "\e[32mstep 5: update visy_user_interface_pkg \e[39m"
echo -e "\e[32mstep 6: build workspace \e[39m"
echo -e "\e[32mstep 7: reboot system \e[39m"
sleep  5


