/***********SETUP***************
 1.Connection Diagram: https://www.dfrobot.com/wiki/index.php?title=Capacitive_Soil_Moisture_Sensor_SKU:SEN0193
 2. soil Sensor is connect to Analog 1 port.
 3. Need to calibrate the sensor fully dry and fully wet, change values below.
 ****************************************************/

const int AirValue = 3140;   //value with sensor completely dry
const int WaterValue = 1510;  //value with sensor submerged in water up to circuit board
int soilMoistureValue; //reading value
int Pct; //mapped value to %
int soilMoisturePct; //limited value from 0% to 100%
const String key = "PQT6E7K8UDLOBMXJ"; //  Thingspeak api write key

void setup() {
 
Serial.begin(9600); 
}

void loop() {
 
soilMoistureValue = analogRead(A1);  //reading value
Pct = map(soilMoistureValue, AirValue, WaterValue, 0, 100); //mapped value to %
soilMoisturePct = constrain(Pct, 0, 100); //limited value from 0% to 100%
 
//for calibration and debug only
Serial.println(String(soilMoistureValue));
Serial.println(String(Pct));
Serial.println(String(soilMoisturePct));
 
//publish on particle console 
Particle.publish("soilMoistureValue",String(soilMoistureValue));
Particle.publish("soilMoisturePct", String(Pct));
Particle.publish("soilMoisturePct", String(soilMoisturePct));
 
//uplaod the data to ThingSpeak
Particle.publish("thingSpeakWrite_All", "{ \"1\": \"" + String(soilMoisturePct) + "\"," +
"\"2\": \"" + String(soilMoistureValue) + "\"," +
"\"k\": \"" + key + "\" }", 60, PRIVATE);

delay(5000); //allow upload time (micro seconds)

System.sleep(SLEEP_MODE_DEEP, 3600); // Set the sleep time (seconds)
}
  



