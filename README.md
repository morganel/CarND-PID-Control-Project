# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

[//]: # (Image References)

[low-p]: videos_hyperparams/low-p.gif "Low P"
[high-p]: videos_hyperparams/high-p.gif "High P"
[low-i]: videos_hyperparams/low-i.gif "Low I"
[high-i]: videos_hyperparams/high-i.gif "High I"
[low-d]: videos_hyperparams/low-d.gif "Low D"
[high-d]: videos_hyperparams/high-d.gif "High D"

## Reflection

## Effect of each of the P, I, D components:
### Effect of P:
P is called the proportional term and is proportional to the error. When P is too high, the car oscillates too much, overshoots and the system becomes unstable. However, when P is too small, the car is not responsive enough.

|Low P (0.01)                                  |  High P (10.0) |
|:-------------------------------------------------------:|:-------------------------------------------------------:|
|![Low P][low-p] |  ![High P][high-p]|


### Effect of I:
I is the integral term and is proportional to the total accumulated error over time. If the car has a bias, like having a bias towards the right, the integral term will take care of that. When I is too low, it does not correct the bias enough and the car will keep drifting. In the video below we added a drift of +0.5 steering angle to see what that a low I does not compensate it. When I is too high, the car oscillates and the system unstable.

|Low I (0.0)                                 |  High I (0.01) |
|:-------------------------------------------------------:|:-------------------------------------------------------:|
|![Low I][low-i] |  ![High I][high-i]|


### Effect of D:
D is the derivative term and is proportional to the derivative of the error. It prevents the car from overshooting and oscillating around the target trajectory. It helps with stability. If D is too low, the car will oscillate since the derivative term won't be able to correct the effects of P and I. If D is too high, it corrects too much and the successive steering angles vary a lot. The car can hardly move, as seen in the video below.

|Low D (0.0)                                 |  High D (1000.0) |
|:-------------------------------------------------------:|:-------------------------------------------------------:|
|![Low D][low-d] |  ![High D][high-d]|


## How the final hyperparameters were chosen:
The final hyperparameters were tuned manually at throttle = 0.3.
1. Tune P while I = 0 and D = 0:
At P = 0.01, the car was not reactive enough. 
At P = 0.1, it was better but still not good enough
Finally, at P = 0.5, the car was reacting properly but was oscillating too much.
2. Tune D while P = 0.5 and I = 0:
Start with D = 0.1, then 1.0, 5.0 (car oscillates but does not go out of the lanes, for the first half of the lap), 10.0 (almost does not go out of the lanes) and finally 20.0 (car does not touch the lane but still makes some hars left/right movements)
3. Lower P from 0.5 to 0.3 to lessen the left/right oscillations
4. Tune I, using P = 0.3 and D = 20.0
The car can drive safely with I = 0. However, it seems like the car has a tendency to go to the right too much. The first values of I that we tried were too high (I = 0.1 and 0.01) and the car was going out of the road at the beginning of the lap. With I = 0.001, the car seems to drive safely in the center of the road. We did not want to have a value of I that is too high since it uses the total accumulated error, it could have a negative impact after driving for a long time.
The final values chosen are: P = 0.3, I = 0.001 and D = 20.0


## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
