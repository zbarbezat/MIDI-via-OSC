import OSC
import socket

confirm = 0
port = 7777

def noteOn(addr, tags, data, client_address):
	print("OSCMessage '%s' from %s: " % (addr, client_address))
	txt = str(data)
	print(data)

def velocity(addr, tags, data, client_address):
	print("OSCMessage '%s' from %s: " % (addr, client_address))
	txt = str(data)
	print(data)

if __name__ == "__main__":
	while (confirm == 0):
		try:
			s = OSC.OSCServer(('127.0.0.1', port))
			s.addMsgHandler('/Note1', noteOn)    # call handler() for OSC messages received with the /startup address
			s.addMsgHandler('/Velocity1', velocity)
			s.serve_forever()
			print("Port number set to" + str(port))
			confirm = 1
		except socket.error, exc:
			print("Caught exception socket.error: %s" % exc)
			port = port + 1
			print("Port number now set to " + str(port))