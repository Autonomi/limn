

//simple A4988 connection
//jumper reset and sleep together
//connect  VDD to Arduino 3.3v or 5v
//connect  GND to Arduino GND (GND near VDD)
//connect  1A and 1B to stepper coil 1
//connect 2A and 2B to stepper coil 2
//connect VMOT to power source (9v battery + term)
//connect GRD to power source (9v battery - term)
/*

int stp = 13;  //connect pin 13 to step
int dir = 8;  // connect pin 12 to dir

void setup() 
{                
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);  
  digitalWrite(dir, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
}


void loop() 
{
    for (int i=0; i<3200; i++) {
        digitalWrite(stp, HIGH);   
        delay(1);          
        digitalWrite(stp, LOW);  
        delay(1); 
    }
    while(1);

}
*/


int ledPin = 13;  // LED is attached to digital pin 13
int x = 0;  // variable to be updated by the interrupt

void setup() {                
  //enable interrupt 0 (pin 2) which is connected to a button
  //jump to the increment function on falling edge
  attachInterrupt(0, increment, FALLING);
  Serial.begin(9600);  //turn on serial communication
}

void loop() {
  digitalWrite(ledPin, LOW);
  delay(3000); //pretend to be doing something useful
  Serial.println(x, DEC); //print x to serial monitor
}

// Interrupt service routine for interrupt 0
void increment() {
    x++;
    digitalWrite(ledPin, HIGH);
}