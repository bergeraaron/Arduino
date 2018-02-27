/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 * http://randomnerdtutorials.com/esp32-dht11-dht22-temperature-humidity-web-server-arduino-ide/
*/

#include "DHT.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);

//#define OLED_SDA 5
//#define OLED_SCL 4
//#define OLED_DC 2
//#define OLED_CS 12
//#define OLED_RESET 3
//Adafruit_SSD1306 display(OLED_SDA, OLED_SCL, OLED_DC, OLED_RESET, OLED_CS);


#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Uncomment one of the lines below for whatever DHT sensor type you're using!
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

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

int ctr=0;

void setup() {

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  // Clear the buffer.
  display.clearDisplay();

  // initialize the DHT sensor
  dht.begin();
  
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while(!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
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
  display.print("Temp:");
  display.println(cur_temp);
	Serial.print("Max Hum:");
	Serial.println(max_hum);
	Serial.print("Min Hum:");
	Serial.println(min_hum);
	Serial.print("Cur Hum:");
	Serial.println(cur_hum);
  display.print("Hum:");
  display.println(cur_hum);
  display.display();
}

void loop()
{

    Serial.println("Clear the display buffer.");
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    Serial.println("reset cursor.");
    display.setCursor(0,0);
    
    read_sensor();
    delay(60000);
}
