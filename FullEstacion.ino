//CAMBIAR AL NANOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
// poner alimentacion de la pantalla a pin digital que se apague cuando pulse boton de apagar
//Poner buzzer y leds 

#include <LiquidCrystal.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <IRremote.h>
#include <IRremoteInt.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const unsigned pin_reciv=11;

unsigned estado=1;

DHT dht(DHTPIN, DHTTYPE);

//Definimos las palabras clave del control remoto
decode_results results;
IRrecv reciv(pin_reciv);//Recibir en el pin 11

//***************** _FUNCIONES_ ***************************


void LeerLuz(){
  unsigned valor=map(analogRead(A0),0,1023,0,100);
    Serial.print(valor);Serial.println("%");
  }

void TempHumedad(){
  float t=dht.readTemperature();
  float h=dht.readHumidity();
    if(isnan(h) || isnan(t) ){
      Serial.println("No muy taki taki");
      return;
    }
      Serial.print("Humedad: ");
      Serial.println(h);
      Serial.print("Temperatura: ");
      Serial.println(t);
}


//**********************************************************

void setup() {
 Serial.begin(9600);
 Serial.println("Hello Moto");
 reciv.enableIRIn();
 dht.begin();
}

void loop() {
  
  if(reciv.decode(&results)){
     switch(results.value){
      case 0xFFA25D: estado=0;break; //apagado     
      case 0xFF30CF: estado=1;Serial.println("TempHumedad");break;
      case 0xFF18E7: estado=2;Serial.println("Luz");break;
      case 0xFF7A85: estado=3;break;
     /* case 0xFF10EF: estado=4;break;
      case 0xFF38C7: estado=5;break;
      case 0xFF5AA5: estado=6;break;
      case 0xFF42BD: estado=7;break;
      case 0xFF4AB5: estado=8;break;
      case 0xFF52AD: estado=9;break;*/
    }
    reciv.resume();
    delay(1000);
  }

  if(estado!=0){
    switch(estado){
      case 1: TempHumedad();break;
      case 2: LeerLuz();break;
     // case 3: ;break;
    }
  }
}
