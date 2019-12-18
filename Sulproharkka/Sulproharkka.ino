#include <LiquidCrystal.h> /* library for the use of lcd screen */
int tempPin = A0; /* analog pin for temp sensor*/
int tempMin = 23.8;
int tempMax = 30.0; /* min and max values to start motor*/
int motorFan = 9; /* pin where the motor is connected*/
int motorFanSpeed = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); /* the pins used on the lcd panels*/
void setup() 
{
    lcd.begin(16,2); /* tells how large screen is*/
    lcd.print("Temp in C:");
    
    pinMode(motorFan, OUTPUT); 
    pinMode(tempPin, INPUT);
    Serial.begin(9600); /* open a serial port*/
}

void loop() 
{

  int sensorVal = analogRead(tempPin); /* to get the values from the sensor*/
  float voltage = (sensorVal/1024.0) * 5.0; /* calculation formula fron sensor's datasheet to change the values to celsius values*/
  float temp = (voltage - 0.5) * 100;

    
    lcd.setCursor(0,1); /* coordinates to move the cursor of the screen to the upper left*/
    lcd.print(temp);
    Serial.println(temp);

  if(temp<tempMin){
    motorFanSpeed = 0;
    digitalWrite(motorFan, LOW); /* motor off*/
  }

  if((temp>= tempMin) && (temp <= tempMax)){
    motorFanSpeed = map(temp, tempMin, tempMax, 50, 200); /* tells how fast the pin will rotate when given the temp values, min and max values*/
    analogWrite(motorFan, motorFanSpeed); 
  }
    
    delay(1000); /* delaying outputs to make the values readable*/
}
