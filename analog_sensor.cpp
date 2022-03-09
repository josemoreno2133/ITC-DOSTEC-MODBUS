#include "analog_sensor.h"

float AnalogSensorPH::PH_Measure()
  {
    int a[Samples-1];
    float avgval=0;
    int tmp=0;
    int flag=1;
  
  //Lectura de datos
    for(int i=0; i<Samples; i++)
    {
      a[i]=analogRead(PinSensorPH);
      delay(Time_Samples);
    }
  
  //Se ordenan de menor a mayor
    for(int j=0; (j<Samples)&&flag; j++){
      flag=0;
      for(int k=0; k<(Samples-1);k++){
        if(a[k+1]<a[k])
        {
          tmp=a[k];
          a[k]=a[k+1];
          a[k+1]=tmp;
          flag=1;
        }
      }
    }

  //Se eliminan los datos atípicos de los extremos
    int N=0;
    if(Samples<20)
    {
      for(int x=2; x<8; x++) 
      { 
        avgval+=a[x];
        N++;
      }  
    }
    
    if(Samples>=20)
    {
      for(int z=4; z<16;z++) 
      { 
        avgval+=a[z];
        N++;
      }
    }

    // Serial.print("El numero demuestras es = ");
    // Serial.println(N);
    float volt=(float)avgval*3.3/4095.00/N;
    float ph_sin_calibrar = volt/0.2357142;
    Serial.print("valor analogico: ");
    Serial.print(avgval/N);
    Serial.print(" Voltaje: ");
    Serial.print(volt);
    Serial.print("V");
    return(ph_sin_calibrar);
}


float AnalogSensorEC::EC_Measure()
  {
    int a[Samples-1];
    float avgval=0;
    int tmp=0;
    int flag=1;
  
  //Lectura de datos
    for(int i=0; i<Samples; i++)
    {
      a[i]=analogRead(PinSensorEC);
      delay(Time_Samples);
    }
  
  //Se ordenan de menor a mayor
    for(int j=0; (j<Samples)&&flag; j++){
      flag=0;
      for(int k=0; k<(Samples-1);k++){
        if(a[k+1]<a[k])
        {
          tmp=a[k];
          a[k]=a[k+1];
          a[k+1]=tmp;
          flag=1;
        }
      }
    }

  //Se eliminan los datos atípicos de los extremos
    int N=0;
    if(Samples<20)
    {
      for(int x=2; x<8; x++) 
      { 
        avgval+=a[x];
        N++;
      }  
    }
    
    if(Samples>=20)
    {
      for(int z=4; z<16;z++) 
      { 
        avgval+=a[z];
        N++;
      }
    }

    // Serial.print("El numero demuestras es = ");
    // Serial.println(N);
    float volt=(float)avgval*3.3/4095.00/N;
    float EC_sin_calibrar = volt/0.0006;
    Serial.print("valor analogico: ");
    Serial.print(avgval/N);
    Serial.print(" Voltaje: ");
    Serial.print(volt);
    Serial.print("V");
    return(EC_sin_calibrar);
}