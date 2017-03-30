import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import themidibus.*; 
import oscP5.*; 
import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class MIDItoOSC extends PApplet {

// Libraries




int port = 0;

OscP5 oscP5; // OSC Object
NetAddress myRemoteLocation;

MidiBus myBus; // The MidiBus
MidiBus myBus2;
MidiBus myBus3;

public void setup() {
  
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

public void draw() {
}

public void noteOn(int channel, int pitch, int velocity) {
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

public void noteOff(int channel, int pitch, int velocity) {
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

public void controllerChange(int channel, int number, int value) {
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
  public void settings() {  size(400, 400); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "MIDItoOSC" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
