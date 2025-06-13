#include <main.h>


void setup() {
  // tulis setup kode mu di sini, untuk dijalankan sekali saja:  
  Serial.begin(115200);
  cetakIdentitasDeveloper();


  urusanWiFi.konek();
  while(urusanWiFi.apakahKonek() == 0){
    Serial.print(".");
  }


  urusanIoT.konek();
  urusanIoT.penangkapPesan(penangkapPesan);


  if(urusanIoT.apakahKonek() == 1){
    subscribe();
  }


  urusanUltrasonic.mulai();


  urusanLED.setWarna(100, 100, 100);
  delay(3000);
  urusanLED.setWarna(0, 0, 0);
}


static unsigned long lastUpdateMillis = 0;
void loop() {
  // tulis kode utama mu di sini, untuk dijalankan berulang-ulang :
  urusanIoT.proses();


  if(urusanIoT.apakahKonek() == 0){
    //Serial.println("UrusanIoT: Koneksi terputus, mencoba untuk menyambung kembali...");
    //urusanIoT.konek();
    if(urusanIoT.apakahKonek() == 1){
      subscribe();
    }
  }


  if (millis() - lastUpdateMillis >= 1000) {
    lastUpdateMillis = millis();


    lastDistance = urusanUltrasonic.bacaJarak();
    lastPercent = urusanUltrasonic.bacaLevel(lastDistance);


    String payload;
    JsonDocument doc;
    doc["distance"] = lastDistance;
    doc["percent"] = lastPercent;
    serializeJson(doc, payload);


    urusanIoT.publish("404notfound/damodar/status", payload);
  }


  // make the led blink if lastPercent is outside bottomThreshold and upperThreshold
  if (lastPercent < bottomThreshold || lastPercent > upperThreshold) {
    urusanLED.setWarna(100, 0, 0); // LED merah
  } else {
    urusanLED.setWarna(0, 0, 0); // LED hijau
  }
  delay(10);
}


void subscribe() {
  urusanIoT.subscribe("404notfound/damodar/command");
}


void penangkapPesan(String topic, String message){
  Serial.printf("penangkapPesan: topic: %s | message: %s\r\n", topic.c_str(), message.c_str());
  JsonDocument dataMasuk;
  DeserializationError galatParseJson = deserializeJson(dataMasuk, message);
  if(galatParseJson == DeserializationError::Ok){
    if(!dataMasuk["bottomThreshold"].isNull() && !dataMasuk["upperThreshold"].isNull()){
      bottomThreshold = dataMasuk["bottomThreshold"].as<int>();
      upperThreshold = dataMasuk["upperThreshold"].as<int>();
    }
  }
  else
  {
    Serial.printf("penangkapPesan: Gagal parse JSON: %s\r\n", galatParseJson.c_str());
  }
}


/**
 * @brief Membaca jarak permukaan air menggunakan sensor ultrasonik.
 * Hasil disimpan pada variabel global lastDistance (cm) dan lastPercent (%).
 * lastPercent = 100 berarti tangki penuh, 0 berarti kosong.
 */
void bacaJarak() {
  // Untuk sensor ultrasonik HC-SR04 pada ESP32:
  pinMode(pinTrigger, OUTPUT);
  pinMode(pinEcho, INPUT);


  // Kirim trigger pulse
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);


  // Baca durasi pantulan
  long duration = pulseIn(pinEcho, HIGH, 30000); // timeout 30ms (sekitar 5 meter)
  // Hitung jarak (cm)
  int distance = duration * 0.034 / 2;
  lastDistance = distance;


  // Hitung persentase ketinggian air
  int percent = 100 - ((distance * 100) / tankHeight);
  if (percent < 0) percent = 0;
  if (percent > 100) percent = 100;
  lastPercent = percent;
}


// tulis definisi fungsi mu di sini:
void cetakIdentitasDeveloper() {
  Serial.printf("NIM: %d\r\n", NIM);  
  Serial.printf("Nama: %s\r\n", NAMA_LENGKAP);
  Serial.printf("Grup: %s\r\n", NAMA_KELOMPOK);
  Serial.printf("Firmware: %s %s\r\n", CURRENT_FIRMWARE_TITLE, CURRENT_FIRMWARE_VERSION);
}