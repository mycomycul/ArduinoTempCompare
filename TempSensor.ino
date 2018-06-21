/*


  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 4
 * LCD D7 pin to digital pin 3
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)



*/
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
const int tempPin1 = A0;
const int tempPin2 = A1;
const int ledPin = 7;
const int button = 2;

//Environment Variables
bool Celsius = false;
bool Light = false;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Calibrating");
  delay(1500);
  
  //Set the LCD LED Pin to OutPut
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  //Setup Button Interrupt  
  pinMode(button, INPUT_PULLUP);

}

void loop() {
   float voltage, temperature1, temperature2;
   int sensorVal = digitalRead(2);
//Check for button push to change format
  if (sensorVal == LOW)
  {Celsius = !Celsius;}
//Get the first sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin1);
    temperature1 = getTemperature(voltage);
//Get the second sensor's value and convert it to a temperature
    voltage = getVoltage(tempPin2);
    temperature2 = getTemperature(voltage);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
	lcd.clear();
  lcd.setCursor(0, 0);
  String s = String(temperature1,1);
  // print the number of seconds since reset:
  lcd.print("In:" + String(temperature1,1));
	lcd.setCursor(0, 1);
    lcd.print("Out:" + String(temperature2,1));
  delay(1000);
}
 
float getTemperature(float voltage)
{
    if (Celsius == true)
    {
        return ((voltage - 0.5) * 100.0);
    }
    else
    {
        return ((voltage - 0.5) * 100.0) * (9.0 / 5.0) + 32.0;
    }
}

float getVoltage(int pin)
{

    return (analogRead(pin) * 0.004882814);

    // This equation converts the 0 to 1023 value that analogRead()
    // returns, into a 0.0 to 5.0 value that is the true voltage
    // being read at that pin.
}
void celsiusButton(){
  Celsius = !Celsius;
}