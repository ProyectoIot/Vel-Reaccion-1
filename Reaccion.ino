#include <Average.h>

#include <TimerOne.h>

bool var=false;
volatile unsigned long tiempo = 0;
int num=10;
int tiempo_prueba [10];

//Average<float> ave(10);
 int minat = 0;
 int maxat = 0;

int prueba=0;
int retardo=3000;
int cant_pruebas;
String modo ="";
int t_aleat=0;

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
     //Serial.println(orden);
     int pos_i=orden.indexOf("<");
     int pos_f=orden.indexOf(">");
    if (pos_i>=0 & pos_f>=0) {
      String contenido=orden.substring(pos_i+1,pos_f);
      //Serial.println(contenido);
       int u=orden.indexOf("-");
      if (u>0)
      {
        modo=contenido.substring(0,u-1);
        contenido=contenido.substring(u);
         u=contenido.indexOf("-");
         if (u>0)
         { 
         String x= contenido.substring(0,u);
         cant_pruebas=x.toInt();
         String x1=contenido.substring(u+1);
         t_aleat=x1.toInt();
         }
         else 
         {
          String x= contenido.substring(0,u);
         cant_pruebas=x.toInt();
         t_aleat=0;
         }
                
//        Serial.println(modo);
//        Serial.println(cant_pruebas);
//        Serial.println(t_aleat);
                
       reaccion(modo,cant_pruebas,t_aleat);
      }
     }
   }
  }



void handleInterrupt() {
  var=true;
  digitalWrite(7,LOW); // apaga el sensor
    
}

void cont_Tiempo(void)
{
  tiempo=tiempo+1;
  
}

void reaccion (String modo,int cant_pruebas, int t_aleat){

  Serial.println("START");
  Average<float> ave(cant_pruebas);
  
 if (modo=="1")
 { 
  tiempo=0;
  Serial.println("LED");
  
 while(prueba<cant_pruebas)
 {
  delay(1);
if(var==true)
{
  Serial.print("PRUEBA"+ (String)(prueba+1) +":");
  Serial.println(tiempo);
  //Serial.println(" ms");
  tiempo_prueba[prueba]=tiempo;
  ave.push(tiempo);
  int d=analogRead(A5);
  randomSeed(d);
  retardo=retardo+random(t_aleat)*1000;
  //Serial.println(retardo);
  delay(retardo);
  var=false;
  //interrupts();
  prueba+=1;
   
    if(prueba==cant_pruebas)
   {
    
    Serial.print("Mean:"); Serial.println(ave.mean());
    Serial.print("Mode:"); Serial.println(ave.mode());
    Serial.print("Max:"); Serial.println(ave.maximum(&maxat));
    Serial.print("pos_max:"); Serial.println(maxat+1);
    Serial.print("Min:"); Serial.println(ave.minimum(&minat));
    Serial.print("pos_min:"); Serial.println(minat+1);
    Serial.print("StdDev:"); Serial.println(ave.stddev());

   
    
   }
   else 
   {
     digitalWrite(7,HIGH);
     Serial.println("LED");
     tiempo=0;
   }
   }
 
  }

  Serial.println("END");
   prueba=0;
 }
}
