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
  <img src="https://img.shields.io/badge/Version_Control-Git-orange?style=for-the-badge&logo=git" />
</p>

---

## 📖 Sobre o projeto

O **termo_controll** é um projeto acadêmico de sistemas embarcados desenvolvido com o microcontrolador ESP32, destinado ao monitoramento de temperatura e umidade do ambiente.

O sistema utiliza o sensor DHT22 para aquisição dos dados ambientais e um display OLED SSD1306 para apresentação das informações.

A aplicação também implementa uma lógica de estados operacionais, permitindo identificar condições normais, situações de alerta e falhas durante o funcionamento.

O desenvolvimento, a montagem do circuito e a validação inicial são realizados através da plataforma Wokwi.

## 🎯 Objetivos

- Realizar a leitura periódica de temperatura e umidade.
- Exibir informações em tempo real através de um display OLED.
- Implementar controle de intervalos utilizando `millis()`.
- Desenvolver uma lógica de estados operacionais.
- Identificar condições de alerta.
- Tratar falhas e leituras inválidas.
- Aplicar conceitos de programação embarcada e monitoramento ambiental.

## 🛠️ Tecnologias e componentes

| Tecnologia | Utilização |
|---|---|
| ESP32 | Microcontrolador principal |
| DHT22 | Sensor de temperatura e umidade |
| OLED SSD1306 | Interface de visualização |
| Arduino C/C++ | Desenvolvimento do firmware |
| Wokwi | Simulação eletrônica |
| Git | Controle de versão |
| GitHub | Hospedagem e documentação |

## 🔌 Arquitetura do hardware

O projeto utiliza os seguintes componentes:

- ESP32 como unidade central de processamento.
- DHT22 conectado ao GPIO 26.
- Display OLED SSD1306 com comunicação I2C.
- GPIO 22 para SDA.
- GPIO 21 para SCL.

### Diagrama de conexões

| Componente | Pino ESP32 |
|---|---|
| DHT22 DATA | GPIO 26 |
| OLED SDA | GPIO 22 |
| OLED SCL | GPIO 21 |
| Alimentação | Conforme especificação dos módulos |

## ⚙️ Funcionamento do sistema

O funcionamento do termo_controll é organizado em um fluxo de execução:

1. Inicialização dos componentes.
2. Aquisição dos dados do sensor DHT22.
3. Verificação da validade das leituras.
4. Processamento das informações.
5. Determinação do estado operacional.
6. Atualização do display OLED.

## 🚦 Estados operacionais

O sistema trabalha com três estados principais:

| Estado | Descrição |
|---|---|
| 🟢 NORMAL | Condições dentro dos parâmetros estabelecidos. |
| 🟡 ALERTA | Temperatura ou condição ambiental que exige atenção. |
| 🔴 FALHA | Problemas na aquisição ou validade das leituras. |

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
| 03 — Integração | Comunicação entre ESP32, DHT22 e OLED. |
| 04 — Simulação | Execução e observação do circuito no Wokwi. |
| 05 — Testes | Verificação das leituras e estados operacionais. |
| 06 — Versionamento | Registro das alterações utilizando Git e GitHub. |
| 07 — Documentação | Organização dos resultados e funcionalidades. |

## 📌 Versionamento

O projeto utiliza Git e GitHub para controle de versão e acompanhamento da evolução do desenvolvimento.

As alterações são registradas através de commits, permitindo manter um histórico organizado das implementações e correções.

### Padrão de commits

| Prefixo | Finalidade |
|---|---|
| `feat` | Nova funcionalidade |
| `fix` | Correção de problemas |
| `refactor` | Reestruturação do código |
| `docs` | Atualização da documentação |
| `test` | Implementação de testes |

### Exemplos

```bash
feat: adiciona leitura do DHT22
feat: implementa interface OLED
feat: adiciona controle de estados
fix: corrige validação das leituras
docs: atualiza README
```

## 🧪 Testes e validação

Os testes são realizados através de simulações no Wokwi, considerando diferentes condições de funcionamento.

Os cenários de validação incluem:

- Leitura de temperatura.
- Leitura de umidade.
- Atualização das informações no OLED.
- Verificação dos estados NORMAL e ALERTA.
- Identificação de leituras inválidas.
- Tratamento de falhas do sensor.

Os resultados detalhados devem ser registrados conforme a execução dos testes.

## 📂 Estrutura do repositório

```text
termo_controll/
│
├── sketch.ino
├── diagram.json
├── libraries.txt
│
├── docs/
│   ├── workflow.md
│   ├── testes.md
│   └── resultados.md
│
└── README.md
```

## 🚀 Melhorias futuras

- Aprimoramento da interface de visualização.
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
