// Remplaza el archivo en \Documents\Arduino\libraries\MCCI_LoRaWAN_LMIC_library\project_config
// por este archivo.
// Si no el dispositivo intentará transmitir en frecuencia de EEUU y no en la Europea.

#define CFG_eu868 1
#define CFG_sx1276_radio 1
#define hal_init LMICHAL_init