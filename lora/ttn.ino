#include <hal/hal.h>
#include <SPI.h>
#include <vector>
#include "configuration.h"
#include "credentials.h"

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



#ifdef USE_OTAA
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8); }
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8); }
void os_getDevKey (u1_t* buf) { memcpy_P(buf, APPKEY, 16); }
#endif

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
