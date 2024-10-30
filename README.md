# Documentação do Código de Monitoramento de Temperatura

## Introdução
Este documento descreve o código desenvolvido para monitorar a temperatura utilizando um sensor analógico conectado a um Arduino. O sistema realiza a leitura dos dados do sensor, converte-os para Celsius e Fahrenheit, armazena esses dados em um banco de dados simulado e simula o envio dos dados para um servidor IoT.

## Constantes Globais

```cpp
#define SENSOR_PIN A0               // Pino analógico do sensor
#define VOLTAGE_REF 5.0             // Tensão de referência do Arduino (em Volts)
#define RESOLUTION 1024             // Resolução do ADC (10 bits)
#define SENSOR_OFFSET 0.5           // Offset do sensor (em Volts)
#define CONVERSION_FACTOR 100.0     // Fator de conversão do sensor (10mV/°C)
#define MAX_RECORDS 10              // Capacidade máxima do pseudo banco de dados
#define DELAY_TIME 20000            // Intervalo de tempo entre as leituras (em milissegundos)
```

- **SENSOR_PIN**: Define o pino analógico conectado ao sensor de temperatura.
- **VOLTAGE_REF**: Tensão de referência usada pelo ADC do Arduino.
- **RESOLUTION**: Resolução do ADC em bits.
- **SENSOR_OFFSET**: Offset do sensor em volts.
- **CONVERSION_FACTOR**: Fator de conversão para transformar a leitura do sensor em temperatura.
- **MAX_RECORDS**: Capacidade máxima do banco de dados simulado.
- **DELAY_TIME**: Intervalo entre as leituras de temperatura, em milissegundos.

## Estrutura de Dados

```cpp
struct TempData {
    float temperaturaC;
    float temperaturaF;
    unsigned long timestamp;
};
```

- **TempData**: Estrutura que armazena a temperatura em Celsius e Fahrenheit e o timestamp de cada leitura.

## Banco de Dados Simulado

```cpp
TempData tempDB[MAX_RECORDS];
int recordIndex = 0;
```

- **tempDB**: Array para armazenar os dados de temperatura.
- **recordIndex**: Índice para gerenciar o armazenamento no banco de dados simulado.

## Funções

### Prototipagem

```cpp
float lerSensor();
float calcularTemperaturaC(float valorSensor);
float calcularTemperaturaF(float temperaturaC);
void armazenarDados(float temperaturaC, float temperaturaF);
void enviarDadosIoT();
void exibirBancoDados();
```

- **lerSensor**: Lê o valor do sensor de temperatura.
- **calcularTemperaturaC**: Converte o valor do sensor em temperatura Celsius.
- **calcularTemperaturaF**: Converte a temperatura em Celsius para Fahrenheit.
- **armazenarDados**: Armazena os dados de temperatura no banco de dados simulado.
- **enviarDadosIoT**: Simula o envio dos dados para um servidor IoT.
- **exibirBancoDados**: Exibe o conteúdo do banco de dados simulado.

### Função de Setup

```cpp
void setup() {
    pinMode(SENSOR_PIN, INPUT);
    Serial.begin(9600);
    Serial.println("Iniciando sistema de monitoramento de temperatura...");
}
```

- **setup**: Configura o pino do sensor como entrada e inicializa a comunicação serial.

### Função Principal de Loop

```cpp
void loop() {
    float valorSensor = lerSensor();
    float temperaturaC = calcularTemperaturaC(valorSensor);
    float temperaturaF = calcularTemperaturaF(temperaturaC);
    armazenarDados(temperaturaC, temperaturaF);
    enviarDadosIoT();
    exibirBancoDados();
    delay(DELAY_TIME);
}
```

- **loop**: Realiza leituras do sensor, cálculos de temperatura, armazenamento e simulação de envio de dados em um ciclo contínuo.

### Função para Ler o Sensor

```cpp
float lerSensor() {
    return analogRead(SENSOR_PIN);
}
```

- **lerSensor**: Lê e retorna o valor do sensor de temperatura.

### Função para Calcular a Temperatura em Celsius

```cpp
float calcularTemperaturaC(float valorSensor) {
    float voltage = valorSensor * (VOLTAGE_REF / RESOLUTION);
    return (voltage - SENSOR_OFFSET) * CONVERSION_FACTOR;
}
```

- **calcularTemperaturaC**: Converte o valor lido do sensor para tensão e calcula a temperatura em Celsius.

### Função para Calcular a Temperatura em Fahrenheit

```cpp
float calcularTemperaturaF(float temperaturaC) {
    return (temperaturaC * 1.8) + 32;
}
```

- **calcularTemperaturaF**: Converte a temperatura de Celsius para Fahrenheit.

### Função para Armazenar Dados

```cpp
void armazenarDados(float temperaturaC, float temperaturaF) {
    tempDB[recordIndex].temperaturaC = temperaturaC;
    tempDB[recordIndex].temperaturaF = temperaturaF;
    tempDB[recordIndex].timestamp = millis();
    recordIndex = (recordIndex + 1) % MAX_RECORDS;
}
```

- **armazenarDados**: Armazena os dados de temperatura e atualiza o índice para o próximo armazenamento.

### Função para Enviar Dados para IoT

```cpp
void enviarDadosIoT() {
    Serial.print("Enviando dados para o servidor IoT (simulado)... ");
    Serial.print("Temperatura (°C): ");
    Serial.print(tempDB[recordIndex].temperaturaC);
    Serial.print(", Temperatura (°F): ");
    Serial.print(tempDB[recordIndex].temperaturaF);
    Serial.print(", Timestamp: ");
    Serial.println(tempDB[recordIndex].timestamp);
}
```

- **enviarDadosIoT**: Simula o envio dos dados para um servidor IoT e exibe no monitor serial.

### Função para Exibir o Banco de Dados

```cpp
void exibirBancoDados() {
    Serial.println("Exibindo banco de dados simulado:");
    for (int i = 0; i < MAX_RECORDS; i++) {
        Serial.print("Registro ");
        Serial.print(i + 1);
        Serial.print(" - Celsius: ");
        Serial.print(tempDB[i].temperaturaC);
        Serial.print(", Fahrenheit: ");
        Serial.print(tempDB[i].temperaturaF);
        Serial.print(", Timestamp: ");
        Serial.println(tempDB[i].timestamp);
    }
}
```

- **exibirBancoDados**: Exibe todos os registros armazenados no banco de dados no monitor serial.
