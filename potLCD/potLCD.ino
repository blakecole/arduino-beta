/************************************************************/
/*    NAME: Blake Cole                                      */
/*    ORGN: PelTEC                                          */
/*    FILE: potLCD                                          */
/*    DATE: 30 MAY 2020                                     */
/************************************************************/

// potLCD : Displays an analog potentiometer value on an LCD
//          Adapted from Arduino samples:
//              - 'LiquidCrystal' : 'Hello World'
//              - 'Analog'        : 'AnalogInput'

/* ARDUINO PIN  :     LCD PIN
 *      0       : D0 (Data input 0) [7]
 *      1       : D1 (Data input 1) [8]
 *      2       : D2 (Data input 2) [9]
 *      3       : D3 (Data input 3) [10]
 *      4       : D4 (Data input 4) [11]
 *      5       : D5 (Data input 5) [12]
 *      6       : D6 (Data input 6) [13]
 *      7       : D7 (Data input 7) [14]
 *      8       : EN (Enable) [6]
 *      9       : RS (Register Select) [4]
 *     GND      : GND [1]
 *     5V       : 5 VDC [2]
 *    0.75V     : Contrast, 0-5V [3]
 *     GND      : R/W (Read-Write) [5]
 *      
 * ARDUINO PIN  :  ANALOG INPUT
 *      A0      :  Potentiometer (middle pin)
 */

#include <LiquidCrystal.h>

//------------------------------------------------------------
// LCD Display Setup:
const int d0=0, d1=1, d2=2, d3=3, d4=4, d5=5, d6=6, d7=7;
const int en=8, rs=9;
LiquidCrystal lcd(rs, en, d7, d6, d5, d4, d3, d2, d1, d0);

// Potentiometer Setup:
const int potPin = A0;
int potVal = 0;


//------------------------------------------------------------
void setup() {
  // define LCD number of columns and rows:
  lcd.begin(16, 2);
}


//------------------------------------------------------------
void loop() {
  // read potentiometer value:
  potVal = analogRead(potPin);
  // set the cursor to beginning of 2nd line (col 0, row 1)
  lcd.clear();
  lcd.print("Potentiometer:");
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(potVal,DEC);
  delay(50);
}
