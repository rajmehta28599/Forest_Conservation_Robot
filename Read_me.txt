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
---->for the arduino nano
	1)main.ino
	2)Z_appplyspd.ino
				
