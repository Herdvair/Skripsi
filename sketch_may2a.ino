#include <NTPClient.h>
#include <MQ135.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <DHT.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Fuzzy.h>
#include <time.h>

unsigned int dataCount = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 8 * 3600, 60000); // Offset waktu untuk GMT+8 dan refresh setiap menit


//sensor 
//dht
#define DHTPIN 5
#define DHTTYPE DHT22
DHT dht (DHTPIN, DHTTYPE);
//co2
const int pin = 34;
MQ135 gasSensor = MQ135(pin);
//ultrasonic
#define triggerPin 19
#define echoPin 21
#define PI 3.14
long duration;
int jarak;
const int TinggiTandon = 35; // sblmnya 40 cm
const int DiameterTandon = 30;
const int vInlet = 5; // cm3
const int vOutlet = 5; // cm3
const int vSelang = 104; //cm3
const int vPompa = 70; // cm3, 70cm klo asumsi full dan 35 cm kalau asumsi sebagian
const int PermukaanPompa = 25; // luas permukaan pompa (cm) 25cm atau 40


//aktuator
float output1, output2;

#define relay2 22
#define relay1 23
int enable1Pin = 13;
int motor1Pin1 = 12;
int motor1Pin2 = 14;
int motor2Pin1 = 27;
int motor2Pin2 = 26;
int enable2Pin = 25;
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;

//firebase
String uid;
#define API_KEY "AIzaSyDUTQU5KmJ6VjUsGfbqE3T6cdbToy_FJ58"
#define DATABASE_URL "https://coba-a2200-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "coba-a2200.firebaseapp.com"
#define EMAIL "trijel02@gmail.com";
#define PASSWORD "Wikwikwik22";
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//wifi
bool signupOK = false;
const char* host = "esp32";
const char* ssid = "Tri";
const char* password = "Tirexpad22";



  //kontrol aktuator
  unsigned long previousMillis = 0; // kipas
  const long interval = 5000; // interval kipas 
  bool fanRunning = false;
  bool fanStopped = false;

 bool pumpRunning = false;
bool pumpStopped = false;
unsigned long mistStartTime = 0;
unsigned long mistDuration = 0;
unsigned long mistDelayStartTime = 0;
const unsigned long delayAfterMistOff = 10000; // 10 detik untuk mistmaker
unsigned long pumpStartTime = 0;
unsigned long pumpDuration = 0;
unsigned long pumpDelayStartTime = 0;
const unsigned long delayAfterPumpOff = 1200000; // 20 menit untuk pompa

  unsigned long sendDataPrevMillis = 0; // firebase
  const long sendDataIntervalMillis = 30000; // firebase

// fuzzy
Fuzzy *fuzzy = new Fuzzy();

FuzzySet *cool = new FuzzySet (0, 0, 20, 22);
FuzzySet *tempnormal = new FuzzySet (20, 23, 28, 30);
FuzzySet *hot = new FuzzySet (29, 30, 40, 40); 

// Fuzzy Input keanggotaan kelembaban
FuzzySet *low = new FuzzySet (40, 40, 78, 80);
FuzzySet *humnormal = new FuzzySet (79, 81, 90, 93);
FuzzySet *high = new FuzzySet (91, 95, 100, 100);    
// Fuzzy Input keanggotaan co2                                            
FuzzySet *co2safe = new FuzzySet (100, 150, 1000, 1050);                
FuzzySet *co2danger = new FuzzySet (1025, 1050, 1200, 1200);          
// Fuzzy Output keanggotaan nozzle
FuzzySet *mati = new FuzzySet (0, 0, 15, 20);              
FuzzySet *singkat = new FuzzySet(15, 22.5, 22.5, 30);                          
FuzzySet *lama = new FuzzySet(28, 32, 40, 40);                        

// Fuzzy Output keanggotaan kipas
FuzzySet *off = new FuzzySet (0, 0, 90, 100);
FuzzySet *normal = new FuzzySet(95, 105, 135, 150);
FuzzySet *fast = new FuzzySet(145, 150, 255, 255);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  configTime(8 * 3600, 0, "pool.ntp.org", "time-nist.gov");
  timeClient.begin();
  //sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  dht.begin();
  //aktuator
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // configure PWM channels
  ledcSetup(pwmChannel1, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcSetup(pwmChannel2, freq, resolution);
  ledcAttachPin(enable2Pin, pwmChannel2);
  //fuzzy
  fRule();
  fSet();
  //others
  wificonnect();
  connectFirebase();
   Serial.println("Firebase connection status: " + String(Firebase.ready() ? "Connected" : "Disconnected"));

  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  
//    String sensorPath = "Sensor/" + uid;
// if (Firebase.RTDB.deleteNode(&fbdo, sensorPath)) {
//     Serial.println("Seluruh data di path 'Sensor' berhasil dihapus.");                          
// } else { 
//     Serial.printf("Gagal menghapus data di path 'Sensor': %s\n", fbdo.errorReason().c_str());
// }

//    String actuatorPath = "Aktuator/" + uid;
// if (Firebase.RTDB.deleteNode(&fbdo, actuatorPath)) {
//     Serial.println("Seluruh data di path 'Aktuator' berhasil dihapus.");                          
// } else { 
//     Serial.printf("Gagal menghapus data di path 'Aktuator': %s\n", fbdo.errorReason().c_str());
// }

}

void loop() {
  checkAndRefreshToken();

  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }

  char timestamp[20];
  strftime(timestamp, sizeof(timestamp), "%Y-%m-%d_%H-%M-%S", &timeinfo);  // Ganti format tanpa ":"

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > sendDataIntervalMillis || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    
    int input1 = dht.readTemperature();
    int input2 = dht.readHumidity();
    int input3 = gasSensor.getPPM();

    // Membaca jarak ultrasonic dan menghitung kapasitas air
    digitalWrite(triggerPin, LOW); 
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    int input4 = duration * 0.034 / 2;

    int tinggiAir = TinggiTandon - input4;
    int JariJariTandon = DiameterTandon / 2;
    int vAir = PI * JariJariTandon * JariJariTandon * tinggiAir;
    int vBersih = vAir + vPompa + vSelang + vInlet + vOutlet - PermukaanPompa;

    // Membuat path sensor dan aktuator
    String sensorPath = "Sensor/" + uid + "/" + String(timestamp);
    String actuatorPath = "Aktuator/" + uid + "/" + String(timestamp);

    Serial.print("Sending data to: ");
    Serial.println(sensorPath);

    // Mengirim data suhu dengan satuan
    String suhu = String(input1) + " °C";
    if (Firebase.RTDB.setString(&fbdo, sensorPath + "/Suhu", suhu)) {
      Serial.print("- Suhu: "); Serial.println(suhu);
      fuzzy->setInput(1, input1);
    } else {
      Serial.printf("Failed to push suhu: %s\n", fbdo.errorReason().c_str());
    }

    // Mengirim kelembaban dengan satuan
    String kelembaban = String(input2) + " % RH";
    if (Firebase.RTDB.setString(&fbdo, sensorPath + "/Kelembaban", kelembaban)) {
      Serial.print("- Kelembaban: "); Serial.println(kelembaban);
      fuzzy->setInput(2, input2);
    } else {
      Serial.printf("Failed to push kelembaban: %s\n", fbdo.errorReason().c_str());
    }

    // Mengirim CO2 dengan satuan
    String CO2 = String(input3) + " ppm";
    if (Firebase.RTDB.setString(&fbdo, sensorPath + "/Karbondioksida", CO2)) {
      Serial.print("- Karbondioksida: "); Serial.println(CO2);
      fuzzy->setInput(3, input3);
    } else {
      Serial.printf("Failed to push CO2: %s\n", fbdo.errorReason().c_str());
    }

    // Mengirim kapasitas air tandon dengan satuan
    String KapasitasAir = String(vBersih) + " ml";
    if (Firebase.RTDB.setString(&fbdo, sensorPath + "/Kapasitas_Air_Tandon", KapasitasAir)) {
      Serial.print("- Kapasitas Air Tandon: "); Serial.println(KapasitasAir);
    } else {
      Serial.printf("Failed to push Kapasitas Air Tandon: %s\n", fbdo.errorReason().c_str());
    }

    // Fuzzifikasi input
    fuzzy->fuzzify();

    Serial.print("Sending data to: ");
    Serial.println(actuatorPath);

    output1 = fuzzy->defuzzify(1);
    output2 = fuzzy->defuzzify(2);

    // Mengirim output kipas dan pompa
    if (Firebase.RTDB.setFloat(&fbdo, actuatorPath + "/kipas", output1)) {
      Serial.print("\tOutput Kipas: "); Serial.println(output1);
      kontrolKipas();
    } else {
      Serial.printf("Failed to push kipas: %s\n", fbdo.errorReason().c_str());
    }

    if (Firebase.RTDB.setFloat(&fbdo, actuatorPath + "/pompa", output2)) {
      Serial.print("\tOutput Pompa: "); Serial.println(output2);
      kontrolPompa();
    } else {
      Serial.printf("Failed to push pompa: %s\n", fbdo.errorReason().c_str());
    }
    dataCount++;
  }
}



void checkAndRefreshToken() {
  if (Firebase.isTokenExpired()) {
    Serial.println("Token expired, refreshing token...");
    Firebase.refreshToken(&config);
    if (Firebase.ready()) {
      Serial.println("Token refreshed successfully.");
    } else {
      Serial.println("Failed to refresh token.");
    }
  }
}


void kontrolKipas() {
  timeClient.update();
  int currentHour = timeClient.getHours();
  // Jika waktu antara 00:00 dan 06:00, kipas harus mati
  if (currentHour >= 21 && currentHour < 6) {
    if (fanRunning) {
      // Matikan kipas
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      fanRunning = false;
      Serial.println("Kipas dimatikan ");
    }
    return;
  }
  unsigned long currentMillis = millis();
  unsigned long fanRunTime = 1000 * output1; // Waktu kipas menyala sesuai output dalam milidetik (output * 1000)

  if (fanRunning) { // kondisi tidak berjalan
    // Cek apakah waktu untuk menyalakan kipas sudah tercapai
    if (currentMillis - previousMillis >= fanRunTime) {
      // Matikan kipas setelah waktu sesuai output
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      ledcWrite(pwmChannel1, 0); // Matikan PWM kipas
      ledcWrite(pwmChannel2, 0); // Matikan PWM kipas
      fanRunning = false;
      previousMillis = currentMillis;
      Serial.println("Kipas dimatikan");
    }
  }  else {
    // Cek apakah waktu delay 30 detik sudah tercapai
    if (currentMillis - previousMillis >= interval) {
      // Jika output fuzzy menunjukkan kipas harus mati
      if (output1 < 100) {
        // Pastikan kipas tetap mati
        if (fanRunning) {
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          ledcWrite(pwmChannel1, 0); // Matikan PWM kipas
          ledcWrite(pwmChannel2, 0); // Matikan PWM kipas
          fanRunning = false;
         
        }
      } else {
        // Nyalakan kipas sesuai output fuzzy
        ledcWrite(pwmChannel1, output1); // Sesuaikan kecepatan kipas
        ledcWrite(pwmChannel2, output1); // Sesuaikan kecepatan kipas
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);

        fanRunning = true;
        Serial.println("Kipas dinyalakan sesuai output fuzzy");
      }
      previousMillis = currentMillis;
    }
  }
}

void kontrolPompa() {
  int currentHourPump = timeClient.getHours();
  unsigned long currentMillis = millis();

  // Tentukan waktu penyiraman
  bool isWithinWateringTime = 
    (currentHourPump >= 8 && currentHourPump < 10) ||
    (currentHourPump >= 12 && currentHourPump < 14) ||
    (currentHourPump >= 16 && currentHourPump < 18);

  // Jika di luar waktu penyiraman atau output tidak memenuhi syarat, matikan pompa
  if (!isWithinWateringTime || output2 <= 20) {
    if (pumpRunning) {
      digitalWrite(relay2, LOW);
      pumpRunning = false;
      Serial.println("Pompa dimatikan karena berada di luar waktu penyiraman atau output tidak memenuhi syarat");
    }
    return; // Keluar dari fungsi jika tidak memenuhi kondisi
  }

  // Jika dalam waktu penyiraman dan output memenuhi syarat
  if (!pumpRunning && !pumpStopped) { // Mulai pompa
    digitalWrite(relay2, HIGH);
    pumpRunning = true;
    pumpStartTime = currentMillis;
    pumpDuration = output2 * 1000; // Durasi pompa sesuai output fuzzy
    Serial.println("Pompa menyala");
  }

  // Jika pompa menyala dan durasi sudah tercapai, matikan pompa
  if (pumpRunning && currentMillis - pumpStartTime >= pumpDuration) {
    digitalWrite(relay2, LOW);
    pumpRunning = false;
    pumpStopped = true;
    pumpDelayStartTime = currentMillis;
    Serial.println("Pompa dimatikan, delay 20 menit dimulai");
  }

  // Jika delay 20 menit telah berlalu, reset kondisi pompa untuk dapat berjalan lagi
  if (pumpStopped && currentMillis - pumpDelayStartTime >= delayAfterPumpOff) {
    pumpStopped = false; // Siapkan pompa untuk siklus berikutnya
    Serial.println("Pompa siap beroperasi kembali setelah 20 menit delay");
  }
}


void connectFirebase() {
  // Set API key, database URL and other required configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL; 
  auth.user.email = EMAIL;
  auth.user.password = PASSWORD;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback;
  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);

  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }

  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid); // Print UID
  signupOK = true;
}

void wificonnect() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
}



