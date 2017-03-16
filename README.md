# MIDI via OSC
## sending midi messages to an Arduino Yun through Open Sound Control

### Installation
`$ pip install -r requirements.txt`

### Usage
+ Navigate to file directory on the Arduino Yun's console
+ Start python OSC server on the Yun with `$ python osc2midi.py`
+ Start processing script
+ You're good to go!

### To-Do
#### Processing
+ Create GUI
..* It should list MIDI devices and allow you to change the MIDIBus objects to use the possible MIDI devices
..* Also should allow for user to change the port number
#### Python
+ Add error exceptions when current port is in use and cycle to next port
..* Find someway to communicate this change to Processing (or allow user to input this change)
