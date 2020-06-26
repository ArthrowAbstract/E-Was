#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(4, 10); // CE, CSN
const byte address[][6] = {"00001", "00002"};

int trig = 3;
int echo = 4;

int gasStatus(){                          // takes input from gas sensor
  int gasValue = analogRead(A3);
  int message = 0;
  if (gasValue>400){
    message = 1;
    }
  return message;
  } 

int binStatus() {                         // takes input from HC SR04 ultrasonic sensor
  digitalWrite(trig, LOW);
delayMicroseconds(2);

digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);

int duration = pulseIn(echo, HIGH);

int distance= duration*0.034/2;

Serial.print("Distance: ");
Serial.println(distance);

int message =0;

if (distance < 3){
  message =1;
  
  }

 return message;
  
 }

void setup() {

radio.begin();
radio.openWritingPipe(address[0]); // 00001 - the next gbin to which we will send our own and forward other's messages
radio.openReadingPipe(1, address[1]); // 00002 - the previous gbin from which we will receive messages
radio.setPALevel(RF24_PA_MIN);

pinMode(trig,OUTPUT);
pinMode(echo,INPUT);




}

int messageReceived(){
  delay(5);
  char message[30] = "";
  
  if ( radio.available()) {
    while (radio.available()) {
      
      radio.read(message, sizeof(message));
      
    }
  }
  if (message != ""){
    radio.stopListening();
    radio.write(message, sizeof(message));

    
    }

    return 0;
} 

void loop() {
radio.startListening();

int binMessage = binStatus();
int gasMessage = gasStatus();

bool sendMessage = false;

int rem = 0;
if (binMessage == gasMessage == 1){
  
  rem =  1;
  sendMessage =true;
 
  }

  
 else if (binMessage == 1){
  
  rem =2;
  sendMessage =true;
    
  }


  
  else if ( gasMessage == 1){
  
  rem =3 ;
  sendMessage =true;
  
  }
 

  
  
  if (sendMessage){                                         // there will be a 5 minute window for sending and receiving of messages
    radio.stopListening();                                  // There are two cases now:
   if (rem == 1){                                           // 1 )if gbin requires to send a message regarding gases or fullness->
    char str[40] = "Bin is FULL + Toxic waste present";     //    - sendMessage will be true and messages will be sent to the next gbin    
    radio.write(str, sizeof (str));                         // 2 )if gbin does not require to send a message       
    }                                                       // after either of these the reading pipe will be reopened and ready to receive messages
    else if (rem == 2 ){                                    // after 1 hour the entire process is repeated, checking for fullness, gases
      char str[40] = "Bin is FULL ";                        // and comunication between the two bins
      radio.write(str, sizeof(str));
      }
    else if (rem == 3){
      char str[40] = "Toxic waste present ";
      radio.write(str,sizeof(str));
      } 
    
    }
  
    radio.startListening();
    int foo = messageReceived();
    delay (5*60*1000);                      
    
      
  delay (1 * 60 * 60 * 1000);
  }
 

  
