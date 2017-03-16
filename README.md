# MIDI via OSC
## Sending midi messages to an Arduino Yun through Open Sound Control

### Description
Arduino devices can recieve MIDI messages as an input via their serial recieve pin. The Arduino Yun is an arduino microcontroller board with an additional Atheros AR9331 processor onboard that supports a Linux distribution based on OpenWrt that allows for WiFi communication.

### Installation
**All of this is done after the intial wifi setup on the Arduino Yun. A good guide for that can be found** [here](https://www.twilio.com/blog/2015/02/arduino-wifi-getting-started-arduino-yun.html)

**First pip must be installed on the Arduino Yun's console**
`$ opkg update`
`$ opkg install distribute`
`$ opkg install python-openssl`
`$ easy_install pip`

**Installs all the required python libraries**
`$ pip install -r requirements.txt`

**The Yun comes with a 'bridge' by default that must be disconnected to allow PySerial to communicate to the Arduino board, the following disables the bridge**
`$ python DisableYunBridge.py`

### Usage
+ Navigate to file directory on the Arduino Yun's console
+ Start python OSC server on the Yun with `$ python osc2midi.py`
+ Start processing script
+ You're good to go!

### To-Do
#### Processing
+ Create GUI
	+ It should list MIDI devices and allow you to change the MIDIBus objects to use the possible MIDI devices
	+ Also should allow for user to change the port number
#### Python
+ Add error exceptions when current port is in use and cycle to next port
	+ Find someway to communicate this change to Processing (or allow user to input this change)
