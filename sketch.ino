#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Imagens.h"

#define DHT22_PIN 26
#define TCA_ADDRESS 0x70
#define DHTTYPE DHT22
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define POT_PIN 35

const int buzzer = 25;
const int btn_pino = 27;
const int btn_pino_2 = 33;

int valor_antigo = LOW;
float pivo,pivo_2,pot_valor,pot_valor_at = 0;
int pot_valor_old = -1;

float maior_umidade , maior_temp = -40;
float max_temp = 0;
float temperatura , umidade;

TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);

DHT dht(DHT22_PIN, DHTTYPE);

Adafruit_SSD1306 display(128, 64, &I2C_1, -1);
Adafruit_SSD1306 display2(128, 64, &I2C_2, -1);

void saida_display(float temperatura,float umidade,float maior_temp,float maior_umidade,float max_temp)
  {

    static unsigned long tempo = 0;
    int valor_novo = digitalRead(btn_pino_2);
    pot_valor_at = analogRead(POT_PIN);

    max_temp =  -40.0 + (pot_valor_at * 120.0 / 4095.0);
    max_temp =  constrain(max_temp, -40.0, 80.0);

    if (abs(pot_valor_at - pot_valor_old) > 20) {
      tempo = millis();
      pot_valor_old = pot_valor_at;
    }
    if (millis() - tempo < 1000) {

      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.drawBitmap(0, 0, temp_reg0, 128, 64, SSD1306_WHITE);
      display.setCursor(55, 35); 
      display.print(max_temp, 0);
      display.print(" C");
      display.display();

      pot_valor_old = pot_valor_at;

    }
    else
    {
      if(valor_novo != valor_antigo)
      {
        if(valor_novo == HIGH)
        {
          pivo = !pivo;
          valor_antigo = valor_novo;
        }
        valor_antigo = valor_novo;
      }

      if (pivo == 0)
      {

        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.drawLine(64, 0, 64, 64, SSD1306_WHITE);

        display.setTextSize(1);
        display.setCursor(3, 10);
        display.print("TEMP. MAX");

        display.setTextSize(2);
        display.setCursor(3, 27);
        display.print(maior_temp, 0);
        display.print(" C");

        display.setTextSize(1);
        display.setCursor(69, 10);
        display.print("UMID. MAX");

        display.setTextSize(2);
        display.setCursor(69, 27);

        if(maior_umidade >= 10 || maior_umidade < 0 )
        {
          display.print(maior_umidade, 0);
        }
        else
        {
          display.print(maior_umidade, 1);
        }
        
        display.setTextSize(1);
        display.setCursor(108, 32);
        display.print("%");
        
        display.setTextSize(1);
        display.setCursor(76, 54);
        display.print("LIM:");
        display.print(max_temp, 0);
        display.print("C");
        display.display();

      }
      else
      {
      }
    }


  }

void saida_display2( float temperatura , float umidade)
  {

    int valor_novo = digitalRead(btn_pino_2);

    if(valor_novo != valor_antigo)
    {
      if(valor_novo == HIGH)
      {
        pivo_2 = !pivo_2;
        valor_antigo = valor_novo;
      }
      valor_antigo = valor_novo;
    }

    if (pivo_2 == 1){
        display2.clearDisplay();
        display2.setTextSize(2);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(0, 0);
        display2.drawBitmap(0, 0, temp0, 128, 64, SSD1306_WHITE);
        if(temperatura >= 10 || temperatura < 0){
          display2.setCursor(53, 25);
          display2.print(temperatura , 0);
          display2.print(" C");
          display2.display();
        }else{
          display2.setCursor(53, 25);
          display2.print(temperatura , 1);
          display2.print(" C");
          display2.display();
        }
        
      }else{
        display2.clearDisplay();
        display2.setTextSize(2);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(0, 0);
        display2.drawBitmap(0, 0, umi0, 128, 64, SSD1306_WHITE);
        display2.setCursor(48, 25); 
        display2.print(umidade, 0);
        display2.print("%");
        display2.display();
      }
  }

void verificar_temp(float temperatura , float max_temp){
  if(temperatura > max_temp){

    display2.clearDisplay();
    display2.setTextColor(SSD1306_WHITE);
    display2.drawLine(64, 0, 64, 64, SSD1306_WHITE);

    display2.setTextSize(1);
    display2.setCursor(63, 32);
    display2.print("Temperatura muito elevada");

    display2.setCursor(63, 42);
    display2.print("Limite definido de :");
    display2.print(max_temp);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.drawBitmap(0, 0, alert_1_0, 128, 64, SSD1306_WHITE);

    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(15, HIGH);

    delay(100);

    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(15, LOW);

    delay(100);

    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(15, HIGH);

    delay(100);

    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(15, LOW);

    delay(100);

    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(15, HIGH);

    delay(100);

    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(15, LOW);

    delay(100);

    digitalWrite(4, HIGH);
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(15, HIGH);

  }
}

void setup() {
  pinMode(btn_pino_2, INPUT);
  Serial.begin(115200);
  Serial.println("Iniciando sistema...");
  dht.begin();

  I2C_1.begin(17, 16);
  I2C_2.begin(19, 18);

  Serial.println("DHT22 iniciado!");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C) || !display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro no OLED!");
    while (true);
  }

  pinMode(buzzer , OUTPUT);
  
  Serial.println("OLED funcionando!");
}

void loop() {

  temperatura = dht.readTemperature();
  umidade = dht.readHumidity();

  if(temperatura >= maior_temp || umidade >= maior_umidade)
  {
   
    if(temperatura >= maior_temp){
      maior_temp = temperatura;
    }
    if (umidade >= maior_umidade){
      maior_umidade = umidade;
    }
  }

  saida_display2
  (
    temperatura,
    umidade
  );

  saida_display
  (
    temperatura,
    umidade,
    maior_temp,
    maior_umidade,
    max_temp
  );

  verificar_temp(temperatura,max_temp);



}