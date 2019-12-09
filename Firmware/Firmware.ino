
// Include Libraries
#include "Arduino.h"
#include "ADXL345.h"
#include "I2Cdev.h"
#include "NewPing.h"
#include "SD.h"
#include "Switchable.h"
#include "VibrationMotor.h"


// Pin Definitions
#define HCSR04_1_PIN_TRIG	6
#define HCSR04_1_PIN_ECHO	5
#define HCSR04_2_PIN_TRIG	8
#define HCSR04_2_PIN_ECHO	7
#define HCSR04_3_PIN_TRIG	10
#define HCSR04_3_PIN_ECHO	9
#define SDFILE_PIN_CS	53
#define SURFACETRANSDUCER1_1_PIN_POS	11
#define SURFACETRANSDUCER2_2_PIN_POS	12
#define VIBRATIONMOTOR1_1_PIN_COIL1	2
#define VIBRATIONMOTOR2_2_PIN_COIL1	3
#define VIBRATIONMOTOR3_3_PIN_COIL1	4



// Global variables and defines
int16_t adxlAx, adxlAy, adxlAz;
// object initialization
ADXL345 adxl;
NewPing hcsr04_1(HCSR04_1_PIN_TRIG,HCSR04_1_PIN_ECHO);
NewPing hcsr04_2(HCSR04_2_PIN_TRIG,HCSR04_2_PIN_ECHO);
NewPing hcsr04_3(HCSR04_3_PIN_TRIG,HCSR04_3_PIN_ECHO);
File sdFile;
VibrationMotor vibrationMotor1_1(VIBRATIONMOTOR1_1_PIN_COIL1);
VibrationMotor vibrationMotor2_2(VIBRATIONMOTOR2_2_PIN_COIL1);
VibrationMotor vibrationMotor3_3(VIBRATIONMOTOR3_3_PIN_COIL1);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    adxl.init();
    // Set SPI SS pin to output otherwise the SD library functions will not work.
    // The SD is set to use SPI SS Arduino pin 10 as chip select(CS) by default.
    // To change the pin use SD.begin(SD_CS_PIN)
    pinMode(SDFILE_PIN_CS, OUTPUT);
    // Check if the card is present and can be initialized
    if (!SD.begin()) {
    Serial.println(F("Card failed, or not present"));
    while(1);
    }
    Serial.println(F("card initialized."));
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // SparkFun ADXL345 - Triple Axis Accelerometer Breakout - Test Code
    // read raw accel measurements from device
    adxl.getAcceleration(&adxlAx, &adxlAy, &adxlAz);
    // display tab-separated accel x/y/z values
    Serial.print(F("ADXL345 accel-\t")); 
    Serial.print(adxlAx); Serial.print(F("\t"));
    Serial.print(adxlAy); Serial.print(F("\t"));  
    Serial.println(adxlAz);

    }
    else if(menuOption == '2') {
    // Ultrasonic Sensor - HC-SR04 #1 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_1Dist = hcsr04_1.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_1Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '3') {
    // Ultrasonic Sensor - HC-SR04 #2 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_2Dist = hcsr04_2.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_2Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '4') {
    // Ultrasonic Sensor - HC-SR04 #3 - Test Code
    // Read distance measurment from UltraSonic sensor           
    int hcsr04_3Dist = hcsr04_3.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04_3Dist); Serial.println(F("[cm]"));

    }
    else if(menuOption == '5') {
    // Micro SD module - Test Code
    // The SD example code creates a datalog.txt file for logging sensor data
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    sdFile = SD.open("datalog.txt", FILE_WRITE);
    // if the file exists in SD card, write sensor data
    if (sdFile) {
    //Write to file
    sdFile.println("ENTER SENSOR DATA HERE");
    // close the file
    sdFile.close();
    // Uncomment to print to the serial port
    //Serial.println("ENTER SENSOR DATA HERE");
    } 
    else {
    // if the file didn't open, print an error
    Serial.println(F("error opening file."));
    }
    }
    else if(menuOption == '6')
    {
    // Disclaimer: The Surface Transducer - Small #1 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '7')
    {
    // Disclaimer: The Surface Transducer - Small #2 is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '8') {
    // Vibration Motor #1 - Test Code
    // The vibration motor will turn on and off for 500ms (0.5 sec)
    vibrationMotor1_1.on();     // 1. turns on
    delay(500);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    vibrationMotor1_1.off();    // 3. turns off
    delay(500);           // 4. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '9') {
    // Vibration Motor #2 - Test Code
    // The vibration motor will turn on and off for 500ms (0.5 sec)
    vibrationMotor2_2.on();     // 1. turns on
    delay(500);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    vibrationMotor2_2.off();    // 3. turns off
    delay(500);           // 4. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '10') {
    // Vibration Motor #3 - Test Code
    // The vibration motor will turn on and off for 500ms (0.5 sec)
    vibrationMotor3_3.on();     // 1. turns on
    delay(500);           // 2. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    vibrationMotor3_3.off();    // 3. turns off
    delay(500);           // 4. waits 500ms (0.5 sec). change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) SparkFun ADXL345 - Triple Axis Accelerometer Breakout"));
    Serial.println(F("(2) Ultrasonic Sensor - HC-SR04 #1"));
    Serial.println(F("(3) Ultrasonic Sensor - HC-SR04 #2"));
    Serial.println(F("(4) Ultrasonic Sensor - HC-SR04 #3"));
    Serial.println(F("(5) Micro SD module"));
    Serial.println(F("(6) Surface Transducer - Small #1"));
    Serial.println(F("(7) Surface Transducer - Small #2"));
    Serial.println(F("(8) Vibration Motor #1"));
    Serial.println(F("(9) Vibration Motor #2"));
    Serial.println(F("(10) Vibration Motor #3"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing SparkFun ADXL345 - Triple Axis Accelerometer Breakout"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #1"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #2"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Ultrasonic Sensor - HC-SR04 #3"));
    		else if(c == '5') 
    			Serial.println(F("Now Testing Micro SD module"));
    		else if(c == '6') 
    			Serial.println(F("Now Testing Surface Transducer - Small #1 - note that this component doesn't have a test code"));
    		else if(c == '7') 
    			Serial.println(F("Now Testing Surface Transducer - Small #2 - note that this component doesn't have a test code"));
    		else if(c == '8') 
    			Serial.println(F("Now Testing Vibration Motor #1"));
    		else if(c == '9') 
    			Serial.println(F("Now Testing Vibration Motor #2"));
    		else if(c == '10') 
    			Serial.println(F("Now Testing Vibration Motor #3"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

/*******************************************************

*    Circuito.io is an automatic generator of schematics and code for off
*    the shelf hardware combinations.

*    Copyright (C) 2016 Roboplan Technologies Ltd.

*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.

*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.

*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*    In addition, and without limitation, to the disclaimers of warranties 
*    stated above and in the GNU General Public License version 3 (or any 
*    later version), Roboplan Technologies Ltd. ("Roboplan") offers this 
*    program subject to the following warranty disclaimers and by using 
*    this program you acknowledge and agree to the following:
*    THIS PROGRAM IS PROVIDED ON AN "AS IS" AND "AS AVAILABLE" BASIS, AND 
*    WITHOUT WARRANTIES OF ANY KIND EITHER EXPRESS OR IMPLIED.  ROBOPLAN 
*    HEREBY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT 
*    NOT LIMITED TO IMPLIED WARRANTIES OF MERCHANTABILITY, TITLE, FITNESS 
*    FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT, AND THOSE ARISING BY 
*    STATUTE OR FROM A COURSE OF DEALING OR USAGE OF TRADE. 
*    YOUR RELIANCE ON, OR USE OF THIS PROGRAM IS AT YOUR SOLE RISK.
*    ROBOPLAN DOES NOT GUARANTEE THAT THE PROGRAM WILL BE FREE OF, OR NOT 
*    SUSCEPTIBLE TO, BUGS, SECURITY BREACHES, OR VIRUSES. ROBOPLAN DOES 
*    NOT WARRANT THAT YOUR USE OF THE PROGRAM, INCLUDING PURSUANT TO 
*    SCHEMATICS, INSTRUCTIONS OR RECOMMENDATIONS OF ROBOPLAN, WILL BE SAFE 
*    FOR PERSONAL USE OR FOR PRODUCTION OR COMMERCIAL USE, WILL NOT 
*    VIOLATE ANY THIRD PARTY RIGHTS, WILL PROVIDE THE INTENDED OR DESIRED
*    RESULTS, OR OPERATE AS YOU INTENDED OR AS MAY BE INDICATED BY ROBOPLAN. 
*    YOU HEREBY WAIVE, AGREE NOT TO ASSERT AGAINST, AND RELEASE ROBOPLAN, 
*    ITS LICENSORS AND AFFILIATES FROM, ANY CLAIMS IN CONNECTION WITH ANY OF 
*    THE ABOVE. 
********************************************************/