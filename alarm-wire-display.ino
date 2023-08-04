// !!!!! Remember to update me before flashing !!!!!
// Display type
// NO = normally open, NC = normally closed, Dual = dual EOL resistor
#define MODE NC


// I/O pin assignments

#define CLOSED_LED 2
#define OPEN_LED 4
#define OC_LED 0
#define SC_LED 1
#define INCORRECT_R_LED 5

#define ADC_IN 3

// Voltage threshold values for each display type
// The ATtiny has a 10-bit ADC over 5V-0V so the numbers are scaled by:
// (voltage)/5V * (2^10-1)

namespace NO{
  constexpr int closed_upper = 1.6/5.0 * 1023;
  constexpr int closed_lower = 0.8/5.0 * 1023;
  constexpr int open_upper = 0.5/5.0 * 1023;
  constexpr int open_lower = 0/5.0 * 1023;
  constexpr int oc_upper = 2.4/5.0 * 1023;
  constexpr int oc_lower = 1.6/5.0 * 1023;
  constexpr int sc_upper = -1;
  constexpr int sc_lower = -1;
}

namespace NC{
  constexpr int closed_upper = 3.5/5.0 * 1023;
  constexpr int closed_lower = 2.5/5.0 * 1023;
  constexpr int open_upper = 2.5/5.0 * 1023;
  constexpr int open_lower = 1.5/5.0 * 1023;
  constexpr int oc_upper = -1;
  constexpr int oc_lower = -1;
  constexpr int sc_upper = 0.5/5.0 * 1023;
  constexpr int sc_lower = 0/5.0 * 1023;
}

namespace Dual{
  constexpr int closed_upper = 1.4/5.0 * 1023;
  constexpr int closed_lower = 1/5.0 * 1023;
  constexpr int open_upper = 1/5.0 * 1023;
  constexpr int open_lower = 0.6/5.0 * 1023;
  constexpr int oc_upper = 2.2/5.0 * 1023;
  constexpr int oc_lower = 1.8/5.0 * 1023;
  constexpr int sc_upper = 0.5/5.0 * 1023;
  constexpr int sc_lower = 0/5.0 * 1023;
}

void setup() {
  // Display LEDs
  pinMode(CLOSED_LED, OUTPUT);
  pinMode(OPEN_LED, OUTPUT);
  pinMode(OC_LED, OUTPUT);
  pinMode(SC_LED, OUTPUT);
  pinMode(INCORRECT_R_LED, OUTPUT);

  // Voltage sense
  pinMode(ADC_IN, INPUT);
}

void loop() {
  // Read the voltage and set the state accordingly

  int voltage = analogRead(ADC_IN);

  int state = 0; // closed, open, oc, sc, incorrect r

  if(voltage > MODE::closed_lower && voltage < MODE::closed_upper){
    state = 1; // closed
  } else if(voltage > MODE::open_lower && voltage < MODE::open_upper){
    state = 2; // open
  } else if(voltage > MODE::oc_lower && voltage < MODE::oc_upper){
    state = 3; // oc
  } else if(voltage > MODE::sc_lower && voltage < MODE::sc_upper){
    state = 4; // sc
  } else {
    state = 5; // incorrect r
  }

  // Turn on the LED for the state we're in and turn off all others

  digitalWrite(CLOSED_LED, state == 1 ? HIGH : LOW);
  digitalWrite(OPEN_LED, state == 2 ? HIGH : LOW);
  digitalWrite(OC_LED, state == 3 ? HIGH : LOW);
  digitalWrite(SC_LED, state == 4 ? HIGH : LOW);
  digitalWrite(INCORRECT_R_LED, state == 5 ? HIGH : LOW);
}
