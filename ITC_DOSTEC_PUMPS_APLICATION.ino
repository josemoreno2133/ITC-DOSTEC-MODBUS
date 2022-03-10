// #if !defined( ESP32 )
//   #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.
// #endif

#include "FreeRTOSConfig.h"
#include <ModbusMaster.h>
#include "config.h"
#include "analog_sensor.h"
#include "sdi12_sensor.h"

//Constructors
ModbusMaster pump1;
ModbusMaster pump2;
ModbusMaster pump3;

AnalogSensorPH pH1(pHsensor1, 20, 5);   //pin, muestras, tiempo entre muestra
AnalogSensorEC EC1(ECsensor1, 20, 5);
AnalogSensorEC EC2(ECsensor2, 20, 5);
AnalogSensorEC EC3(ECsensor3, 20, 5);

//Create a news tasks
TaskHandle_t Task2;

//Function check Modbus request
uint8_t CheckModbusRequest(ModbusMaster &b, const uint8_t result)
{
  if(result == b.ku8MBSuccess) 
  {
    Serial.println("\nCorrect request.");
    return true;
  }
  else 
  {
    Serial.println("Modbus request error!!! ");
    Serial.print("--> Error type: ");    
    b.getResultMsg(result);
    menu_mqtt = 18;
    return false;
  }
}

void setup() 
{
  pinMode(flowSensor1, INPUT_PULLUP);
  pinMode(pulse_emitter_relay_1, OUTPUT);
  pinMode(pulse_emitter_relay_2, OUTPUT);
  pinMode(pulse_emitter_relay_3, OUTPUT);
  pinMode(StatusPin_DE_RE, OUTPUT);
  digitalWrite(StatusPin_DE_RE, HIGH);
  digitalWrite(pulse_emitter_relay_1, HIGH);
  
  xTaskCreatePinnedToCore(loop2, "Task_2", 1000, NULL, 1, &Task2, 0);
  delay(500);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);   //Para la comunicación Modbus

  //Interruption
  noInterrupts();  
  attachInterrupt(digitalPinToInterrupt(flowSensor1), ISR, FALLING);   
  interrupts();
  delay(200);
                       
  setup_Wifi();

  //Assigns the Modbus slave ID and serial port.
  pump1.begin(id_slave_pump1, Serial2);   
  delay(100);
  pump2.begin(id_slave_pump2, Serial2);   
  delay(100);
  pump3.begin(id_slave_pump3, Serial2);   
  delay(100);
  
  // Callbacks allow us to configure the RS485 transceiver correctly
  pump1.preTransmission(preTransmission);
  pump1.postTransmission(postTransmission);
  pump2.preTransmission(preTransmission);
  pump2.postTransmission(postTransmission);
  pump3.preTransmission(preTransmission);
  pump3.postTransmission(postTransmission);

  setup_sdi12();
  
  print_data_flash_memory();

  setup_ready = true; 
}

//*********************************************************************************************************************************
//-----------------------------------------------------LOOP (CPU0)-----------------------------------------------------------------
//*********************************************************************************************************************************
void loop2(void *parameter)
{  
  /*Implementation of vTaskDelayUntil
    Delay a task until a specified time. This function can be used by periodic tasks to ensure a constant execution frequency.*/
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 10;
  xLastWakeTime = xTaskGetTickCount();

  /*Implementation of uxTaskGetStackHighWaterMark
    uxTaskGetStackHighWaterMark() returns the minimum amount of remaining stack space that was available to the task since the task 
    started executing - that is the amount of stack that remained unused when the task stack was at its greatest (deepest) value.*/
    UBaseType_t uxHighWaterMark; 
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );         
  
  for(;;)
  {
    //Wait for the next cycle.
    vTaskDelayUntil( &xLastWakeTime, xFrequency ); 

    uint8_t result;
    Actual_Time = millis();
//*********************************************************************************************************************************
//-----------------------------------------------------WRITE REGISTER MODBUS-------------------------------------------------------
//*********************************************************************************************************************************  
    switch(menu_modbus)
    {
      case 1:
      Serial.println("Escribiendo registro Modbus...");
      result = pump1.writeSingleRegister(4696, regulation1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      Serial.println("Escribiendo registro Modbus...");
      result = pump1.writeSingleRegister(4698, FlowLimit1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 2:
      result = pump2.writeSingleRegister(4696, regulation2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4698, FlowLimit2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 3:
      result = pump3.writeSingleRegister(4696, regulation3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4698, FlowLimit3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 4:
      result = pump1.writeSingleRegister(4718, k_factor1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      result = pump1.writeSingleRegister(4720, FlowTimeZero1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 5:
      result = pump2.writeSingleRegister(4718, k_factor2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4720, FlowTimeZero2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 6:
      result = pump3.writeSingleRegister(4718, k_factor3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4720, FlowTimeZero3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 7:
      result = pump1.writeSingleRegister(4756, Min_Span1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      result = pump1.writeSingleRegister(4758, Max_Span1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 8:
      result = pump2.writeSingleRegister(4756, Min_Span2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4758, Max_Span2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 9:
      result = pump3.writeSingleRegister(4756, Min_Span3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4758, Max_Span3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;
      
      case 10:
      result = pump1.writeSingleRegister(4706, liters);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 11:
      result = pump2.writeSingleRegister(4706, liters);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 12:
      result = pump3.writeSingleRegister(4706, liters);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 13:
      result = pump1.writeSingleRegister(4708, bar);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 14:
      result = pump2.writeSingleRegister(4708, bar);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 15:
      result = pump3.writeSingleRegister(4708, bar);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 16:
      result = pump1.writeSingleRegister(4710, unitsProportional);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 17:
      result = pump2.writeSingleRegister(4710, unitsProportional);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 18:
      result = pump3.writeSingleRegister(4710, unitsProportional);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 19:
      result = pump1.writeSingleRegister(4712, typeFlowmeter);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 20:
      result = pump2.writeSingleRegister(4712, typeFlowmeter);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 21:
      result = pump3.writeSingleRegister(4712, typeFlowmeter);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 22:
      result = pump1.writeSingleRegister(4702, PumpDosingMode1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 23:
      result = pump2.writeSingleRegister(4702, PumpDosingMode2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 24:
      result = pump3.writeSingleRegister(4702, PumpDosingMode3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 25:
      result = pump1.writeSingleRegister(4742, typeProportional);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 26:
      result = pump2.writeSingleRegister(4742, typeProportional);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 27:
      result = pump3.writeSingleRegister(4742, typeProportional);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 28:
      result = pump1.writeSingleRegister(4760, type_analog_input);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 29:
      result = pump2.writeSingleRegister(4760, type_analog_input);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 30:
      result = pump3.writeSingleRegister(4760, type_analog_input);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 31:
      result = pump1.writeSingleRegister(1, stop_run1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 32:
      result = pump2.writeSingleRegister(1, stop_run2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 33:
      result = pump3.writeSingleRegister(1, stop_run3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 34:
      result = pump1.writeSingleRegister(4686, dosing_flow1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 35:
      result = pump2.writeSingleRegister(4686, dosing_flow2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 36:
      result = pump3.writeSingleRegister(4686, dosing_flow3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 37:
      result = pump1.writeSingleRegister(4744, xy_input_pulses1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}  
      result = pump1.writeSingleRegister(4748, xy_output_cycles1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;} 
      result = pump1.writeSingleRegister(4750, flowsetpoint_xy1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      result = pump1.writeSingleRegister(4746, memory_xy1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 38:
      result = pump2.writeSingleRegister(4744, xy_input_pulses2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4748, xy_output_cycles2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4750, flowsetpoint_xy2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      result = pump2.writeSingleRegister(4746, memory_xy2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;
      
      case 39:
      result = pump3.writeSingleRegister(4744, xy_input_pulses3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4748, xy_output_cycles3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4750, flowsetpoint_xy3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      result = pump3.writeSingleRegister(4746, memory_xy3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break; 

      case 40:
      result = pump1.writeSingleRegister(4752, setpoint_mode_ppm1);
      if(CheckModbusRequest(pump1, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 41:
      result = pump2.writeSingleRegister(4752, setpoint_mode_ppm2);
      if(CheckModbusRequest(pump2, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;

      case 42:      
      result = pump3.writeSingleRegister(4752, setpoint_mode_ppm3);
      if(CheckModbusRequest(pump3, result)) {menu_mqtt = 1;}
      menu_modbus = 0;
      break;
    }
//*********************************************************************************************************************************
//-----------------------------------------------------READ REGISTERS MODBUS-------------------------------------------------------
//********************************************************************************************************************************* 

                                          /* ESTE APARTADO QUEDA PENDIENTE DE IMPLEMENTAR TODAVIA*/

//*********************************************************************************************************************************
//---------------------------------------------------------FLOW MEASUREMENT--------------------------------------------------------
//*********************************************************************************************************************************
    if(k_factor1 == k_factor2 == k_factor3)
    {
      if((Actual_Time >= flow_measurement_event) && (!send_mqtt_flow))
      {
        frequency = NumPulses;
        NumPulses = 0.f;
        flow_measurement_event = millis();
        flow_measurement_event += flow_measurement_interval;
        Serial.println();
        Serial.println("*****************************************************************************************************");
        Serial.println("El numero de pulsos en 10 segundos ha sido..." + String(frequency));
        frequency = frequency/10.00;
        measured_flow_value = frequency/k_div_freq1; 
        copy_measured_flow_value = measured_flow_value; 
        send_mqtt_flow = true;
        Serial.println("El valor del caudal es..." + String(measured_flow_value, 5));
        Serial.println("*****************************************************************************************************");
        Serial.println();
      }
    }
    else
    {
      if(Actual_Time >= not_factor_k_event)
      {
        not_factor_k_event = millis();
        not_factor_k_event += not_factor_k_interval;
        menu_mqtt = 14;
      }
    }
//*********************************************************************************************************************************
//-------------------------------------------------------PH ANALOG MEASUREMENT-----------------------------------------------------
//*********************************************************************************************************************************
    if(Actual_Time >= ph_measurement_event)
    {
      if(!send_mqtt_ph1)
      {
        ph_measurement_event = millis();
        ph_measurement_event += ph_measurement_interval;
        pH_value = pH1.PH_Measure();
        copy_ph_value = pH_value;
        send_mqtt_ph1 = true;
        Serial.print("   PH: ");
        Serial.println(pH_value);
      } 
    }
//*********************************************************************************************************************************
//-------------------------------------------------------EC1 ANALOG MEASUREMENT----------------------------------------------------
//*********************************************************************************************************************************
    if(Actual_Time >= ec1_measurement_event)
    {
      if(!send_mqtt_ec1)
      {
        ec1_measurement_event = millis();
        ec1_measurement_event += ec1_measurement_interval;
        ec1_value = EC1.EC_Measure();
        copy_ec1_value = ec1_value;
        send_mqtt_ec1 = true;
        Serial.print("   EC1: ");
        Serial.println(ec1_value);
      }
    }  
//*********************************************************************************************************************************
//-------------------------------------------------------EC2 ANALOG MEASUREMENT----------------------------------------------------
//*********************************************************************************************************************************
    if(Actual_Time >= ec2_measurement_event)
    {  
      if(!send_mqtt_ec2)
      {
        ec2_measurement_event = millis();
        ec2_measurement_event += ec2_measurement_interval;
        ec2_value = EC2.EC_Measure();
        copy_ec2_value = ec2_value;
        send_mqtt_ec2 = true;
        Serial.print("   EC2: ");
        Serial.println(ec2_value);
      }
    }  
//*********************************************************************************************************************************
//-------------------------------------------------------EC3 ANALOG MEASUREMENT----------------------------------------------------
//*********************************************************************************************************************************
    if(Actual_Time >= ec3_measurement_event)
    {  
      if(!send_mqtt_ec3)
      {
        ec3_measurement_event = millis();
        ec3_measurement_event += ec3_measurement_interval;
        ec3_value = EC3.EC_Measure();
        copy_ec3_value = ec3_value;
        send_mqtt_ec3 = true;
        Serial.print("   EC3: ");
        Serial.println(ec3_value);
      }
    }  
//*********************************************************************************************************************************
//---------------------------------------------------------SDI12 MEASUREMENT-------------------------------------------------------
//********************************************************************************************************************************* 
    if(Actual_Time >= sdi12_sensors_event)
    {
      loop_sdi12_measurement();
      sdi12_sensors_event = millis();
      sdi12_sensors_event += sdi12_sensors_interval;
      send_mqtt_ec1_sdi = true;
    }
//*********************************************************************************************************************************
//----------------------------------------------TRANSMIT PULSES FLOW TO PUMPS (relay G3MB-202P)------------------------------------
//********************************************************************************************************************************* 
    if(flag_activate_relay_outputs) {ActivateRelayOutputs();}
//*********************************************************************************************************************************
//-----------------------------------------------------STACK SPACE CALCULATION-----------------------------------------------------
//*********************************************************************************************************************************        
    if(Actual_Time >= StackHighWaterMark_event)
    {
      StackHighWaterMark_event = millis();
      StackHighWaterMark_event += StackHighWaterMark_interval;
      uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
      Serial.println();
      Serial.println("-----------------------------------------------------------------------------------------------------");
      Serial.println("Task 2 --> Restante pila = " + String(uxHighWaterMark));
      Serial.println("-----------------------------------------------------------------------------------------------------");
      Serial.println();
    }
  }
}




//*********************************************************************************************************************************
//-------------------------------------------------------LOOP (CPU1)---------------------------------------------------------------
//*********************************************************************************************************************************
void loop()
{
    while(!setup_ready) {delay(100);} 
    if (!client.connected()) { reconnect(); }
    client.loop();

    if(client.connected())
    {
      switch(menu_mqtt)
      {
        case 1:
        client.publish("notification/correct/data", "Data added successfully.");
        menu_mqtt = 0;
        break;

        case 2:
        client.publish("notification/error/1", "Invalid quantity error.");
        menu_mqtt = 0;
        break;

        case 3:
        client.publish("notification/error/2", "0% is not possible value.");
        menu_mqtt = 0;
        break;

        case 4:
        client.publish("notification/menu/error", "Error. The data not added. Try again");
        menu_mqtt = 0;
        break;

        case 5:
        client.publish("notification/manual/error/1", "Error. Maximum flow = 301 (l/h)");
        menu_mqtt = 0;
        break;

        case 6:
        client.publish("notification/manual/error/2", "Error. Minimun flow = 30 (l/h)");
        menu_mqtt = 0;
        break;

        case 7:
        client.publish("notification/manual/error/3", "Error. Minimun flow = 3.01 (l/h)");
        menu_mqtt = 0;
        break;

        case 8:
        client.publish("notification/manual/error/4", "Error. Maximum flow = 150 (l/h)");
        menu_mqtt = 0;
        break;

        case 9:
        client.publish("notification/manual/error/5", "Error. Maximum flow = 105 (l/h)");
        menu_mqtt = 0;
        break;

        case 10:
        client.publish("notification/pulse/ratio/error", "Error. Maximum number of pump cycles in XY proportional mode.");
        menu_mqtt = 0;
        break;

        case 11:
        client.publish("notification/not/manual/error", "Please, switch to manual mode.");
        menu_mqtt = 0;
        break;

        case 12:
        client.publish("notification/not/proportional/error", "Please, switch to proportional mode.");
        menu_mqtt = 0;
        break;

        case 13:
        client.publish("notification/not/k/factor", "Please, enter factor-k for all pump.");
        menu_mqtt = 0;
        break;

        case 14:
        client.publish("notification/different/k/factor", "Please, enter an equal k-factor for all pumps.");
        menu_mqtt = 0;
        break;

        case 15:
        client.publish("notification/span/analog/error/1", "Error, PUMP 1 Analog Input Span --> MIN > MAX.");
        menu_mqtt = 0;
        break;

        case 16:
        client.publish("notification/span/analog/error/2", "Error, PUMP 2 Analog Input Span --> MIN > MAX.");
        menu_mqtt = 0;
        break;

        case 17:
        client.publish("notification/span/analog/error/3", "Error, PUMP 3 Analog Input Span --> MIN > MAX.");
        menu_mqtt = 0;
        break;

        case 18:
        client.publish("notification/modbus/error", "Error Modbus. Please, try again and check the pump slave number.");
        menu_mqtt = 0;
        break;

        case 19:
        client.publish("notification/setup/dosing/error", "Error, Flow limit can't be higher than Regulation.");
        menu_mqtt = 0;
        break;
      }
        
        if(send_mqtt_flow)
        {
          char flow_Measurement_String[8];
          dtostrf(copy_measured_flow_value, 1, 2, flow_Measurement_String); 
          client.publish("esp32/flow/measurement",flow_Measurement_String);
          send_mqtt_flow = false;
        }

        
        if(send_mqtt_ph1)
        {
          char phString[8];
          dtostrf(copy_ph_value, 1, 2, phString); 
          client.publish("esp32/ph/analog/measurement",phString);
          send_mqtt_ph1 = false;
        }
        
        if(send_mqtt_ec1)
        {
          char ec1String[8];
          dtostrf(copy_ec1_value, 1, 2, ec1String); 
          client.publish("esp32/ec1/analog/measurement",ec1String);
          send_mqtt_ec1 = false;
        }
        
        if(send_mqtt_ec2)
        {
          char ec2String[8];
          dtostrf(copy_ec2_value, 1, 2, ec2String); 
          client.publish("esp32/ec2/analog/measurement",ec2String);
          send_mqtt_ec2 = false;
        }
       
        if(send_mqtt_ec3)
        {
          char ec3String[8];
          dtostrf(copy_ec3_value, 1, 2, ec3String); 
          client.publish("esp32/ec3/analog/measurement",ec3String);
          send_mqtt_ec3 = false;
        }
       
        if(send_mqtt_ec1_sdi)
        {
          char ec1_sdi[10];
          char temp_sdi[8];
          dtostrf(electroconductividad, 1, 2, ec1_sdi);
          dtostrf(temperatura, 1, 2, temp_sdi);
          client.publish("esp32/ec1/sdi12/measurement",ec1_sdi);
          client.publish("esp32/ec2/sdi1/temperature", temp_sdi);
          send_mqtt_ec1_sdi = false;
        }   
    }
}


