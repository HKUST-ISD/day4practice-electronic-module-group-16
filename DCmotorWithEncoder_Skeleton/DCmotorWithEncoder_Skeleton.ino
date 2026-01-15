/*Change all the ? in the code and add code in ??? to Control the speed of rotation.*/

#define IN1   6  // Replace the ? with the GPIO pin you selected to connect IN1
#define IN2   7   // Replace the ? with the GPIO pin you selected to connect IN2
#define A  4 // Replace the ? with the GPIO pin you selected to connect encoder A
#define B  5 // Replace the ? with the GPIO pin you selected to connect encoder B
#define PWM 15  // Replace the ? with the GPIO pin you selected to output PWM

// encoder output value
int A_data=0;
int B_data=0;

String command;

void setup() {
   // Initialize Serial communication (use 115200 - standard & reliable)
  Serial.begin(115200);


  // Set pin modes
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM, OUTPUT);
  pinMode(A, INPUT);
  pinMode(B, INPUT);

  // Set rotation direction: Forward (CCW) - most common for this setup
  // According to L298N table: IN1 HIGH + IN2 LOW = Forward (CCW)
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Optional: start motor stopped
  analogWrite(PWM, 0);

  Serial.println("=== DC Motor + Encoder Control Ready ===");
  Serial.println("Enter: 0, 25, 50, 75, or 100  then press ENTER");
  Serial.println("Watching encoder A and B in Serial Plotter...");
    delay(500);  // Give time for Serial Monitor to connect
}


void loop() {
  //   Serial.println("=== DC Motor + Encoder Control Ready ===");
  // Serial.println("Enter: 0, 25, 50, 75, or 100  then press ENTER");
  // Serial.println("Watching encoder A and B in Serial Plotter...");
  //   delay(500);  // Give time for Serial Monitor to connect
    // send the duty cycle of PWM to control the speed of DC motor
    if (Serial.available() > 0) {
        command = Serial.readStringUntil('\n'); // Read the incoming command
        command.trim(); // Remove any leading or trailing whitespace
        if (command == "0") {
        // output PWM signals with 0% duty cycle
        analogWrite(PWM,0);  
        delay(300);
        } 
        else if (command == "25") {
        // output PWM signals with 25% duty cycle
        analogWrite(PWM,64);   
        delay(300);
        }
        else if (command == "50") {
        // output PWM signals with 50% duty cycle
        analogWrite(PWM,128);   
        delay(300);
        }
        else if (command == "75") {
        // output PWM signals with 75% duty cycle
        analogWrite(PWM,192);   
        delay(300);
        }
        else if (command == "100") {
        // output PWM signals with 100% duty cycle
        analogWrite(PWM,255);   
        delay(300);
        }
        }
    // Read values of A and B
    A_data=digitalRead(A);
    B_data=digitalRead(B);
    // Plot A B in Serial Plotter
    Serial.print("A:");
    Serial.print(A_data);
    Serial.print(",");
    Serial.print("B:");
    Serial.print(B_data);
    Serial.println("\t"); 
    
}
