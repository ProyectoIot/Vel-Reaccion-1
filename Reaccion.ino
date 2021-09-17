#include <TimerOne.h>

bool var=false;
volatile unsigned long tiempo = 0;
int prueba=0;
int retardo=5000;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(7,OUTPUT);
 // encoder pin on interrupt 0 (pin 2)
// FALLING to trigger on transition from dark to light
// RISING  to trigger on transition from light to dark
// CHANGE to trigger on either transition
 attachInterrupt(0, handleInterrupt, RISING); 

Timer1.initialize(1000);
  Timer1.attachInterrupt(cont_Tiempo); // blinkLED to run every 1 miliseconds
 digitalWrite(7,HIGH);
 Serial.println("START");
 
}



void loop() {
  // put your main code here, to run repeatedly:

if (prueba<5)
{
if(var==true)
{
  Serial.print("Prueba "+ (String)(prueba+1) +" : ");
  Serial.print(tiempo);
  Serial.println(" ms");
  delay(retardo);
  var=false;
  //interrupts();
  prueba+=1;
  digitalWrite(7,HIGH);
  Serial.println("Begin");
  tiempo=0;
   } 
   
   }
   else if(prueba==5)
   {
    prueba=11;
    Serial.println("FIN");
    }
  
}

void handleInterrupt() {
  var=true;
  digitalWrite(7,LOW);
  
  
  
}

void cont_Tiempo(void)
{
  tiempo=tiempo+1;
  
}
