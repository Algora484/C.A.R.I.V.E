const char* ssid = "Torre_5G";
const char* password = "484cx9900";

#define BOTtoken "5960342524:AAHRXsM6sjsydOhF_yYNfVd_KWWUGyS79lo" // your Bot Token (Get from Botfather)
#define CHAT_ID "5658825194"



String textoLCD[2]; // Arreglo para almacenar el texto en cada nivel del LCD (hasta 2 filas)// Variable global para almacenar el texto del LCD

 // //////////////////////////////////////////////////////////////////////////////
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
/////////////////////////////////////////////////////////////////////////


#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;


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


void escribirEnLCD(String texto, int nivel) {
  // Verifica que el nivel sea válido (0 o 1 para un LCD de 2 filas)
  if (nivel >= 0 && nivel < lcd.Rows()) {
    // Actualiza el texto almacenado en la variable global
    textoLCD[nivel] = texto;

    lcd.clear(); // Limpia el LCD
    for (int i = 0; i < lcd.Rows(); i++) {
      lcd.setCursor(0, i); // Establece la posición del cursor para cada nivel
      lcd.print(textoLCD[i]); // Escribe el texto en el LCD para cada nivel
    }
  } 
}
