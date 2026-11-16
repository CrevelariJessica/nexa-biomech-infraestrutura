// C++ code

// Pinos dos LEDs
const int LED_VERDE = 8;
const int LED_AMARELO = 9;
const int LED_VERMELHO = 10;

// Pino de sensor de temperatura
const int SENSOR_TEMP = A0;

// Configuração inicial
void setup()
{
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  Serial.begin(9600);
}

// Execução contínua
void loop()
{
  // 1. Realiza a leitura do sensor
  int leituraSensor = analogRead(SENSOR_TEMP);
  
  // 2. Converte a leitura em tensão elétrica
  float tensao = leituraSensor * (5.0 / 1023.0);
  
  // 3. Converte a tensão em temperatura Celsius
  float temperaturaC = (tensao - 0.5) * 100;
  
  // 4. Exibe a temperatura no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println(" C");
  
  // Desliga todos os LEDs
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  // Verifica a temperatura
  if (temperaturaC < 28) {
  	digitalWrite(LED_VERDE, HIGH);
    Serial.println("Status: NORMAL (VERDE)");
  }
  else if (temperaturaC < 32) {
    digitalWrite(LED_AMARELO, HIGH);
    Serial.println("Status: ATENCAO (AMARELO)");
  }
  else {
    digitalWrite(LED_VERMELHO, HIGH);
    Serial.println("Status: CRITICO (VERMELHO)");
  }

  // 1000 milisegundos = 1 segundo
  delay(1000);
  
  
}