/* 
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AM / EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Practica No. 1 3er Bimestre
   Dev: Josivar Sebastian Rayjam Alva López
   Fecha: 15 de julio.
   link de la simulacion: https:
 */

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
 
// pantalla lcd con I2C
#define direccion_lcd 0x27
#define filas 2
#define columnas 16
 
bool estadoSensorHall;
 
bool estadoSensorObstaculos;
 
int paso [8][4] =
{
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};
 
LiquidCrystal_I2C LCD(direccion_lcd, columnas, filas);
 
int contador_revoluciones = 0;
 
unsigned int velocidad_adc;
 
unsigned char velocidad;
 
void setup()
{
  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Contador de rev.");
  LCD.setCursor(0, 1);
  LCD.print("No. de Rev: 0");
 
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
 
  pinMode(A0, INPUT);
         
  pinMode(4, INPUT);
 
  pinMode(3, INPUT);
}
 
void loop() {
  estadoSensorObstaculos = digitalRead(3);
 
  if(estadoSensorObstaculos == LOW){
    medicion_adc();
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(12, paso[i][0]);
      digitalWrite(11, paso[i][1]);
      digitalWrite(10, paso[i][2]);
      digitalWrite(9, paso[i][3]);
      delay(velocidad);
    }
 
    estadoSensorHall = digitalRead(4);
   
    if(estadoSensorHall == LOW){
      medicion_rev_lcd();
      delay(1000);
    }
  }
}
 
void medicion_adc(){
  velocidad_adc = analogRead(A0);    
  velocidad = map(velocidad_adc,0,1023,0,10);
}
 
int medicion_rev_lcd(){
  contador_revoluciones = contador_revoluciones+1;
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Contador de rev.");
  LCD.setCursor(0, 1);
  LCD.print("No. de rev: ");
  LCD.setCursor(13, 1);
  LCD.print(contador_revoluciones);
}
