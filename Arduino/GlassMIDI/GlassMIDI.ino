#include <Servo.h>
#include <MIDI.h>
#include <AccelStepper.h>

/*
 * References:
 * Teensy PWM functions (https://www.pjrc.com/teensy/td_pulse.html)
 */
 
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midi_in);
const int stepsPerRevolution = 3200;
AccelStepper stepper(AccelStepper::DRIVER, 9, 8);
float motorSpeed = 100;              // Speed of the stepper motor

// Control servo motors using a combination of MIDI note OFF/ON messages (0x80/0x90) and Control Change (CC) message values
typedef struct {
    byte note;                  // MIDI note number
    Servo servo;                // Servo object
    int servo_min_pos = 0;      // Minimum servo position
    int servo_max_pos = 180;    // Maximum servo position
    int note_home_pos = 0;      // Note home position, set by cc_knob (between servo_min_pos and servo_max_pos)
    int note_end_pos = 0;       // Note end position, set by cc_slider (between note_home_pos and servo_max_pos)
    byte cc_slider = 0;         // Control Change slider number
    byte cc_knob = 0;           // Control Change knob number
} servo_note; // End definition

// Control stepper motors using only CC messages
typedef struct {
    int stepper_pulse_pin;      // Stepper motor pulse pin
    bool stepper_dir_pin;       // Stepper motor direction pin
    byte cc_knob = 0;           // Control Change knob number
} stepper_CC; // End definition

// Control solenoids using both MIDI note ON/OFF and CC messages
typedef struct {
    byte note;                  // MIDI note number
    byte solenoid_pin;          // Solenoid pin number
    int solenoid_min_pwm = 0;   // Minimum PWM duty cycle (0 -> 0%);
    int solenoid_max_pwm = 255; // Maximum PWM duty cycle (255 -> 100%);
    int velocity = 0;           // MIDI note velocity
    byte cc_slider = 0;         // Control Change slider number
} solenoid_note; // End definition

int kbd = 1; // AKM320 keyboard channel
int korg = 2; // Korg Nanokontrol2 channel

int led_pin = 13; // LED pin number

// Servo note objects
servo_note C, D, E, F;

// Stepper object
stepper_CC Glass;

// Note On message handler
void OnNoteOn(byte channel, byte note, byte velocity)  {
    // Print out the message received over serial
    digitalWrite(led_pin, HIGH);
    Serial.print("NOTE ON\tChannel: ");
    Serial.print(channel);
    Serial.print("\tNote: ");
    Serial.print(note);
    Serial.print("\tVelocity: ");
    Serial.println(velocity);

    // If the note came fron the keyboard:
    if (channel == kbd) {
        if (note == C.note) {
            C.servo.write(C.note_end_pos);
        } else if (note == D.note) {
            D.servo.write(D.note_end_pos);
        } else if (note == E.note) {
            E.servo.write(E.note_end_pos);
        } else if (note == F.note) {
            F.servo.write(F.note_end_pos);
        }
    } else if (channel == korg) {
        // Korg doesn't send MIDI notes
    }
}

// Note Off message handler
void OnNoteOff(byte channel, byte note, byte velocity) {
    // Print out the message received over serial
    digitalWrite(led_pin, LOW);
    Serial.print("NOTE OFF\tChannel: ");
    Serial.print(channel);
    Serial.print("\tNote: ");
    Serial.print(note);
    Serial.print("\tVelocity: ");
    Serial.println(velocity);
    if (channel == kbd) {
        if (note == C.note) {
            C.servo.write(C.note_home_pos);
        } else if (note == D.note) {
            D.servo.write(D.note_home_pos);
        } else if (note == E.note) {
            E.servo.write(E.note_home_pos);
        } else if (note == F.note) {
            F.servo.write(F.note_home_pos);
        }
  } else if (channel == korg) {
    // ???
  }
}

// Control Change message handler
void OnControlChange(byte channel, byte control, byte value) {
    // Print out the message received over serial
    Serial.print("Channel: ");
    Serial.print(channel);
    Serial.print("\tControl: ");
    Serial.print(control);
    Serial.print("\tValue: ");
    Serial.println(value);
    
    // If the note came fron the keyboard:
    if (channel == 2) {
        if (control == 21) { // Control change for wheel
            motorSpeed = value * 100;
            stepper.setSpeed(motorSpeed);
        }
    } else if (channel == 3) {
        if (control == C.cc_slider) {
            C.note_end_pos = map(value, 0, 127, C.note_home_pos, C.servo_max_pos);
            C.servo.write(C.note_end_pos);
        } else if (control == C.cc_knob) {
            C.note_home_pos = map(value, 0, 127, C.servo_min_pos, C.servo_max_pos);
            C.servo.write(C.note_home_pos);
        } else if (control == D.cc_slider) {
            D.note_end_pos = map(value, 0, 127, D.note_home_pos, D.servo_max_pos);
            D.servo.write(D.note_end_pos);
        } else if (control == D.cc_knob) {
            D.note_home_pos = map(value, 0, 127, D.servo_min_pos, D.servo_max_pos);
            D.servo.write(D.note_home_pos);
        } else if (control == E.cc_slider) {
            E.note_end_pos = map(value, 0, 127, E.note_home_pos, E.servo_max_pos);
            E.servo.write(E.note_end_pos);
        } else if (control == E.cc_knob) {
            E.note_home_pos = map(value, 0, 127, E.servo_min_pos, E.servo_max_pos);
            E.servo.write(E.note_home_pos);
        } else if (control == F.cc_slider) {
            F.note_end_pos = map(value, 0, 127, F.note_home_pos, F.servo_max_pos);
            F.servo.write(F.note_end_pos);
        } else if (control == F.cc_knob) {
            F.note_home_pos = map(value, 0, 127, F.servo_min_pos, F.servo_max_pos);
            F.servo.write(F.note_home_pos);
        }
    }
}

void setup() {
    Serial.begin(9600);
    
    stepper.setMaxSpeed(10000);
    stepper.setSpeed(0);

    // Attach the servos to the respective pins
    C.servo.attach(3);
    D.servo.attach(5);
    E.servo.attach(6);
    F.servo.attach(10);

    // Set the note, slider, and knob values for C
    C.note = 60;
    C.cc_slider = 0;
    C.cc_knob = 16;

    // Set the note, slider, and knob values for D
    D.note = 62;
    D.cc_slider = 1;
    D.cc_knob = 17;

    // Set the note, slider, and knob values for E
    E.note = 64;
    E.cc_slider = 2;
    E.cc_knob = 18;

    // Set the note, slider, and knob values for F
    F.note = 65;
    F.cc_slider = 3;
    F.cc_knob = 19;

    // Set the pulse pin, direction pin, and knob values for the stepper motor
    Glass.stepper_pulse_pin = 3;
    Glass.stepper_dir_pin = 5;
    Glass.cc_knob = 21;

    // Misc. setup
    pinMode(led_pin, OUTPUT);
    pinMode(Glass.stepper_dir_pin, OUTPUT);
    pinMode(Glass.stepper_dir_pin, OUTPUT);
    
    midi_in.setHandleNoteOff(OnNoteOff);
    midi_in.setHandleNoteOn(OnNoteOn);
    midi_in.setHandleControlChange(OnControlChange);

    midi_in.begin(MIDI_CHANNEL_OMNI);
    Serial1.begin(115200);
    
    digitalWrite(led_pin, HIGH);
    delay(1000);
    digitalWrite(led_pin, LOW);
    delay(1000);
}

// Read MIDI input
void loop() {
   midi_in.read();
   stepper.runSpeed();
}

