/*****************************************************************
 * INTERFACING PH SENSOR with NODEMCU
 * PROGRAMMER: MADHU PARVATHANENI
 * HARDWARE DESIGNER: MADHU PARVATHANENI
 * TESTER: RABBANI BASHA 
 * GROUP: MADHU HARDWARE GROUP, ORL INDUSTRIES
 * CONTACT: www.linkedin.com/in/MadhuPIoT
 *****************************************************************/
#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

WiFiClient client;

String olpAddress= "http://orlindustries.com/olp/upload_data?";
String writeAPIKey;
String tsfield1Name;
String request_string;
String channel_api_key="4e4f99287a7522e5192dab4723976deb"; // change api key

HTTPClient http;
int flag=0;

// Sensor Declarations
int ph_sensor=A0;

void setup() 
{
 Serial.begin(9600);
 pinMode(ph_sensor,INPUT);
 Serial.println("WELCOME TO PH SENSOR PROGRAM");
 delay(1000);

 WiFi.disconnect();
 WiFi.begin("Madhu P","Madhu23!");
 while ((!(WiFi.status() == WL_CONNECTED)))
 {
   delay(300);
   Serial.print(".");
 }
 Serial.println("Connected");
}

void loop() 
{
 float ph_value=analogRead(ph_sensor);
 Serial.print("Value: ");
 Serial.print(ph_value);
 Serial.print(", pH: ");
 float ph=(ph_value/1023)*5;
 ph=-5.70 * ph + 21.34;
 Serial.println(ph);
 upload_data(String(ph));
 delay(2000);
}

void upload_data(String m)
{
  if (client.connect("orlindustries.com",80)) 
    {
      Serial.println("Connected to OLP Dashboard");
      request_string = olpAddress;
      request_string += "channel_api_key=";
      request_string += channel_api_key;
      request_string += "&";
      request_string += "sensor1_name=";
      request_string += m;
      http.begin(request_string);
      http.GET();
      http.end();
      Serial.println("Data Uploaded to Cloud Successfully");
      flag=1;
      delay(5000);
    }
}

