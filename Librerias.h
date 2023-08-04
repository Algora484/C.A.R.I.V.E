#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SD.h> // Comentamos la inclusión de la librería para el módulo SD Card
#include <SPIFFS.h> // Para el manejo del sistema de archivos SPIFFS en ESP32
#include <WiFiClientSecure.h>
#include <NewPing.h>