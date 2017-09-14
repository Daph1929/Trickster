#define CHARGE_PIN 2
#define DISCHARGE_PIN 3
#define INPUT_PIN 4
#define LED_PIN 5

#define LOOP_LIMIT 10 // You may need to modify this.
#define DEBOUNCE_TIME 100 // You may need to modify this.

unsigned long debounceTimer;
unsigned char switchState;
unsigned char ledOn = 0;

void setup()
{
  // Set up the switch pins.
  pinMode(CHARGE_PIN, OUTPUT);
  pinMode(DISCHARGE_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT);
  
  // Set up the LED pin.
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  unsigned char loopCount = 0;
  
  digitalWrite(CHARGE_PIN, HIGH); // CHarge the circuit.
  
  while(!digitalRead(INPUT_PIN)) // Count the loops until the input pin is charged.
  {
    loopCount++;
  }
  
  if(loopCount > LOOP_LIMIT) // Someone is touching the switch.
  {
    unsigned long currentTime = millis();
    
    // Leave 100 ms from when the input pin goes low before
    // registering a switch. This acts as a crude but effective
    // debounce mechanism.
    if((currentTime - debounceTimer) > DEBOUNCE_TIME)
    {
      switchState = 1;
    }
    debounceTimer = currentTime;
  }
  else
  {
    switchState = 0;
  }
  
  // Toggle the LED if the switch is activated.
  if(switchState)
  {
    ledOn = !ledOn;
    digitalWrite(LED_PIN, ledOn);
  }
  
  digitalWrite(CHARGE_PIN, LOW); // Turn off the charge pin
  digitalWrite(DISCHARGE_PIN, HIGH); // Disharge the circuit.
  digitalWrite(DISCHARGE_PIN, LOW);
}
