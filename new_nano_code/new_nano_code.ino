#include <Servo.h>

Servo entryservo;
Servo exitservo;
int entry1 = 2;
int exit1 = 3;
//========================================================================================
int pos = 0; 
int count = 0;
int count1 = 0;
int slot = 0;
int slot2,i;
int cm1 = 0;     // Defining variable for ultrasonic distance
int cm2 = 0;

int led[] = {A0,A1,A2,A3,A4,A5,4,11,13,12}; 

//========================================================================================
void turnoff()                                  //Turnoff all the LEDs
 {
    for(int i = 0; i<=9;i++)
    {
      digitalWrite(led[i],HIGH);
    }
 }
//=========================================================================================
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);  
  delayMicroseconds(2);
 
  digitalWrite(triggerPin, HIGH);   // send the ultrasound 
  delayMicroseconds(10);              // wait for 10ms
  digitalWrite(triggerPin, LOW);     
  pinMode(echoPin, INPUT);
 
  return pulseIn(echoPin, HIGH);     //recive the ultrasound 
  
  /* calculation of formula: Distance = (Time x SpeedOfSound) / 2   
     2 is in the formula because the sound has to travel back and forth.
     First the sound travels away from the sensor,
     and then it bounces off of a surface and returns back.
     
     *******speed of sound is 240m/s***********
  */
}
//========================================================================================

void checktraffic(int dis1, int dis2)                         //this function is use for check traffic
{
  if(dis1 >= 30 && dis2 >=30)                              // if no traffic then use forward path 
  {
    forward();
  }
  else if(slot == 3 && dis1 <= 19 && dis2 >=30)         // all the else if conditions will check for traffic and
  {                            //if satisfy the condition then it will go reverse
    reverse();
  }
  else if(slot == 2 && dis1 <= 11 && dis2 >= 30)
  {
    reverse();
  }
  else if(slot == 1 && dis1 <= 5 && dis2 >= 30)
  {
    reverse();
  }
  else if(slot == 4 && dis1 >= 30 && dis2 <= 5)
  {
    reverse();
  }
  else if(slot == 5 && dis1 >= 30 && dis2 <= 11)
  {
    reverse();
  }
  else if(slot == 6 && dis1 >= 30 && dis2 <= 19)
  {
    reverse();
  }
  else                        //By default it will go forwars path
  {
    forward();
  }
}
//=======================================================================================
 void forward()                            // Forward path LED glow
 {
                            // open the Entry gate       
    if(slot >= 1 && slot <= 3)               // for slot 1,2,3
    {
      for(i= 0; i <= (slot) ; i ++)
      {
        digitalWrite(led[i],LOW);
      }
    }
    else if(slot >= 4 && slot <= 6)          // for slot 4,5,6
    {
      for(i= 5; i <= (slot+2) ; i ++)
      {
        digitalWrite(led[i],LOW);
      }
    }
    //servoentry(); 
    delay(15000);
                       // wait 10second
    turnoff();                             // turnoff all LEDs
 }
//========================================================================================
 void reverse()                           // Reverse LEDs will glow
 {    
                            // open the Entry gate 
   if(slot >= 1 && slot <= 3 )             // for slot 1,2,3
    {
     for(int i = 5 ; i <= 9 ; i++)
      {
        digitalWrite(led[i],LOW);
      }
     for(int j = 4; j >= slot ; j = j-1)
     {
       digitalWrite(led[j],LOW);
     }
   }
     if(slot >= 4 && slot <= 6)           // for slot 4,5,6
    {
      for(int i = 0; i <= 4 ; i++)
      {
        digitalWrite(led[i],LOW);
      }
      for(int j = 9; j >= (slot+2) ; j = j-1)
      {
        digitalWrite(led[j],LOW);
      }
    }
   // servoentry();
   delay(15000);
   turnoff();
 }

//--------------------------------------------------------------------------------------------------------SERVO-ENTRY--------
 void servoentry()                       // this function is to control the servo motor on entry gate
 {
   for (pos = 0; pos <= 180; pos += 1) {       // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    entryservo.write(pos);                     // tell servo to go to position in variable 'pos'
    delay(15);                                 // waits 15ms for the servo to reach the position
  }
             
  delay(2000); 
  for (pos = 180; pos >= 0; pos -= 1) {        // goes from 180 degrees to 0 degrees
    entryservo.write(pos);                     // tell servo to go to position in variable 'pos'
    delay(15);                                 // waits 15ms for the servo to reach the position
  }
 }

 
//--------------------------------------------------------------------------------------------------------SERVO-EXIT--------
 void servoexit()                          // this function will controll the servo motor in exit gate
{ 
   for (pos = 0; pos <= 180; pos += 1) 
   { 
       exitservo.write(pos);              
       delay(15);                     
   }
        
   delay(2000); 
   for (pos = 180; pos >= 0; pos -= 1) 
   { 
        exitservo.write(pos);              
        delay(15);
   }
}

//========================================================================================

void setup() 
{
  entryservo.attach(6);      // attach servo to PWM pin 6 and 5
  exitservo.attach(5);
  
  pinMode(entry1,INPUT);       // defining entry gate IR sensor pin to input mode
  pinMode(exit1,INPUT);         //defining exit gate IR sensor pin to input mode
  Serial.begin(115200);
  for(int i = 0; i <= 9; i++)    // for loop is for defining all the LEDs to OUTPUT nmode
    {
      pinMode(led[i],OUTPUT);
    } 
  turnoff();
}

//===========================================================================================

void loop() {
  if(digitalRead(entry1) == 0){
    while(count < 1)
    {
      Serial.print("0"); 
      delay(1000);
      count++; 
    }
    if(Serial.available() > 0)                      // this will check weather serial monitor has any input ot not 
    {
        char serialc = Serial.read();
        slot = int(serialc-'0');
        if (slot >= 1 && slot <= 6)
        {
           char serialc = Serial.read();
           slot2 = int(serialc-'0');
           cm2 = 0.01723 * readUltrasonicDistance(7,8 );    //Read the distsnce of ultrasonic sensor 1 and 2
           cm1 = 0.01723 * readUltrasonicDistance(9, 10);     //  and display it on serial monitor
           
           checktraffic(cm1,cm2);
         }
      }
    
  }
  else if(digitalRead(exit1) == 0){
    while(count1 <1)
    {
    Serial.print("1");
    delay(1000);
    count1++;
    }
  //  servoexit(); 
  }
  else{
    count = 0;
    count1 = 0;
  }
}
