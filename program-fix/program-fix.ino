  const int startButtonPin = 12;
  const int stopSwitchPin = 2;
  const int rightSwitchPin = 4; 
  const int pwmPin = 5; //to 'enable' pin on L298N motor control module
  const int IN_1 = 7;  //to Input 1 on L298N
  const int IN_2 = 8;  //to Input 2 on L298N
  int startButton;
  int stopSwitch;
  int rightSwitch;
  bool startButtonState = false;
  bool stopSwitchState = false;
  bool rightSwitchState = false;
  bool start = false;
  bool bluetoothStart = false;

  void setup () {
    Serial.begin(9600);
    pinMode(startButtonPin, INPUT_PULLUP);
    pinMode(stopSwitchPin, INPUT_PULLUP);
    pinMode(rightSwitchPin, INPUT_PULLUP);
    pinMode(pwmPin, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
  }
  
  void loop () {
  // read serial from bluetooth module ------------------
    char bluetoothOut = Serial.read();
    Serial.println(bluetoothStart);
  
  // read all output pin --------------------------------
    startButton = digitalRead(startButtonPin);
    stopSwitch = digitalRead(stopSwitchPin);
    rightSwitch = digitalRead(rightSwitchPin);
  
  // check all output pin value -------------------------
    if (startButton == HIGH || bluetoothOut == '1'){
      start = true;
      setState(true, false, false);
    }else if(stopSwitch == LOW){
      setState(false, true, false);
    }else if(rightSwitch == LOW){
      start = false;   
      setState(false, false, true);
    }
  
  // check all state --------------------------------------
    if(startButtonState){
      runMotor();
    }else if(stopSwitchState && !start){
      pauseMotor();
    }else if(rightSwitchState){
      rightMotor();
    }
     
  }

// function for set state run motor ----------------------------------------

  void setState(bool button, bool stopSwitch, bool rightSwitch){
    startButtonState = button;
    stopSwitchState = stopSwitch;
    rightSwitchState = rightSwitch;
  }
  void runMotor() {
    digitalWrite (IN_1, HIGH);     //start motor
    digitalWrite (IN_2, LOW);
    digitalWrite (pwmPin, 255);    //run motor full speed
  }
  
  void rightMotor() {
    digitalWrite (IN_1, LOW);    
    digitalWrite (IN_2, HIGH);     //right motor
    digitalWrite (pwmPin, 255);    //run motor full speed
  }
  
  void pauseMotor() {
    digitalWrite (IN_1, LOW);       //stop motor
    digitalWrite (IN_2, LOW);       //stop motor
  }
