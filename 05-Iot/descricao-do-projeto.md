# Monitoramento de Temperatura da Sala de Servidores (IoT) — NEXA Biomech

**Simulação no Tinkercad:** [Acessar circuito no Tinkercad](https://www.tinkercad.com/things/b2jdqs66WQX-medidor-de-temperatura?sharecode=c22C3FEhAkmG6nMhoAsNOZw9SZ63KbWr5BZCC4SM0os)

## 1. Problema e Justificativa

A infraestrutura computacional da **NEXA Biomech** concentra servidores críticos, switches principais e sistemas de armazenamento (NAS/RAID) na sala de servidores localizada no 4º andar do prédio. Como esses equipamentos operam em regime contínuo (24/7), geram calor constantemente.

O aumento anormal da temperatura ambiente pode causar perda de desempenho, desligamentos inesperados e danos permanentes ao hardware. Para mitigar esse risco, foi desenvolvido um protótipo de monitoramento térmico utilizando a plataforma Arduino no Tinkercad, oferecendo um sistema de alerta visual imediato para a equipe de Tecnologia da Informação.

---

## 2. Componentes Utilizados

| Componente                      |     Quantidade      | Pino(s) no Arduino                    | Função no Circuito                                                                                                 |
| :------------------------------ | :-----------------: | :------------------------------------ | :----------------------------------------------------------------------------------------------------------------- |
| **Arduino Uno R3**              |          1          | `5V`, `GND`, `A0`, `D8`, `D9`, `D10`  | Microcontrolador responsável por ler o sensor, processar a temperatura e acionar os alertas visuais.               |
| **Protoboard pequena**          |          1          | Trilhas `+` e `-` (`5V` e `GND`)      | Base de prototipagem para organizar e interligar os componentes eletrônicos sem necessidade de solda.              |
| **Sensor de temperatura TMP36** |          1          | Esq: `5V` / Centro: `A0` / Dir: `GND` | Realizar a leitura térmica da sala de servidores e enviar um sinal analógico de tensão proporcional à temperatura. |
| **LED Verde**                   |          1          | Digital `D8` (ânodo)                  | Indicador visual de operação normal (temperatura abaixo de 28 °C).                                                 |
| **LED Amarelo**                 |          1          | Digital `D9` (ânodo)                  | Indicador visual de estado de atenção (temperatura de 28 °C até menos de 32 °C).                                   |
| **LED Vermelho**                |          1          | Digital `D10` (ânodo)                 | Indicador visual de alerta crítico (temperatura a partir de 32 °C).                                                |
| **Resistor de 220 Ω**           |          3          | Em série entre cada LED e o `GND`     | Limitar a corrente elétrica em cada LED, protegendo os componentes e as portas digitais do Arduino.                |
| **Fios jumper**                 | Conforme necessário | Interligações gerais                  | Conectar alimentação (`5V`/`GND`), sinais analógicos e portas digitais entre o Arduino e a protoboard.             |

---

## 3. Montagem e Lógica de Funcionamento

### 3.1 Ligações Físicas

- **Alimentação:** O pino `5V` do Arduino alimenta o barramento positivo (`+`) da protoboard, e o pino `GND` conecta-se ao barramento negativo (`-`).
- **Sensor TMP36:** Com a face plana voltada para frente, o terminal esquerdo recebe `5V`, o terminal central envia o sinal analógico para a porta `A0` e o terminal direito conecta-se ao `GND`.
- **Sinalização (LEDs):** Os ânodos (pernas maiores) dos LEDs verde, amarelo e vermelho estão conectados às portas digitais `D8`, `D9` e `D10`, respectivamente. Cada cátodo (perna menor) passa por um resistor individual de `220 Ω` antes de chegar ao `GND`.

_(Consulte a imagem geral da montagem no arquivo `circuito.png` desta pasta.)_

### 3.2 Lógica do Programa

O código-fonte (disponível no arquivo `codigo.ino` desta pasta) executa um ciclo contínuo a cada 1 segundo:

1. Lê o valor analógico bruto da porta `A0` (escala de `0` a `1023`).
2. Converte o valor lido para tensão elétrica (base `5.0 V`) e aplica a fórmula de conversão do sensor TMP36 para graus Celsius: `temperaturaC = (tensao - 0.5) * 100`.
3. Desliga todos os LEDs antes de avaliar a leitura atual para garantir que apenas um indicador permaneça aceso por vez.
4. Compara a temperatura obtida com as faixas definidas e exibe o status e o valor calculado no Monitor Serial:
   - **Abaixo de 28 °C:** Acende apenas o LED Verde (Normal).
   - **De 28 °C até menos de 32 °C:** Acende apenas o LED Amarelo (Atenção).
   - **A partir de 32 °C:** Acende apenas o LED Vermelho (Crítico).

### 3.3 Código-Fonte (`codigo.ino`)

```cpp
// Monitoramento de Temperatura da Sala de Servidores - NEXA Biomech

const int LED_VERDE = 8;
const int LED_AMARELO = 9;
const int LED_VERMELHO = 10;
const int SENSOR_TEMP = A0;

void setup() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Leitura analógica e conversão para graus Celsius (TMP36)
  int leituraSensor = analogRead(SENSOR_TEMP);
  float tensao = leituraSensor * (5.0 / 1023.0);
  float temperaturaC = (tensao - 0.5) * 100;

  // Garante que apenas um LED fique aceso por ciclo
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  // Avaliação das faixas de temperatura e acionamento dos alertas
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

  // Exibição da temperatura medida no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println(" C");

  delay(1000);
}

## 4. Registro dos Testes Obrigatórios

Foram realizados três testes simulados alterando diretamente a temperatura no sensor TMP36 durante a execução no Tinkercad:

| Caso de Teste | Entrada (TMP36) | Resultado Esperado | Resultado Obtido (Circuito e Serial) | Status | Evidência |
| :--- | :---: | :--- | :--- | :---: | :--- |
| **Teste 1 — Normal** | 25 °C | Somente o LED verde aceso; leitura abaixo de 28 °C no Monitor Serial. | LED verde aceso; Monitor Serial exibiu `24.78 C` e `Status: NORMAL (VERDE)`. | **Aprovado** | `teste-normal.png` |
| **Teste 2 — Atenção** | 30 °C | Somente o LED amarelo aceso; leitura entre 28 °C e 31,9 °C no Monitor Serial. | LED amarelo aceso; Monitor Serial exibiu `31.13 C` e `Status: ATENCAO (AMARELO)`. | **Aprovado** | `teste-atencao.png` |
| **Teste 3 — Crítico** | 38 °C | Somente o LED vermelho aceso; leitura a partir de 32 °C no Monitor Serial. | LED vermelho aceso; Monitor Serial exibiu `37.98 C` e `Status: CRITICO (VERMELHO)`. | **Aprovado** | `teste-critico.png` |

---

## 5. Conclusão

O protótipo desenvolvido funcionou conforme o planejado em todos os cenários testados, respondendo com precisão às variações térmicas simuladas no sensor TMP36 e acionando corretamente os respectivos indicadores visuais.

Na operação da **NEXA Biomech**, a adoção desse sistema de monitoramento proporciona detecção rápida de falhas no sistema de climatização da sala de servidores, permitindo que a equipe de TI atue preventivamente antes que o superaquecimento comprometa a disponibilidade dos serviços internos ou danifique os ativos de rede e armazenamento.
```
