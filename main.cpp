/*
 * wallaby-estop - main.cpp
 *
 *  Created on: Jan 16, 2016
 *      Author: Joshua Southerland
 */

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h>
#include <fcntl.h>
#include <cstdlib>
#include <string>
#include <unistd.h>

int main(int argc, char ** argv)
{
    const std::string event_path = "/dev/input/event1";
    std::cout << "Wallaby E-Stop" << std::endl;

    int fd;

    if ((fd = open(event_path.c_str(), O_RDONLY)) == -1) std::cout << "Could not open " << event_path << std::endl;

    std::cout << "Monitoring " << event_path << std::endl;

    while(true)
    {
        std::cout << "Checking"<< event_path << std::endl;
        struct input_event event[64];
        int ret;
        if ((ret = read(fd, event, sizeof(struct input_event) * 64)) < sizeof(struct input_event))
        {
            std::cerr << "Error reading from device" << std::endl;
        }
        else
        {
            std::cout << "Event value = " << event[0].value << std::endl;
            if (event[0].value == 1)
            {
                std::cout << "Stopping user botball programs\n" << std::endl;
                system("killall -s 2 botball_user_program"); // send SIGINT (2)
            }
        }

        usleep(100000);
    }

    return 0;
}

