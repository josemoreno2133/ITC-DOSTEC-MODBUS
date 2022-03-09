#ifndef SDI12_SENSOR_H
#define SDI12_SENSOR_H

#include <SDI12.h>
uint8_t numSensors = 0;
float electroconductividad = 0.f;
float temperatura = 0.f;
bool cont = false;
uint8_t const DATA_PIN = 2;       //The pin of the SDI-12 data bus 

SDI12 mySDI12(DATA_PIN);          //Define the SDI-12 bus 

bool isActive[64] = {0,};         // keeps track of active addresses

/**
 * @brief converts allowable address characters ('0'-'9', 'a'-'z', 'A'-'Z') to a 
 * decimal number between 0 and 61 (inclusive) to cover the 62 possible addresses.
 */
byte charToDec(char i) {
  if ((i >= '0') && (i <= '9')) return i - '0';
  if ((i >= 'a') && (i <= 'z')) return i - 'a' + 10;
  if ((i >= 'A') && (i <= 'Z'))
    return i - 'A' + 36;
  else
    return i;
}

/**
 * @brief maps a decimal number between 0 and 61 (inclusive) to allowable
 * address characters '0'-'9', 'a'-'z', 'A'-'Z',
 */
char decToChar(byte i) {
  if (i < 10) return i + '0';
  if ((i >= 10) && (i < 36)) return i + 'a' - 10;
  if ((i >= 36) && (i <= 62))
    return i + 'A' - 36;
  else
    return i;
}

/**
 * @brief gets identification information from a sensor, and prints it to the serial
 * port a character between '0'-'9', 'a'-'z', or 'A'-'Z'.
 */
void printInfo(char i) {
  String command = "";
  command += (char)i;
  command += "I!";
  mySDI12.sendCommand(command);
  delay(100);

  String sdiResponse = mySDI12.readStringUntil('\n');
  sdiResponse.trim();
  // allccccccccmmmmmmvvvxxx...xx<CR><LF>
  Serial.print(sdiResponse.substring(0, 1));  // address
  Serial.print(", ");
  Serial.print(sdiResponse.substring(1, 3).toFloat() / 10);  // SDI-12 version number
  Serial.print(", ");
  Serial.print(sdiResponse.substring(3, 11));  // vendor id
  Serial.print(", ");
  Serial.print(sdiResponse.substring(11, 17));  // sensor model
  Serial.print(", ");
  Serial.print(sdiResponse.substring(17, 20));  // sensor version
  Serial.print(", ");
  Serial.print(sdiResponse.substring(20));  // sensor id
  Serial.print(", ");
}

bool getResults(char i, int resultsExpected) {
  uint8_t resultsReceived = 0;
  uint8_t cmd_number      = 0;
  while (resultsReceived < resultsExpected && cmd_number <= 9) {
    String command = "";
    // in this example we will only take the 'DO' measurement
    command = "";
    command += i;
    command += "D";
    command += cmd_number;
    command += "!";  // SDI-12 command to get data [address][D][dataOption][!]
    mySDI12.sendCommand(command);

    uint32_t start = millis();
    while (mySDI12.available() < 3 && (millis() - start) < 1500) {}
    mySDI12.read();           // ignore the repeated SDI12 address
    char c = mySDI12.peek();  // check if there's a '+' and toss if so
    if (c == '+') { mySDI12.read(); }

    while (mySDI12.available()) {
      char c = mySDI12.peek();
      if (c == '-' || (c >= '0' && c <= '9') || c == '.') {
        float result = mySDI12.parseFloat(SKIP_NONE);
        if(!cont) 
        {
          electroconductividad = result;
          cont = true;
        }
        else
        {
          temperatura = result;
          cont = false;
        }
        Serial.println("EL RESULTADO ES: " + String(result));
        if (result != -9999) { resultsReceived++; }
      } else if (c == '+') {
        mySDI12.read();
        Serial.print(", ");
      } else {
        mySDI12.read();
      }
      delay(10);  // 1 character ~ 7.5ms
    }
    if (resultsReceived < resultsExpected) { Serial.print(", "); }
    cmd_number++;
  }
  mySDI12.clearBuffer();

  return resultsReceived == resultsExpected;
}

bool takeMeasurement(char i, String meas_type = "") {
  mySDI12.clearBuffer();
  String command = "";
  command += i;
  command += "M";
  command += meas_type;
  command += "!";  // SDI-12 measurement command format  [address]['M'][!]
  mySDI12.sendCommand(command);
  delay(100);

  // wait for acknowlegement with format [address][ttt (3 char, seconds)][number of
  // measurments available, 0-9]
  String sdiResponse = mySDI12.readStringUntil('\n');
  sdiResponse.trim();

  String addr = sdiResponse.substring(0, 1);
  Serial.println("id.Sensor: " + addr);

  // find out how long we have to wait (in seconds).
  uint8_t wait = sdiResponse.substring(1, 4).toInt();

  // Set up the number of results to expect
  int numResults = sdiResponse.substring(4).toInt();

  unsigned long timerStart = millis();
  while ((millis() - timerStart) < (1000 * (wait + 1))) {
    if (mySDI12.available())  // sensor can interrupt us to let us know it is done early
    {
      //Serial.print(millis() - timerStart);
      //Serial.print("-->");
      mySDI12.clearBuffer();
      break;
    }
  }
  // Wait for anything else and clear it out
  delay(30);
  mySDI12.clearBuffer();

  if (numResults > 0) { return getResults(i, numResults); }

  return true;
}

// this checks for activity at a particular address
// expects a char, '0'-'9', 'a'-'z', or 'A'-'Z'
boolean checkActive(char i) {
  String myCommand = "";
  myCommand        = "";
  myCommand += (char)i;  // sends basic 'acknowledge' command [address][!]
  myCommand += "!";

  for (int j = 0; j < 3; j++) {  // goes through three rapid contact attempts
    mySDI12.sendCommand(myCommand);
    delay(100);
    if (mySDI12.available()) {  // If we here anything, assume we have an active sensor
      mySDI12.clearBuffer();
      return true;
    }
  }
  mySDI12.clearBuffer();
  return false;
}


void setup_sdi12() {

  Serial.println("Opening SDI-12 bus...");
  mySDI12.begin();
  delay(500); 

  Serial.print("Timeout value: ");
  Serial.println(mySDI12.TIMEOUT);

  // Power the sensors;
  // if (POWER_PIN > 0) {
  //   Serial.println("Powering up sensors...");
  //   pinMode(POWER_PIN, OUTPUT);
  //   digitalWrite(POWER_PIN, HIGH);
  //   delay(200);
  // }

  // Quickly Scan the Address Space
  Serial.println("Scanning all addresses, please wait...");
  Serial.println("Sensor Address, Protocol Version, Sensor Vendor, Sensor Model, Sensor Version, Sensor ID");

  for (byte i = 0; i < 62; i++) {
    char addr = decToChar(i);
    if (checkActive(addr)) {
      numSensors++;
      isActive[i] = 1;
      printInfo(addr);
      Serial.println();
    }
  }
  Serial.print("Total number of sensors found:  ");
  Serial.println(numSensors);

  if (numSensors == 0) {
    Serial.println("No sensors found, please check connections and restart the Arduino.");
    //while (true) { delay(10); }  // do nothing forever
  }

  Serial.println();
  Serial.println(
    "Time Elapsed (s), Sensor Address, Est Measurement Time (s), Number Measurements, "
    "Real Measurement Time (ms), Measurement 1, Measurement 2, ... etc.");
  Serial.println(
    "-------------------------------------------------------------------------------");
}

void loop_sdi12_measurement() {
  String commands[] = {"", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
  for (uint8_t a = 0; a < 1; a++) {
    // measure one at a time
    for (byte i = 0; i < 62; i++) {
      char addr = decToChar(i);
      if (isActive[i]) {
        // Serial.print(millis() / 1000);
        Serial.println("-----------------------------------------");
        Serial.println("Medicion de EC...");
        takeMeasurement(addr, commands[a]);
        // electroconductividad = ecmastemp.substring(0, 7);
        // temperatura = ecmastemp.substring(7, 12);

        Serial.println("   Electroconductividad = " + String(electroconductividad));
        Serial.println("   Temperatura = " + String(temperatura));
        Serial.println("-----------------------------------------");
        
      }
    }
  }
}

#endif