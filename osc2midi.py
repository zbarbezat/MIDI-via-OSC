import mido
import OSC
import serial
import socket

port = 7777
confirm = 0

notenumber = 0
ser = serial.Serial('/dev/ttyATH0')
print("Server open and sending messages to " + ser.name)
ser.baudrate = 115200

def noteOn(addr, tags, data, client_address):
	txt = "OSCMessage '%s' from %s: " % (addr, client_address)
	txt += str(data)
	notenumber = data[0]
	print(notenumber)
	msg = mido.Message('note_on', note = notenumber)
	bmsg = msg.bytes()
	smsg = bytearray(bmsg)

	ser.write(smsg)

def noteOff(addr, tags, data, client_address):
	txt = "OSCMessage '%s' from %s: " % (addr, client_address)
	txt += str(data)
	print(txt)
	notenumber = data[0]
	msg = mido.Message('note_off', note = notenumber)
	bmsg = msg.bytes()
	smsg = bytearray(bmsg)

	ser.write(smsg)

def controllerChange(addr, tags, data, client_address):
	txt = "OSCMessage '%s' from %s: " % (addr, client_address)
	txt += str(data)
	print(txt)
	channel_number = data[0]
	control_number = data[1]
	value_number  =  data[2]
	msg = mido.Message('control_change', channel = channel_number, control = control_number, value = value_number)
	bmsg = msg.bytes()
	smsg = bytearray(bmsg)

	ser.write(smsg)

if __name__ == "__main__":
	while (confirm == 0):
		try:
			s = OSC.OSCServer(('192.168.0.108', port))
			s.addMsgHandler('/', noteOn)    # call handler() for OSC messages received with the /startup address
			s.addMsgHandler('/nOff', noteOff)
			s.addMsgHandler('/cchange', controllerChange)
			s.serve_forever()
			print("Port number set to" + str(port))
			confirm = 1
		except socket.error, exc:
			print("Caught exception socket.error: %s" % exc)
			port = port + 1
			print("Port number now set to " + str(port))