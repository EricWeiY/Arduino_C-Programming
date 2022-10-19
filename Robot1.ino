//hong wai yao kong kai shi
#include <IRremote.h>

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);

decode_results results;
//hong wai yao kong jie shu

//kai shi dong
int aForward = 3;
int aBackward = 4;
int bRight = 5;
int bLeft = 6;
int dRight = 9;
int dLeft = 10;
int cBackward = 12;
int cForward = 13;
int buttonstate1 = 0;

void forward() {
  digitalWrite(aForward,HIGH);
  digitalWrite(aBackward,LOW);
  digitalWrite(cForward,HIGH);
  digitalWrite(cBackward,LOW);
}
void backward() {
  digitalWrite(aBackward,HIGH);
  digitalWrite(aForward,LOW);
  digitalWrite(cBackward,HIGH);
  digitalWrite(cForward,LOW);
}
void leftForward() {
  digitalWrite(aForward,HIGH);
  digitalWrite(aBackward,LOW);
  digitalWrite(bLeft,HIGH);
  digitalWrite(bRight,LOW);
}
void rightForward() {
  digitalWrite(cForward,HIGH);
  digitalWrite(cBackward,LOW);
  digitalWrite(bRight,HIGH);
  digitalWrite(bLeft,LOW);
}
void left() {
  digitalWrite(bLeft,HIGH);
  digitalWrite(bRight,LOW);
  digitalWrite(dLeft,HIGH);
  digitalWrite(dRight,LOW); 
}
void right() {
  digitalWrite(bRight,HIGH);
  digitalWrite(bLeft,LOW);
  digitalWrite(dRight,HIGH); 
  digitalWrite(dLeft,LOW); 
}
void leftBackward() {
  digitalWrite(aBackward,HIGH);
  digitalWrite(aForward,LOW); 
  digitalWrite(dLeft,HIGH);
  digitalWrite(dRight,LOW);
}
void rightBackward() {
  digitalWrite(cBackward,HIGH);
  digitalWrite(cForward,LOW);
  digitalWrite(dRight,HIGH);
  digitalWrite(dLeft,LOW);
}
void brake(){
 digitalWrite(aForward,LOW);
 digitalWrite(aBackward,LOW);
 digitalWrite(bLeft,LOW);
 digitalWrite(bRight,LOW);
 digitalWrite(cForward,LOW);
 digitalWrite(cBackward,LOW);
 digitalWrite(dLeft,LOW);
 digitalWrite(dRight,LOW);
}
//bu dong le



void setup() {
   pinMode(3,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(12,OUTPUT);
   pinMode(13,OUTPUT);

// hong wai yao kong
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
   
  // put your setup code here, to run once:

}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(0);

if(results.value == 0xFF38C7){
  buttonstate1 = 0;
} else if(results.value == 0xFF18E7){
  buttonstate1 = 1;
}
if(buttonstate1 == 1){
 forward();
}

if(results.value == 0xFF4AB5){
  buttonstate1 = 2;
}
if(buttonstate1 == 2){
backward ();
}

if(results.value == 0xFF10EF){
  buttonstate1 = 3;
}
if(buttonstate1 == 3){
left ();
}

 if(results.value == 0xFF5AA5){
  buttonstate1 = 4;
}
if(buttonstate1 == 4){
right ();
}

 if(results.value == 0xFF30CF){
  buttonstate1 = 5;
}
if(buttonstate1 == 5){
leftForward ();
}

if(results.value == 0xFF7A85){
  buttonstate1 = 6;
}
if(buttonstate1 == 6){
rightForward ();
}

 if(results.value == 0xFF42BD){
  buttonstate1 = 7;
}
if(buttonstate1 == 7){
leftBackward ();
}

 if(results.value == 0xFF52AD){
  buttonstate1 = 8;
}
if(buttonstate1 == 8){
rightBackward ();
}
 
if(buttonstate1 == 0){
 brake ();
}


 
}
