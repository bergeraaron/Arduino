/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 * http://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/
*/

#include <WiFi.h>
#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Replace with your network credentials
const char* ssid     = "";
const char* password = "";

WiFiServer server(80);

// DHT Sensor
const int DHTPin = 16;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Temporary variables
static char celsiusTemp[7];
static char fahrenheitTemp[7];
static char humidityTemp[7];

//sensor variables
float min_temp = 999.9;
float max_temp = -999.9;
float cur_temp = 0;
float min_hum = 999.9;
float max_hum = -999.9;
float cur_hum = 0;

// Client variables 
char linebuf[80];
int charcount=0;

int ctr=0;

void setup() {
  // initialize the DHT sensor
  dht.begin();
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  /**/
  while(true)
  {
    read_sensor();
    delay(60000);
  }
 /**
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  // attempt to connect to Wifi network:
  while(WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
/**/
}

void read_sensor()
{
	Serial.println("Read Sensor");

	float h = dht.readHumidity();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	float f = dht.readTemperature(true);
	if(f < min_temp)
		min_temp = f;
	if(f > max_temp)
		max_temp = f;
	cur_temp = f;
	if(h < min_hum)
		min_hum = h;
	if(h > max_hum)
		max_hum = h;
	cur_hum = h;

	Serial.print("Max Temp:");	
	Serial.println(max_temp);
	Serial.print("Min Temp:");
	Serial.println(min_temp);
	Serial.print("Cur Temp:");
	Serial.println(cur_temp);
	Serial.print("Max Hum:");
	Serial.println(max_hum);
	Serial.print("Min Hum:");
	Serial.println(min_hum);
	Serial.print("Cur Hum:");
	Serial.println(cur_hum);


}

void loop() {

  if(ctr == 1000)
  {
	read_sensor();
 	ctr=0; 
  }
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //read char by char HTTP request
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        //
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
          client.println("<meta http-equiv=\"refresh\" content=\"30\"></head>");
          client.println("<body><div style=\"font-size: 3.5rem;\"><p>ESP32 - DHT</p><p>");
          client.println(celsiusTemp);
          client.println("*C</p><p>");
          client.println(fahrenheitTemp);
          client.println("*F</p></div><p>");
          client.println(humidityTemp);
          client.println("%</p></div>");
          client.println("</body></html>");     
        //  break;
        
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
	ctr++;
}
