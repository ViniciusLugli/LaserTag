#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>

static const int servoPin = 21; 
#define buzzer 19

Servo servo1;

//Estrutura para envio dos dados. Deve ser a mesma tanto no emissor como no receptor.
typedef struct DataStruct
{
  char value[30];
} DataStruct;

//Cria uma struct_message chamada myData
DataStruct dataStruct;

int pos = 0;
int mortes = 0;

void setup() {

  Serial.begin(115200);
  servo1.attach(servoPin);
  pinMode(buzzer, OUTPUT);

  WiFi.mode(WIFI_STA);

  //Inicializa o ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erro ao inicializar o ESP-NOW");
    return;
  } else {
    Serial.println("ESP-NOW Inicializado");
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}


void loop() {
  fechar();

  if (mortes == 2){
    abrir();
    delay(5000);
    tocarAlarme();
    mortes = 0;
    delay(40000);

    for (int i = 0; i < 15; i++){
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }
  }
}

void abrir() {
  servo1.write(120);
}

void fechar() {
  servo1.write(0);
}

void tocarAlarme(){
  for (int i = 0; i < 15; i++){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  }

  for (int i = 0; i < 5; i++){
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(150);
  }

  for (int i = 0; i < 3; i++){
    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
}

// callback when data is recv from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  Serial.println("recebi");
  memcpy(&dataStruct, data, sizeof(dataStruct));  // Copia os dados recebidos para a estrutura de dados
  
  String valores = dataStruct.value;

  if(valores == "1"){
    mortes += 1;
  }
}
