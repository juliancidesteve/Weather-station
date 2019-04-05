

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

const unsigned pin_reciv=12;

unsigned estado=1;

DHT dht(DHTPIN, DHTTYPE);

//Definimos las palabras clave del control remoto
decode_results results;
IRrecv reciv(pin_reciv);//Recibir en el pin 12

const unsigned rs = 5, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//***************** _FUNCIONES_ ***************************


void LeerLuz(){
  unsigned valor=map(analogRead(A0),0,1023,0,100);
  lcd.setCursor(0,0);
  lcd.print("Cantidad de luz:");
  lcd.setCursor(6,1);
  lcd.print(valor);lcd.print("%");
  }

void TempHumedad(){
  
  float t=dht.readTemperature();
  float h=dht.readHumidity();
    if(isnan(h) || isnan(t) ){
      lcd.setCursor(0,0);
      lcd.print("No muy taki taki");
      return;
    }
    lcd.setCursor(0,0);
    lcd.print("Humed: ");
    lcd.setCursor(0,1);
    lcd.print(h);
    lcd.setCursor(8,0);
    lcd.print("Temp: ");
    lcd.setCursor(8,1);
    lcd.print(t);lcd.print("C");
}


//**********************************************************

void setup() {
 Serial.begin(9600);

 reciv.enableIRIn();
 dht.begin();
 lcd.begin(16, 2);
 lcd.setCursor(3,0);
 lcd.print("Hello Moto");
 delay(1500);
digitalWrite(2,HIGH);
 pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(3,LOW);
  delay(100);
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(3,LOW);

 
}

void loop() {
  if(reciv.decode(&results)){
     switch(results.value){
      case 0xFFA25D: estado=0;break; //apagado     
      case 0xFF30CF: estado=1;lcd.setCursor(2,0);lcd.print("TempHumedad");break;
      case 0xFF18E7: estado=2;lcd.setCursor(6,0);lcd.print("Luz");break;
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
    lcd.clear();
    switch(estado){
      case 1: TempHumedad();break;
      case 2: LeerLuz();break;
      //case 3: ;break;
    }
    lcd.clear();
  }
}
