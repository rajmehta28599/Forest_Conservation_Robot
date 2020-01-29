!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Download the Arduino Software (IDE) (for arduino nano)
	link:  https://www.arduino.cc/en/Main/Software
	1.Get the latest version from the download page. You can choose between the Installer (.exe) and the Zip packages. We suggest you use the first one that installs directly everything you need to use the Arduino Software (IDE), including the drivers. With the Zip package you need to install the drivers manually. The Zip file is also useful if you want to create a portable installation.
	2.When the download finishes, proceed with the installation and please allow the driver installation process when you get a warning from the operating system.
	3.Choose the components to install
	4.Choose the installation directory (we suggest to keep the default one)
	The process will extract and install all the required files to execute properly the Arduino Software (IDE)


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Installing Nano on Debian/Ubuntu (for raspberry pi)
	To install Nano text editor on Debian or Ubuntu machines, execute the following command:

		" $ sudo apt-get install nano"
	Wait for the installation process to finish.

	The sudo part is meant for running this command as a root user. This means you may be prompted to enter a password in case you are currently not logged in as a root user.

		"$yum install nano"
	That is it for the installation. As soon as the setup ends, you can use it immediately!
	
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	till the date 27-1-2020 monday codes
	
---->for the raspberry pi
	1)python code 
		main.py
	2)html code
		main.html

	1)python code(main.py)			'''
		*
		* Project Name: 	Forest Conservation Robot(e-Yantra 						Project)
		* Author List: 		Mehta Raj Vinodbhai
					Purohit Mahima
					Soni maitri
					Dubey Snehal
		* Filename: 		main.py(python file)
		* Functions: 		def writeNumber(value):,
						def readNumber():,
						def index():,
						def action(deviceName, action):
		* Global Variables:	f=0
						var=0
						var1=100
						var2=100
		'''

		import os, sys
		import smbus
		import time
		''' RPi.GPIO, is a Python module to control the GPIO interface on the Raspberry Pi
		'''
		import RPi.GPIO as GPIO
		from flask import Flask, render_template, request
		#Flask object called app
		app = Flask(__name__)
		# Broadcom SOC that the pins are connected
		GPIO.setmode(GPIO.BCM)
		GPIO.setwarnings(False)

		# for RPI version 1, use bus = smbus.SMBus(0)
		bus = smbus.SMBus(1)
		# This is the address we setup in the Arduino Program random one
		address = 4

		#define flame sensors GPIOs
		button = 18	#gpio 18
		#define GPIOs
		ledRed = 1	#gpio 1
		enablei2c = 21	#gpio 21
		#initialize GPIO status variables
		buttonSts = 0
		f=0
		var=0
		var1=100
		var2=100

		# Define flame sensor pin as an input
		GPIO.setup(button, GPIO.IN)
		# Define led pin as output
		GPIO.setup(ledRed, GPIO.OUT)
		GPIO.setup(enablei2c, GPIO.OUT)
		# turn led pins OFF
		GPIO.output(ledRed, GPIO.LOW)	
		#enable i2c for the web control
		GPIO.output(enablei2c, GPIO.LOW)	

		'''
		* Function Name:	def writeNumber(value):
		* Input:			var1,var2->value
		* Output:			provide the direction and the speed of the robot which is give through the web control
		* Logic: 			for i2c communication to write data from raspberry pi to arduino nano
		* Example Call:		writeNumber(var1)
		'''
		# i2c function for write data
		def writeNumber(value):
		    bus.write_byte(address, value)
		    return -1
		'''
		* Function Name:	def readNumber():
		* Input:			var1,var2->value
		* Output:			to apply the flag logic to differentiate the two data
		* Logic: 			for i2c communication to read data from	arduino nano to raspberry pi
		* Example Call:		f=readNumber()
		'''
		# i2c function for read data
		def readNumber():
		    f = bus.read_byte(address)
			# number = bus.read_byte_data(address, 1)
		    return f

		'''
		* Function Name:	def index():
		* Input:			flame sesor data
		* Output:			buttonSts
		* Logic: 			Run the index() function when someone accesses the root URL (‘/’) of the server

		* Example Call:		/
		'''

		@app.route("/")
		def index():
			#Read GPIO Status of flame sensor
			buttonSts = GPIO.input(button)
			#status print on web control
			   templateData = {
				'button'  : buttonSts,
			}
			   #that return to html file
			return render_template('main.html', **templateData)
		#for the html url request

		'''
		* Function Name:	def action(deviceName, action):
		* Input:		deviceName, action
		* Output:		gpio pins high and low,writeNumber and	readNumber(),var increment decrement value
		* Logic: 		Run the index() function when someone accesses the root URL(‘/<deviceName>/<action>’) of the 						server
		* Example Call:		/ledRed/on
		'''

		@app.route("/<deviceName>/<action>")
		def action(deviceName, action):
			if deviceName == 'ledRed':
				actuator = ledRed
			   if action == "on":
					GPIO.output(actuator, GPIO.HIGH)  
			if action == "off":
					GPIO.output(actuator, GPIO.LOW)

			if deviceName == 'enablei2c':
				actuator = enablei2c
			if deviceName == 'forward':
					  f = readNumber()
			if deviceName == 'backward':
					  f = readNumber()
			if deviceName == 'left':
				       f = readNumber()
			if deviceName == 'right':
					  f = readNumber()
			if deviceName == 'stop':
					  f = readNumber()
			if deviceName == 'increase':
				var=var+1
			if deviceName == 'decrease':
				var=var-1
			   if action == "forward":
					  if f == 0:
						writeNumber(var1)
					  else:
						writeNumber(var2)
			if action == "backward":
					  if f == 0:
						writeNumber(var1)
					  else:
						writeNumber(var2)
			   if action == "left":
					  if f == 0:
						writeNumber(var1)
					  else:
						writeNumber(var2)

			if action == "right":
					  if f == 0:
						writeNumber(var1)
					  else:
						writeNumber(var2)
			   if action == "stop":
					  var1=0
					  var2=0
					  if f == 0:
						writeNumber(var1)
					  else:
						writeNumber(var2)
			if action == "increase":
					var1=var
					var2=var
			   if action == "decrease":
					var1=var
					var2=var


			buttonSts = GPIO.input(button)

			templateData = {
				'button'  : buttonSts,
			}
			return render_template('main.html', **templateData)

			if __name__ == "__main__":
			   app.run(host='0.0.0.0', port=8080, debug=True)
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
---->for the arduino nano
	1)main.ino
-----------------------------------------------------main.ino------------------------------------------------------------
		/*
		* Project Name:   Forest Conservation Robot(e-Yantra Project)
		* Author List:    Mehta Raj Vinodbhai,
		*                 Purohit Mahima
		* 
		* Filename:       main.ino
		* Functions:      setup()
		*                 receiveData(int byteCount)
		*                 sendData()
		*                 loop()
		*                 servo_filter()
		*                 lookRight()
		*                 lookLeft()
		*                 ultra()
		*                 moveBackward()
		*                 moveForward()
		*                 
		  * Global Variables: 
				      spd1, spd2,distance,speedSet,ct,d,distanceR, distanceL,seru,setu,setd,serd;data,ispd1,ispd2,state
				      MAX_DISTANCE MAX_SPEED 
		*
		*/


		#include <Servo.h>
		#include <Wire.h>

		#define SLAVE_ADDRESS 0x04
		int state = 0;
		int enablei2c=10;//pin for enable i2c
		int ispd1=0,ispd2=0;

		#define MAX_DISTANCE 80
		#define MAX_SPEED 20 // sets speed of DC  motors
		// ultrasonic
		const int  trigPin = 10, echoPin = 12;
		int data;

		//servo motor
		Servo myservo1;
		Servo myservo2;
		#define dir myservo1.write
		#define uls myservo2.write
		int seru = 0, setu = 0, setd = 90, serd = 90;

		int distance = 0;
		int speedSet = 0;
		int ct = 0, d = 0;
		int distanceR = 0;
		int distanceL =  0;

		//motor
		int8_t spd1 = 0, spd2 = 0;
		int8_t mot2 = 11, mot21 = 6;
		int8_t mot1 = 3, mot11 = 4;


		/*
		*
		* Function Name:  setup()
		* Input:          none
		* Output:         define the pins mode input,output
		* Logic:          at time of execution of the code that function run first
		* Example Call:   setup()
		*
		*/
		void setup()
		{

		  pinMode(10, INPUT);
		  // initialize i2c as slave
		  Wire.begin(SLAVE_ADDRESS);
		  // define callbacks for i2c communication
		  Wire.onReceive(receiveData);
		  Wire.onRequest(sendData);
		  //motor
		  pinMode(mot1, OUTPUT); pinMode(mot11, OUTPUT);
		  pinMode(mot2, OUTPUT); pinMode(mot21, OUTPUT);
		  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
		  myservo1.attach(A0);
		  myservo2.attach(A1);
		  uls(seru);
		  dir(serd);
		  distance = ultra();
		  //Serial.begin(115200);
		}

		/*
		*
		* Function Name:  receiveData(int byteCount) 
		* Input:          byteCount mean limitation of the size of the data 
		* Output:         get the data from the raspberry pi to arduino nano 
		* Logic:          read the data spd1 and spd2 from the raspberry pi using the flage logic to differentiate data
		* Example Call:   receiveData(int byteCount) 
		*
		*/
		void receiveData(int byteCount) {
		   if(Wire.available()) {
		      if (state == 0) {
			ispd1 = Wire.read();
			state = 1;
		      }
		      else {
			ispd2 = Wire.read();
			state = 0;
		      }
		  }
		}

		/*
		*
		* Function Name:  sendData()
		* Input:          none
		* Output:         respone to the raspberry pi.data travel from arduino to raspberry pi
		* Logic:          for the purp[ose of seprating two data use flage logic to differentiate
		* Example Call:   sendData()
		*
		*/
		void sendData() {Wire.write(state);}

		/*
		*
		* Function Name:  loop()
		* Input:          enablei2c pin data from the raspberry pi
		* Output:         main execution of the robot through the help of the subroutines
		* Logic:          here the robot enablei2c=1 then it travel through the help of the web control data otherwise obstacle 				  avoiding logic
		* Example Call:   loop()
		*
		*/
		void loop()
		{
		  if(digitalRead(enablei2c)){spd1=ispd1;spd2=ispd2;applyspeed();}
		  else  {
			switch (distance)
			{
			  case 0 ... 10:
				  while(d==0)
				  {
				    lookRight();
				    lookLeft();  
				    if (distanceR >= distanceL) {setd = 150;dir(serd);servo_acc_dacc();d=1;}    //0 to 180
				    else if (distanceR <distanceL) {setd = 50;uls(seru);servo_acc_dacc();d=1;}
				  }
			    break;
			  default: 
			      setd = setu = 90; uls(seru); moveForward(); applyspeed();
			      if(ct>1000){dir(serd);d=ct=0;}else{ct++;} 
			      break;
			}
			distance = ultra();
			servo_acc_dacc();
		  }
		}
		/*
		*
		* Function Name:  servo_acc_dacc()
		* Input:          none
		* Output:         smooth rotation of the servo motor
		* Logic:          the logic of the acc_dacc of the servo motor angle
		* Example Call:   servo_acc_dacc()
		*
		*/

		void servo_acc_dacc()
		{
		  if (serd < setd)serd++; else if (serd > setd)serd--; else serd = setd;
		  if (seru < setu)seru++; else if (seru > setu)seru--; else seru = setu;
		}
		/*
		*
		* Function Name:  lookRight()
		* Input:          none
		* Output:         temporary value of the distance
		* Logic:          ultrasonic servo rotate right side and get the temp. distance data
		* Example Call:   lookRight()
		*
		*/
		int lookRight() {setu = 30;uls(seru);servo_acc_dacc();delay(500);distanceR=0;distanceR = ultra();return distanceR;}
		/*
		*
		* Function Name:  lookLeft()
		* Input:          none
		* Output:         temporary value of the distance
		* Logic:          ultrasonic servo rotate left side and get the temp. distance data
		* Example Call:   lookLeft()
		*
		*/
		int lookLeft() {setu = 150;uls(seru);servo_acc_dacc();delay(500);distanceL=0;distanceL = ultra();return distanceL;}
		/*
		*
		* Function Name:  ultra()
		* Input:          none
		* Output:         value of the distance
		* Logic:          getting the ultrasonic value as distance in 6000 miliseconds
		* Example Call:   ultra()
		*
		*/
		int ultra()
		{
		    digitalWrite(trigPin, LOW); 
		    delayMicroseconds(2);
		    digitalWrite(trigPin, HIGH); 
		    delayMicroseconds(5);
		    digitalWrite(trigPin, LOW);

		    data = pulseIn(echoPin, HIGH, 6000);
		    data = data * 0.017;
		    return data;
		}
		/*
		*
		* Function Name:  moveForward()
		* Input:          none
		* Output:         value of spd1 and spd2 
		* Logic:          increase the speed
		* Example Call:   moveForward()
		*
		*/
		void moveForward() {for (speedSet = 0; speedSet < MAX_SPEED; speedSet++) {spd1 = spd2 = speedSet;}}
		/*
		*
		* Function Name:  moveBackward()
		* Input:          none
		* Output:         value of spd1 and spd2 
		* Logic:          decrease the speed
		* Example Call:   moveBackward()
		*
		*/
		void moveBackward(){for (speedSet = 0; speedSet < MAX_SPEED; speedSet--) {spd1 = spd2 = -speedSet;}}
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	2)Z_appplyspd.ino
-----------------------------------------------------------------------------------------------------------------------------------	
	
		/*
		*
		* Function Name:  applyspeed()
		* Input:          none
		* Output:         speed and direction of the motor
		* Logic:          here if the speed of motor is positive the one direction and the negative then another direction and 					  default for stop the motion
		* Example Call:   applyspeed()
		*
		*/
		void applyspeed()
		{
		  switch (spd1)
		  {
		    case -255 ... -1:    analogWrite(mot1, -spd1); digitalWrite(mot11 , HIGH);      break;
		    case 1 ... 255:      analogWrite(mot1, spd1); digitalWrite(mot11 , LOW);     break;
		    default:             analogWrite(mot1, 0);     digitalWrite(mot11 , LOW);      break;
		  }
		  switch (spd2)
		  {
		    case -255 ... -1:    analogWrite(mot2, -spd2); digitalWrite(mot21 , LOW);    break;
		    case 1 ... 255:      analogWrite(mot2, spd2); digitalWrite(mot21 , HIGH);     break;
		    default:             analogWrite(mot2, 0); digitalWrite(mot21 , LOW);        break;
		  }
		}
---------------------------------------------------------------------------------------------------------------------------------------
