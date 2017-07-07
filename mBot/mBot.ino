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

/**
* Sample music playing of the Imperial march
*/
void starWars( ){
    // TODO implement
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
    // TODO implement
}
void handleInput() {
    // TODO implement
}
void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}
void _loop(){
  
}

