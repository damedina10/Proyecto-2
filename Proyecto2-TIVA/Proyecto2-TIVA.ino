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

//Archivo para la SD
File archivo;

//Pantalla TFT
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include <SPI.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"
//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------
//Botones
#define boton1 PF_4
#define boton2 PF_0

//Color del texto en la pantalla TFT
#define celeste 0x1C7F

//Buzzer
#define sound PB_0

//Pines de la pantalla TFT
// El SPI es el 0
//MOSI va a PA_5
//MISO va a PA_4
//SCK va a PA_2

#define LCD_RST PD_0
#define LCD_DC PD_1
#define LCD_CS PA_3

//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------

//Variable para el dato del sensor proveniente del ESP32
String humedad = "";



//-------------------------------------------------------------------------------------------------
// Prototipo de funciones
//-------------------------------------------------------------------------------------------------
void memoriaSD(void);

//-------------------------------------------------------------------------------------------------
// ISR
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Configuración del sistema
//-------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin (115200);
  Serial3.begin (115200);

  //Configuración de los botones
  pinMode(boton1, INPUT_PULLUP);
  pinMode(boton2, INPUT_PULLUP);

  //Configuración de la SD
  pinMode(PB_5, OUTPUT);
  
  SPI.setModule(2);
    // Estamos Inicializando la tarjeta SD
  if (!SD.begin(PB_5)) {
    Serial.println("Ha ocurrido un error!");
    return;
  }

  //Configuración buzzer
  pinMode(sound, OUTPUT);
}

//-------------------------------------------------------------------------------------------------
// Loop principal
//-------------------------------------------------------------------------------------------------
void loop() {
  //Si se presiona el botón 1, se le dice al ESP32 que lea el dato
  if(digitalRead(boton1)==0){
    delay(150);
    Serial3.println("1");
    //Sonido de medición 
    tone(sound,440,100);
    delay(100);
    tone(sound,523.25,100);
    delay(100);
    tone(sound,587.33,100);
    delay(200);
    tone(sound,587.33,100);
    delay(200);
    tone(sound,587.33,100);
    delay(100);
    tone(sound,659.25,100);
    delay(100);
    tone(sound,698.45,100);
    delay(200);
    tone(sound,698.45,100);
    delay(200);
    tone(sound,698.45,100);
    delay(100);
    tone(sound,783.99,100);
    delay(100);
    tone(sound,659.25,100);
    delay(200);
    tone(sound,659.25,100);
    delay(200);
    tone(sound,587.33,100);
    delay(100);
    tone(sound,523.25,100);
    delay(100);
    tone(sound,523.25,100);
    delay(100);
    tone(sound,587.33,100);
    delay(300);

    noTone(sound);   
  }

  //Datos del sensor recibidos del ESP32
  if(Serial3.available()>0){
    //Se lee el dato y se guarda en una variable
    humedad = Serial3.readStringUntil('\n');
    
  }


  //Si se presiona el botón 2, se guardan los datos en la memoria SD
  if(digitalRead(boton2)==0){
    delay(150);
    memoriaSD();
    Serial3.println("2");
    //Sonido de guardado
    tone(sound,440,100);
    delay(100);
    tone(sound,523.25,100);
    delay(100);
    tone(sound,587.33,100);
    delay(200);
    tone(sound,587.33,100);
    delay(200);
    tone(sound,587.33,100);
    delay(100);
    tone(sound,659.25,100);
    delay(100);
    tone(sound,698.45,100);
    delay(200);
    tone(sound,698.45,100);
    delay(200);
    tone(sound,698.45,100);
    delay(100);
    tone(sound,783.99,100);
    delay(100);
    tone(sound,659.25,100);
    delay(200);
    tone(sound,659.25,100);
    delay(200);
    tone(sound,587.33,100);
    delay(100);
    tone(sound,523.25,100);
    delay(100);
    tone(sound,587.33,100);
    delay(400);
    noTone(sound);    
  }

  
  delay(500);
}

//-------------------------------------------------------------------------------------------------
// Función para guardar los datos en la memoria SD
//-------------------------------------------------------------------------------------------------
void memoriaSD(void){
    //Se abre el documento para escribir
    archivo = SD.open("Humedad.csv", FILE_WRITE);
  
  // Si se abrió el documento, entonces se escriben los datos
  if (archivo) {
    //Se muestra en el monitor que se están guardando los datos
    Serial.println("Se guardó el siguiente dato: ");
    Serial.print("Humedad: ");
    Serial.println(humedad);

    //Se imprimen los datos en la memoria SD
    archivo.print("28/10/21");
    archivo.print(",");
    archivo.println(humedad);
   
    //Cerramos el documento
    archivo.close();
    Serial.println("Dato guardado exitosamente.");
  } 
  else {
    //Si no se logra abrir el archivo, aparece un mensaje
    Serial.println("No se pudo abrir el archivo");
  }
  
}
