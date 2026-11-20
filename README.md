# 🌡️ termo_controll

<p align="center">
  <strong>Sistema de Monitoramento de Temperatura e Umidade</strong>
  <br>
  Sistemas Embarcados • ESP32 • IoT • Engenharia da Computação
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-ESP32-red?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus" />
  <img src="https://img.shields.io/badge/Simulation-Wokwi-purple?style=for-the-badge" />
</p>

---

## 📖 Sobre o projeto

O **termo_controll** é um projeto acadêmico de sistemas embarcados desenvolvido com o microcontrolador ESP32, destinado ao monitoramento de temperatura e umidade do ambiente.

O sistema utiliza o sensor DHT22 para aquisição dos dados ambientais e dois displays OLED SSD1306 para apresentação das informações.

A aplicação também implementa uma lógica de estados operacionais, permitindo identificar condições normais, situações de alerta e falhas durante o funcionamento.

O projeto conta com interfaces de visualização, botões de interação, um potenciômetro para ajuste do limite de temperatura e um buzzer para sinalização sonora de alertas.

O desenvolvimento, a montagem do circuito e a validação inicial são realizados através da plataforma Wokwi.

## 🎯 Objetivos

- Realizar a leitura periódica de temperatura e umidade.
- Exibir informações através de dois displays OLED.
- Implementar controle de intervalos utilizando `millis()`.
- Desenvolver uma lógica de estados operacionais.
- Permitir o ajuste do limite de temperatura através de um potenciômetro.
- Identificar condições de alerta.
- Tratar falhas e leituras inválidas.
- Aplicar conceitos de programação embarcada e monitoramento ambiental.

## 🛠️ Tecnologias e componentes

| Componente / Tecnologia | Utilização |
|---|---|
| ESP32 | Microcontrolador principal |
| DHT22 | Sensor de temperatura e umidade |
| 2x OLED SSD1306 | Interfaces de visualização |
| Potenciômetro | Ajuste do limite máximo de temperatura |
| Botões | Navegação e interação com as interfaces |
| Buzzer | Sinalização sonora de alertas |
| Arduino C/C++ | Desenvolvimento do firmware |
| Wokwi | Simulação eletrônica |

## 🔌 Arquitetura do hardware

O projeto é constituído pelos seguintes componentes:

- **ESP32:** unidade central de processamento, responsável pelo controle dos dispositivos e execução do firmware.
- **DHT22:** realiza a medição da temperatura e da umidade do ambiente.
- **Dois displays OLED SSD1306:** apresentam informações diferentes sobre o funcionamento do sistema.
- **Potenciômetro:** permite ajustar o limite máximo de temperatura utilizado pelo sistema.
- **Botões:** permitem interagir com as interfaces e alternar entre as informações exibidas.
- **Buzzer:** emite um sinal sonoro quando a temperatura ultrapassa o limite configurado.

### Diagrama de conexões

| Componente | Pino ESP32 |
|---|---|
| DHT22 DATA | GPIO 26 |
| Potenciômetro | GPIO 35 |
| Buzzer | GPIO 25 |
| Botão 1 | GPIO 27 |
| Botão 2 | GPIO 33 |
| OLED 1 SDA / SCL | GPIO 17 / GPIO 16 |
| OLED 2 SDA / SCL | GPIO 19 / GPIO 18 |

## ⚙️ Funcionamento do sistema

O funcionamento do termo_controll é organizado em um fluxo de execução:

1. Inicialização do ESP32 e dos componentes.
2. Aquisição dos dados do sensor DHT22.
3. Verificação da validade das leituras.
4. Processamento das informações de temperatura e umidade.
5. Leitura do potenciômetro para definição do limite de temperatura.
6. Determinação do estado operacional.
7. Atualização das interfaces OLED e acionamento dos alertas, quando necessário.

As leituras do sensor são realizadas periodicamente, utilizando `millis()` para controlar o intervalo entre as aquisições sem bloquear a execução do programa.

## 🖥️ Interfaces de visualização

O sistema utiliza dois displays OLED SSD1306, cada um com uma finalidade específica.

**Display principal:**
- Exibição dos valores máximos registrados de temperatura e umidade.
- Apresentação do limite máximo de temperatura configurado.
- Exibição dos contadores de falhas e situações de excesso de temperatura.

**Segundo display:**
- Alternância entre as informações de temperatura e umidade.
- Apresentação de informações relacionadas ao estado atual do sistema.
- Exibição de mensagens de alerta e falha.

Os botões permitem navegar entre as informações, tornando a interação com o sistema mais prática.

## 🚦 Estados operacionais

O sistema trabalha com três estados principais:

| Estado | Descrição |
|---|---|
| 🟢 NORMAL | Temperatura dentro do limite estabelecido e leituras válidas. |
| 🟡 ALERTA | Temperatura acima do limite configurado, com sinalização visual e sonora. |
| 🔴 FALHA | Identificação de problemas ou leituras inválidas do sensor. |

### Funcionamento do alerta

O limite máximo de temperatura pode ser ajustado através do potenciômetro.

Quando a temperatura medida ultrapassa esse limite, o sistema entra no estado de alerta, atualiza as interfaces OLED e aciona o buzzer.

O estado de alerta possui prioridade sobre as informações normais, mantendo a sinalização enquanto a condição permanecer ativa.

### Simulação de falha

O sistema também possui um recurso para simular falhas durante os testes.

Para ativar ou desativar a simulação, basta abrir o Monitor Serial e pressionar a tecla **F**.

Quando ativada, a simulação representa uma falha na aquisição dos dados do sensor, permitindo verificar o comportamento do sistema diante de leituras inválidas.

## 🖥️ Simulação

O circuito e o firmware são desenvolvidos e testados utilizando o simulador online Wokwi.

<p align="center">
  <a href="https://wokwi.com/projects/480669874309969921">
    <img src="https://img.shields.io/badge/ABRIR_SIMULAÇÃO-WOKWI-purple?style=for-the-badge" />
  </a>
</p>

**Plataforma:** Wokwi  
**Microcontrolador:** ESP32  
**Ambiente:** Simulação de sistemas embarcados.

## 🔄 Workflow de desenvolvimento

O desenvolvimento segue uma abordagem incremental, organizada nas seguintes etapas:

| Etapa | Atividade |
|---|---|
| 01 — Planejamento | Definição dos requisitos e componentes. |
| 02 — Desenvolvimento | Implementação do firmware. |
| 03 — Integração | Comunicação entre ESP32, DHT22 e displays OLED. |
| 04 — Simulação | Execução e observação do circuito no Wokwi. |
| 05 — Testes | Verificação das leituras, interfaces e estados operacionais. |
| 06 — Documentação | Organização dos resultados e funcionalidades. |

## 🧪 Testes e validação

Os testes são realizados através de simulações no Wokwi, considerando diferentes condições de funcionamento.

Os cenários de validação incluem:

- Leitura de temperatura.
- Leitura de umidade.
- Atualização das informações nos dois displays OLED.
- Navegação entre as interfaces através dos botões.
- Ajuste do limite de temperatura pelo potenciômetro.
- Verificação do estado NORMAL.
- Ativação do estado ALERTA quando o limite é ultrapassado.
- Acionamento do buzzer.
- Simulação de falhas através da tecla F no Monitor Serial.
- Tratamento de leituras inválidas do sensor.

## 🚀 Melhorias futuras

- Aprimoramento das interfaces de visualização.
- Expansão dos cenários de testes.
- Implementação de novas condições de alerta.
- Melhorias no tratamento de falhas.
- Possível integração com sistemas de monitoramento remoto.

## 👨‍💻 Desenvolvimento

Projeto acadêmico desenvolvido no contexto da disciplina de Engenharia da Computação.

**Área:** Sistemas Embarcados  
**Projeto:** termo_controll  
**Microcontrolador:** ESP32

---

<p align="center">
  <strong>termo_controll</strong>
  <br>
  Monitoramento ambiental através da tecnologia embarcada.
  <br><br>
  <sub>Desenvolvido com ESP32 • C/C++ • Wokwi</sub>
</p>
