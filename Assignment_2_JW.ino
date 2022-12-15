//declare sensor pins and values

const int button1Pin = 2;
const int button2Pin = 3;
const int trigPin = 6;
const int echoPin = 5;
const int pot1Pin = A0;
const int pot2Pin = A1;
const int fsrPin = A5;
const int pot3Pin = A3;
const int pot4Pin = A4;

int button1Value = 0;
int button2Value = 0;
int pot1Value = 0;
int pot2Value = 0;
int pot3Value = 0;
int pot4Value = 0;
int fsrValue = 0;

//declare led pins

const int led1 = 13;
const int led2 = 12;
const int led3 = 11;
const int led4 = 10;

const int ledDrum1 = 9;
const int ledDrum2 = 8;
const int ledDrum3 = 7;

int inByte = 0;

float duration;
float distance;




void setup() {

//set pinModes for sensors

Serial.begin(9600);

pinMode(button1Pin, INPUT);
pinMode(button2Pin, INPUT);
pinMode(pot1Pin, INPUT);
pinMode(pot2Pin, INPUT);
pinMode(pot3Pin, INPUT);
pinMode(pot4Pin, INPUT);
pinMode(fsrPin, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

//set pinModes for leds

pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);

pinMode(ledDrum1, OUTPUT);
pinMode(ledDrum2, OUTPUT);
pinMode(ledDrum3, OUTPUT);

}

void loop() {

//sensor Values are taken from their pins - these are what will be printed and sent to max

button1Value = digitalRead(button1Pin);
button2Value = digitalRead(button2Pin);
pot1Value = analogRead(pot1Pin);
pot2Value = analogRead(pot2Pin);
pot3Value = analogRead(pot3Pin);
pot4Value = analogRead(pot4Pin);
fsrValue = analogRead(fsrPin);

//the ultrasonic sensor requires the below code and calulation

 digitalWrite(trigPin, LOW); //clear trigPin
 delayMicroseconds(2); //2 microsecond delay
 digitalWrite(trigPin, HIGH); //set trigPin hight
 delayMicroseconds(10); // delay 10 microseconds
 digitalWrite(trigPin, LOW); //set trigPin low

 duration = pulseIn(echoPin, HIGH); //reads echoPin and returns the time the soundwave has travelled in microsecconds
 distance = (duration*.0343)/2; // calculates the distance by multiplying the wave duration by the speed of sound divided by 2
                                //the distnce value is what will be printed to the serial


inByte = Serial.read(); //reads any data coming in from max

//sensor values are printed for Max to be able to read, with a space (32) in between each, then final with a println so as to end the message.

Serial.print(button1Value);
Serial.write(32);
Serial.print(button2Value);
Serial.write(32);
Serial.print(pot1Value);
Serial.write(32);
Serial.print(pot2Value);
Serial.write(32);
Serial.print(pot3Value);
Serial.write(32);
Serial.print(pot4Value);
Serial.write(32);
Serial.print(fsrValue);
Serial.write(32);
Serial.print(distance); 
Serial.write(32);
Serial.println(inByte);


//leds to be triggered...

if (inByte == 2) digitalWrite(led1, HIGH),  digitalWrite(led2, LOW), digitalWrite(led3, LOW), digitalWrite(led4, LOW);
if (inByte == 3) digitalWrite(led1, LOW),  digitalWrite(led2, HIGH), digitalWrite(led3, LOW), digitalWrite(led4, LOW);
if (inByte == 4) digitalWrite(led1, LOW),  digitalWrite(led2, LOW), digitalWrite(led3, HIGH), digitalWrite(led4, LOW);
if (inByte == 5) digitalWrite(led1, LOW),  digitalWrite(led2, LOW), digitalWrite(led3, LOW), digitalWrite(led4, HIGH);

if (inByte == 6) { digitalWrite(ledDrum1, HIGH), digitalWrite(ledDrum2, HIGH);
delay (75); 
digitalWrite(ledDrum1, LOW), digitalWrite(ledDrum2, LOW);
}
if (inByte == 7) { digitalWrite(ledDrum2, HIGH); 
delay (75); 
digitalWrite(ledDrum2, LOW) ;
}

if (inByte == 8) { digitalWrite(ledDrum3, HIGH); 
delay (75); 
digitalWrite(ledDrum3, LOW);
}

if (inByte == 0) digitalWrite(led1, LOW),  digitalWrite(led2, LOW), digitalWrite(led3, LOW), digitalWrite(led4, LOW),
                 digitalWrite(ledDrum1, LOW),  digitalWrite(ledDrum2, LOW), digitalWrite(ledDrum3, LOW);                






delay(65); //delay set so as not to overload max - multiple delay settings were tried so there was no 'lag' between max and Arduino

}
