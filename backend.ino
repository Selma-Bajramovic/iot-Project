#include <LiquidCrystal_I2C.h>
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <Wire.h>



#define _SSID "Galaxy A51 C212" 
#define _PASSWORD "sejoboss"   
#define REFERENCE_URL "https://smart-alarm-5e173-default-rtdb.europe-west1.firebasedatabase.app"  // Your Firebase project reference url
#define BUZZER_PIN D8  
#define BUTTON_PIN D3  
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2


// Initialize Firebase object
Firebase firebase(REFERENCE_URL);

// Initialize LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Flag to indicate whether the alarm is active or not
bool alarmActive = false;
bool buttonPressed = false;

void setup() {
  configTime(0, 0, "pool.ntp.org");
  setenv("TZ", "CEST-2", 1);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Assuming the button is connected between pin and ground

  Serial.begin(115200);
  delay(1000);

  // Connect to Wi-Fi
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("No wifi conn");
  }
  Serial.println();
  Serial.println("Connected to WiFi!");

  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  
}

void loop() {

int sosSignal = firebase.getInt("/sos");
if (sosSignal > 0) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("STA IMA");
  firebase.setInt("/sos", 0);
}


 
}
