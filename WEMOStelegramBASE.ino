#include "Librerias.h"
#include "Definitions.h"
#include "SD_config.h"
#include "auto.h"



void setup() {
  lcd.begin(16, 2); // Inicializar el LCD (16 columnas y 2 filas)
 // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  ///////////////////////////////////////////////
 // Configuración de los pines de control H
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorAPin, OUTPUT);
  pinMode(motorBPin, OUTPUT);
//////////////////////////////////////////////////
  Serial.begin(921600); // eliminar el serial al final

  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // obtener la hora UTC a través de NTP
    client.setTrustAnchors(&cert); // Agregar el certificado raíz para api.telegram.org
  #endif

  // Conectar a Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Agregar el certificado raíz para api.telegram.org
  #endif

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi..");
  }
  
  // Inicializar el sistema de archivos SPIFFS para guardar el chat (Comentado temporalmente)
  if (!SPIFFS.begin()) {
   Serial.println("Error al inicializar SPIFFS");
  }
  
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
lcd.setCursor(0, 0);


  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();

  }


//////////////////////////////////////////////////////////////////////////
  // Lectura de distancias desde los sensores ultrasonicos
  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();

  // Comprueba si hay obstáculos en ambos lados del carro
  if (distance1 < obstacleDistance && distance2 < obstacleDistance) {
    // Detener el carro si encuentra obstáculos en ambos lados
    stopCar();
    Serial.println("Obstáculo detectado en ambos lados. Deteniendo el carro.");
  } else if (distance1 < obstacleDistance) {
    // Obstáculo detectado en el sensor 1, girar al otro lado
    turnRight();
    Serial.println("Obstáculo detectado en el lado derecho. Girando hacia la izquierda.");
  } else if (distance2 < obstacleDistance) {
    // Obstáculo detectado en el sensor 2, girar al otro lado
    turnLeft();
    Serial.println("Obstáculo detectado en el lado izquierdo. Girando hacia la derecha.");
  } else {
    // No hay obstáculos, avanzar el carro a una velocidad media
    driveForward();
    Serial.println("Avanzando...");
  }

  // Muestra las distancias en el monitor serial
  Serial.print("Distancia sensor 1: ");
  Serial.print(distance1);
  Serial.print(" cm | ");
  Serial.print("Distancia sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
 escribirEnLCD("Distancia sensor 1: ", distance1, 0); // Mostrar "Nivel 0" en la fila 0 del LCD
  escribirEnLCD("Distancia sensor 2: ", distance2, 1); // Mostrar "Nivel 1" en la fila 1 del LCD
  delay(1000);  // Retardo antes de la siguiente iteración
/////////////////////////////////////////////////////////////////////////////////////////

}