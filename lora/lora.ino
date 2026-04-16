/************************************************************************************************************************************************************
Plantilla Minima Lora TTN - MEDIALAB LPWAN UNIVERSIDAD DE OVIEDO
2026
*************************************************************************************************************************************************************/
#include "configuration.h"


static uint8_t txBuffer[TX_BUFFER_SIZE];
unsigned long previousMillis = 0;
boolean firstTime = true;


// ===========================================================================================================================================================
// Sensores - Edita aquí para añadir tus sensores
// ===========================================================================================================================================================

void doSensor(uint8_t txBuffer[]) {

  memset(txBuffer, 0, TX_BUFFER_SIZE);

  // Datos de ejemplo inventados!!!
  int temperature = random(1500, 2500);
  int humidity    = random(0, 10000);
  int pressure    = random(9500, 10500);
  int battery     = random(0, 100);

  add_data(txBuffer, temperature, 1);
  add_data(txBuffer, humidity,    2);
  add_data(txBuffer, pressure,    3);
  add_data(txBuffer, battery,     4);

  Serial.print("Temp: ");     Serial.println(temperature);
  Serial.print("Humidity: "); Serial.println(humidity);
  Serial.print("Pressure: "); Serial.println(pressure);
  Serial.print("Battery: ");  Serial.println(battery);

}

// ===========================================================================================================================================================
// Configuración Inicial
// ===========================================================================================================================================================
void setup(){

  // Activar mensajes por consola-----------------------------------------------------------------------------------------------------------------------------

  Serial.begin(9600);
  printDecoder();

  // Inicialización Modulo Lora ------------------------------------------------------------------------------------------------------------------------------
  if(!lora_setup()){
    Serial.println("[ERROR] Modulo Lora no encontrado!");
    sleep_forever();
  }

  // Inicialización TTN --------------------------------------------------------------------------------------------------------------------------------------
  ttn_begin(callback);


}

// ===========================================================================================================================================================
// Loop main
// ===========================================================================================================================================================

void loop(){

  // se encarga de mandar/recibir mensajes pendientes
  ttn_loop();

  unsigned long currentMillis = millis();  // Lee el tiempo actual

  // Verifica si han pasado X segundos y en tal caso lee sensores y envia
  if (currentMillis - previousMillis >= SEND_INTERVAL || firstTime) {

    previousMillis = currentMillis;  // Actualiza el tiempo de la última ejecución
    firstTime =false;
    
    doSensor(txBuffer);  // Lee los sensores y llena el buffer de transmisión

    if (!ttn_send(txBuffer)) {
      Serial.println(F("[ERROR] o se pudo enviar, esperando al siguiente ciclo"));
    }
  }

}
