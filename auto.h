// Librería para controlar los sensores ultrasonicos


// Definición de los pines para el control H
// Ajusta los pines según tu configuración
int motorPin1 = 2;
int motorPin2 = 4;
int motorPin3 = 3;
int motorPin4 = 5;
int motorAPin = 10; // Enable para el motor A
int motorBPin = 14; // Enable para el motor B

// Definición de los pines para los sensores ultrasonicos HC-SR04
// Ajusta los pines según tu configuración
int triggerPin1 = 6;  // Pin de trigger del sensor ultrasonico 1
int echoPin1 = 7;     // Pin de echo del sensor ultrasonico 1
int triggerPin2 = 8;  // Pin de trigger del sensor ultrasonico 2
int echoPin2 = 9;     // Pin de echo del sensor ultrasonico 2

// Distancia de detección de obstáculos en centímetros
int obstacleDistance = 5;

// Declaración de objetos para los sensores ultrasonicos HC-SR04
NewPing sonar1(triggerPin1, echoPin1, 200);  // Ajusta el máximo rango de detección según tus necesidades
NewPing sonar2(triggerPin2, echoPin2, 200);  // Ajusta el máximo rango de detección según tus necesidades

// Variables de control de velocidad
int minSpeed = 130; // Velocidad mínima permitida
int maxSpeed = 200; // Velocidad máxima permitida
  // Lectura de distancias desde los sensores ultrasonicos
  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();







// Función para avanzar el carro a una velocidad media
void driveForward() {
  int speed = map(distance1 + distance2, obstacleDistance * 2, 0, minSpeed, maxSpeed);
  analogWrite(motorAPin, speed);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

}

// Función para detener el carro
void stopCar() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  analogWrite(motorAPin, 0);
  analogWrite(motorBPin, 0);
}

// Función para girar a la derecha
void turnRight() {
 
  analogWrite(motorAPin, 180);
  analogWrite(motorBPin, 200);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

// Función para girar a la izquierda
void turnLeft() {
 
  analogWrite(motorAPin, 180);
  analogWrite(motorBPin, 200);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}