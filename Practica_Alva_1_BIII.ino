#include <Adafruit_NeoPixel.h>

// Enumeración de colores
enum {
   verde,
   rojo,
};
 
// Definición para los pines del sensor
#define pin_trig 13
#define pin_echo 12
 
// Definición del pin para el NeoPixel
int PINNEO = 2;
int NUMPIXELS = 16;
 
// Constructor del neopixel
Adafruit_NeoPixel pixels(NUMPIXELS, PINNEO, NEO_GRB + NEO_KHZ800);
 
// Definición para los pines del display
#define A 11
#define B 10
#define C 9
#define D 8
#define E 7
#define F 6
#define G 5
 
// Variables globales
int personas = 0;
float Medida;
float Medida_Anterior = 0;
 
// Funciones
float LecturaDistancia();
void Aforo();
void Display(int numero);
void setColor(int color);
 
void setup() {
  Serial.begin(9600);
 
  pixels.begin();
 
  pinMode(pin_trig, OUTPUT);
  pinMode(pin_echo, INPUT);
 
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  // Inicio el color verde del NeoPixel
  setColor(verde);
}
 
void loop() {
  Medida = LecturaDistancia();
  delay(100);
 
  Aforo();
  Serial.print("La cantidad de personas es ");
  Serial.println(personas);
  Serial.print("La distancia detectada es de ");
  Serial.println(Medida);
}
 
float LecturaDistancia() {
  digitalWrite(pin_trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(pin_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig, LOW);
 
  float sensor = pulseIn(pin_echo, HIGH);
  float distancia = sensor / 59;
 
  return distancia;
}
 
void Aforo() {
  if (Medida >= 6 && Medida <= 10 && (Medida_Anterior < 6 || Medida_Anterior > 10)) {
    personas++;
    if (personas > 10) {
      personas = 0; 
    }
  }
  Medida_Anterior = Medida;
 
  if (personas == 9) {
    setColor(rojo);
  } else {
    setColor(verde);
  }
 
  Display(personas);
}
 
void Display(int numero) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
 
  switch (numero) {
    case 0:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      break;
    case 1:
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    case 2:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 3:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 4:
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 5:
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 6:
      digitalWrite(A, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 7:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      break;
    case 8:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 9:
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      // Mostrar "-" después de 3 segundos
      delay(3000);
 
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
 
      // Detener la ejecución
      while (true);
      break;
  }
}
 
void setColor(int color) {
  switch(color) {
    case verde:
      for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // Verde
      }
      pixels.show();
      break;
    case rojo:
      for(int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Rojo
      }
      pixels.show();
      break;
  }
}

