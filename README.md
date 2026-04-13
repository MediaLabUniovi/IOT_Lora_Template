# Plantilla LoRa — LilyGO T3 V1.6.1

Plantilla para enviar datos de sensores a través de **LoRaWAN (TTN)** con la placa **LilyGO T3 V1.6.1** (ESP32 + SX1276).

Desarrollada por **[MediaLab Uniovi](https://medialab.uniovi.es/)**.

<img src="https://www.tinytronics.nl/image/cache/catalog/products_2023/lilygo-ttgo-t3-lora32-868mhz-v1.6.1-esp32-600x600w.jpg" width="400"/>

---

## Requisitos

**Hardware**
- LilyGO T3 V1.6.1 (módulo LoRa SX1276 integrado)
- Sensores a medida

**Software**
- Arduino IDE con soporte para ESP32
- Librería [Arduino-LMIC](https://github.com/mcci-catena/arduino-lmic)

---

## Estructura del proyecto

```
lora/
├── lora.ino           # Setup y loop principal
├── sensor.ino         # Lectura de sensores y empaquetado del payload
├── ttn.ino            # Gestión de la conexión LoRaWAN con TTN
├── sleep.ino          # Deep sleep entre envíos
├── configuration.h    # Parámetros configurables (intervalo, SF, pines...)
├── credentials.h      # Claves TTN (APPEUI, DEVEUI, APPKEY)
└── lmic_project_config.h
```

---

## Puesta en marcha

### 1. Clonar

```bash
git clone https://github.com/MediaLabUniovi/Lora-Template.git
```

### 2. Credenciales TTN

Edita `lora/credentials.h` con los valores de tu dispositivo en TTN:

```cpp
static const u1_t PROGMEM APPEUI[8]  = { ... };  // LSB first
static const u1_t PROGMEM DEVEUI[8]  = { ... };  // LSB first
static const u1_t PROGMEM APPKEY[16] = { ... };  // MSB first
```

### 3. Configuración

Ajusta los parámetros en `lora/configuration.h` según tus necesidades:

| Parámetro | Por defecto | Descripción |
|---|---|---|
| `TX_BUFFER_SIZE` | 2 | Tamaño del payload en bytes |
| `SEND_INTERVAL` | 60000 ms | Intervalo entre envíos |
| `LORAWAN_SF` | DR_SF9 | Spreading Factor |
| `LORAWAN_ADR` | 1 | ADR activado |
| `SLEEP_BETWEEN_MESSAGES` | 1 | Deep sleep entre envíos |

### 4. Añadir sensores

Edita `lora/sensor.ino`. La función `doSensor()` recibe el buffer de envío:

```cpp
void doSensor(uint8_t txBuffer[]) {
  memset(txBuffer, 0, TX_BUFFER_SIZE);

  // Lee tu sensor y rellena txBuffer
  int valor = analogRead(PIN_SENSOR);
  txBuffer[0] = byte(valor);
  txBuffer[1] = valor >> 8;
}
```

### 5. Flashear

En Arduino IDE: selecciona la placa **TTGO LoRa32-OLED** y sube el código.

---

## Licencia

[MIT](LICENSE) — MediaLab Uniovi
