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

File archivo;

//-------------------------------------------------------------------------------------------------
// Definición de pines
//-------------------------------------------------------------------------------------------------
//Botones
#define boton1 PF_4
#define boton2 PF_0

//Color del texto en la pantalla TFT
#define celeste 0x1C7F

//Notas musicales para el buzzer
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_A4  440
#define NOTE_B4  494

//Buzzer
#define buzzer PB_0

//-------------------------------------------------------------------------------------------------
// Variables Locales
//-------------------------------------------------------------------------------------------------

//Variable para el dato del sensor proveniente del ESP32
String humedad = "";

//notas para el buzzer
int melody[] = {
   NOTE_A4, NOTE_E4,
   NOTE_A4, NOTE_E4,
   NOTE_B4, NOTE_E4,
   NOTE_B4, NOTE_E4,
   NOTE_C4, NOTE_E4,
   NOTE_C4, NOTE_E4,
   NOTE_D4, NOTE_E4,
   NOTE_D4, NOTE_E4, NOTE_B4};

//Duración de las notas para el buzzer
int noteDurations[] = {
  1, 2, 
  1, 2, 
  1, 2, 
  1, 2,
  1, 2,
  1, 2,
  1, 2,
  1, 1, 1};

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
  pinMode(buzzer, OUTPUT);
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
    for (int thisNote = 0; thisNote < 9; thisNote++) {
      int noteDuration = 1000/noteDurations[thisNote];
      tone(buzzer, melody[thisNote],noteDuration);

      int pauseBetweenNotes = noteDuration + 50;   
      delay(pauseBetweenNotes);
    
      noTone(buzzer);    
    }
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
    for (int thisNote = 9; thisNote < 18; thisNote++) {
      int noteDuration = 1000/noteDurations[thisNote];
      tone(buzzer, melody[thisNote],noteDuration);

      int pauseBetweenNotes = noteDuration + 50;   
      delay(pauseBetweenNotes);
    
      noTone(buzzer);    
    }
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
    archivo.print("28/10/21,");
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
