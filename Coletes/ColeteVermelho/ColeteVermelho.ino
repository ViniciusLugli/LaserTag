//Colete
#include <esp_now.h>
#include <WiFi.h>
#include <IRremote.h>

#define IR_RECEIVE_PIN 5  // Pino conectado ao receptor IR
#define led1 18
#define led2 19
#define led3 21
#define buzzer 13

int vida = 3;
int dado = 0;

// MUDAR AQUI COM O MAC ADDRESS DO ROVER
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0xD3, 0x1E, 0x60};

// Estrutura de dados para troca de informações
typedef struct DataStruct {
  char value[30];
} DataStruct;

// Variável para armazenar os dados recebidos
DataStruct dataStruct;

esp_now_peer_info_t peerInfo;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(115200);

  //Inicialização IR
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Receptor IR iniciado");

  /***************ESP NOW******************/
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

}

void loop() {
  dano();

  if (IrReceiver.decode()) {
    dado = IrReceiver.decodedIRData.decodedRawData, DEC;
    Serial.println(dado);

    // Comparar o valor recebido com o valor esperado, considerando o formato
    if (dado == -1119747841) {
      vida -= 1;
      dano();
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
    } else {
      strcpy(dataStruct.value, "0");
    }

    IrReceiver.resume();
  }
}

// callback when data is sent from Master to Slave
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status: "); 
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void dano(){
  if (vida == 0){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

    strcpy(dataStruct.value, "1");
    Serial.print("morri!");

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &dataStruct, sizeof(dataStruct));
      
    if (result == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    Serial.print("Sending: "); Serial.println(dataStruct.value);

    digitalWrite(buzzer, HIGH);
    delay(1000);
    digitalWrite(buzzer, LOW);
    delay(10000);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);

    vida = 3;

  } else if (vida == 1){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    
  } else if (vida == 2){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);

  } else {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
   
  }
}
