#ifndef ANALOG_SENSOR_H
#define ANALOG_SENSOR_H
#include <Arduino.h>

class AnalogSensorPH
{
  private:
    int PinSensorPH;
    int Samples;
    int Time_Samples;
  
  public:
  //Constructor con inicializador
  AnalogSensorPH(int _PinSensorPH, const int _Samples, int _Time_Samples):PinSensorPH(_PinSensorPH),Samples(_Samples),Time_Samples(_Time_Samples){}

  //Funciones get
  int getPinSensorPH() const { return PinSensorPH; }
  int getSamples() const { return Samples; }
  int getTimeSamples() const { return Time_Samples; }

  //Funciones empleadas
  float PH_Measure();
};

class AnalogSensorEC
{
  private:
    int PinSensorEC;
    int Samples;
    int Time_Samples;
  
  public:
  //Constructor con inicializador
  AnalogSensorEC(int _PinSensorEC, const int _Samples, int _Time_Samples):PinSensorEC(_PinSensorEC),Samples(_Samples),Time_Samples(_Time_Samples){}

  //Funciones get
  int getPinSensorPH() const { return PinSensorEC; }
  int getSamples() const { return Samples; }
  int getTimeSamples() const { return Time_Samples; }

  //Funciones empleadas
  float EC_Measure();
};

#endif