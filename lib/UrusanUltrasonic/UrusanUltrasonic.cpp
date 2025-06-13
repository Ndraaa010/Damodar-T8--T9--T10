#include "UrusanUltrasonic.h"


UrusanUltrasonic::UrusanUltrasonic(float tinggiReservoir,
    const int trigPin, const int echoPin) : _tinggiReservoir(tinggiReservoir), _trigPin(trigPin),
    _echoPin(echoPin), _hcsr04(trigPin, echoPin){}


bool UrusanUltrasonic::mulai(){
    return true;
}


bool UrusanUltrasonic::apakahSensorSiap(){
    return true;
}


/// @brief Fungsi untuk membaca jarak ke permukaan air dalam centi meter
/// @return jarak dalam CM
float UrusanUltrasonic::bacaJarak(){
    float jarakCm = _hcsr04.dist();
    return jarakCm;
}


/// @brief Fungsi untuk membaca level air dalam persen
/// @param jarak
/// @return level dalam persen
float UrusanUltrasonic::bacaLevel(float jarak){
    float level = (_tinggiReservoir - jarak) / _tinggiReservoir * 100;


    return level;
}
