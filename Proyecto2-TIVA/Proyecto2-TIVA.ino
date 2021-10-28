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
  
  SPI.setModule(2);
    // Estamos Inicializando la tarjeta SD
  if (!SD.begin(PB_5)) {
    Serial.println("Ha ocurrido un error!");
    return;
  }

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

  //Si se presiona el botón 2, se guardan los datos en la memoria SD
  if(digitalRead(boton2)==0){
    delay(150);
    memoriaSD();
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
