# Arduino Line Follower Robot

#### Video Demo: [https://youtube.com/shorts/AMYpM3uG960]

#### Description:

This Arduino-based line follower robot is designed to autonomously follow a line path while avoiding obstacles. The system uses infrared sensors to detect the line and an ultrasonic sensor for obstacle detection, providing a robust and adaptable robotic solution.

Key Features:
1. **Line Following**: The robot uses three infrared sensors (Left, Middle, Right) to detect and follow a line on the ground.
2. **Obstacle Avoidance**: An ultrasonic sensor detects obstacles in the robot's path, triggering an avoidance maneuver.
3. **Smooth Movement**: The code implements a smoothing algorithm for sensor readings to reduce noise and improve stability.
4. **Variable Speed Control**: Different movement scenarios (straight, slight turns, sharp turns) use varying motor speeds for precise control.
5. **Debugging Output**: Serial output helps in monitoring sensor values and robot states for easy debugging.

Technical Implementation:
The project is implemented using Arduino and makes use of several key components:

- Analog pins (A1, A2, A3) for infrared sensors
- Digital pins (5, 6, 10, 11) for motor control
- Analog pin (A0) for the ultrasonic sensor

The main loop continuously reads sensor values, determines the robot's position relative to the line, and adjusts motor speeds accordingly. The obstacle avoidance routine is triggered when an object is detected within a certain range.

Key Functions:
1. `smooth()`: Implements a moving average filter to smooth sensor readings.
2. `setup()`: Initializes pin modes and serial communication.
3. `loop()`: Main program loop handling line following and obstacle avoidance.

Data Processing:
The code processes analog readings from the sensors, converting them to binary values (0 or 1) based on a threshold. This binary representation is used to determine the robot's position and required movement.

Obstacle Avoidance Algorithm:
When an obstacle is detected, the robot executes a series of movements:
1. Turn left
2. Move forward
3. Turn right
4. Move forward
5. Turn right again
6. Move forward
7. Turn left to realign with the line

This sequence allows the robot to navigate around the obstacle and return to its original path.

In conclusion, this Arduino line follower robot demonstrates the use of sensors, motor control, and decision-making algorithms to create an autonomous robot capable of following lines and avoiding obstacles.
