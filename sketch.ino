#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT22_PIN 26
#define DHTTYPE DHT22

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 22
#define OLED_SCL 21

DHT dht(DHT22_PIN, DHTTYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {

  // Serial.begin(115200);
  // Serial.println("OI!");
  Serial.begin(115200);

  Serial.println("Iniciando sistema...");

  dht.begin();

  Serial.println("DHT22 iniciado!");

  Wire.begin(OLED_SDA, OLED_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro no OLED!");
    while (true);
  }

  // // 
  // pinMode(27 , OUTPUT);
  // pinMode(26, INPUT);
  // pinMode(22 , OUTPUT); 
  // pinMode(21 , OUTPUT);
  // pinMode(25 , OUTPUT);
  // pinMode(14 , OUTPUT);
  pinMode(15 , INPUT);

  Serial.println("OLED funcionando!");

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("Kaua");

  display.setCursor(0, 25);
  display.println("Lindo");

  display.display();
}

void loop() {

  Serial.println("Realizando leitura...");

  float temperatura = dht.readTemperature();
  float umidade = dht.readHumidity();

  int btn = digitalRead(15);

  Serial.println(btn);

  if (isnan(temperatura) || isnan(umidade)) {

    Serial.println("ERRO: Falha na leitura do DHT22!");

  } else {

    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" C");

    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %");
  }

  Serial.println("--------------------");

  delay(2000);
}
