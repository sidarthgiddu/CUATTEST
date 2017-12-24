  #include <SPI.h> // SPI library included for SparkFunLSM9DS1
#include <Wire.h> // I2C library included for SparkFunLSM9DS1
#include <SparkFunLSM9DS1.h> // SparkFun LSM9DS1 library

//const int servoPin1 = 2;
//const int servoPin2 = 3;
//const int servoPin3 = 4;

const int mosfetpin1 = 1;
const int mosfetpin2 = 2;
const int mosfetpin3 = 3;
const int mosfetonoff = 4;

/*
const int gasvalvex = 5;
const int gasvalvenx = 6;
const int gasvalvey = 7;
const int gasvalveny = 8;
const int gasvalvez = 9;
const int gasvalvenz = 10;
*/

/*
int xAxis, yAxis, zAxis, xAcc, yAcc, zAcc;
const int accThresh = 0.1;
const int axisThresh = 10;

#define INITIALIZATION 1
#define STABILIZE 2
#define NORMAL_OPS 3
#define OFF 4

int STATE = INITIALIZATION;
*/




// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

// SDO_XM and SDO_G are both pulled high, so our addresses are:
#define LSM9DS1_M   0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //for I2C
  
  imu.settings.device.commInterface = IMU_MODE_I2C; // Set mode to I2C
  imu.settings.device.mAddress = LSM9DS1_M; // Set mag address to 0x1E
  imu.settings.device.agAddress = LSM9DS1_AG; // Set ag address to 0x6B
  
  if (!imu.begin()){
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Looping to infinity.");
    while (1);
  }
  
  
  /*
  Serial.begin(9600);

  pinMode(mosfetpin1, OUTPUT); //mosfetpin1 controls reaction wheel X
  pinMode(mosfetpin2, OUTPUT); //mosfetpin2 controls reaction wheel Y
  pinMode(mosfetpin3, OUTPUT); //mosfetpin3 controls reaction wheel Z
  pinMode(mosfetonoff, OUTPUT);
  pinMode(gasvalvex, OUTPUT);
  pinMode(gasvalvenx, OUTPUT);
  pinMode(gasvalvey, OUTPUT);
  pinMode(gasvalveny, OUTPUT);
  pinMode(gasvalvez, OUTPUT);
  pinMode(gasvalvenz, OUTPUT);
  */

}

void loop() {
  // put your main code here, to run repeatedly:
  runIMU();
  digitalWrite(mosfetonoff, HIGH); //turn on motor circuit
  if(Serial.available() > 0){
    if(Serial.peek() == '0'){ //turn OFF
      digitalWrite(mosfetpin1, LOW);
      digitalWrite(mosfetpin2, LOW);
      digitalWrite(mosfetpin3, LOW);
      digitalWrite(mosfetonoff, LOW); 
    }

    else if(Serial.peek() == '1'){ //enable rotation about x-axis
      digitalWrite(mosfetpin1, HIGH);
      delay(5000);  
    }
    else if(Serial.peek() == '2'){ //enable rotation about y-axis
      digitalWrite(mosfetpin2, HIGH);
      delay(5000);  
    }
    else if(Serial.peek() == '3'){ //enable rotation about z-axis
      digitalWrite(mosfetpin3, HIGH);
      delay(5000);  
    }
    else{
      
    }
  }
  /*
  switch(STATE){
    case(INITIALIZATION): {
      digitalWrite(mosfetonoff, HIGH); //enable the MOSFET that allows current flow in the motor circuit
      STATE = STABILIZE;
      };
    case(STABILIZE): {
      if(abs(zAcc - 1)<= accThresh){ //true if the force felt in the z-axis is around 1g, indicates that simulator is stable
        STATE = NORMAL_OPS;  
      }
      else{ //if simulator is not stable, rotate simulator about and x and y axes until it is
        if((zAcc - 1) >= accThresh){ 
          analogWrite(mosfetpin1, 5);
          analogWrite(mosfetpin2, 5);
          delay(1000);
        }
        else{
          analogWrite(mosfetpin1, -5);
          analogWrite(mosfetpin2, -5);
          delay(1000);
        }
      }
    };
    case(NORMAL_OPS): {
      if(Serial.available() > 0){
        if(Serial.peek() == '0'){ //turn off simulator
          STATE = OFF;
        }
        else{
          if(Serial.peek() == '1'){ //rotate about x axis
            analogWrite(mosfetpin1, 50);
            delay(5000);
          }
          else if (Serial.peek() == '2'){ //rotate about y axis
            analogWrite(mosfetpin2, 50);
            delay(5000);
          }
          else if (Serial.peek() == '3'){ //rotate about z axis
            analogWrite(mosfetpin3, 50); 
            delay(5000);
          }
          else{
            Serial.print(data);
          }
        }
      }
    };
    case(OFF): {
      analogWrite(mosfetpin1, 0);
      analogWrite(mosfetpin2, 0);
      analogWrite(mosfetpin3, 0);
      digitalWrite(mosfetonoff, LOW);
    };
  }
  */
  /*
  if(Serial.available() > 0){
        if(Serial.peek() == '0'){ //turn off simulator
          analogWrite(mosfetpin1, 0);
          analogWrite(mosfetpin2, 0);
          analogWrite(mosfetpin3, 0);
          digitalWrite(mosfetonoff, LOW);
          
          delay(5000);
        }
        else{
          if(Serial.peek() == '1'){ //rotate about x axis
            analogWrite(mosfetpin1, 50);
            Serial.print(xAcc);
            Serial.print(yAcc);
            Serial.print(zAcc);
            Serial.print(xAxis);
            Serial.print(yAxis);
            Serial.print(zAxis);
            delay(5000);
          }
          else if (Serial.peek() == '2'){ //rotate about y axis
            analogWrite(mosfetpin2, 50);
            delay(5000);
          }
          else if (Serial.peek() == '3'){ //rotate about z axis
            analogWrite(mosfetpin3, 50); 
            delay(5000);
          }
          else{
            Serial.print(data);
          }
        }
   }
   */ 
}


void runIMU(){
  Serial.println("XAcc, YAcc, ZAcc");
  imu.readAccel(); // Update the accelerometer data
  
  float xAcc = imu.calcAccel(imu.ax);
  Serial.print(xAcc); // Print x-axis data
  Serial.print(", ");
  float yAcc = imu.calcAccel(imu.ay);
  Serial.print(yAcc); // print y-axis data
  Serial.print(", ");
  float zAcc = imu.calcAccel(imu.az);
  Serial.println(zAcc); // print z-axis data
  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println();

  
  Serial.println("XAxis, YAxis, ZAxis");
  imu.readGyro(); // Update gyroscope data

  float xAxis = imu.calcGyro(imu.gx);
  Serial.print(xAxis); // Print x-axis rotation in DPS
  Serial.print(", ");
  float yAxis = imu.calcGyro(imu.gy);
  Serial.print(yAxis); // Print y-axis rotation in DPS
  Serial.print(", ");
  float zAxis = imu.calcGyro(imu.gz);
  Serial.println(zAxis); // Print z-axis rotation in DPS
  delay(1000);

  Serial.println();
  Serial.println();
  Serial.println();

  imu.settings.accel.scale = 16; // Set accel range to +/-16g
  imu.settings.gyro.scale = 2000; // Set gyro range to +/-2000dps
  imu.settings.mag.scale = 8; // Set mag range to +/-8Gs
  imu.begin(); // Call begin to update the sensor's new settings
}







