

void doSensor(uint8_t txBuffer[]) {

  // Ponemos a 0s el buffer de envío
  memset(txBuffer, 0, TX_BUFFER_SIZE);

  int temperature = random(1500, 2500);
  Serial.print("Temp: ");
  Serial.println(temperature);
  txBuffer[0] = byte(temperature);
  txBuffer[1] = temperature >> 8;

  Serial.println(txBuffer[0]);
  Serial.println(txBuffer[1]);

}
