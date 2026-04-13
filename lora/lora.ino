/************************************************************************************************************************************************************
Lora to Do - MEDIALAB LPWAN UNIVERSIDAD DE OVIEDO
*********************************************************************************************************************************************************** */
#include "configuration.h"
#include "credentials.h"
#include "lmic_project_config.h"


static uint8_t txBuffer[TX_BUFFER_SIZE];      // Enter the length of the payload in bytes (this has to be more than 3 if you want to receive downlinks)
unsigned long previousMillis = 0;             // Save the time from previous send
unsigned long count = 0;                     // Contador de mensajes enviados
unsigned long txStartMillis = 0;             // Tiempo de inicio de transmisión
boolean waitingTxComplete = false;           // Indica que esperamos EV_TXCOMPLETE
boolean firstTime = true;


// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para enviar el paquete de datos LoRa
// -----------------------------------------------------------------------------------------------------------------------------------------------------------

bool loraSend(){

  bool sent = ttn_send(txBuffer);
  if (sent) {
    count++;
    txStartMillis = millis();
    waitingTxComplete = true;
  }
  return sent;
}


// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para mostrar mensajes por monitor serial segun se interactue con TTN
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void callback(uint8_t message){
  switch(message) {
    case EV_JOINING:
      Serial.println("Joining TTN...");
      break;

    case EV_JOINED:
      Serial.println("TTN joined!");
      break;

    case EV_JOIN_FAILED:
      Serial.println("TTN join failed");
      break;

    case EV_ACK:
      Serial.println("ACK received");
      break;

    case EV_PENDING:
      Serial.println("Message discarded");
      break;

    case EV_QUEUED:
      Serial.println("Message queued");
      break;

    case EV_TXCOMPLETE:
      Serial.println("TX complete");
      waitingTxComplete = false;      
      sleep();
      break;

    default:
      break;
  }
}



// ===========================================================================================================================================================
// Setup main
// ===========================================================================================================================================================
void setup(){
  //
  // Debug ---------------------------------------------------------------------------------------------------------------------------------------------------
  //
  Serial.begin(115200);

  //
  // Inicialización Modulo Lora -----------------------------------------------------------------------------------------------------------------------------------------------
  //
  if(!lora_setup()){
    Serial.println("[ERROR] Modulo Lora no encontrado!");
    sleep_forever();
  }

  //
  // Inicialización TTN --------------------------------------------------------------------------------------------------------------------------------------------
  //
  ttn_begin(callback);


}

// ===========================================================================================================================================================
// Loop main
// ===========================================================================================================================================================

void loop(){
  ttn_loop();

  unsigned long currentMillis = millis();  // Lee el tiempo actual

  // Verifica si han pasado X segundos desde la última vez que se ejecutaron doSensor() y loraSend()

  if (currentMillis - previousMillis >= SEND_INTERVAL || firstTime) {
    previousMillis = currentMillis;  // Actualiza el tiempo de la última ejecución
    firstTime =false;
    
    doSensor(txBuffer);  // Lee los sensores y llena el buffer de transmisión

    if (!loraSend()) {
      Serial.println(F("[AVISO] TX busy o no se pudo enviar, esperando al siguiente ciclo"));
    }
  }

  // Verifica si han pasado X segundos desde el envio del mensaje y aún no se ha recibido EV_TXCOMPLETE

  if (waitingTxComplete && (currentMillis - txStartMillis >= TX_COMPLETE_TIMEOUT_MS)) {
    Serial.println(F("[AVISO] Timeout EV_TXCOMPLETE alcanzado, entrando en deep sleep"));
    waitingTxComplete = false;
    sleep();
  }
}
