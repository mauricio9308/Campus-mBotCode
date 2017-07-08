#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

#define MOVE_FORWARD 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3
#define MOVE_REVERSE 4
#define MOVE_DANCE 7
#define MOVE_STAR_WARS 8
#define MOVE_STOP 6

#define SLOW_SPEED 100
#define DEFAULT_SPEED 200

//Definition of the notes' frequecies in Hertz.
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

// Variable declaration
MeDCMotor motor_9(9);
MeDCMotor motor_10(10);    
MeRGBLed rgbled_7(7, 7==7?2:4);
MeBuzzer buzzer;
int isPlayingMusic = 0;
int receivedCommand;
boolean newData = false;

/*
* Helper method for the handling of the 
*/
void updateSpeed(int leftSpeed, int rightSpeed){
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}

void dance(){
    rgbled_7.setColor(1,0, 255, 213);
    rgbled_7.show();
    handle( MOVE_LEFT, SLOW_SPEED );
    _delay(1);
    handle( MOVE_RIGHT, SLOW_SPEED );
    _delay(1);
    handle( MOVE_LEFT, SLOW_SPEED );
    _delay(1);
    handle( MOVE_RIGHT, SLOW_SPEED );
    _delay(1);
    handle( MOVE_FORWARD, SLOW_SPEED );
    _delay(1);
    handle( MOVE_REVERSE, SLOW_SPEED );
    _delay(1);
    handle( MOVE_STOP, SLOW_SPEED );
    rgbled_7.setColor(1,255, 0, 255);
    rgbled_7.show();
}

/**
* Sample music playing of the Imperial march
*/
void starWars(){
    isPlayingMusic = 1;
    buzzer.tone(a, 500);
    buzzer.tone(a, 500);
    buzzer.tone(a, 500);
    buzzer.tone(f, 350);
    buzzer.tone(cH, 150);
    buzzer.tone(a, 500);
    buzzer.tone(f, 350);
    buzzer.tone(cH, 150);
    buzzer.tone(a, 650);
    
    rgbled_7.setColor(1,0, 255, 213);
    rgbled_7.show();
    handle( MOVE_LEFT, SLOW_SPEED );
    handle( MOVE_RIGHT, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
 
    //end of first bit
    
    buzzer.tone(eH, 500);    
    buzzer.tone(eH, 500);
    buzzer.tone(eH, 500);
    buzzer.tone(fH, 350);
    buzzer.tone(cH, 150);
    buzzer.tone(gS, 500);
    buzzer.tone(f, 350);
    buzzer.tone(cH, 150);
    buzzer.tone(a, 650);
    
    rgbled_7.setColor(1,55, 98, 100);
    rgbled_7.show();
    handle( MOVE_FORWARD, SLOW_SPEED );
    handle( MOVE_REVERSE, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
 
    //end of second bit...
 
    buzzer.tone(aH, 500);
    buzzer.tone(a, 300);
    buzzer.tone(a, 150);
    buzzer.tone(aH, 400);
    buzzer.tone(gSH, 200);
    buzzer.tone(gH, 200);
    buzzer.tone(fSH, 125);
    buzzer.tone(fH, 125);
    buzzer.tone(fSH, 250);

    rgbled_7.setColor(1,0, 255,0);
    rgbled_7.show();
    handle( MOVE_REVERSE, SLOW_SPEED );
    handle( MOVE_FORWARD, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
 
    buzzer.tone(aS, 250);
    buzzer.tone(dSH, 400);
    buzzer.tone(dH, 200);
    buzzer.tone(cSH, 200);
    buzzer.tone(cH, 125);
    buzzer.tone(b, 125);
    buzzer.tone(cH, 250);

    rgbled_7.setColor(1,0,0,255);
    rgbled_7.show();
    handle( MOVE_RIGHT, SLOW_SPEED );
    handle( MOVE_LEFT, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
 
    buzzer.tone(f, 125);
    buzzer.tone(gS, 500);
    buzzer.tone(f, 375);
    buzzer.tone(a, 125);
    buzzer.tone(cH, 500);
    buzzer.tone(a, 375);
    buzzer.tone(cH, 125);
    buzzer.tone(eH, 650);

    rgbled_7.setColor(1,255,0,0);
    rgbled_7.show();
    handle( MOVE_LEFT, SLOW_SPEED );
    handle( MOVE_RIGHT, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
    
    //end of third bit... (Though it doesn't play well)
    //let's repeat it
 
    buzzer.tone(aH, 500);
    buzzer.tone(a, 300);
    buzzer.tone(a, 150);
    buzzer.tone(aH, 400);
    buzzer.tone(gSH, 200);
    buzzer.tone(gH, 200);
    buzzer.tone(fSH, 125);
    buzzer.tone(fH, 125);
    buzzer.tone(fSH, 250);

    rgbled_7.setColor(1,0,255,0);
    rgbled_7.show();
    handle( MOVE_RIGHT, SLOW_SPEED );
    handle( MOVE_LEFT, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );

    buzzer.tone(aS, 250);
    buzzer.tone(dSH, 400);
    buzzer.tone(dH, 200);
    buzzer.tone(cSH, 200);
    buzzer.tone(cH, 125);
    buzzer.tone(b, 125);
    buzzer.tone(cH, 250);

    rgbled_7.setColor(1,0,0,255);
    rgbled_7.show();
    handle( MOVE_FORWARD, SLOW_SPEED );
    handle( MOVE_REVERSE, SLOW_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );
     
    buzzer.tone(f, 250);
    buzzer.tone(gS, 500);
    buzzer.tone(f, 375);
    buzzer.tone(cH, 125);
    buzzer.tone(a, 500);
    buzzer.tone(f, 375);
    buzzer.tone(cH, 125);
    buzzer.tone(a, 650);
    //end of the song

    rgbled_7.setColor(1,255,0,0);
    rgbled_7.show();
    handle( MOVE_LEFT, SLOW_SPEED );
    handle( MOVE_RIGHT, SLOW_SPEED );
    handle( MOVE_REVERSE, DEFAULT_SPEED );
    handle( MOVE_FORWARD, DEFAULT_SPEED );
    handle( MOVE_STOP, SLOW_SPEED );    
    isPlayingMusic = 0;
}

void handle(int command, int speed){
      int leftSpeed;
      int rightSpeed;
      switch( command ){
        case MOVE_FORWARD:
          leftSpeed = speed;
          rightSpeed = speed;
          break;
        case MOVE_REVERSE:
          leftSpeed = -speed;
          rightSpeed = -speed;
          break;
        case MOVE_LEFT:
          leftSpeed = -speed;
          rightSpeed = speed;
          updateSpeed( leftSpeed, rightSpeed );
          _delay(0.25);
          leftSpeed = speed;
          rightSpeed = speed;
          break;
        case MOVE_RIGHT:
          leftSpeed = speed;
          rightSpeed = -speed;
          updateSpeed( leftSpeed, rightSpeed );
          _delay(0.25);
          leftSpeed = speed;
          rightSpeed = speed;
          break;
        case MOVE_DANCE:
          dance();
          break;
        case MOVE_STAR_WARS:
          starWars();
          break;
        case MOVE_STOP:
          leftSpeed = 0;
          rightSpeed = 0;
          break;
        default:
          leftSpeed = 0;
          rightSpeed = 0;
      }

      updateSpeed(leftSpeed, rightSpeed);
}

void setup() {
    Serial.begin(115200);
    Serial.println("mBot waiting for instructions");

    // We show a yellow ready when the arduino is ready
    rgbled_7.setColor(1,156,14,179);
    rgbled_7.show();
    
    // We show a green when play music
    rgbled_7.setColor(1,255,255,0);
    rgbled_7.show();
}

void loop() {
    receiveCommand();
    handleInput();
    _delay(1.0);
}
void receiveCommand() {
    if (isPlayingMusic == 0 && Serial.available() > 0) {
        receivedCommand = Serial.read();
        newData = true;
    }
}
void handleInput() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedCommand, DEC);
        newData = false;
        rgbled_7.setColor(1,0,0,255);
        rgbled_7.show();

        handle( receivedCommand, DEFAULT_SPEED );
    }else{
        rgbled_7.setColor(1,255,0,0);
        rgbled_7.show();
    }
}
void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}
void _loop(){
  
}

