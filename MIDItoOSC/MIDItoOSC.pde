// Libraries
import themidibus.*;
import oscP5.*;
import netP5.*;

int port = 0;



OscP5 oscP5; // OSC Object
NetAddress myRemoteLocation;

MidiBus myBus; // The MidiBus
MidiBus myBus2;
MidiBus myBus3;

void setup() {
  size(400, 400);
  background(0);
  
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, 12000);
  
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress("192.168.0.108", port);
  
  MidiBus.list(); // List all available Midi devices on STDOUT. This will show each device's index and name.
  
  myBus = new MidiBus(this, 1, "Microsoft MIDI Mapper");
  myBus2 = new MidiBus(this, 2, "Microsoft MIDI Mapper");
  myBus2 = new MidiBus(this, 3, "Microsoft MIDI Mapper");
}

void draw() {
  
}

void noteOn(int channel, int pitch, int velocity) {
  // Receive a noteOn
  println();
  println("Note On:");
  println("--------");
  println("Channel:"+channel);
  println("Pitch:"+pitch);
  println("Velocity:"+velocity);
  OscMessage myMessage = new OscMessage("/nOn");
  myMessage.add(pitch);
  myBus.sendNoteOn(channel, pitch, velocity);
  oscP5.send(myMessage, myRemoteLocation);
}

void noteOff(int channel, int pitch, int velocity) {
  // Receive a noteOff
  println();
  println("Note Off:");
  println("--------");
  println("Channel:"+channel);
  println("Pitch:"+pitch);
  println("Velocity:"+velocity);
  OscMessage myMessage = new OscMessage("/nOff");
  myMessage.add(pitch);
  myBus.sendNoteOff(channel, pitch, velocity);
  oscP5.send(myMessage, myRemoteLocation);
}

void controllerChange(int channel, int number, int value) {
  // Receive a controllerChange
  println();
  println("Controller Change:");
  println("--------");
  println("Channel:"+channel);
  println("Number:"+number);
  println("Value:"+value);
  OscMessage myMessage = new OscMessage("/cchange");
  myMessage.add(channel + 1);
  myMessage.add(number);
  myMessage.add(value);
  oscP5.send(myMessage, myRemoteLocation);
}