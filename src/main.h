#ifndef MAIN_H
#define MAIN_H
#include <Arduino.h>
#include <params.h>
#include <secret.h>
#include <UrusanWiFi.h>
#include <UrusanBuzzer.h>
#include <UrusanIoT.h>
#include <ArduinoJson.h>
#include <UrusanLED.h>
#include <UrusanUltrasonic.h>


// Tulis parameter lokal mu di sini
const uint8_t pinLED = 27;
const uint8_t pinEcho = 34;
const uint8_t pinTrigger = 33;
String clientId = String(CURRENT_FIRMWARE_TITLE) + String(NIM);
unsigned long lastSent = 0;
bool flagUpdate = false;
int lastDistance = 0;
int lastPercent = 0;


int tankHeight = 100;
uint8_t bottomThreshold = 20;
uint8_t upperThreshold = 100;


// Tulis instansiasi objek global mu di sini
UrusanWiFi urusanWiFi(wssid, wpass);
UrusanLED urusanLED(pinLED, pinLED, pinLED); // LED RGB dengan warna putih
UrusanIoT urusanIoT(tbAddr, tbPort, clientId.c_str(), "latihan", "bukanbudakai");
UrusanUltrasonic urusanUltrasonic(tankHeight, pinTrigger, pinEcho);


// Tulis deklarasi fungsi mu di sini:
void cetakIdentitasDeveloper();
void penangkapPesan(String topic, String message);
void subscribe();
void bacaJarak();


#endif