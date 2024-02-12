float altura = 0;
float heightoffset = 0;
float temperatura = 10;
float presion = 5;
float height = 11;
float humedad = 1;
float velocidadviento = 2;
float windCalDirection = 22;
float precipitacion = 33;
float battery = 3.4;
int vaneValue = 0;
int windDirection = 0;
int VaneOffset = 0;
String windCompassDirection;

float analogBat = 0;
float digitalBat = 0;

void BME280() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
  temperatura = bme.readTemperature();

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
  presion = bme.readPressure();

  Serial.print("Approx. Altitude = ");
  altura = bme.readAltitude(SEALEVELPRESSURE_HPA);
  height = altura + heightoffset;
  Serial.print(height);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  humedad = bme.readHumidity();

  Serial.println();
}

void RAINRATE() {
  TimeBetweenOverflows = millis() - LastOverflowTime;
  rainDataAvailable = false;
  if (OverflowCount == 2) {
    rainDataAvailable = true;
    precipitacion = (0.2 * 3600000) / TimeBetweenOverflows;
    Serial.print("Rainrate");
    Serial.print(precipitacion);
  }
  OverflowCount = 0;
}

void count() {
  currentTime = millis();
  if ((currentTime - tiptime) < interval) {
    return;
  }
  tiptime = currentTime;
  if (OverflowCount == 0) {
    LastOverflowTime = currentTime;
    OverflowCount = 1;
  } else {
    OverflowCount = 2;
    rainDataAvailable = true;
  }
}

void Velocidad_Viento() {
  WindSpeed = Rotations * 0.9;
  Rotations = 0;
  velocidadviento = WindSpeed * 1.61;
  Serial.print("wind_speed=");
  Serial.print(velocidadviento);
  Serial.print(" km/h");
  Serial.print(" ,");
  Serial.print(" wind_direction=");
  Serial.print(windCalDirection);
  Serial.print(" ,");
  Serial.print(" wind_compass_direction=");
  Serial.print(windCompassDirection);
  Serial.println();
}

void getWindDirection() {
  vaneValue = analogRead(WindVanePin);
  windDirection = map(vaneValue, 0, 3050, 0, 360);
  windCalDirection = windDirection + VaneOffset;
  if (windCalDirection > 360) windCalDirection = windCalDirection - 360;
  if (windCalDirection < 0) windCalDirection = windCalDirection + 360;

  if (windCalDirection < 22) windCompassDirection = "N";
  else if (windCalDirection < 67) windCompassDirection = "NE";
  else if (windCalDirection < 112) windCompassDirection = "E";
  else if (windCalDirection < 157) windCompassDirection = "SE";
  else if (windCalDirection < 212) windCompassDirection = "S";
  else if (windCalDirection < 247) windCompassDirection = "SW";
  else if (windCalDirection < 292) windCompassDirection = "W";
  else if (windCalDirection < 337) windCompassDirection = "NW";
  else windCompassDirection = "N";
}

void isr_rotation() {
  if ((millis() - ContactBounceTime) > 15) {
    Rotations++;
    ContactBounceTime = millis();
  }
}

void ReadBattery() {
  analogBat = analogRead(BatteryPin);
  Serial.print(analogBat);
  digitalBat = (analogBat - 0) * (2.1 - 0) / (2500 - 0);
  battery = digitalBat * 2;
  Serial.print(" Bateria Real ");
  if (battery)
    Serial.print(battery);
}

void doSensor(uint8_t txBuffer[]) {
  memset(txBuffer, 0, TX_BUFFER_SIZE);

  int shiftTemp = int(temperatura * 100);
  txBuffer[0] = byte(shiftTemp);
  txBuffer[1] = shiftTemp >> 8;

  int shiftpresion = int(presion * 100);
  txBuffer[2] = byte(shiftpresion);
  txBuffer[3] = shiftpresion >> 8;
  txBuffer[4] = shiftpresion >> 16;
  txBuffer[5] = shiftpresion >> 32;

  int shiftAltura = int(height * 100);
  txBuffer[6] = byte(shiftAltura);
  txBuffer[7] = shiftAltura >> 8;

  int shifthumedad = int(humedad * 100);
  txBuffer[8] = byte(shifthumedad);
  txBuffer[9] = shifthumedad >> 8;
  int shiftdirviento = int(windCalDirection * 100);
  txBuffer[10] = byte(shiftdirviento);
  txBuffer[11] = shiftdirviento >> 8;
  txBuffer[12] = shiftdirviento >> 16;

  int shiftVel = int(velocidadviento * 100);
  txBuffer[13] = byte(shiftVel);
  txBuffer[14] = shiftVel >> 8;

  int shiftprecipitacion = int(precipitacion * 100);
  txBuffer[15] = byte(shiftprecipitacion);
  txBuffer[16] = shiftprecipitacion >> 8;
  txBuffer[17] = shiftprecipitacion >> 16;

  int shiftVoltage = int(battery * 10);
  txBuffer[18] = byte(shiftVoltage);
}
