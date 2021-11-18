//CODIGO QUE ESCRIBE UNA CONSIGNA DE CAUDAL PARA LA BOMBA ITC DOSTEC-AC
// MANUAL DE LA BOMBA: https://www.itc.es/wp-content/uploads/ITC_DostecAC-ES.pdf
// MANUAL MODBUS: https://www.itc.es/wp-content/uploads/ITC_DostecAC_Modbus-ES.pdf


#include <ModbusMaster.h>
//#include <driver/uart.h>    // necessary to define UART_MODE_RS485_HALF_DUPLEX   (posible solución para Serial.flush)

/*------------------------------------------------VARIABLES GLOBALES---------------------------------------------*/
bool comienzo = 0;
uint8_t StatusPin_DE_RE = 14;                     // Habilita y desabilida la transmisión del MAX485 IC.
uint8_t id_slave = 1;                             // Direccion del esclavo remoto.                 
uint16_t MAR = 4684;                              // Memory Address Register (MAR).
uint16_t NMR = 2;                                 // Number of Memory Records (NMR).
uint16_t ModbusTimeout = 1000;                    // Modbus timeout [milliseconds].
uint32_t u32_ConsignaCaudal = 9000;               // Consigna de Caudal = 90 l/h.

/*A continuación definiremos las varialbles para la configuración del puerto Serial para el ESP32 Dev Module.
  Por defecto, en el archivo HardwareSerial.cpp se utiliza: HardwareSerial Serial(0);
  Los pines rxPin & txPin tienen que ser menor que 0 para asignar correctamente los pines Rx y Tx en el ESP32.*/
   
unsigned long baudios = 9600;                     // Tasa de bits/segundo.
uint32_t config = SERIAL_8N1;                     // Serial -> 8 bits de datos, 1 bits de parada, 0 bits de paridad.
int8_t rxPin= -1;                 
int8_t txPin= -1; 
bool invert=false;
unsigned long timeout_ms = 20000UL;
uint8_t rxfifo_full_thrhd = 112;

// Creación de una instancia del objeto ModbusMaster
  ModbusMaster node;

/*------------------------------------------------FUNCIONES--------------------------------------------------------*/ 

// Función que habilita los pines RE y DE para activar el modo de transmisión de datos.
void preTransmission(){ digitalWrite(StatusPin_DE_RE, 1); }

// Función que deshabilita los pines RE y DE para activar el modo de recepción de datos.
void postTransmission() { digitalWrite(StatusPin_DE_RE, 0); }

// Funcion que convierte un numero uint32_t en dos numeros uint16_t
// Se utiliza ya que para añadir la variable u32_ConsignaCaudal al buffer de transmisión implementado en la clase 
// <ModbusMaster.h> es necesario descomponerlo en dos registros/numeros de 16 bits.
// uint8_t  setTransmitBuffer(uint8_t, uint16_t);
void u32_to_u16(const uint32_t u32)
{
  uint16_t u16_ArrayTmp[2];                  // Array auxiliar para setear el buffer de transmision
  Serial.print(" Consigna de caudal = ");
  Serial.print(u32/100);
  Serial.println(" l/h");
  delay(2000);

  Serial.println("Iniciando descomposicion uint32_t --> uint16_t...");
  u16_ArrayTmp[0] = (u32 & 0xffff0000) >> 16;
  u16_ArrayTmp[1] = (u32 & 0x0000ffff);
  delay(100);

  for(int i=0; i<2; i++)
  {
    Serial.print("u16_ArrayTmp[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(u16_ArrayTmp[i]);
    delay(1000);
  }  

  // Se añanden los valores de 8 bits de la consigna de caudal al buffer de transmision y se comprueba que ha sido correcto.
  if(node.setTransmitBuffer(0, u16_ArrayTmp[0]) == node.ku8MBSuccess){ Serial.println("MSB adjuntado correctamente al Buffer de transmision.");}
  delay(1000);
  if(node.setTransmitBuffer(1, u16_ArrayTmp[1]) == node.ku8MBSuccess){ Serial.println("LSB adjuntado correctamente al Buffer de transmision.");}
  else{Serial.println("Error al añadir los datos al Buffer de transmision!!! :(");}   
}

// Funcion de detección de errores. Devuelve que tipo de erros es.
bool getResultMsg(uint8_t result)
{
  String tmpstr2;

  switch (result) {
    case node.ku8MBSuccess:
      return true;
      break;
    case node.ku8MBIllegalFunction:
      tmpstr2 = "Illegal Function";
      break;
    case node.ku8MBIllegalDataAddress:
      tmpstr2 = "Illegal Data Address";
      break;
    case node.ku8MBIllegalDataValue:
      tmpstr2 = "Illegal Data Value";
      break;
    case node.ku8MBSlaveDeviceFailure:
      tmpstr2 = "Slave Device Failure";
      break;
    case node.ku8MBInvalidSlaveID:
      tmpstr2 = "Invalid Slave ID";
      break;
    case node.ku8MBInvalidFunction:
      tmpstr2 = "Invalid Function";
      break;
    case node.ku8MBResponseTimedOut:
      tmpstr2 = "Response Timed Out";
      break;
    case node.ku8MBInvalidCRC:
      tmpstr2 = "Invalid CRC";
      break;
    default:
      tmpstr2 = "Unknown error: " + String(result);
      break;
  }
  Serial.println(tmpstr2);
  return false;
}

/*------------------------------------------------PARAMETROS DE CONFIGURACIÓN----------------------------------------------------------------*/
void setup() 
{
  // Configuración de pines.
  pinMode(StatusPin_DE_RE, OUTPUT);
  delay(50);

  // Iniciar en modo de transmision.
  digitalWrite(StatusPin_DE_RE, 1);
  delay(50);

  // Inicializa los pines Rx y Tx para que puedan ser usados como puerto serial.
  // void HardwareSerial::begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert, unsigned long timeout_ms)
  Serial.begin(baudios, config , rxPin, txPin, invert, timeout_ms);
  while(!Serial) {delay(50);} 
  
  // Se limpian los Buffer de Respuesta y transmision.
  node.clearResponseBuffer();
  node.clearTransmitBuffer();
  delay(100);

  // Asigna la ID de esclavo Modbus y el puerto serie.
  // void ModbusMaster::begin(uint8_t slave, Stream &serial)
  node.begin(id_slave, Serial);   
  delay(100);
  // Set RS485 half duplex mode on UART_0.  This shall force flush to wait up to sending all bits out
  //ESP_ERROR_CHECK(uart_set_mode(0, UART_MODE_RS485_HALF_DUPLEX));  //(posible solución para Serial.flush), me da error de compilación
  //delay(100);

  // Las devoluciones de llamada nos permiten configurar correctamente el transceptor RS485
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  

  comienzo = 1;
  
  
}

/*------------------------------------------------FUNCIÓN LOOP--------------------------------------------------------------------*/

void loop() 
{ 
  while(!comienzo) {delay(2000);}
  uint32_t  result;
  uint16_t data[6];

  u32_to_u16(u32_ConsignaCaudal);
  delay(500); 

  result = node.writeMultipleRegisters(MAR, NMR);
  delay(500);
  
  // Si la petición ha sido correcta y no ha fallado tendremos un buffer con los
	// registros, en el primero esta la parte alta del valor y en el segundo la baja.
  if(result == node.ku8MBSuccess)
  {
		Serial.println("Peticion correcta.");
	}

  else 
  {
    Serial.println("Error en la orden de writeMultipleRegisters!!! ");
    delay(1000);
    Serial.print("Tipo de Error = ");
    Serial.println(result);
    delay(1000);
    Serial.print(". Se identifica con: ");    
    getResultMsg(result);
    delay(2000);
  }
    
}



  