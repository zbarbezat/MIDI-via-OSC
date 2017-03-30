# MIDI via OSC
## Sending midi messages to an Arduino Yun through Open Sound Control

### Description
Arduino devices can recieve MIDI messages as an input via their serial recieve pin. The Arduino Yun is an arduino microcontroller board with an additional Atheros AR9331 processor onboard that supports a Linux distribution based on OpenWrt that allows for WiFi communication.

### Installation and Set-Up
+ **All of this is done after the intial wifi setup on the Arduino Yun. A good guide for that can be found** [here](https://www.twilio.com/blog/2015/02/arduino-wifi-getting-started-arduino-yun.html)
+ **First pip must be installed on the Arduino Yun's console**
	+ `$ opkg update`
	+ `$ opkg install distribute`
	+ `$ opkg install python-openssl`
	+ `$ easy_install pip`
+ **Installs all the required python libraries**
	+ `$ pip install -r requirements.txt`
+ **The Yun comes with a 'bridge' by default that must be disconnected to allow PySerial to communicate to the Arduino board, the following disables the bridge**
	+ `$ python DisableYunBridge.py`
	+ If for some reason the bridge must be re-enabled use `$ python EnableYunBridge.py`
+ The arduino code should then be uploaded to the Yun. This can be done wirelessly or over microUSB.

### Usage
+ Navigate to file directory on the Arduino Yun's console
+ Start python OSC server on the Yun
	+ Use `$ python abletonOSC.py` if using with Ableton
	+ Use `$ python osc2midi.py` if using with the Processing script
+ For use with Ableton Live
	+ Start Ableton Live
	+ Drop `OSC_MIDI_Send.amxd` into Ableton Live where it says "Drop an Instrument or Sample Here"
	+ Wait for the OSC send device to load and then fill in the correct values for Host and Port.
	+ In the main window of Ableton Live there will be two MIDI tracks, right-click the first MIDI track and select "Insert MIDI Clip"
	+ A piano roll should appear at the bottom of the window. You can then program any sequence of notes that you want.
	+ To start sending your MIDI messages just press the play button on the MIDI 1 track to start looping your sequence.
+ For use with the Processing Script
	+ Start the processing script
	+ Available MIDI devices connected should show up in the processing console.
	+ Take note of the number for the MIDI device you would like to use and place it in `myBus2 = new MidiBus(this, >here<, "Microsoft MIDI Mapper");`
	+ Make sure the port and IP address values are correct
	+ Start using your MIDI device (It should be sending OSC)



### To-Do
#### Processing (has been replaced with Audacity)
+ ~~Create GUI~~
	+ It should list MIDI devices and allow you to change the MIDIBus objects to use the possible MIDI devices
	+ Also should allow for user to change the port number
#### Python
+ ~~Add error exceptions when current port is in use and cycle to next port~~
+ Add a way to change the IP address without opening the script
+ Add a webapp using some sort of framework
