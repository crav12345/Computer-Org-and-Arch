const int tiltSwitchPin = 9;    // pin tilt switch is on
unsigned long previousTime = 0; // time last LED's state was changed

// Variables used to compare switch position from one loop() call
// to the next.
int switchState = 0;
int prevSwitchState = 0;

int led = 4;                    // LED pin # we start w/
long interval = 2000;           // 2000 milliseconds between lights

#include <Servo.h>  // Import Servo library
Servo myServo;      // Instance of Servo library

void setup() {
  myServo.attach(10); // Set output pin for servo
  myServo.write(0);   // Set servo default position

  // Make pins 4-8 output pins
  for (int x = 4; x < 8; x++) {
    pinMode(x, OUTPUT);
  } // for

  // Set the pin which we will attach the tilt switch to as
  // an input pin.
  pinMode(tiltSwitchPin, INPUT);
} // setup

void loop() {
  // Amount of milliseconds for which the Arduino has been running
  unsigned long currentTime = millis();

  // Check to see if enough time has passed since the last LED
  // was turned on. If 2 seconds (2000 ms) have passed, the
  // instructions inside will execute.
  if (currentTime - previousTime > interval){
    previousTime = currentTime;

    // turn on the next LED in the sequence and increment the
    // LED counter.
    digitalWrite(led, HIGH);
    led++;

    // Once we've incremented past the last LED pin...
    if (led == 8){
      // ...wait 2 seconds so user can see last LED lit...
      delay(2000);
      // ...then we play our song.
      playMusic();

      // Then, put all the lights back to how they were before
      // the song played.
      for (int x = 4; x < 8; x++)
        digitalWrite(x, HIGH);

      // Turn off all the LEDs in the reversed order.
      for (int x = 8; x > 3; x--){
        digitalWrite(x, LOW);
        delay(2000);
      } // for
      
      // Reset the LED loop by setting the led variable back
      // to the first LED we will turn on.
      led = 4;

      // Wiggle the servo back and forth to show that the
      // song has ended and we are restarting the
      // process!
      wiggleServo();
    } // if
  } // if

  // check the current state of the tiltSwitch
  switchState = digitalRead(tiltSwitchPin);
  // If the current state is different, it means
  // the tilt switch has picked up some motion. So...
  if (switchState != prevSwitchState){
    // ...turn off all the LEDs...
    for (int x = 4; x < 8; x++){
      digitalWrite(x, LOW);
    } // for

    // ...and reset the counter.
    led = 4;

    // also, reset the difference in previousTime and
    // currentTime.
    previousTime = currentTime;
  }// if

  // Update the previous switch value to the one
  // we just evaluated.
  prevSwitchState = switchState;
} // loop

int playMusic(){
  //====================SETTING UP MUSIC======================
  // Music from robsoncouto on GitHub ************************
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978
  #define REST      0

  // This array will hold instances of the above
  // definitions which will determine the pitch
  // the piezo plays. Every second value represents
  // the duration of the note (quarter, eight, or
  // sixteenth. Every third value determines which
  // LED turns on.
  int melody[] = {
    REST, 4, 4,
    REST, 8, 7,
    REST, 8, 6,
    REST, 8, 5,
    NOTE_E4, 8, 7, 
    NOTE_A4, 8, 6,
    NOTE_C5, 8, 5,
    NOTE_B4, 8, 4,
    NOTE_A4, 8, 7,
    NOTE_C5, 8, 6,
    NOTE_A4, 8, 5,
    NOTE_B4, 8, 4,
    NOTE_A4, 8, 5,
    NOTE_F4, 8, 6,
    NOTE_G4, 8, 7,
    NOTE_E4, 2, 4,
    NOTE_E4, 8, 7,
    NOTE_A4, 8, 4,
    NOTE_C5, 8, 5,
    NOTE_B4, 8, 6,
    NOTE_A4, 8, 7,
    NOTE_C5, 8, 6,
    NOTE_A4, 8, 4,
    NOTE_C5, 8, 5,
    NOTE_A4, 8, 4,
    NOTE_E4, 8, 6,
    NOTE_DS4, 8, 5,
    NOTE_D4, 2, 7,
    NOTE_D4, 8, 7,
    NOTE_F4, 8, 5,
    NOTE_GS4, 8, 4,
    NOTE_B4, 2, 6,
    NOTE_D4, 8, 5,
    NOTE_F4, 8, 6,
    NOTE_GS4, 8, 7, 
    NOTE_A4, 2, 4,
    NOTE_C4, 8, 5,
    NOTE_C4, 8, 4,
    NOTE_G4, 8, 7,
    NOTE_F4, 8, 6,
    NOTE_E4, 8, 5,
    NOTE_G4, 8, 4,
    NOTE_F4, 8, 7,
    NOTE_F4, 8, 6,
    NOTE_E4, 8, 4,
    NOTE_E4, 8, 7,
    NOTE_GS4, 8, 6,
    NOTE_A4, 2, 5,  //Stop here
    
    /*
    REST,8, 5,
    
    NOTE_A4, 8, 6, 
    NOTE_A4, 8, 7,
    NOTE_GS4, 8, 4,
    NOTE_G4, 2, 5,
    NOTE_B4, 8, 4,
    NOTE_A4, 8, 5,
    NOTE_F4, 8, 4,
    NOTE_E4, 2, 5,
    NOTE_E4, 8, 6,
    NOTE_G4, 8, 7,
    NOTE_E4, 8, 6,
    NOTE_D4, 2, 7,
    NOTE_D4, 8, 6,
    NOTE_D4, 8, 7,
    NOTE_F4, 8, 5,
    NOTE_DS4, 8, 7,
    NOTE_E4, 2, 6,
    REST, 8, 4,
    NOTE_E4, 8, 5, 
    NOTE_A4, 8, 6,
    NOTE_C5, 8, 5,
    NOTE_B4, 8, 6,
    NOTE_A4, 8, 5,
    NOTE_C5, 8, 4,
    NOTE_A4, 8, 7,
    NOTE_B4, 8, 4,
    NOTE_A4, 8, 7,
    NOTE_F4, 8, 6,
    NOTE_G4, 8, 7,
    NOTE_E4, 2, 5,
    NOTE_E4, 8, 4,
    NOTE_A4, 8, 7,
    NOTE_C5, 8, 6,
    NOTE_B4, 8, 5,
    NOTE_A4, 8, 4,
    NOTE_C5, 8, 7,
    NOTE_A4, 8, 6,
    NOTE_C5, 8, 5,
    NOTE_A4, 8, 4,
    NOTE_E4, 8, 5,
    NOTE_DS4, 8,6,
    NOTE_D4, 2, 7,
    NOTE_D4, 8, 4,
    NOTE_F4, 8, 6,
    NOTE_GS4, 8, 5,
    NOTE_B4, 2, 7,
    NOTE_D4, 8, 4,
    NOTE_F4, 8, 6,
    NOTE_GS4, 8,5,
    NOTE_A4, 2, 7,
    NOTE_C4, 8, 6,
    NOTE_C4, 8, 7,
    NOTE_G4, 8, 6,
    NOTE_F4, 8, 5,
    NOTE_E4, 8, 4,
    NOTE_G4, 8, 7,
    NOTE_F4, 8, 6,
    NOTE_F4, 8, 5,
    NOTE_E4, 8, 4,
    NOTE_E4, 8, 7,
    NOTE_GS4, 8, 6,
    NOTE_A4, 2, 7,
    REST,8, 4,
    NOTE_A4, 8, 5,
    NOTE_A4, 8, 6,
    NOTE_GS4, 8, 4,
    NOTE_G4, 2, 6,
    NOTE_B4, 8, 7,
    NOTE_A4, 8, 7,
    NOTE_F4, 8, 4,
    NOTE_E4, 2, 7,
    NOTE_E4, 8, 5,
    NOTE_G4, 8, 7,
    NOTE_E4, 8,6,
    NOTE_D4, 2, 7,
    NOTE_D4, 8, 4,
    NOTE_D4, 8, 5,
    NOTE_F4, 8, 6,
    NOTE_DS4, 8, 7,
    NOTE_E4, 2, 4
    */
  }; // melody

  int tempo = 80;   // Value to determine speed of the tune
  int buzzer = 8;   // Value to tell us where the piezo is attached

  // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
  // there are two values per note (pitch and duration), so for each note there are four bytes
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

  // this calculates the duration of a whole note in ms
  int wholenote = (60000 * 4) / tempo;

  int divider = 0, noteDuration = 0;
  
  //==========================================================
  
  //=====================PLAYING MUSIC========================
  // Iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 3) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    } // else if

    //============LEDs=============
    // The third int in the array
    // will determine which light
    // comes on.
    int ledNum = melody[thisNote + 2];
    
    for (int x = 4; x < 8; x++){
      digitalWrite(x, LOW);
    } // for

    digitalWrite(ledNum, HIGH);
    //=============================

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  } // for
  //==========================================================
  
  return 1;
} // playMusic

// WiggleServo() does just that. It rotates the servo back and
// forth. It is called whenever the song stops playing.
int wiggleServo(){
  // Rotate to 179 degrees and wait a moment
  myServo.write(179);
  delay(1000);
  // Rotate back to 0 and wait another moment
  myServo.write(0);
  delay(1000);
  
  // Do it again
  myServo.write(179);
  delay(1000);
  myServo.write(0);
  delay(1000);
  return 1;
} // wiggleServo
