// Constantes globais
#define SENSOR_PIN A0               // Pino analógico do sensor
#define VOLTAGE_REF 5.0             // Tensão de referência do Arduino (em Volts)
#define RESOLUTION 1024             // Resolução do ADC (10 bits)
#define SENSOR_OFFSET 0.5           // Offset do sensor (em Volts)
#define CONVERSION_FACTOR 100.0     // Fator de conversão do sensor (10mV/°C)
#define MAX_RECORDS 10              // Capacidade máxima do pseudo banco de dados
#define DELAY_TIME 20000             // Intervalo de tempo entre as leituras (em milissegundos)

// Estrutura para armazenar dados de temperatura
struct TempData {
    float temperaturaC;
    float temperaturaF;
    unsigned long timestamp;
};

// Banco de dados simulado
TempData tempDB[MAX_RECORDS];
int recordIndex = 0;  // Índice de armazenamento no pseudo banco de dados

// Prototipagem de funções
float lerSensor();
float calcularTemperaturaC(float valorSensor);
float calcularTemperaturaF(float temperaturaC);
void armazenarDados(float temperaturaC, float temperaturaF);
void enviarDadosIoT();
void exibirBancoDados();

// Função de setup (inicialização)
void setup() {
    pinMode(SENSOR_PIN, INPUT);    // Configura o pino do sensor como entrada
    Serial.begin(9600);            // Inicializa a comunicação serial
    Serial.println("Iniciando sistema de monitoramento de temperatura...");
}

// Função principal de loop
void loop() {
    // 1. Lê o valor do sensor
    float valorSensor = lerSensor();
    
    // 2. Calcula a temperatura em Celsius e Fahrenheit
    float temperaturaC = calcularTemperaturaC(valorSensor);
    float temperaturaF = calcularTemperaturaF(temperaturaC);

    // 3. Armazena os dados no pseudo banco de dados
    armazenarDados(temperaturaC, temperaturaF);

    // 4. Simula o envio dos dados para um servidor IoT
    enviarDadosIoT();

    // 5. Exibe o banco de dados completo
    exibirBancoDados();

    // Aguardando antes da próxima leitura
    delay(DELAY_TIME);
}

// Função para ler o valor do sensor de temperatura
float lerSensor() {
    return analogRead(SENSOR_PIN);
}

// Função para calcular a temperatura em Celsius
float calcularTemperaturaC(float valorSensor) {
    float voltage = valorSensor * (VOLTAGE_REF / RESOLUTION);  // Converte o valor para tensão
    return (voltage - SENSOR_OFFSET) * CONVERSION_FACTOR;      // Calcula e retorna a temperatura em °C
}

// Função para calcular a temperatura em Fahrenheit
float calcularTemperaturaF(float temperaturaC) {
    return (temperaturaC * 1.8) + 32;  // Converte de Celsius para Fahrenheit
}

// Função para armazenar os dados no pseudo banco de dados
void armazenarDados(float temperaturaC, float temperaturaF) {
    // Armazena os dados no índice atual
    tempDB[recordIndex].temperaturaC = temperaturaC;
    tempDB[recordIndex].temperaturaF = temperaturaF;
    tempDB[recordIndex].timestamp = millis();  // Armazena o tempo em milissegundos

    // Atualiza o índice do banco de dados (ciclo circular)
    recordIndex = (recordIndex + 1) % MAX_RECORDS;
}

// Função para simular o envio dos dados para um servidor IoT
void enviarDadosIoT() {
    Serial.print("Enviando dados para o servidor IoT (simulado)... ");
    Serial.print("Temperatura (°C): ");
    Serial.print(tempDB[recordIndex].temperaturaC);
    Serial.print(", Temperatura (°F): ");
    Serial.print(tempDB[recordIndex].temperaturaF);
    Serial.print(", Timestamp: ");
    Serial.println(tempDB[recordIndex].timestamp);
}

// Função para ler o valor do sensor de temperatura com tratamento de erro
float capturarValorSensor() {
    int leitura = analogRead(SENSOR_PIN);
    if (leitura == -1) {
        Serial.println("Erro na leitura do sensor.");
        return -1;
    }
    return leitura;
}


// Função para exibir o conteúdo completo do pseudo banco de dados
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
