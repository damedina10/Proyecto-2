//-------------------------------------------------------------------------------------------------
/*
 * Universidad del Valle de Guatemala
 * BE3015 - Electrónica Digital 2
 * Proyecto 2
 * Comunicación SPI
 * Nombre: Diego Andrés Medina Mencos
 * Carné: 19697
 */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Librerías
//-------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------
//Botones
#define boton1 PF_4
#define boton2 PF_0




//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------
//Variable para que solo se lea un dato cuando se presiona el boton
int estadoBoton1 = 0;




//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin (115200);

  //Configuración de los botones
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);

  //Configuración de la SD
  pinMode(PB_5, OUTPUT);


}

//-------------------------------------------------------------------------------------------------
// Loop principal
//-------------------------------------------------------------------------------------------------
void loop() {
  //Si se presiona el botón 1, cambia el estado del botón a 1
  if(digitalRead(boton1)==0){
    delay(150);
    estadoBoton1 = 1;
  }

  //Si el estado del botón 1 es 1, entonces se realiza la lectura
  if(estadoBoton1 == 1){
    
  }
  

  delay(500);
}
