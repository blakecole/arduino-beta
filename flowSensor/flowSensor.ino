/************************************************************/
/*    NAME: Blake Cole                                      */
/*    ORGN: hydrocycle                                      */
/*    FILE: flowSensor                                      */
/*    DATE: 6 MARCH 2021                                    */
/************************************************************/

// define pins:
const byte flowPin = 2;    // flow rate sensor pin

// define constants:
const float conversionFactor   = 6.54;   // [PULSE] per [LPM]
const unsigned long loopDelay  = 1000;   // loop delay [ms]

// define flow vars:
float flowRate           = 0.0;    // [L/min]
float totalVol           = 0.0;    // [L]
volatile int vPulseCount = 0;      // pulses interrupt
unsigned int pulseCount  = 0;      // pulses per loop

// define timer vars:
unsigned long interval   = 0;      // ms elapsed since prev calc
unsigned long prevTime   = 0;      // loop timer

// -----------------------------------------------------
void setup() {
  pinMode(flowPin, INPUT);
  digitalWrite(flowPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(flowPin), pulseCounter, FALLING);
  Serial.begin(9600);
}

// -----------------------------------------------------
void loop() {
  interval = millis()-prevTime;
  
  if(interval >= loopDelay) {
    pulseCount = vPulseCount; // grab ISR pulse count
    vPulseCount = 0;          // reset ISR pulse count

    // compute flow rate and total volume
    flowRate = (1000.0/interval)*pulseCount/conversionFactor;
    totalVol += (flowRate/60.0)*(interval/1000.0);
    prevTime = millis();

    // Print flow rate for this interval [L/min]
    Serial.print("FLOW_RATE=");
    Serial.print(flowRate);
    Serial.print(",");

    // Print total integrated volume [L]
    Serial.print("TOTAL_VOL=");
    Serial.print(totalVol);
    Serial.print(",\n");
  }
}

// -----------------------------------------------------
// define interrupt service routine (ISR)
// NOTE: ISR takes 5.125 µS + code time
void pulseCounter() {
  vPulseCount++;
}
