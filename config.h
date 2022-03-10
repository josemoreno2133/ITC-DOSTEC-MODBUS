#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Preferences.h>
#include <ArduinoJson.h>

//WiFi & MQTT 
const char* ssid = "xxxxx";
const char* password = "xxxxx";
const char* mqtt_server = "xxxxx.myqnapcloud.com";


//ESP32 pin utilization
const uint8_t StatusPin_DE_RE = 27;                       // Habilita y desabilida la transmisión del MAX485 IC.
const uint8_t RXD2 = 16;                                  // Pin Receptor de datos R0
const uint8_t TXD2 = 17;                                  // Pin Transmisor de datos DI
const uint8_t pHsensor1 = 39;                             // Pin lectura analógica del sensor de pH1
const uint8_t ECsensor1 = 36;                             // Pin lectura analógica del sensor de EC1
const uint8_t ECsensor2 = 34;                             // Pin lectura analógica del sensor de EC2
const uint8_t ECsensor3 = 35;                             // Pin lectura analógica del sensor de EC3 
const uint8_t flowSensor1 = 14;                           // Pin lectura pwm del contador de pulsos (caudalímetro).
const uint8_t pulse_emitter_relay_1 = 12;                 // Pin emisor de caudal para la bomba 1
const uint8_t pulse_emitter_relay_2 = 13;                 // Pin emisor de caudal para la bomba 2
const uint8_t pulse_emitter_relay_3 = 5;                  // Pin emisor de caudal para la bomba 3

//Need to take care of the synchronization between the main code and the interrupt.
portMUX_TYPE synch = portMUX_INITIALIZER_UNLOCKED;

WiFiClient espClient;                     
PubSubClient client(espClient);           
Preferences preferences;                  

//Global Variables
uint8_t id_slave_pump1 = 1;                      
uint8_t id_slave_pump2 = 2;                      
uint8_t id_slave_pump3 = 3;                     
uint16_t dosing_flow1 = 0;
uint16_t dosing_flow2 = 0;
uint16_t dosing_flow3 = 0;
uint16_t regulation1 = 0;
uint16_t regulation2 = 0;
uint16_t regulation3 = 0; 
uint16_t FlowLimit1 = 0; 
uint16_t FlowLimit2 = 0; 
uint16_t FlowLimit3 = 0; 
uint16_t FlowTimeZero1 = 0;
uint16_t FlowTimeZero2 = 0;
uint16_t FlowTimeZero3 = 0;
uint16_t PumpDosingMode1 = 0;     //guardar en memoria
uint16_t PumpDosingMode2 = 0;     //guardar en memoria
uint16_t PumpDosingMode3 = 0;     //guardar en memoria
uint16_t Min_Span1 = 0;
uint16_t Min_Span2 = 0;
uint16_t Min_Span3 = 0;
uint16_t Max_Span1 = 0;
uint16_t Max_Span2 = 0;
uint16_t Max_Span3 = 0;
uint16_t xy_input_pulses1 = 0;    //guardar en memoria
uint16_t xy_input_pulses2 = 0;    //guardar en memoria
uint16_t xy_input_pulses3 = 0;    //guardar en memoria
uint16_t xy_output_cycles1 = 0;   //guardar en memoria
uint16_t xy_output_cycles2 = 0;   //guardar en memoria
uint16_t xy_output_cycles3 = 0;   //guardar en memoria
uint16_t flowsetpoint_xy1 = 0;
uint16_t flowsetpoint_xy2 = 0;
uint16_t flowsetpoint_xy3 = 0;
uint16_t memory_xy1 = 0;
uint16_t memory_xy2 = 0;
uint16_t memory_xy3 = 0;
uint16_t setpoint_mode_ppm1 = 0;  //guardar en memoria
uint16_t setpoint_mode_ppm2 = 0;  //guardar en memoria
uint16_t setpoint_mode_ppm3 = 0;  //guardar en memoria
uint16_t k_factor1 = 0;           //guardar en memoria
uint16_t k_factor2 = 0;           //guardar en memoria
uint16_t k_factor3 = 0;           //guardar en memoria
float k_div_freq1 = 0.f;          //guardar en memoria
float k_div_freq2 = 0.f;          //guardar en memoria
float k_div_freq3 = 0.f;          //guardar en memoria
float pulse_ratio1 = 0.f;         //guardar en memoria
float pulse_ratio2 = 0.f;         //guardar en memoria
float pulse_ratio3 = 0.f;         //guardar en memoria
float pH_value = 0.f;
float copy_ph_value = 0.f;
float ec1_value = 0.f;
float copy_ec1_value = 0.f;
float ec2_value = 0.f;
float copy_ec2_value = 0.f;
float ec3_value = 0.f;
float copy_ec3_value = 0.f;
float frequency = 0.f;
float measured_flow_value = 0.f;
float copy_measured_flow_value = 0.f;
volatile float NumPulses = 0.f;
bool liters = false;                              
bool bar = false;                                 
bool unitsProportional = false;                   
bool typeFlowmeter = false;                       
bool typeProportional = false;                   
bool type_analog_input = false;                   
bool select_manual_mode1 = true;  //guardar en memoria
bool select_manual_mode2 = true;  //guardar en memoria
bool select_manual_mode3 = true;  //guardar en memoria
bool stop_run1 = false;           //guardar en memoria
bool stop_run2 = false;           //guardar en memoria
bool stop_run3 = false;           //guardar en memoria
String id_pump;


uint8_t menu_modbus = 0;
uint8_t menu_json = 0;
uint8_t menu_mqtt = 0;
unsigned long Actual_Time = 0;
unsigned long flow_measurement_event = 0;
unsigned long flow_measurement_interval = 10000UL;
unsigned long not_factor_k_event = 10000UL;
unsigned long not_factor_k_interval = 20000UL;
unsigned long span_analog_error_event1 = 0;
unsigned long span_analog_error_event2 = 0;
unsigned long span_analog_error_event3 = 0;
unsigned long span_analog_error_interval1 = 8000UL;
unsigned long span_analog_error_interval2 = 8000UL;
unsigned long span_analog_error_interval3 = 8000UL;
unsigned long sdi12_sensors_event = 0;
unsigned long sdi12_sensors_interval = 1000UL;
unsigned long ph_measurement_event = 0;
unsigned long ph_measurement_interval = 2000UL;
unsigned long ec1_measurement_event = 0;
unsigned long ec1_measurement_interval = 3000UL;
unsigned long ec2_measurement_event = 0;
unsigned long ec2_measurement_interval = 4000UL;
unsigned long ec3_measurement_event = 0;
unsigned long ec3_measurement_interval = 4500UL;
unsigned long StackHighWaterMark_event = 0;
unsigned long StackHighWaterMark_interval = 10000UL;

//Flags
bool setup_ready = false;
bool flag_setup_analog_input1 = false;
bool flag_setup_analog_input2 = false;
bool flag_setup_analog_input3 = false;
bool flag_setup_min_span1 = false;
bool flag_setup_max_span1 = false;
bool flag_setup_min_span2 = false;
bool flag_setup_max_span2 = false;
bool flag_setup_min_span3 = false;
bool flag_setup_max_span3 = false;
bool flag_setup_factor_k1 = false;
bool flag_setup_factor_k2 = false;
bool flag_setup_factor_k3 = false;
bool flag_setup_flowtime1 = false;
bool flag_setup_flowtime2 = false;
bool flag_setup_flowtime3 = false;
bool flag_setup_regulation1 = false;
bool flag_setup_regulation2 = false;
bool flag_setup_regulation3 = false;
bool flag_setup_flowlimit1 = false;
bool flag_setup_flowlimit2 = false;
bool flag_setup_flowlimit3 = false;
bool flag_proportional_x1 = false;
bool flag_proportional_x2 = false;
bool flag_proportional_x3 = false;
bool flag_proportional_y1 = false;
bool flag_proportional_y2 = false;
bool flag_proportional_y3 = false;
bool flag_proportional_q1 = false;
bool flag_proportional_q2 = false;
bool flag_proportional_q3 = false;
bool flag_proportional_m1 = false;
bool flag_proportional_m2 = false;
bool flag_proportional_m3 = false;
volatile bool flag_activate_relay_outputs = false;

//Flags MQTT
bool send_mqtt_flow = false;
bool send_mqtt_ph1 = false;
bool send_mqtt_ec1 = false;
bool send_mqtt_ec2 = false;
bool send_mqtt_ec3 = false;
bool send_mqtt_ec1_sdi = false;
bool send_mqtt_ec2_sdi = false;
bool send_mqtt_ec1_analg = false;
bool send_mqtt_ec2_analg = false;
bool send_mqtt_ec3_analg = false;

//Flags Notification Message
// bool send_notification_correct_data = false;              //menu_mqtt = 1
// bool send_notification_error1 = false;                    //menu_mqtt = 2                     
// bool send_notification_error2 = false;                    //menu_mqtt = 3                        
// bool send_notification_menu_error = false;                //menu_mqtt = 4
// bool send_notification_manual_error1 = false;             //menu_mqtt = 5
// bool send_notification_manual_error2 = false;             //menu_mqtt = 6
// bool send_notification_manual_error3 = false;             //menu_mqtt = 7
// bool send_notification_manual_error4 = false;             //menu_mqtt = 8
// bool send_notification_manual_error5 = false;             //menu_mqtt = 9
// bool send_notification_pulse_ratio_error = false;         //menu_mqtt = 10
// bool send_notification_not_manual_error = false;          //menu_mqtt = 11
// bool send_notification_not_proportional_error = false;    //menu_mqtt = 12
// bool send_notification_not_k_factor = false;              //menu_mqtt = 13
// bool send_notification_different_k_factor = false;        //menu_mqtt = 14
// bool send_notification_span_analog_error1 = false;        //menu_mqtt = 15
// bool send_notification_span_analog_error2 = false;        //menu_mqtt = 16
// bool send_notification_span_analog_error3 = false;        //menu_mqtt = 17
// bool send_notification_modbus_error = false;              //menu_mqtt = 18
// bool send_notification_setup_dosing_error = false;        //menu_mqtt = 19


//*********************************************************************************************************************************
//-------------------------------------------------TRANSMISIÓN MODBUS MAX485-------------------------------------------------------
//*********************************************************************************************************************************
// Función que habilita los pines RE y DE para activar el modo de transmisión de datos.
void preTransmission(){ digitalWrite(StatusPin_DE_RE, 1); }

// Función que deshabilita los pines RE y DE para activar el modo de recepción de datos.
void postTransmission() { digitalWrite(StatusPin_DE_RE, 0); }

//*********************************************************************************************************************************
//----------------------------------------------------FUNCTION MENU SETUP UNITS---------------------------------------------------
//*********************************************************************************************************************************
void menu_setup_units(String topic, String messageTemp)
{
  uint8_t varTemp = messageTemp.toInt();
  switch(varTemp){
    case 0:
    liters = false; 
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 10;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 11;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 12;}
    break;

    case 1:
    liters = true;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 10;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 11;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 12;}
    break;

    case 2:
    bar = false; 
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 13;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 14;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 15;}
    break;

    case 3:
    bar = true;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 13;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 14;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 15;}
    break;

    case 4:
    unitsProportional = false;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 16;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 17;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 18;}
    break;

    case 5:
    unitsProportional = true;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 16;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 17;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 18;}
    break;

    case 6:
    typeFlowmeter = false;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 19;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 20;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 21;}
    break;

    case 7:
    typeFlowmeter = true;
    if(topic == "esp32/setup/units/pump/1") {menu_modbus = 19;}
    if(topic == "esp32/setup/units/pump/2") {menu_modbus = 20;}
    if(topic == "esp32/setup/units/pump/3") {menu_modbus = 21;}
    break;

    default:
    menu_mqtt = 4;
  }
}
//*********************************************************************************************************************************
//--------------------------------------------------FUNCTION SETUP DOSING MODE-----------------------------------------------------
//*********************************************************************************************************************************
uint16_t menu_setup_dosing_mode(String messageTemp)
{
  uint16_t varTemp = messageTemp.toInt();
  switch(varTemp){
    case 0:
    Serial.print("Modo de dosificacion NORMAL");
    return varTemp;
    break;

    case 1:
    Serial.print("Modo de dosificacion Low Flow");
    return varTemp; 
    break;

    case 2:
    Serial.print("Modo de dosificacion Slow Suction");
    return varTemp;
    break;

    case 3:
    Serial.print("Modo de dosificacion Low Pulsation");
    return varTemp;
    break;

    default:
    menu_mqtt = 4;
    return 4;
  }
}
//*********************************************************************************************************************************
//--------------------------------------------------FUNCTION SETUP PROPORTIONAL TYPE-----------------------------------------------
//*********************************************************************************************************************************
void menu_setup_proportional_type(String topic, String messageTemp)
{
  uint8_t varTemp = messageTemp.toInt();
  switch(varTemp){
    case 0:  
    typeProportional = false;
    if(topic == "esp32/setup/proportional/mode/type/1") {menu_modbus = 25;}
    if(topic == "esp32/setup/proportional/mode/type/2") {menu_modbus = 26;}
    if(topic == "esp32/setup/proportional/mode/type/3") {menu_modbus = 27;}
    break;

    case 1:
    typeProportional = true;
    if(topic == "esp32/setup/proportional/mode/type/1") {menu_modbus = 25;}
    if(topic == "esp32/setup/proportional/mode/type/2") {menu_modbus = 26;}
    if(topic == "esp32/setup/proportional/mode/type/3") {menu_modbus = 27;}
    break;

    default:
    menu_mqtt = 4;
  }
}
//*********************************************************************************************************************************
//----------------------------------------------------FUNCTION SETUP ANALOG INPUT--------------------------------------------------
//*********************************************************************************************************************************
void menu_setup_analog_input(String topic, String messageTemp)
{
  uint8_t varTemp = messageTemp.toInt();
  switch(varTemp){
    case 0:  
    type_analog_input = false;
    if(topic == "esp32/setup/analog/input/pump/1") {menu_modbus = 28;}
    if(topic == "esp32/setup/analog/input/pump/2") {menu_modbus = 29;}
    if(topic == "esp32/setup/analog/input/pump/3") {menu_modbus = 30;}
    break;

    case 1:
    type_analog_input = true;
    if(topic == "esp32/setup/analog/input/pump/1") {menu_modbus = 28;}
    if(topic == "esp32/setup/analog/input/pump/2") {menu_modbus = 29;}
    if(topic == "esp32/setup/analog/input/pump/3") {menu_modbus = 30;}
    break;

    default:
    menu_mqtt = 4;
  }  
}
//*********************************************************************************************************************************
//----------------------------------------------------FUNCTION CHECK DOSING MODE MENU----------------------------------------------
//*********************************************************************************************************************************
void check_dosing_mode_menu(uint16_t var, String id_pump, uint16_t flow)
{
  switch(var)
  {
    case 0: //standar
    if(flow > 30100) {menu_mqtt = 5;}
    if(flow < 3000)  {menu_mqtt = 6;}
    if((flow >= 3000) && (flow <= 30100))
    {
      if(id_pump == "pump1") {menu_modbus = 34;}
      if(id_pump == "pump2") {menu_modbus = 35;}
      if(id_pump == "pump3") {menu_modbus = 36;}
    }
    break;

    case 1: //low flow
    if(flow > 30100) {menu_mqtt = 5;}
    if(flow < 301)   {menu_mqtt = 7;}
    if((flow >= 301) && (flow <= 3000))
    {
      if(id_pump == "pump1") {menu_modbus = 34;}
      if(id_pump == "pump2") {menu_modbus = 35;}
      if(id_pump == "pump3") {menu_modbus = 36;}
    }
    break;

    case 2: //slow suction
    if(flow > 15000) {menu_mqtt = 8;}
    if(flow < 3000)  {menu_mqtt = 6;}
    if((flow >= 3000) && (flow <= 15000)) 
    {
      if(id_pump == "pump1") {menu_modbus = 34;}
      if(id_pump == "pump2") {menu_modbus = 35;}
      if(id_pump == "pump3") {menu_modbus = 36;}
    }
    break;

    case 3: //low pulsation
    if(flow > 10500) {menu_mqtt = 9;}
    if(flow < 3000)  {menu_mqtt = 6;}
    if((flow >= 3000) && (flow <= 10500)) 
    {
      if(id_pump == "pump1") {menu_modbus = 34;}
      if(id_pump == "pump2") {menu_modbus = 35;}
      if(id_pump == "pump3") {menu_modbus = 36;}
    }
    break;

    default:
    menu_mqtt = 4;
  }
}
//*********************************************************************************************************************************
//----------------------------------------------------EXTRAER ARCHIVO JSON---------------------------------------------------------
//*********************************************************************************************************************************
void DeserializeObject(String str_topic, String messageTemp)
{
  String json = messageTemp;
  StaticJsonDocument<96> doc;
  DeserializationError error = deserializeJson(doc, json);
  
  if (error) 
  {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  switch(menu_json)
  {
    case 1:
    if(doc["R1"] != "")
    {
      regulation1 = doc["R1"];
      if(regulation1 > 100) {menu_mqtt = 2;}
      if(regulation1 < 0.5) {menu_mqtt = 3;}
      if((regulation1 >= 0.5) && (regulation1 < 100)) {flag_setup_regulation1 = true;}     
    }
    if(doc["FL1"] != "")
    {
      FlowLimit1 = doc["FL1"];
      if(FlowLimit1 > 100) {menu_mqtt = 2;}
      if(FlowLimit1 < 0.5) {menu_mqtt = 3;}
      if((FlowLimit1 >= 0.5) && (FlowLimit1 < 100)) {flag_setup_flowlimit1 = true;}
    }
    if(FlowLimit1 > regulation1) {menu_mqtt = 19;}
    else
    {
      if((flag_setup_regulation1)&&(flag_setup_flowlimit1)) 
      {
        menu_modbus = 1;
        flag_setup_regulation1 = false;
        flag_setup_flowlimit1 = false;
      }
    }
    menu_json = 0;
    break;

    case 2:
    if(doc["R2"] != "")
    {
      regulation2 = doc["R2"];
      if(regulation2 > 100) {menu_mqtt = 2;}
      if(regulation2 < 0.5) {menu_mqtt = 3;}
      if((regulation2 >= 0.5) && (regulation2 < 100)) {flag_setup_regulation2 = true;}      
    }
    if(doc["FL2"] != "")
    {
      FlowLimit2 = doc["FL2"];
      if(FlowLimit2 > 100) {menu_mqtt = 2;}
      if(FlowLimit2 < 0.5) {menu_mqtt = 3;}
      if((FlowLimit2 >= 0.5) && (FlowLimit2 < 100)) {flag_setup_flowlimit2 = true;}
    }
    if(FlowLimit2 > regulation2) {menu_mqtt = 19;}
    else
    {
      if((flag_setup_regulation2)&&(flag_setup_flowlimit2)) 
      {
        menu_modbus = 2;
        flag_setup_regulation2 = false;
        flag_setup_flowlimit2 = false;
      }
    }
    menu_json = 0;
    break;

    case 3:
    if(doc["R3"] != "")
    {
      regulation3 = doc["R3"];
      if(regulation3 > 100) {menu_mqtt = 2;}
      if(regulation3 < 0.5) {menu_mqtt = 3;}
      if((regulation3 >= 0.5) && (regulation3 < 100)) {flag_setup_regulation3 = true;}        
    }
    if(doc["FL3"] != "")
    {
      FlowLimit3 = doc["FL3"];
      if(FlowLimit3 > 100) {menu_mqtt = 2;}
      if(FlowLimit3 < 0.5) {menu_mqtt = 3;}
      if((FlowLimit3 >= 0.5) && (FlowLimit3 < 100)) {flag_setup_flowlimit3 = true;}
    }
    if(FlowLimit3 > regulation3) {menu_mqtt = 19;}
    else
    {
      if((flag_setup_regulation3)&&(flag_setup_flowlimit3)) 
      {
        menu_modbus = 3;
        flag_setup_regulation3 = false;
        flag_setup_flowlimit3 = false;
      }
    }
    menu_json = 0;
    break;

    case 4:
    if(doc["K1"] != "")
    {
      k_factor1 = doc["K1"];
      if(k_factor1 > 999) {menu_mqtt = 2;}    
      if(k_factor1 < 1)   {menu_mqtt = 3;}
      if((k_factor1 >= 1) && (k_factor1 <= 999))
      {
        k_div_freq1 = float(k_factor1)/60.00;
        preferences.begin("my-app", false);
        preferences.putInt("k_factor1", k_factor1);
        preferences.putFloat("k_div_freq1", k_div_freq1);        
        preferences.end();
        flag_setup_factor_k1 = true;
      }
    }
    if(doc["FTK1"] != "")
    {
      FlowTimeZero1 = doc["FTK1"];  
      if(FlowTimeZero1 < 0.5) {menu_mqtt = 3;}
      else {flag_setup_flowtime1 = true;}
    } 
    if((flag_setup_factor_k1) && (flag_setup_flowtime1)) 
    {
      menu_modbus = 4;
      flag_setup_factor_k1 = false;
      flag_setup_flowtime1 = false;
    }
    menu_json = 0;
    break;

    case 5:
    if(doc["K2"] != "")
    {
      k_factor2 = doc["K2"];
      if(k_factor2 > 999) {menu_mqtt = 2;}    
      if(k_factor2 < 1)   {menu_mqtt = 3;}
      if((k_factor2 >= 1) && (k_factor2 <= 999))
      {
        k_div_freq2 = float(k_factor2)/60.00;
        preferences.begin("my-app", false);
        preferences.putInt("k_factor2", k_factor2);
        preferences.putFloat("k_div_freq2", k_div_freq2);
        preferences.end();
        flag_setup_factor_k2 = true;
      }   
    }
    if(doc["FTK2"] != "")
    {
      FlowTimeZero2 = doc["FTK2"];
      if(FlowTimeZero2 < 0.5) {menu_mqtt = 3;}
      else {flag_setup_flowtime2 = true;}
    }
    if((flag_setup_factor_k2) && (flag_setup_flowtime2)) 
    {
      menu_modbus = 5;
      flag_setup_factor_k2 = false;
      flag_setup_flowtime2 = false;     
    }
    menu_json = 0;
    break;

    case 6:
    if(doc["K3"] != "")
    {
      k_factor3 = doc["K3"];
      if(k_factor3 > 999) {menu_mqtt = 2;}    
      if(k_factor3 < 1)   {menu_mqtt = 3;}
      if((k_factor3 >= 1) && (k_factor3 <= 999))
      {
        k_div_freq3 = float(k_factor3)/60.00;
        preferences.begin("my-app", false);
        preferences.putInt("k_factor3", k_factor3);
        preferences.putFloat("k_div_freq3", k_div_freq3);
        preferences.end();
        flag_setup_factor_k3 = true;
      }
    }
    if(doc["FTK3"] != "")
    {
      FlowTimeZero3 = doc["FTK3"]; 
      if(FlowTimeZero3 < 0.5) {menu_mqtt = 3;}
      else {flag_setup_flowtime3 = true;}
    }
    if((flag_setup_factor_k3) && (flag_setup_flowtime3)) 
    {
      menu_modbus = 6;
      flag_setup_factor_k3 = false;
      flag_setup_flowtime3 = false;
    }
    break;

    case 7:
    if(doc["SPAN1"] != "")
    {
      Min_Span1 = doc["SPAN1"];
      if(Min_Span1 > 100) {menu_mqtt = 2;}
      if(Min_Span1 < 0.5) {menu_mqtt = 3;}
      if((Min_Span1 >= 0.5) && (Min_Span1 <= 100)) {flag_setup_min_span1 = true;}
    }
    if(doc["SPAN2"] != "")
    {
      Max_Span1 = doc["SPAN2"];
      if(Max_Span1 > 100) {menu_mqtt = 2;}
      if(Max_Span1 < 0.5) {menu_mqtt = 3;}
      if((Max_Span1 >= 0.5) && (Max_Span1 <= 100)) {flag_setup_max_span1 = true;}
    }
    if(Min_Span1 >= Max_Span1) {menu_mqtt = 15;}
    else
    {
      if((flag_setup_min_span1) && (flag_setup_max_span1)) 
      {
        menu_modbus = 7;
        flag_setup_min_span1 = false;
        flag_setup_max_span1 = false;
      }
    } 
    menu_json = 0;
    break;

    case 8:
    if(doc["SPAN3"] != "")
    {
      Min_Span2 = doc["SPAN3"];
      if(Min_Span2 > 100) {menu_mqtt = 2;}
      if(Min_Span2 < 0.5) {menu_mqtt = 3;}
      if((Min_Span2 >= 0.5) && (Min_Span2 <= 100)) {flag_setup_min_span2 = true;}
    }
    if(doc["SPAN4"] != "")
    {
      Max_Span2 = doc["SPAN4"];
      if(Max_Span2 > 100) {menu_mqtt = 2;}
      if(Max_Span2 < 0.5) {menu_mqtt = 3;}
      if((Max_Span2 >= 0.5) && (Max_Span2 <= 100)) {flag_setup_max_span2 = true;}
    }
    if(Min_Span2 >= Max_Span2) {menu_mqtt = 16;}
    else
    {
      if((flag_setup_min_span2) && (flag_setup_max_span2)) 
      {
        menu_modbus = 8;
        flag_setup_min_span2 = false;
        flag_setup_max_span2 = false;
      }
    }
    menu_json = 0;
    break;

    case 9:
    if(doc["SPAN5"] != "")
    {
      Min_Span3 = doc["SPAN5"];
      if(Min_Span3 > 100) {menu_mqtt = 2;}
      if(Min_Span3 < 0.5) {menu_mqtt = 3;}
      if((Min_Span3 >= 0.5) && (Min_Span3 <= 100)) {flag_setup_min_span3 = true;}
    }
    if(doc["SPAN6"] != "")
    {
      Max_Span3 = doc["SPAN6"];
      if(Max_Span3 > 100) {menu_mqtt = 2;}
      if(Max_Span3 < 0.5) {menu_mqtt = 3;}
      if((Max_Span3 >= 0.5) && (Max_Span3 <= 100)) {flag_setup_max_span3 = true;}
    }
    if(Min_Span3 >= Max_Span3) {menu_mqtt = 17;}
    else
    {
      if((flag_setup_min_span3) && (flag_setup_max_span3)) 
      {
        menu_modbus = 9;
        flag_setup_min_span3 = false;
        flag_setup_max_span3 = false;
      }
    }
    menu_json = 0;
    break;

    case 10:
    if(doc["setpoint1"] != "")
    {
      if(select_manual_mode1)
      {
        float dsg_flow1 = doc["setpoint1"];
        dsg_flow1 = dsg_flow1 * 100.00;
        dosing_flow1 = int(dsg_flow1);
        id_pump = "pump1";
        Serial.println();
        Serial.println("Modo de dosificacion = " +String(PumpDosingMode1));
        Serial.println("dosing flow 1 = "+String(dosing_flow1));
        check_dosing_mode_menu(PumpDosingMode1, id_pump, dosing_flow1);
      }
      else {menu_mqtt = 11;}
    }
    menu_json = 0;
    break;

    case 11:
    if(doc["setpoint2"] != "")
    {
      if(select_manual_mode2)
      {
        float dsg_flow2 = doc["setpoint2"];
        dsg_flow2 = dsg_flow2 * 100.00;
        dosing_flow2 = int(dsg_flow2);
        id_pump = "pump2";
        check_dosing_mode_menu(PumpDosingMode2, id_pump, dosing_flow2);
      }
      else {menu_mqtt = 11;}
    }
    menu_json = 0;
    break;

    case 12:
    if(doc["setpoint3"] != "")
    {
      if(select_manual_mode3)
      {
        float dsg_flow3 = doc["setpoint3"];
        dsg_flow3 = dsg_flow3 * 100.00;
        dosing_flow3 = int(dsg_flow3);
        id_pump = "pump3";
        check_dosing_mode_menu(PumpDosingMode3, id_pump, dosing_flow3);
      }
      else {menu_mqtt = 11;}
    }
    menu_json = 0;
    break;

    case 13:
    if(!select_manual_mode1)
    {
      if(doc["X"] != "")
      {
        xy_input_pulses1 = doc["X"];
        if(xy_input_pulses1 < 0.5) {menu_mqtt = 3;}
        else 
        {
          flag_proportional_x1 = true;
          preferences.begin("my-app", false);
          preferences.putInt("xy_input1", xy_input_pulses1);
          preferences.end(); 
        }
      }
      if(doc["Y"] != "")
      {
        xy_output_cycles1 = doc["Y"];
        pulse_ratio1 = float(xy_input_pulses1)/float(xy_output_cycles1);
        if(xy_output_cycles1 < 0.5) {menu_mqtt = 3;}
        if(pulse_ratio1 < 1.37) {menu_mqtt = 10;}
        if((xy_output_cycles1 >= 0.5) && (pulse_ratio1 >= 1.37))
        {
          flag_proportional_y1 = true;
          preferences.begin("my-app", false);
          preferences.putFloat("ratio1", pulse_ratio1);
          preferences.putInt("xy_cycles1", xy_output_cycles1);
          preferences.end();
        }
      }
      if(doc["Q"] != "")
      {
        flowsetpoint_xy1 = doc["Q"];
        if(flowsetpoint_xy1 > 100) {menu_mqtt = 2;}
        if(flowsetpoint_xy1 < 0.5) {menu_mqtt = 3;}
        if((flowsetpoint_xy1 >= 0.5) && (flowsetpoint_xy1 <= 100)) {flag_proportional_q1 = true;}
      }
      if(doc["M"] != "")
      {
        memory_xy1 = doc["M"];
        if((memory_xy1) > 1000) {menu_mqtt = 2;}
        if(memory_xy1 < 0.5)    {menu_mqtt = 3;}
        if((memory_xy1 >= 0.5) && (memory_xy1 <= 1000)) {flag_proportional_m1 = true;}
      }

      if((flag_proportional_x1)&&(flag_proportional_y1)&&(flag_proportional_q1)&&(flag_proportional_m1))
      {
        menu_modbus = 37;
        flag_proportional_x1 = false;
        flag_proportional_y1 = false;
        flag_proportional_q1 = false;
        flag_proportional_m1 = false;
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

    case 14:
    if(!select_manual_mode2)
    {
      if(doc["X"] != "")
      {
        xy_input_pulses2 = doc["X"];
        if(xy_input_pulses2 < 0.5) {menu_mqtt = 3;}
        else 
        {
          flag_proportional_x2 = true;
          preferences.begin("my-app", false);
          preferences.putInt("xy_input2", xy_input_pulses2);
          preferences.end();
        }
      }
      if(doc["Y"] != "")
      {
        xy_output_cycles2 = doc["Y"];
        pulse_ratio2 = float(xy_input_pulses2)/float(xy_output_cycles2);
        if(xy_output_cycles2 < 0.5) {menu_mqtt = 3;}
        if(pulse_ratio2 < 1.37) {menu_mqtt = 10;}
        if((xy_output_cycles2 >= 0.5) && (pulse_ratio2 >= 1.37))
        {
          flag_proportional_y2 = true;
          preferences.begin("my-app", false);
          preferences.putFloat("ratio2", pulse_ratio2);
          preferences.putInt("xy_cycles2", xy_output_cycles2);
          preferences.end();          
        }
      }
      if(doc["Q"] != "")
      {
        flowsetpoint_xy2 = doc["Q"];
        if(flowsetpoint_xy2 > 100) {menu_mqtt = 2;}
        if(flowsetpoint_xy2 < 0.5) {menu_mqtt = 3;}
        if((flowsetpoint_xy2 >= 0.5) && (flowsetpoint_xy2 <= 100)) {flag_proportional_q2 = true;}
      }
      if(doc["M"] != "")
      {
        memory_xy2 = doc["M"];
        if((memory_xy2) > 1000) {menu_mqtt = 2;}
        if(memory_xy2 < 0.5)    {menu_mqtt = 3;}
        if((memory_xy2 >= 0.5) && (memory_xy2 <= 1000)) {flag_proportional_m2 = true;}
      }
      if((flag_proportional_x2)&&(flag_proportional_y2)&&(flag_proportional_q2)&&(flag_proportional_m2))
      {
        menu_modbus = 38;
        flag_proportional_x2 = false;
        flag_proportional_y2 = false;
        flag_proportional_q2 = false;
        flag_proportional_m2 = false;
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

    case 15:
    if(!select_manual_mode3)
    {
      if(doc["X"] != "")
      {
        xy_input_pulses3 = doc["X"];
        if(xy_input_pulses3 < 0.5) {menu_mqtt = 3;}
        else 
        {
          flag_proportional_x3 = true;
          preferences.begin("my-app", false);
          preferences.putInt("xy_input3", xy_input_pulses3);
          preferences.end();
        }
      }
      if(doc["Y"] != "")
      {
        xy_output_cycles3 = doc["Y"];
        pulse_ratio3 = float(xy_input_pulses3)/float(xy_output_cycles3);
        if(xy_output_cycles3 < 0.5) {menu_mqtt = 3;}
        if(pulse_ratio3 < 1.37) {menu_mqtt = 10;}
        if((xy_output_cycles3 >= 0.5) && (pulse_ratio3 >= 1.37))
        {
          flag_proportional_y3 = true;
          preferences.begin("my-app", false);
          preferences.putFloat("ratio3", pulse_ratio3);
          preferences.putInt("xy_cycles3", xy_output_cycles3);
          preferences.end();
        }
      }
      if(doc["Q"] != "")
      {
        flowsetpoint_xy3 = doc["Q"];
        if(flowsetpoint_xy3 > 100) {menu_mqtt = 2;}
        if(flowsetpoint_xy3 < 0.5) {menu_mqtt = 3;}
        if((flowsetpoint_xy3 >= 0.5) && (flowsetpoint_xy3 <= 100)) {flag_proportional_q3 = true;}
      }
      if(doc["M"] != "")
      {
        memory_xy3 = doc["M"];
        if((memory_xy3) > 1000) {menu_mqtt = 2;}
        if(memory_xy3 == 0)     {menu_mqtt = 3;}
        if((memory_xy3 >= 0.5) && (memory_xy3 <= 1000)) {flag_proportional_m3 = true;}
      }
      if((flag_proportional_x3)&&(flag_proportional_y3)&&(flag_proportional_q3)&&(flag_proportional_m3))
      {
        menu_modbus = 39;
        flag_proportional_x3 = false;
        flag_proportional_y3 = false;
        flag_proportional_q3 = false;
        flag_proportional_m3 = false;
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

    case 16:
    if(!select_manual_mode1)
    {
      if(doc["SPP1"] != "")
      {
        float spp1 = doc["SPP1"];
        if(spp1 > 100) {menu_mqtt = 2;}
        if(spp1 < 0.5) {menu_mqtt = 3;}
        if((spp1 >= 0.5) && (spp1 <= 100)) 
        {
          spp1 = spp1 * 100.00;
          setpoint_mode_ppm1 = int(spp1);
          menu_modbus = 40;
          preferences.begin("my-app", false);
          preferences.putInt("ppm1", setpoint_mode_ppm1);
          preferences.end();
        }
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

    case 17:
    if(!select_manual_mode2)
    {
      if(doc["SPP2"] != "")
      {
        float spp2 = doc["SPP2"]; 
        if(spp2 > 100) {menu_mqtt = 2;}
        if(spp2 < 0.5) {menu_mqtt = 3;}
        if((spp2 >= 0.5) && (spp2 <= 100))
        {
          spp2 = spp2 * 100.00;
          setpoint_mode_ppm2 = int(spp2);
          menu_modbus = 41;
          preferences.begin("my-app", false);
          preferences.putInt("ppm2", setpoint_mode_ppm2);
          preferences.end();
        }
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

    case 18:
    if(!select_manual_mode3)
    {
      if(doc["SPP3"] != "")
      {
        float spp3 = doc["SPP3"]; 
        if(spp3 > 100) {menu_mqtt = 2;}
        if(spp3 < 0.5) {menu_mqtt = 3;}
        if((spp3 >= 0.5) && (spp3 <= 100))
        {
          spp3 = spp3 * 100.00;
          setpoint_mode_ppm3 = int(spp3);
          menu_modbus = 42;
          preferences.begin("my-app", false);
          preferences.putInt("ppm3", setpoint_mode_ppm3);
          preferences.end();
        }
      }
    } else {menu_mqtt = 12;}
    menu_json = 0;
    break;

  }
}
//*********************************************************************************************************************************
//-------------------------------------------------------CALLBACK MQTT------------------------------------------------------------
//*********************************************************************************************************************************
void callback(char* topic, byte* message, unsigned int length) 
{
  String str_topic = String(topic);
  String messageTemp = "";
  for(int i=0; i<length; i++) {messageTemp.concat((char)message[i]);}

  if(str_topic == "esp32/setup/dosing/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 1;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/dosing/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 2;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/dosing/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 3;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/flowmeter/parameters/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 4;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/flowmeter/parameters/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 5;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/flowmeter/parameters/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 6;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/units/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_units(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/units/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_units(str_topic, messageTemp);
  } 

  if(str_topic == "esp32/setup/units/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_units(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/dosing/mode/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    PumpDosingMode1 = menu_setup_dosing_mode(messageTemp);
    menu_modbus = 22;
    preferences.begin("my-app", false);
    preferences.putInt("PDM1", PumpDosingMode1);
    preferences.end();
  }  

  if(str_topic == "esp32/setup/dosing/mode/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    PumpDosingMode2 = menu_setup_dosing_mode(messageTemp);
    menu_modbus = 23;
    preferences.begin("my-app", false);
    preferences.putInt("PDM2", PumpDosingMode2);
    preferences.end();
  }
  
  if(str_topic == "esp32/setup/dosing/mode/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    PumpDosingMode3 = menu_setup_dosing_mode(messageTemp);
    menu_modbus = 24;
    preferences.begin("my-app", false);
    preferences.putInt("PDM3", PumpDosingMode3);
    preferences.end();
  }

  if(str_topic == "esp32/setup/proportional/mode/type/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_proportional_type(str_topic, messageTemp);
  }  

  if(str_topic == "esp32/setup/proportional/mode/type/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_proportional_type(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/proportional/mode/type/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_proportional_type(str_topic, messageTemp);
  }  

  if(str_topic == "esp32/setup/analog/input/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_analog_input(str_topic, messageTemp);
  }
  
  if(str_topic == "esp32/setup/analog/input/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_analog_input(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/analog/input/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_setup_analog_input(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/analog/span/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 7;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/analog/span/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 8;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/setup/analog/span/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 9;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/select/mode/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {select_manual_mode1 = true;}
    if(messageTemp == "true" ) {select_manual_mode1 = false;}
    preferences.begin("my-app", false);
    preferences.putBool("mode_manu1", select_manual_mode1);
    preferences.end();
  }

  if(str_topic == "esp32/control/select/mode/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {select_manual_mode2 = true;}
    if(messageTemp == "true" ) {select_manual_mode2 = false;}
    preferences.begin("my-app", false);
    preferences.putBool("mode_manu2", select_manual_mode2);
    preferences.end();
  }

  if(str_topic == "esp32/control/select/mode/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {select_manual_mode3 = true;}
    if(messageTemp == "true" ) {select_manual_mode3 = false;}
    preferences.begin("my-app", false);
    preferences.putBool("mode_manu3", select_manual_mode3);
    preferences.end();
  }

  if(str_topic == "esp32/control/stop/run/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {stop_run1 = false;}
    if(messageTemp == "true" ) {stop_run1 = true;}
    menu_modbus = 31;
    preferences.begin("my-app", false);
    preferences.putBool("sr1", stop_run1);
    preferences.end();  
  }

  if(str_topic == "esp32/control/stop/run/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {stop_run2 = false;}
    if(messageTemp == "true" ) {stop_run2 = true;}
    menu_modbus = 32;
    preferences.begin("my-app", false);
    preferences.putBool("sr2", stop_run2);
    preferences.end();
  }

  if(str_topic == "esp32/control/stop/run/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    if(messageTemp == "false") {stop_run3 = false;}
    if(messageTemp == "true" ) {stop_run3 = true;}
    menu_modbus = 33;
    preferences.begin("my-app", false);
    preferences.putBool("sr3", stop_run3);
    preferences.end();
  }

  if(str_topic == "esp32/control/mode/manual/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 10;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/mode/manual/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 11;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/mode/manual/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 12;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/mode/proportional/pump/1")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 13;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/mode/proportional/pump/2")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 14;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/mode/proportional/pump/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 15;
    DeserializeObject(str_topic, messageTemp);
  }

  if(str_topic == "esp32/control/proportional/setpoint/1") 
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 16;
    DeserializeObject(str_topic, messageTemp);
  }  

  if(str_topic == "esp32/control/proportional/setpoint/2") 
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 17;
    DeserializeObject(str_topic, messageTemp);
  } 

  if(str_topic == "esp32/control/proportional/setpoint/3")
  {
    Serial.println("Message received from the topic: " + str_topic + ". Message: " + messageTemp);
    menu_json = 18;
    DeserializeObject(str_topic, messageTemp);
  } 
}
//*********************************************************************************************************************************
//-------------------------------------------------RECONECT & SUBSCRIBE-------------------------------------------------------------
//*********************************************************************************************************************************
void reconnect() 
{
  while (!client.connected()) 
  {
    Serial.print("Trying to connect MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connect");  
      //subscribe a topic...
      client.subscribe("esp32/setup/dosing/pump/1");
      client.subscribe("esp32/setup/dosing/pump/2");
      client.subscribe("esp32/setup/dosing/pump/3");
      client.subscribe("esp32/setup/flowmeter/parameters/1");
      client.subscribe("esp32/setup/flowmeter/parameters/2");
      client.subscribe("esp32/setup/flowmeter/parameters/3");
      client.subscribe("esp32/setup/units/pump/1");
      client.subscribe("esp32/setup/units/pump/2");
      client.subscribe("esp32/setup/units/pump/3");
      client.subscribe("esp32/setup/dosing/mode/1");
      client.subscribe("esp32/setup/dosing/mode/2");
      client.subscribe("esp32/setup/dosing/mode/3");
      client.subscribe("esp32/setup/proportional/mode/type/1");
      client.subscribe("esp32/setup/proportional/mode/type/2");
      client.subscribe("esp32/setup/proportional/mode/type/3");
      client.subscribe("esp32/setup/analog/input/pump/1");
      client.subscribe("esp32/setup/analog/input/pump/2");
      client.subscribe("esp32/setup/analog/input/pump/3");
      client.subscribe("esp32/setup/analog/span/pump/1");
      client.subscribe("esp32/setup/analog/span/pump/2");
      client.subscribe("esp32/setup/analog/span/pump/3");
      client.subscribe("esp32/control/select/mode/pump/1");
      client.subscribe("esp32/control/select/mode/pump/2");
      client.subscribe("esp32/control/select/mode/pump/3");  
      client.subscribe("esp32/control/stop/run/pump/1");  
      client.subscribe("esp32/control/stop/run/pump/2"); 
      client.subscribe("esp32/control/stop/run/pump/3");
      client.subscribe("esp32/control/mode/manual/pump/1"); 
      client.subscribe("esp32/control/mode/manual/pump/2");
      client.subscribe("esp32/control/mode/manual/pump/3");
      client.subscribe("esp32/control/mode/proportional/pump/1");
      client.subscribe("esp32/control/mode/proportional/pump/2");
      client.subscribe("esp32/control/mode/proportional/pump/3");  
      client.subscribe("esp32/control/proportional/setpoint/1");
      client.subscribe("esp32/control/proportional/setpoint/2");
      client.subscribe("esp32/control/proportional/setpoint/3");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" Will try again in 5 seconds...");
      delay(5000);
    }
  }
}
//*********************************************************************************************************************************
//-------------------------------------------------Flowmeter interruption function-------------------------------------------------
//*********************************************************************************************************************************
void IRAM_ATTR ISR()
{ 
    portENTER_CRITICAL(&synch);
    NumPulses++;
    flag_activate_relay_outputs = true; 
    portEXIT_CRITICAL(&synch);
}
//*********************************************************************************************************************************
//---------------------------------------------FUNCTION PRINT DATA FLASH MEMORY----------------------------------------------------
//*********************************************************************************************************************************
void print_data_flash_memory()
{
  preferences.begin("my-app", false);

  k_factor1 = preferences.getInt("k_factor1", k_factor1);
  k_factor2 = preferences.getInt("k_factor2", k_factor2);
  k_factor3 = preferences.getInt("k_factor3", k_factor3);

  k_div_freq1 = preferences.getFloat("k_div_freq1", k_div_freq1);
  k_div_freq2 = preferences.getFloat("k_div_freq2", k_div_freq2);
  k_div_freq3 = preferences.getFloat("k_div_freq3", k_div_freq3);

  PumpDosingMode1 = preferences.getInt("PDM1", PumpDosingMode1);
  PumpDosingMode2 = preferences.getInt("PDM2", PumpDosingMode2);
  PumpDosingMode3 = preferences.getInt("PDM3", PumpDosingMode3);

  xy_input_pulses1 = preferences.getInt("xy_input1", xy_input_pulses1);
  xy_input_pulses2 = preferences.getInt("xy_input2", xy_input_pulses2);
  xy_input_pulses3 = preferences.getInt("xy_input3", xy_input_pulses3);

  xy_output_cycles1 = preferences.getInt("xy_cycles1", xy_output_cycles1);
  xy_output_cycles2 = preferences.getInt("xy_cycles1", xy_output_cycles2);
  xy_output_cycles3 = preferences.getInt("xy_cycles3", xy_output_cycles3);

  setpoint_mode_ppm1 = preferences.getInt("ppm1", setpoint_mode_ppm1);
  setpoint_mode_ppm2 = preferences.getInt("ppm2", setpoint_mode_ppm2);
  setpoint_mode_ppm3 = preferences.getInt("ppm3", setpoint_mode_ppm3);

  pulse_ratio1 = preferences.getFloat("ratio1", pulse_ratio1);
  pulse_ratio2 = preferences.getFloat("ratio2", pulse_ratio2);
  pulse_ratio3 = preferences.getFloat("ratio3", pulse_ratio3);

  select_manual_mode1 = preferences.getBool("mode_manu1", select_manual_mode1);
  select_manual_mode2 = preferences.getBool("mode_manu2", select_manual_mode2);
  select_manual_mode3 = preferences.getBool("mode_manu3", select_manual_mode3);

  stop_run1 = preferences.getBool("sr1", stop_run1);
  stop_run2 = preferences.getBool("sr2", stop_run2);
  stop_run3 = preferences.getBool("sr3", stop_run3);

  preferences.end();

  Serial.println("[1] k-factor = " + String(k_factor1, 5));
  Serial.println("[2] k-factor = " + String(k_factor2, 5));
  Serial.println("[3] k-factor = " + String(k_factor3, 5));
  Serial.println();

  if((k_factor1 == 0) || (k_factor2 == 0) ||(k_factor3 == 0)) {menu_mqtt = 13;}
  //if((k_factor1 != k_factor2) || (k_factor1 != k_factor3) || (k_factor2 != k_factor3)) {menu_mqtt = 14;}

  Serial.println("[1] k_div_freq = " + String(k_div_freq1, 5));
  Serial.println("[2] k_div_freq = " + String(k_div_freq2, 5));
  Serial.println("[3] k_div_freq = " + String(k_div_freq3, 5));
  Serial.println();  

  Serial.println("[1] XY mode input pulses = " + String(xy_input_pulses1));
  Serial.println("[2] XY mode input pulses = " + String(xy_input_pulses2));
  Serial.println("[3] XY mode input pulses = " + String(xy_input_pulses3));
  Serial.println();

  Serial.println("[1] XY mode output cycles = " + String(xy_output_cycles1));
  Serial.println("[2] XY mode output cycles = " + String(xy_output_cycles2));
  Serial.println("[3] XY mode output cycles = " + String(xy_output_cycles3));
  Serial.println();

  Serial.print("[1] (XY input / XY output) < 1.37  -->  ");
  Serial.println(pulse_ratio1, 5);
  Serial.print("[2] (XY input / XY output) < 1.37  -->  ");
  Serial.println(pulse_ratio2, 5);
  Serial.print("[3] (XY input / XY output) < 1.37  -->  ");
  Serial.println(pulse_ratio3, 5);
  Serial.println();

  Serial.println("[1] Setpoint mode %/ppm = " + String(setpoint_mode_ppm1));
  Serial.println("[2] Setpoint mode %/ppm = " + String(setpoint_mode_ppm2));
  Serial.println("[3] Setpoint mode %/ppm = " + String(setpoint_mode_ppm3)); 
  Serial.println();

  if(select_manual_mode1) {Serial.println("[1] Mode Manual Activate.");}
  else {Serial.println("[1] Mode Proportional Activate.");}
  if(select_manual_mode2) {Serial.println("[2] Mode Manual Activate.");}
  else {Serial.println("[2] Mode Proportional Activate.");}
  if(select_manual_mode3) {Serial.println("[3] Mode Manual Activate.");}
  else {Serial.println("[3] Mode Proportional Activate.");}
  Serial.println();

  if(stop_run1) {Serial.println("[1] Pump running.");}
  else {Serial.println("[1] pump stopped.");}
  if(stop_run2) {Serial.println("[2] Pump running.");}
  else {Serial.println("[2] pump stopped.");}
  if(stop_run3) {Serial.println("[3] Pump running.");}
  else {Serial.println("[3] pump stopped.");}
  Serial.println();
} 
//*********************************************************************************************************************************
//-------------------------------------------------CONFIGURACIÓN SETUP-------------------------------------------------------------
//*********************************************************************************************************************************
void setup_Wifi()
{
  // Inicia la conexión WiFi
   Serial.println("");
   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   { 
     delay(100);  
     Serial.print('.'); 
   }
   WiFi.setSleep(false);
   delay(500);
   Serial.println("");
   Serial.print("CPU Freq: ");
   Serial.println(getCpuFrequencyMhz());
   Serial.println("");
   Serial.print("Iniciado STA:\t");
   Serial.println(ssid);
   Serial.print("IP address:\t");
   Serial.println(WiFi.localIP());
   Serial.println("Conexion exitosa!");
   delay(1000);
   client.setServer(mqtt_server, 1883);
   client.setCallback(callback);
}


void ActivateRelayOutputs()
{
  digitalWrite(pulse_emitter_relay_1,LOW);
  delay(10);
  digitalWrite(pulse_emitter_relay_2,LOW);
  delay(10);
  digitalWrite(pulse_emitter_relay_3,LOW);
  delay(10);
  digitalWrite(pulse_emitter_relay_1,HIGH);
  delay(10);
  digitalWrite(pulse_emitter_relay_2,HIGH);
  delay(10);
  digitalWrite(pulse_emitter_relay_3,HIGH);
  delay(10);
  flag_activate_relay_outputs = false;  
}


#endif
