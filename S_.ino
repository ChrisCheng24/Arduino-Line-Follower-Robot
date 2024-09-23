// Pin Definitions
int LinputPin = A1;  // Left sensor input pin
int MinputPin = A2;  // Middle sensor input pin
int RinputPin = A3;  // Right sensor input pin

int L = 0;  // Left sensor state (0 or 1)
int M = 0;  // Middle sensor state (0 or 1)
int R = 0;  // Right sensor state (0 or 1)

// Function to smooth sensor readings by averaging over 10 samples
int smooth(int pin) {
    const int numReadings = 10;  // Number of readings to average
    int readings[numReadings];   // Array to store readings
    int readIndex = 0;           // Index for the current reading
    int total = 0;               // Running total of readings
    int average = 0;             // Calculated average

    // Initialize serial communication for debugging
    Serial.begin(9600);

    // Initialize all readings to 0
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
        readings[thisReading] = 0;
    }

    // Take a new reading
    total = total - readings[readIndex];          // Subtract the last reading
    readings[readIndex] = analogRead(pin);        // Read new value from the sensor
    total = total + readings[readIndex];          // Add new reading to the total
    readIndex = readIndex + 1;                    // Move to the next index

    // Wrap around the index if it exceeds the number of readings
    if (readIndex >= numReadings) {
        readIndex = 0;
    }

    // Calculate the average
    average = total / numReadings;

    // Print the average to the serial monitor for debugging
    Serial.println(average);

    // Small delay for stability
    delay(10);
}

// Setup function to initialize pins and motor states
void setup() {
    Serial.begin(9600); // Start serial communication at 9600 baud

    // Set motor control pins as output
    pinMode(5, OUTPUT); 
    pinMode(6, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
  
    // Initialize motors to zero (stopped)
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
}

// Main loop function where the robot control logic resides
void loop() {
    // Print sensor values and states to the serial monitor
    Serial.print(analogRead(LinputPin)); // Left sensor value
    Serial.print("---");
    Serial.print(analogRead(MinputPin)); // Middle sensor value
    Serial.print("---");
    Serial.print(analogRead(RinputPin)); // Right sensor value
    Serial.print("-----");
    Serial.print(L);  // Left state
    Serial.print("---");
    Serial.print(M);  // Middle state
    Serial.print("---");
    Serial.print(R);  // Right state
    Serial.print("---");
    Serial.println(analogRead(A0));  // Obstacle sensor value
  
    // Update sensor states based on readings
    L = (analogRead(LinputPin) > 700) ? 1 : 0;  // Left sensor threshold
    M = (analogRead(MinputPin) > 700) ? 1 : 0;  // Middle sensor threshold
    R = (analogRead(RinputPin) > 700) ? 1 : 0;  // Right sensor threshold
  
    // Control the motor based on sensor states
    if (L == 0 && M == 1 && R == 0) { // Move forward
        analogWrite(5, 0);
        analogWrite(6, 50);
        analogWrite(10, 50);
        analogWrite(11, 0);
    }  
    else if (L == 1 && M == 1 && R == 0) { // Turn slightly left
        analogWrite(5, 0);
        analogWrite(6, 80);
        analogWrite(10, 40);
        analogWrite(11, 0);
    } 
    else if (L == 0 && M == 1 && R == 1) { // Turn slightly right
        analogWrite(5, 0);
        analogWrite(6, 30);
        analogWrite(10, 90);
        analogWrite(11, 0);
    } 
    else if (L == 1 && M == 0 && R == 0) { // Turn sharply left
        analogWrite(5, 0);
        analogWrite(6, 100);
        analogWrite(10, 40);
        analogWrite(11, 0);
    }
    else if (L == 0 && M == 0 && R == 1) { // Turn sharply right
        analogWrite(5, 0);
        analogWrite(6, 30);
        analogWrite(10, 100);
        analogWrite(11, 0);
    }
    else if (L == 1 && M == 1 && R == 1) { // Stop
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(10, 0);
        analogWrite(11, 0);
    }
    else if (L == 1 && M == 0 && R == 1) { // Stop
        analogWrite(5, 0);
        analogWrite(6, 0);
        analogWrite(10, 0);
        analogWrite(11, 0);
    }  

    // Obstacle avoidance logic (A0 sensor reading)
    if (analogRead(A0) > 580) {
        // Execute obstacle avoidance sequence

        // Turn left
        analogWrite(6, 80);   
        analogWrite(5, 0);
        analogWrite(11, 0);
        analogWrite(10, 0);
        delay(600);

        // Move forward
        analogWrite(6, 60);   
        analogWrite(5, 0);
        analogWrite(11, 0);
        analogWrite(10, 60);
        delay(700);

        // Turn right
        analogWrite(6, 0);    
        analogWrite(5, 0);
        analogWrite(11, 0);
        analogWrite(10, 60);
        delay(800);

        // Continue moving forward
        analogWrite(6, 60);   
        analogWrite(5, 0);
        analogWrite(11, 0);
        analogWrite(10, 60);
        delay(1000);

        // Final right turn to avoid obstacle
        analogWrite(6, 0);    
        analogWrite(5, 60);
        analogWrite(11, 0);
        analogWrite(10, 70);
        delay(450);

        // Move forward again
        analogWrite(6, 60);   
        analogWrite(5, 0);
        analogWrite(11, 0);
        analogWrite(10, 60);

        // Re-align with the track
        if (M == 1 && L == 1 && R == 1) {
            analogWrite(6, 60);   
            analogWrite(5, 0);
            analogWrite(11, 0);
            analogWrite(10, 60);
            delay(300);

            // Turn left slightly to align with the track
            analogWrite(6, 60);   
            analogWrite(5, 0);
            analogWrite(11, 60);
            analogWrite(10, 0);
            delay(550);
            
            // Stop motors
            analogWrite(6, 0);
            analogWrite(5, 0);
            analogWrite(11, 0);
            analogWrite(10, 0);
            delay(100);
        }
    }

    // Small delay before the next loop iteration
    delay(50);
}

