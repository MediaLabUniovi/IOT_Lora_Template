<div align="right">

[![english](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png)](./README.md) | [![spanish](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/es.png)](./README_ES.md)

</div>


# Plantilla LoRa

Este repositorio contiene un código plantilla diseñado para la placa **LilyGO T3 V1.6.1**. El propósito de este proyecto es establecer comunicación utilizando la tecnología **LoRa** para enviar lecturas de sensores a través de una red LoRa.

Esta plantilla fue desarrollada por **MediaLab Uniovi**, un laboratorio universitario de tecnología y diseño que surgió en 2018 a partir de la colaboración entre el **Ayuntamiento de Gijón**, **Gijón Impulsa** y la **Universidad de Oviedo**. MediaLab tiene su sede en la **Escuela de Ingeniería de Gijón** y su objetivo principal es acercar las nuevas tecnologías y metodologías de creación de proyectos a las personas.

## Características

- Compatible con la placa **LilyGO T3 V1.6.1**
- Soporte para comunicación **LoRa**
- Plantilla modular y fácil de personalizar para agregar nuevos sensores
- Lectura y transmisión eficiente de datos de sensores
- Comunicación confiable con otras estaciones en una red LoRa

## Requisitos de Hardware

- **LilyGO T3 V1.6.1**
- Módulo **LoRa SX1276/78** (integrado en la placa LilyGO)
- Sensores compatibles (puedes añadir los tuyos)

<img src="https://www.tinytronics.nl/image/cache/catalog/products_2023/lilygo-ttgo-t3-lora32-868mhz-v1.6.1-esp32-600x600w.jpg" alt="Logo de MediaLab Uniovi" width="500"/>

## Requisitos de Software

- **Arduino IDE** (o cualquier otro IDE compatible con plataformas ESP32)
- Librerías necesarias:
  - Arduino-Lmic: Librería para gestionar la comunicación LoRa
  - `Wire.h`: Librería para comunicación I2C con sensores
  - `SPI.h`: Librería para comunicación SPI (LoRa)
  - Librerías adicionales según los sensores que utilices

## Instalación

1. **Clonar el repositorio**:
   
   Clona este repositorio en tu máquina local usando:

   ```bash
   git clone https://github.com/MediaLabUniovi/Lora-Template.git
   ```

2. **Configurar el entorno**:
   
   Abre el proyecto en **Arduino IDE** o en tu IDE preferido y asegúrate de haber instalado las librerías necesarias mencionadas anteriormente.

3. **Conectar el hardware**:
   
   - Conecta la **LilyGO T3 V1.6.1** a tu computadora usando un cable USB.
   - Añade los sensores requeridos según tu aplicación y conéctalos a los pines correspondientes.
   
4. **Configurar credenciales de TTN**:
   
   En el archivo de credenciales (generalmente `credentials.h`), ajusta los parámetros de LoRa como **APPEUI**, **DEVEUI** y **APPKEY** de acuerdo con tu aplicación de TTN:

   ```cpp
       static const u1_t PROGMEM APPEUI[8]  = {};  // INTRODUCE EN LSB
       static const u1_t PROGMEM DEVEUI[8]  = {};  // INTRODUCE EN LSB
       static const u1_t PROGMEM APPKEY[16] = {};  // INTRODUCE EN MSB
   ```

5. **Cargar el código**:
   
   Selecciona la placa **TTGO LoRa 32-OLED** desde el menú de herramientas y carga el código a la placa.

## Uso

1. **Encender la placa**: 
   Una vez cargado el código, la placa comenzará a leer datos de los sensores conectados y los enviará a través de la red LoRa.
   
2. **Recepción de datos**:
   Los datos de los sensores enviados pueden recibirse y visualizarse en otro dispositivo compatible con LoRa dentro del rango de la red.
   
3. **Modificación y personalización**:
   Puedes añadir nuevos sensores importando las librerías necesarias y agregando el código en la sección correspondiente de la plantilla.

## Acerca de MediaLab Uniovi

<img src="img/medialab_logo.png" alt="Logo de MediaLab Uniovi" width="200"/>

**MediaLab Uniovi** es un laboratorio universitario de tecnología y diseño que fue creado en 2018 como resultado de la colaboración entre el **Ayuntamiento de Gijón**, **Gijón Impulsa**, y la **Universidad de Oviedo**. Su misión es acercar las nuevas tecnologías y metodologías de creación de proyectos a las personas. MediaLab tiene su sede en la **Escuela de Ingeniería de Gijón** y trabaja para fomentar la innovación tecnológica y la creatividad.

## Contribuciones

Las contribuciones son bienvenidas. Si deseas mejorar este proyecto o añadir nuevas características, siéntete libre de abrir un **pull request** o crear un **issue** en este repositorio.

## Licencia

Este proyecto está licenciado bajo la [Licencia MIT](LICENSE).
