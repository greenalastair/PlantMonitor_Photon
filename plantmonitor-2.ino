/***********SETUP***************
 1.Connection Diagram: https://www.dfrobot.com/wiki/index.php?title=Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 2. soil Sensor is connect to Analog 1 port.
 3. Need to calibrate the sensor fully dry and fully wet, change values below.
 ****************************************************/

const int AirValue = 3140;   //value with sensor completely dry
const int WaterValue = 1510;  //value with sensor submerged in water up to circuit board

int soilMoistureValue;
int Pct;
int soilMoisturePct;

const String key = "PQT6E7K8UDLOBMXJ"; // Change this to your Thingspeak api write key

void setup() {
Serial.begin(9600); // open serial port, set the baud rate to 9600 bps

}

void loop() {

soilMoistureValue = analogRead(A1);  //put Sensor insert into soil
Pct = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
soilMoisturePct = constrain(Pct, 0, 100);


Serial.println(String(soilMoistureValue));
Serial.println(String(Pct));
Serial.println(String(soilMoisturePct));

Particle.publish("soilMoistureValue",String(soilMoistureValue));
Particle.publish("soilMoisturePct", String(Pct));
Particle.publish("soilMoisturePct", String(soilMoisturePct));

Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(soilMoisturePct) + "\"," +
"\"2\": \"" + String(soilMoistureValue) + "\"," +
"\"k\": \"" + key + "\" }", 60, PRIVATE);

delay(5000); //allow upload time

System.sleep(SLEEP_MODE_DEEP, 3600); // Set the sleep time (seconds)
}
  



