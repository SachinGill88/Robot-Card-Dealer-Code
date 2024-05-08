# Robot Card Dealer 
## Software Description 
## Function

1. **configure_sensors()**: Initializes and configures the sensors required for the robot's operation, including ultrasonic sensors for obstacle detection, and color sensors to detect the starting position.

2. **emergency_stop()**: Implements an emergency stop mechanism triggered by the ultrasonic sensor if an obstacle is detected in the robot's path. This ensures the safety of both the robot and its surroundings.

3. **drive()**: Controls the movement of the robot, allowing it to navigate to predefined locations within its environment using a combination of motor control and sensor feedback. This description covers various functions, including rotation, and simple straight motion. 

4. **deal_cards**(int players): Determines the number of players and deals an appropriate number of cards to each player. This function takes into account factors such as the number of available cards and the desired distribution among players (user inputs number of cards, as seen in linked video).

5. **drive_to_color** (int colour) Drives the robot to the center of the card table (indicated by a color of tape placed there), ensuring optimal positioning for card dealing.

6. **remainder_dispense**(int players, int cards): Handles the dispensing of remaining cards if the total number of cards does not evenly divide among players. This function ensures fair distribution and efficient use of available cards.

7. **exit_code**(int players, float distance, int remainder): Robot determines how to cleanly escape the playing area, without contacting any of the piles of cards.
