<div align="right">

[![english](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png)](./README.md) | [![spanish](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/es.png)](./README_ES.md)

</div>

# Lora Template

This repository contains a template code designed for the **LilyGO T3 V1.6.1** board. The purpose of this project is to establish communication using **LoRa** technology to send sensor readings through a LoRa network.

This template was developed by **MediaLab Uniovi**, a university laboratory of technology and design that emerged in 2018 from a collaboration between the **City Council of Gijón**, **Gijón Impulsa**, and the **University of Oviedo**. MediaLab is headquartered at the **School of Engineering of Gijón**, and its main objective is to bring new technologies and project creation methodologies closer to people.

## Features

- Compatible with the **LilyGO T3 V1.6.1** board
- Support for **LoRa** communication
- Modular and easy-to-customize template for adding new sensors
- Efficient sensor data reading and transmission
- Reliable communication with other stations in a LoRa network

## Hardware Requirements

- **LilyGO T3 V1.6.1**
- **LoRa SX1276/78** module (integrated on the LilyGO board)
- Compatible sensors (you can add your own)


<img src="https://www.tinytronics.nl/image/cache/catalog/products_2023/lilygo-ttgo-t3-lora32-868mhz-v1.6.1-esp32-600x600w.jpg" alt="MediaLab Uniovi Logo" width="500"/>
## Software Requirements

- **Arduino IDE** (or any other compatible IDE for ESP32 platforms)
- Required libraries:
  - Arduino-Lmic: Library to manage LoRa communication
  - `Wire.h`: Library for I2C communication with sensors
  - `SPI.h`: Library for SPI communication (LoRa)
  - Additional libraries depending on the sensors you use

## Installation

1. **Clone the repository**:
   
   Clone this repository to your local machine using:

   ```bash
   git clone https://github.com/MediaLabUniovi/IOT_Lora_Template.git
   ```

2. **Set up the environment**:
   
   Open the project in **Arduino IDE** or your preferred IDE and ensure you have installed the necessary libraries mentioned above.

3. **Connect your hardware**:
   
   - Connect the **LilyGO T3 V1.6.1** to your computer using a USB cable.
   - Add the required sensors according to your application and connect them to the corresponding pins.
   
4. **Configure TTN credentials**:
   
   In the credentials code file (usually `credentials.h`), adjust the LoRa parameters such as **APPEUI**, **DEVEUI**, and **APPKEY** according to your TTN application:

   ```cpp
       static const u1_t PROGMEM APPEUI[8]  = {};  // INTRODUCE EN LSB
       static const u1_t PROGMEM DEVEUI[8]  = {};  // INTRODUCE EN LSB
       static const u1_t PROGMEM APPKEY[16] = {};  // INTRODUCE EN MSB
   ```

5. **Upload the code**:
   
   Select the **TTGO LoRa 32-OLED** board from the tools menu and upload the code to the board.

## Usage

1. **Power up the board**: 
   Once the code is uploaded, the board will start reading data from the connected sensors and send them over the LoRa network.
   
2. **Data reception**:
   The sensor data sent can be received and visualized on another LoRa-compatible device within the network range.
   
3. **Modification and Customization**:
   You can add new sensors by simply importing the required libraries and adding the code in the appropriate section of the template.

## About MediaLab Uniovi

<img src="img/medialab_logo.png" alt="MediaLab Uniovi Logo" width="200"/>

**MediaLab Uniovi** is a university laboratory of technology and design that was created in 2018 as a result of a collaboration between the **City Council of Gijón**, **Gijón Impulsa**, and the **University of Oviedo**. Its mission is to bring new technologies and project creation methodologies closer to people. MediaLab is based at the **School of Engineering of Gijón** and works to foster technological innovation and creativity.

## Contributions

Contributions are welcome. If you want to improve this project or add new features, feel free to open a **pull request** or create an **issue** in this repository.

## License

This project is licensed under the [MIT License](LICENSE).
