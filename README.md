Tracking and control code for the floor robots testbed.  In the process of being updated to use features we've developed for Beluga.

To compile this, you need to first compile [MADTraC](https://github.com/leonard-lab/MADTraC).  If that goes according to plan, you just need to run CMake on the CMakeLists.txt file here.  If you're using the command line, it'll be like this:

    mkdir build && cd build
    cmake ..
    make

