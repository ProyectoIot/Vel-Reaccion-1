#include <Average.h>

#include <TimerOne.h>

bool var=false;
volatile unsigned long tiempo = 0;
int num=10;
int tiempo_prueba [10];

Average<float> ave(10);
 int minat = 0;
 int maxat = 0;

int prueba=0;
int retardo=5000;

char orden="";

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(7,OUTPUT);
 // encoder pin on interrupt 0 (pin 2)
// FALLING to trigger on transition from dark to light
// RISING  to trigger on transition from light to dark
// CHANGE to trigger on either transition
 attachInterrupt(digitalPinToInterrupt(2), handleInterrupt, RISING); 

Timer1.initialize(1000);
  Timer1.attachInterrupt(cont_Tiempo); // blinkLED to run every 1 miliseconds
 digitalWrite(7,HIGH);
 Serial.println("START");

 
}



void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available()) {

     String orden = Serial.readStringUntil('\n');
     Serial.println(orden);
     int pos_i=orden.indexOf("<");
     int pos_f=orden.indexOf(">");
    if (pos_i>=0 & pos_f>=0) {
      String contenido=orden.substring(pos_i+1,pos_f);
      Serial.println(contenido);
      if (contenido=="1")
      {
        reaccion();
      }
     }
     
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

void reaccion (){
Serial.println("BEGIN");

 while(prueba<5)
 {
  delay(1);
if(var==true)
{
  Serial.print("Prueba "+ (String)(prueba+1) +" : ");
  Serial.print(tiempo);
  Serial.println(" ms");
  tiempo_prueba[prueba]=tiempo;
  ave.push(tiempo);
  delay(retardo);
  var=false;
  //interrupts();
  prueba+=1;
   
    if(prueba==5)
   {
    
    Serial.print("Mean:   "); Serial.println(ave.mean());
    Serial.print("Mode:   "); Serial.println(ave.mode());
    Serial.print("Max:    "); Serial.println(ave.maximum(&maxat));
    Serial.print(" at:    "); Serial.println(maxat+1);
    Serial.print("Min:    "); Serial.println(ave.minimum(&minat));
    Serial.print(" at:    "); Serial.println(minat+1);
    Serial.print("StdDev: "); Serial.println(ave.stddev());
   
   }
   else 
   {
     digitalWrite(7,HIGH);
     Serial.println("Begin");
     tiempo=0;
   }
   }
   
  }

  Serial.println("END");
}
