#ifndef UrusanUltrasonic_h
#define UrusanUltrasonic_h


#include <Arduino.h>
#include <HCSR04.h>


class UrusanUltrasonic {
    public:
        UrusanUltrasonic(float tinggiReservoir, const int trigPin, const int echoPin);
        bool mulai();
        float bacaLevel(float jarak);
        float bacaJarak();
        bool apakahSensorSiap();
   
    private:
        float _tinggiReservoir;
        bool _sensorSiap = false;
        const int _trigPin;
        const int _echoPin;
        HCSR04 _hcsr04;
};


#endif
