#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// #include <SD.h> // Comentamos la inclusión de la librería para el módulo SD Card
#include <SPIFFS.h> // Para el manejo del sistema de archivos SPIFFS en ESP32
#include <WiFiClientSecure.h>
const char* ssid = "Torre_5G";
const char* password = "484cx9900";

#define BOTtoken "5960342524:AAHRXsM6sjsydOhF_yYNfVd_KWWUGyS79lo" // your Bot Token (Get from Botfather)
#define CHAT_ID "5658825194"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//////////////////////////////////////////////////////////////////////////////
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
///////////////////////////////////////////////////////////////////////////
// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

// Funciones para guardar mensajes en la SD Card (Comentado temporalmente)
// void saveMessageToSD(const String& chat_id, const String& message) {
//   // Código para guardar mensajes en la SD Card
// }

// void saveQuickResponseToSD(const String& response) {
//   // Código para guardar respuestas rápidas en la SD Card
// }

// void saveActionToSD(const String& action) {
//   // Código para guardar comandos de acción en la SD Card
// }

// Función para manejar nuevos mensajes recibidos
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id del remitente
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Imprimimos el mensaje recibido
    String text = bot.messages[i].text;
    Serial.println(text);
  lcd.setCursor(0, 0);
  lcd.print(text);
 // lcd.print("Hello, World!");
  delay(5000);
  // clears the display to print new message
  lcd.clear();


    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Bienvenido, " + from_name + ".\n";
      welcome += "Utiliza los siguientes comandos para controlar tus salidas y obtener estados de sensores.\n\n";
      welcome += "/state para solicitar el estado actual de las salidas\n";
      welcome += "/SFR para obtener el estado del sensor de distancia frontal\n";
      welcome += "/SBR para obtener el estado del sensor de barrido\n";
      welcome += "/SPT para obtener el estado del sensor posterior\n";
      welcome += "/FRTEMP para obtener la temperatura frontal\n";
      welcome += "/PTTEMP para obtener la temperatura posterior\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    // Resto de comandos para controlar salidas y obtener estados de sensores (por ejemplo, "/led_on1", "/SFR", "/SBR", "/SPT", "/FRTEMP", "/PTTEMP")

    // Guardamos los mensajes en la SD Card (Comentado temporalmente)
    // saveMessageToSD(chat_id, text);
  }
}

void setup() {
 // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  
  Serial.begin(921600);

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
  // if (!SPIFFS.begin()) {
  //   Serial.println("Error al inicializar SPIFFS");
  // }
  
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
}
