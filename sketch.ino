
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
int valor_antigo_2 = LOW;
int pot_valor_at = 0;
int pot_valor_old = -1;

bool pivo = 0;
bool pivo_2 = 0;
bool simular_falha = false;

float maior_umidade = 0;
float maior_temp = -40;
float max_temp = -40;
float temperatura = NAN;
float umidade = NAN;

unsigned long ultima_leitura = 0;
unsigned long contador_falhas = 0;
unsigned long contador_excesso = 0;

TwoWire I2C_1 = TwoWire(0);
TwoWire I2C_2 = TwoWire(1);

DHT dht(DHT22_PIN, DHTTYPE);

Adafruit_SSD1306 display(128, 64, &I2C_1, -1);
Adafruit_SSD1306 display2(128, 64, &I2C_2, -1);

void saida_display(float temperatura, float umidade, float maior_temp, float maior_umidade, bool simular_falha)
{
    // ALTERAÇÃO: Mostra erro0 sem bloquear a execução do programa
    if (simular_falha) {

        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.drawBitmap(0, 0, erro0, 128, 64, SSD1306_WHITE);
        display.display();

        return;
    }

    static unsigned long tempo = 0;

    int valor_novo = digitalRead(btn_pino);
    pot_valor_at = analogRead(POT_PIN);

    if (abs(pot_valor_at - pot_valor_old) > 20) {
        tempo = millis();
        pot_valor_old = pot_valor_at;
    }

    if (valor_novo != valor_antigo) {
        if (valor_novo == HIGH) {
            pivo = !pivo;
        }

        valor_antigo = valor_novo;
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

    }
    else if (pivo == 0) {

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

        if (maior_umidade >= 10 || maior_umidade < 0) {
            display.print(maior_umidade, 0);
        }
        else {
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
    else {

        // Tela dividida entre os contadores
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);

        display.drawLine(64, 0, 64, 64, SSD1306_WHITE);

        // Contador de excessos
        display.setTextSize(1);
        display.setCursor(5, 8);
        display.print("EXCESSOS");

        display.setTextSize(2);
        display.setCursor(5, 30);
        display.print(contador_excesso);

        // Contador de falhas
        display.setTextSize(1);
        display.setCursor(70, 8);
        display.print("FALHAS");

        display.setTextSize(2);
        display.setCursor(70, 30);
        display.print(contador_falhas);

        display.display();

    }
}

void saida_display2(float temperatura, float umidade, bool simular_falha)
{
    // ALTERAÇÃO: Mostra erro0 sem bloquear a execução do programa
    if (simular_falha) {

        display2.clearDisplay();
        display2.setTextSize(2);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(0, 0);
        display2.drawBitmap(0, 0, erro0, 128, 64, SSD1306_WHITE);
        display2.display();

        return;
    }

    int valor_novo = digitalRead(btn_pino_2);

    if (valor_novo != valor_antigo_2) {
        if (valor_novo == HIGH) {
            pivo_2 = !pivo_2;
        }

        valor_antigo_2 = valor_novo;
    }

    if (pivo_2 == 1) {

        display2.clearDisplay();
        display2.setTextSize(2);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(0, 0);
        display2.drawBitmap(0, 0, temp0, 128, 64, SSD1306_WHITE);

        if (!isnan(temperatura)) {

            if (temperatura >= 10 || temperatura < 0) {
                display2.setCursor(53, 25);
                display2.print(temperatura, 0);
            }
            else {
                display2.setCursor(53, 25);
                display2.print(temperatura, 1);
            }

            display2.print(" C");

        }
        else {
            display2.setCursor(40, 30);
            display2.print("ERRO");
        }

        display2.display();

    }
    else {

        display2.clearDisplay();
        display2.setTextSize(2);
        display2.setTextColor(SSD1306_WHITE);
        display2.setCursor(0, 0);
        display2.drawBitmap(0, 0, umi0, 128, 64, SSD1306_WHITE);
        display2.setCursor(48, 25);

        if (!isnan(umidade)) {
            display2.print(umidade, 0);
            display2.print("%");
        }
        else {
            display2.print("ERRO");
        }

        display2.display();

    }
}

void verificar_temp(float temperatura, float max_temp)
{
    static bool alerta_anterior = false;

    // ALTERAÇÃO: Impede que o alerta de temperatura sobrescreva erro0
    if (simular_falha) {
        noTone(buzzer);
        alerta_anterior = false;
        return;
    }

    bool alerta = !isnan(temperatura) && temperatura > max_temp;

    if (alerta) {

        display.clearDisplay();
        display.drawBitmap(0, 0, alert_1_0, 128, 64, SSD1306_WHITE);
        display.display();

        display2.clearDisplay();
        display2.setTextColor(SSD1306_WHITE);
        display2.setTextSize(1);

        display2.setCursor(12, 10);
        display2.print("Temperatura");

        display2.setCursor(12, 27);
        display2.print("acima do");

        display2.setCursor(12, 44);
        display2.print("limite");

        display2.display();

        // Conta somente quando um novo alerta começa
        if (!alerta_anterior) {

            contador_excesso++;

            tone(buzzer, 2000);

            Serial.println("ALERTA: Temperatura acima do limite!");
            Serial.print("Total de excessos: ");
            Serial.println(contador_excesso);
        }

    }
    else {

        noTone(buzzer);

    }

    alerta_anterior = alerta;
}

void setup()
{
    pinMode(btn_pino, INPUT);
    pinMode(btn_pino_2, INPUT);

    pinMode(buzzer, OUTPUT);

    analogReadResolution(12);

    Serial.begin(115200);
    Serial.println("Iniciando sistema...");

    dht.begin();

    I2C_1.begin(17, 16);
    I2C_2.begin(19, 18);

    Serial.println("DHT22 iniciado!");

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Erro no OLED 1!");
        while (true);
    }

    if (!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Erro no OLED 2!");
        while (true);
    }

    noTone(buzzer);

    Serial.println("OLED funcionando!");
    Serial.println("Digite F para simular uma falha.");
}


void loop()
{
    if (Serial.available() > 0) {

        char comando = Serial.read();

        if (comando == 'F' || comando == 'f') {

            simular_falha = !simular_falha;

            if (simular_falha) {
                Serial.println("SIMULACAO DE FALHA ATIVADA!");
            }
            else {
                Serial.println("SIMULACAO DE FALHA DESATIVADA!");
            }
        }
    }

    if (millis() - ultima_leitura >= 2000) {

        ultima_leitura = millis();

        float nova_temperatura = dht.readTemperature();
        float nova_umidade = dht.readHumidity();

        if (simular_falha) {
            nova_temperatura = NAN;
            nova_umidade = NAN;
        }

        if (!isnan(nova_temperatura) && !isnan(nova_umidade)) {

            temperatura = nova_temperatura;
            umidade = nova_umidade;

            if (temperatura >= maior_temp) {
                maior_temp = temperatura;
            }

            if (umidade >= maior_umidade) {
                maior_umidade = umidade;
            }

            Serial.print("Temperatura: ");
            Serial.println(temperatura);

            Serial.print("Umidade: ");
            Serial.println(umidade);

        }
        else {

            contador_falhas++;

            temperatura = NAN;
            umidade = NAN;

            Serial.println("Erro na leitura do DHT22!");

            Serial.print("Total de falhas: ");
            Serial.println(contador_falhas);

        }
    }

    pot_valor_at = analogRead(POT_PIN);

    max_temp = -40.0 + (pot_valor_at * 120.0 / 4095.0);
    max_temp = constrain(max_temp, -40.0, 80.0);

    // Verifica se existe excesso de temperatura
    bool alerta = !isnan(temperatura) && temperatura > max_temp;

    // Prioridade 1: Simulação de falha
    if (simular_falha) {

        saida_display2(temperatura, umidade, simular_falha);

        saida_display(
            temperatura,
            umidade,
            maior_temp,
            maior_umidade,
            simular_falha
        );

        verificar_temp(temperatura, max_temp);

    }

    // Prioridade 2: Alerta de temperatura
    else if (alerta) {

        verificar_temp(temperatura, max_temp);

    }

    // Prioridade 3: Funcionamento normal
    else {

        saida_display2(temperatura, umidade, simular_falha);

        saida_display(
            temperatura,
            umidade,
            maior_temp,
            maior_umidade,
            simular_falha
        );

        verificar_temp(temperatura, max_temp);

    }
}
