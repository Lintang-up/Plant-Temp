#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
 
// -------------------- KONFIG WIFI - SUPABASE - DHT11 - LOKALTIME --------------------
const char* ssid = "P1";
const char* password = "69696969";
 
const String supabaseURL = "https://qrystrtfrixzdmpdqaji.supabase.co";
const String apiKey ="eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InFyeXN0cnRmcml4emRtcGRxYWppIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NjQ0MTE4OTksImV4cCI6MjA3OTk4Nzg5OX0.64DSATRINkd3QCJZPaDczQj2H0rsJPAKKW4IyW3U6Ig";
 
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

HTTPClient https;
WiFiClientSecure client;

//Interval Kirim 
int sendingInterval = 3000;
// -------------------------------------------------------------------------------------

void setup() {
 Serial.begin(9600);
// Menghubungkan ke Wi-Fi 
 connectToWiFi();
// HTTPS tanpa validasi sertifikat
 client.setInsecure();
// DHT11
  dht.begin();
}
 
void loop() {
// Cek status koneksi Wi-Fi
 if (WiFi.status() == WL_CONNECTED) {
 // Membaca DHT
    float t, h;
    bacaDHT(t, h);  
 // Mengirim data ke Supabase
    sendToSupabase(t, h);
    
 } else {
   Serial.println("Error Koneksi Wifi");
 }
 delay(sendingInterval);
}
 
// ---------------------------------------------------------
// 1. Fungsi untuk Menghubungkan Wi-Fi
// ---------------------------------------------------------
void connectToWiFi() {
 Serial.print("Connecting to Wi-Fi");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("Wi-Fi connected.");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
 
// ---------------------------------------------------------
// 2. Fungsi membaca sensor DHT11
// ---------------------------------------------------------
void bacaDHT(float &t, float &h) {
  t = dht.readTemperature();
  h = dht.readHumidity();

  Serial.println("====================== DATA SENSOR ======================");
  Serial.println("Temp             : " + String(t));
  Serial.println("Humidity         : " + String(h));
}
 
// ---------------------------------------------------------
// 3. Fungsi Mengirim Data ke Supabase
// ---------------------------------------------------------
void sendToSupabase(float t, float h) {
 // Menyusun data JSON untuk dikirim
  String postData = "{\"suhu\":" + String(t, 2) +
                    ",\"kelembaban\":" + String(h, 2) + "}";
 
 // Mengirim permintaan POST ke Supabase
 https.begin(client, supabaseURL + "/rest/v1/Sensor");
 https.addHeader("Content-Type", "application/json");
 https.addHeader("Prefer", "return=representation");
 https.addHeader("apikey", apiKey);
 https.addHeader("Authorization", "Bearer " + apiKey);
 // Mengirim data JSON
 int httpCode = https.POST(postData);
 String payload = https.getString();
  // Menampilkan hasil HTTP
 Serial.println(httpCode);
 Serial.println(payload);
 https.end(); // Menutup koneksi
}
