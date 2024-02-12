#pragma once

#include <Arduino.h>
#include <lmic.h>



// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------------------------------------------------------------------------------------------


#define CLOCK_ERROR             1
#define DEBUG_PORT              Serial      // Serial debug port
#define SERIAL_BAUD             115200      // Serial debug baud rate
#define ENABLE_DEBUG            1           // Serial debug on/off
#define SLEEP_BETWEEN_MESSAGES  1           // Do sleep between messages
#define SEND_INTERVAL           10000       // Sleep for these many millis
#define LORAWAN_PORT            1           // Port the messages will be sent to
#define LORAWAN_CONFIRMED_EVERY 0           // Send confirmed message every these many messages
#define LORAWAN_SF              DR_SF7      // Spreading factor
#define LORAWAN_ADR             1           // Enable ADR

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// DEBUG
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef DEBUG_PORT
#define DEBUG_MSG(...) DEBUG_PORT.printf( __VA_ARGS__ )
#else
#define DEBUG_MSG(...)
#endif

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Custom messages
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define EV_QUEUED       100
#define EV_PENDING      101
#define EV_ACK          102
#define EV_RESPONSE     103

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Sensores
// -----------------------------------------------------------------------------------------------------------------------------------------------------------


#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define heightoffset 56; //factor para calibrar la altura


/*---------------------Variables Anemometro y veleta---------------------------------------------------------------------------------------------------------*/ 

#include <math.h> 
#define WindSensorPin (34) // El sensor se coloca en el pin 2 digital del arduino, el cual esta habilitado con la interrupcion 0 
#define WindVanePin (04) // Pin analogico para controlar la direccion del viento  
#define VaneOffset 0; // Factor para calibrar la veleta y que apunte al norte  

/*----------------------Variables Pluviometro---------------------------------------------------------------------------------------------------------------*/

#define PluviometroPin (36) // la interrupcion del pluviometro se hace con el Pin 3 digital del arduino 

/*--------------------------------Digital input--------------------------------------------------------------------------------------------------------------*/
#define  VOLTAGE_PIN 0

/*--------------------------------BatteryRead--------------------------------------------------------------------------------------------------------------*/
#define BatteryPin 12

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// LoRa SPI
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define SCK_GPIO        5
#define MISO_GPIO       19
#define MOSI_GPIO       27
#define NSS_GPIO        18
#define RESET_GPIO      23
#define DIO0_GPIO       26
#define DIO1_GPIO       33
#define DIO2_GPIO       32

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// AXP192 (Rev1-specific options)
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
#define LORA_POWER_CTRL_CH    2
