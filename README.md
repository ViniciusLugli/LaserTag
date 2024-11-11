# Shine Wizards

Neste projetos eu desenvolvi um laser tag, onde utilizei ESP Now e IR.

A ideia do jogo é ter uma dupla de cada lado, onde um time é o vermelho e o outro azul, o IR é utilizado para dar dano no adversario, mas não consegue dar dano em seu proprio time, quando a contagem de vidas chegar em 0 duas vezes, utlizei o ESP Now para enviar um codigo para o tesouro, assim desbloqueando ele e ganhando o jogo.

### Varinha:
  - Bibliotecas utilizadas:
    - IRremote.h
  - Módulo Emissor Infravermelho KY-005 LED 
  - Branco (pode utilizar a cor de sua preferencia) 
  - Botão 
  - Arduino Nano 
  - Bateria 9V

### Colete:
  - Bibliotecas utilizadas:
    - IRremote.h
    - WiFi.h
    - esp_now.h
  - Módulo Receptor Infravermelho KY-022
  - 3x LEDs da cor do time
  - Buzzer
  - ESP32
  - Bateria 9V

### Tesouro 
  - Bibliotecas utilizadas:
    - ESP32Servo.h
    - esp_now.h
    - WiFi.h
  - Servo 180
  - Buzzer
  - ESP32
  - Fonte 5V
