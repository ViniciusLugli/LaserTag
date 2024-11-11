#include <IRremote.h>


#define IR_SEND_PIN 3  // Pino conectado ao emissor IR
#define botao 4
#define cor1 5
#define cor2 6
#define cor3 7

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(cor1, OUTPUT);
  pinMode(cor2, OUTPUT);
  pinMode(cor3, OUTPUT);
  IrSender.begin(IR_SEND_PIN);

  Serial.begin(115200);
  Serial.println("Emissor IR iniciado");

  digitalWrite(cor1, HIGH);
  digitalWrite(cor2, HIGH);
  digitalWrite(cor3, HIGH);
}

void loop() {
  char letra = 'A';            // Letra a ser enviada
  uint16_t endereco = 0x00FF;  // Exemplo de endereço (pode ser qualquer valor de 16 bits)
  uint16_t comando = letra;    // Comando é o código ASCII da letra

  if (!digitalRead(botao)) {
    // Envia o código usando o protocolo NEC com 0 repetições
    IrSender.sendNEC(endereco, comando, 0);

    Serial.print("Letra enviada: ");
    Serial.println(comando);
    digitalWrite(cor1, LOW);
    digitalWrite(cor2, LOW);
    digitalWrite(cor3, LOW);
    delay(3000);  // Aguarda 2 segundos antes de enviar novamente
    digitalWrite(cor1, HIGH);
    digitalWrite(cor2, HIGH);
    digitalWrite(cor3, HIGH);
  }
}
