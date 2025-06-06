//  Pin Assignments 
const int RED_LED        = 13;
const int GREEN_LED      = 11;
const int YELLOW_LED     = 12;
const int TEMP_SENSOR    = A1;   
const int LIGHT_SENSOR   = A0;
const int BUZZER         = 9;
const int IR_RECEIVER    = 7;
const int IR_TRANSMITTER = 4;
const int DISARM_BUTTON  = A4;
const int ARM_BUTTON     = A5;

//  Global Variables 
int tempVal = 0;
int lightVal = 0;
int armButtonState = 0;
int disarmButtonState = 0;

const int DELAY_TIME = 2000;

//  Thresholds 
const int LIGHT_THRESHOLD = 100;
const int TEMP_THRESHOLD = 500;
const int ANALOG_HIGH = 1023;
const int ANALOG_LOW = 0;

void setup() {
  Serial.begin(9600);

  // Set LED and buzzer pins as OUTPUT
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Set sensor and button pins as INPUT
  pinMode(TEMP_SENSOR, INPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(IR_RECEIVER, INPUT);
  pinMode(IR_TRANSMITTER, OUTPUT);

  pinMode(DISARM_BUTTON, INPUT);
  pinMode(ARM_BUTTON, INPUT);

  // Optionally start IR transmission tone 
  // tone(IR_TRANSMITTER, 38000); 
}

void loop() {
  readInputs();

  if (isArmedCondition()) {
    handleArmedState();
  }

  if (isDisarmedCondition()) {
    handleDisarmedState();
  }

  if (isAlertCondition()) {
    triggerAlert();
  }
}

//  Input Handling 
void readInputs() {
  disarmButtonState = analogRead(DISARM_BUTTON);
  armButtonState = analogRead(ARM_BUTTON);
  lightVal = analogRead(LIGHT_SENSOR);
  tempVal = analogRead(TEMP_SENSOR);
}

//  Conditions 
bool isArmedCondition() {
  return armButtonState == ANALOG_HIGH && lightVal <= LIGHT_THRESHOLD;
}

bool isDisarmedCondition() {
  return armButtonState == ANALOG_LOW || disarmButtonState == ANALOG_HIGH;
}

bool isAlertCondition() {
  return armButtonState == ANALOG_HIGH && 
        (lightVal >= LIGHT_THRESHOLD || tempVal < TEMP_THRESHOLD);
}

//  Actions 
void handleArmedState() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  Serial.println("System Armed");
  Serial.print("Temperature: ");
  Serial.println(tempVal);
  Serial.print("Light: ");
  Serial.println(lightVal);
  delay(DELAY_TIME);
}

void handleDisarmedState() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("System Disarmed");
}

void triggerAlert() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  digitalWrite(YELLOW_LED, HIGH);
  tone(BUZZER, 2500);
  delay(250);

  digitalWrite(YELLOW_LED, LOW);
  noTone(BUZZER);
  delay(250);
}

