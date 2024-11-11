#include <IRremote.h>


#define IR_SEND_PIN 3  // Pino conectado ao emissor IR
#define botao 4
#define led 5

void setup() {
  pinMode(botao, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  IrSender.begin(IR_SEND_PIN);

  Serial.begin(115200);
  Serial.println("Emissor IR iniciado");
}

void loop() {
  char letra = 'B';            // Letra a ser enviada
  uint16_t endereco = 0x00FF;  // Exemplo de endereço (pode ser qualquer valor de 16 bits)
  uint16_t comando = letra;    // Comando é o código ASCII da letra

  if (!digitalRead(botao)) {
    // Envia o código usando o protocolo NEC com 0 repetições
    IrSender.sendNEC(endereco, comando, 0);

    Serial.print("Letra enviada: ");
    Serial.println(comando);
    digitalWrite(led, HIGH);
    delay(3000);  // Aguarda 2 segundos antes de enviar novamente
    digitalWrite(led, LOW);
  }
}
