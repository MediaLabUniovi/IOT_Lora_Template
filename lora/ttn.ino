#include <hal/hal.h>
#include <SPI.h>
#include <vector>
#include <esp_sleep.h>
#include "configuration.h"
#include "credentials.h"

// -----------------------------------------------------------------------------
// Sleep
// -----------------------------------------------------------------------------

void sleep_interrupt(uint8_t gpio, uint8_t mode) {
    esp_sleep_enable_ext0_wakeup((gpio_num_t) gpio, mode);
}

void sleep_interrupt_mask(uint64_t mask, uint8_t mode) {
    esp_sleep_enable_ext1_wakeup(mask, (esp_sleep_ext1_wakeup_mode_t) mode);
}

void sleep_millis(uint64_t ms) {
    esp_sleep_enable_timer_wakeup(ms * 1000);
    esp_deep_sleep_start();
}

void sleep_seconds(uint32_t seconds) {
    esp_sleep_enable_timer_wakeup(seconds * 1000000);
    esp_deep_sleep_start();
}

void sleep_forever() {
    esp_deep_sleep_start();
}

void sleep(){
  #if SLEEP_BETWEEN_MESSAGES == 1
    Serial.println("Iniciando deep sleep...");
    uint32_t sleep_for = (millis() < SEND_INTERVAL ? SEND_INTERVAL - millis() : SEND_INTERVAL);
    sleep_millis(sleep_for);
  #endif
}

// -----------------------------------------------------------------------------
// Globals
// -----------------------------------------------------------------------------

// LMIC GPIO configuration
const lmic_pinmap lmic_pins = {
    .nss = NSS_GPIO,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = RESET_GPIO,
    .dio = {DIO0_GPIO, DIO1_GPIO, DIO2_GPIO},
};



void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey (u1_t* buf) { memcpy_P(buf, APPKEY, 16); }

std::vector<void(*)(uint8_t message)> _lmic_callbacks;

// -----------------------------------------------------------------------------
// Private methods
// -----------------------------------------------------------------------------

void _ttn_callback(uint8_t message) {
    for (uint8_t i=0; i<_lmic_callbacks.size(); i++) {
        (_lmic_callbacks[i])(message);
    }
}

// LMIC library will call this method when an event is fired
void onEvent(ev_t event) {
    if (EV_TXCOMPLETE == event) {

        if (LMIC.txrxFlags & TXRX_ACK) {
            _ttn_callback(EV_ACK);
        }

        if (LMIC.dataLen) {
            _ttn_callback(EV_RESPONSE);
        }

    }

    // Send message callbacks
    _ttn_callback(event);
}

// -----------------------------------------------------------------------------
// Helpers de codificación de datos
// -----------------------------------------------------------------------------

// Codifica un int (2 bytes) en el buffer en la posicion indicada (1-4)
void add_data(uint8_t* buffer, int valor, uint8_t posicion) {
    buffer[(posicion-1) * 2]     = byte(valor);
    buffer[(posicion-1) * 2 + 1] = valor >> 8;
}

// Imprime por Serial el decoder JavaScript listo para pegar en TTN
void printDecoder() {
    int numFields = TX_BUFFER_SIZE / 2;
    Serial.println();
    Serial.println("===== TTN Payload Formatter =====");
    Serial.println("function decodeUplink(input) {");
    Serial.println("  var data = {};");
    for (int i = 0; i < numFields; i++) {
        int byteA = i * 2;
        int byteB = i * 2 + 1;
        Serial.print("  data.field");
        Serial.print(i + 1);
        Serial.print(" = (input.bytes[");
        Serial.print(byteB);
        Serial.print("] << 8) | input.bytes[");
        Serial.print(byteA);
        Serial.println("];");
    }
    Serial.println("  return { data: data };");
    Serial.println("}");
    Serial.println("=================================");
    Serial.println();
}

// -----------------------------------------------------------------------------
// Callback TTN - Mensajes por monitor serial
// -----------------------------------------------------------------------------

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
      sleep();
      break;

    default:
      break;
  }
}

// -----------------------------------------------------------------------------
// Public methods
// -----------------------------------------------------------------------------

void ttn_register(void (*callback)(uint8_t message)) {
    _lmic_callbacks.push_back(callback);


}

size_t ttn_response_len() {
    return LMIC.dataLen;
}

void ttn_response(uint8_t * buffer, size_t len) {
    for (uint8_t i = 0; i < LMIC.dataLen; i++) {
        buffer[i] = LMIC.frame[LMIC.dataBeg + i];
    }
}

bool lora_setup() {
    // SPI interface
    SPI.begin(SCK_GPIO, MISO_GPIO, MOSI_GPIO, NSS_GPIO);

    // LMIC init
    return ( 1 == os_init_ex( (const void *) &lmic_pins ) );
}

void ttn_begin(void (*callback)(uint8_t message)){
    ttn_register(callback);
    ttn_join();
    ttn_sf(LORAWAN_SF);
    ttn_adr(LORAWAN_ADR);
}

void ttn_join() {
    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    LMIC_setClockError(MAX_CLOCK_ERROR / 100);

}

void ttn_sf(unsigned char sf) {
    LMIC_setDrTxpow(sf, 14);
}

void ttn_adr(bool enabled) {
    LMIC_setAdrMode(enabled);
}

void ttn_cnt(unsigned char num) {
    LMIC_setSeqnoUp(num);
}

bool ttn_send(uint8_t * data){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        _ttn_callback(EV_PENDING);
        return false;
    }

    LMIC_setTxData2(LORAWAN_PORT, data, TX_BUFFER_SIZE, 0);
            
    _ttn_callback(EV_QUEUED);
    return true;
}

void ttn_loop() {
    os_runloop_once();
}
