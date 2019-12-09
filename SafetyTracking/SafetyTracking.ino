
#include "Wire.h" // This library allow
const int MPU_ADDR = 0x68;

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


// defines pins numbers 
#define motorX 2
#define motorY 3
#define motorZ 4

int trigPinX=2;
int echoPinX=3;

int trigPinY=4;
int echoPinY=5;

int trigPinZ=6;
int echoPinZ=7;


void setup() {
  Serial.begin (9600);
  pinMode(trigPinX, OUTPUT);
  pinMode(echoPinX, INPUT);
  pinMode(motorX,OUTPUT);
  
   pinMode(trigPinY, OUTPUT);
  pinMode(echoPinY, INPUT);
  pinMode(motorY,OUTPUT);
  
   pinMode(trigPinZ, OUTPUT);
  pinMode(echoPinZ, INPUT);
  pinMode(motorZ,OUTPUT);
  

Wire.begin();
Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
Wire.write(0x6B); // PWR_MGMT_1 register
Wire.write(0); // set to zero (wakes up the MPU-6050)
Wire.endTransmission(true);

}

void loop() {
  long durationN, distanceN;
  digitalWrite(trigPinX, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinX, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinX, LOW);
  durationX = pulseIn(echoPinX, HIGH);
  distanceX = (durationN/2) / 29.1;

   if (distanceX <= 2 {
    digitalWrite(motorX,HIGH);
  }
  else {
    Serial.print ( "Sensor1  ");
    Serial.print ( distanceX);
    Serial.println("cm");
  }
  delay(2000);
  
long durationY, distanceY;
  digitalWrite(trigPinY, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinY, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinY, LOW);
  durationY = pulseIn(echoPinY, HIGH);
  distanceY= (durationY/2) / 29.1;

   if (distanceY <=2 {
    digitalWrite(motorY,HIGH);
  }
  else {
    Serial.print("Sensor2  ");
    Serial.print(distanceY);
    Serial.println("cm");
  }
  delay(2000);
  long durationZ, distanceZ;
  digitalWrite(trigPinZ, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinZ, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinZ, LOW);
  durationZ = pulseIn(echoPinZ, HIGH);
  distanceZ= (durationZ/2) / 29.1;

   if (distanceZ <= 2 {
    digitalWrite(motorZ,HIGH);
  }
  else {
    Serial.print("SensorZ  ");
    Serial.print(distanceZ);
    Serial.println("cm");
  }
  delay(2000);
  
  Serial.print(" | aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));

  Serial.println();
  delay(2000);

}
