/****************************************************************************************************

RepRapFirmware - Platform: RepRapPro Mendel with Prototype Arduino Due controller

Platform contains all the code and definitons to deal with machine-dependent things such as control 
pins, bed area, number of extruders, tolerable accelerations and speeds and so on.

No definitions that are system-independent should go in here.  Put them in Configuration.h.  Note that
the lengths of arrays such as DRIVES (see below) are defined here, so any array initialiser that depends on those
lengths, for example:

#define DRIVES 4
.
.
.
#define DRIVE_RELATIVE_MODES {false, false, false, true}

also needs to go here.

-----------------------------------------------------------------------------------------------------

Version 0.1

18 November 2012

Adrian Bowyer
RepRap Professional Ltd
http://reprappro.com

Licence: GPL

****************************************************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

// Language-specific includes

#include <stdio.h>
#include <ctype.h>

// Platform-specific includes

#include <Arduino.h>
#include <Ethernet.h>
#include <SD.h>

/**************************************************************************************************/

// Some numbers...

#define STRING_LENGTH 1000
#define TIME_TO_REPRAP 1.0e6 // Convert seconds to the units used by the machine (usually microseconds)
#define TIME_FROM_REPRAP 1.0e-6 // Convert the units used by the machine (usually microseconds) to seconds

/**************************************************************************************************/

// The physical capabilities of the machine

#define DRIVES 4  // The number of drives in the machine, including X, Y, and Z plus extruder drives
#define AXES 3    // The number of movement axes in the machine, usually just X, Y and Z. <= DRIVES
#define HEATERS 2 // The number of heaters in the machine; 0 is the heated bed even if there isn't one.

// The numbers of entries in each array must correspond with the values of DRIVES,
// AXES, or HEATERS.  Set values to -1 to flag unavailability.

// DRIVES

#define STEP_PINS {54, 60, 46, 26}
#define DIRECTION_PINS {55, 61, 48, 28}
#define FORWARDS true     // What to send to go... 
#define BACKWARDS false    // ...in each direction
#define ENABLE_PINS {38, -1, 62, -1}
#define ENABLE false      // What to send to enable... 
#define DISABLE true     // ...and disable a drive
#define DISABLE_DRIVES {false, false, true, false} // Set true to disable a drive when it becomes idle
#define LOW_STOP_PINS {3, 14, 17, -1}
#define HIGH_STOP_PINS {-1, -1, -1, -1}
#define ENDSTOP_HIT 1 // when a stop == this it is hit
#define MAX_FEEDRATES {300.0, 300.0, 3.0, 45.0}    // mm/sec   
#define ACCELERATIONS {800.0, 800.0, 30.0, 250.0}    // mm/sec^2??
//#define ACCELERATIONS {80, 80, 3, 25} 
#define DRIVE_STEPS_PER_UNIT {91.4286, 91.4286, 4000.0, 948.0}
#define INSTANT_DVS {15.0, 15.0, 0.4, 15}    // (mm/sec) - Bit high? AB

// AXES

#define START_FEED_RATE 200.0  // Default.  mm/min

#define AXIS_LENGTHS {210, 200, 120} // mm
#define HOME_FEEDRATES {50.0*60.0, 50.0*60.0, 1.0*60.0}  // mm/min
#define HEAD_OFFSETS {0.0, 0.0, 0.0}

#define X_AXIS 0  // The index of the X axis
#define Y_AXIS 1  // The index of the Y axis
#define Z_AXIS 2  // The index of the Z axis


// HEATERS - The bed is assumed to be the first

#define TEMP_SENSE_PINS {10, 9}  // Analogue pin numbers
#define HEAT_ON_PINS {8, 9}
#define THERMISTOR_BETAS {3480.0, 3960.0} // Bed thermistor: RS 484-0149; EPCOS B57550G103J; Extruder thermistor: RS 198-961
#define THERMISTOR_SERIES_RS {4700, 4700} // Ohms in series with the thermistors
#define THERMISTOR_25_RS {10000.0, 100000.0} // Thermistor ohms at 25 C = 298.15 K
#define USE_PID {false, true} // PID or bang-bang for this heater?
#define PID_KIS {-1, 2.2} // PID constants...
#define PID_KDS {-1, 80}
#define PID_KPS {-1, 12}
#define FULL_PID_BAND {-1, 150.0}
#define PID_MIN {-1, 0.0}
#define PID_MAX {-1, 125.0}
#define D_MIX {-1, 0.95}
#define TEMP_INTERVAL 0.122 // secs - check and control temperatures this often
#define STANDBY_TEMPERATURES {ABS_ZERO, ABS_ZERO} // We specify one for the bed, though it's not needed
#define ACTIVE_TEMPERATURES {ABS_ZERO, ABS_ZERO}

#define AD_RANGE 1023.0//16383 // The A->D converter that measures temperatures gives an int this big as its max value

#define HOT_BED 0 // The index of the heated bed; set to -1 if there is no heated bed

/****************************************************************************************************/

// File handling

#define MAX_FILES 7
#define FILE_BUF_LEN 256
#define SD_SPI 4 //Pin
#define WEB_DIR "www/" // Place to find web files on the server
#define GCODE_DIR "gcodes/" // Ditto - g-codes
#define SYS_DIR "sys/" // Ditto - system files
#define TEMP_DIR "tmp/" // Ditto - temporary files
#define CONFIG_FILE "config.g" // The file that sets the machine's parameters
#define FILE_LIST_SEPARATOR ','
#define FILE_LIST_BRACKET '"'
#define FILE_LIST_LENGTH 1000 // Maximum length of file list

#define FLASH_LED 'F' // Type byte of a message that is to flash an LED; the next two bytes define 
                      // the frequency and M/S ratio.
#define DISPLAY_MESSAGE 'L'  // Type byte of a message that is to appear on a local display; the L is 
                             // not displayed; \f and \n should be supported.
#define HOST_MESSAGE 'H' // Type byte of a message that is to be sent to the host; the H is not sent.

/****************************************************************************************************/

// Networking

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
#define MAC { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
#define MAC_BYTES 6

#define IP0 192
#define IP1 168
#define IP2 1
#define IP3 14

#define IP_BYTES 4

#define ETH_B_PIN 10

// port 80 is default for HTTP
  
#define HTTP_PORT 80

// Connection statuses - ORed

#define CLIENT 1
#define CONNECTED 2
#define AVAILABLE 4

// Seconds to wait after serving a page
 
#define CLIENT_CLOSE_DELAY 0.001


/****************************************************************************************************/

// Miscellaneous...

#define LED_PIN 13 // Indicator LED

#define BAUD_RATE 115200 // Communication speed of the USB if needed.

/****************************************************************************************************/

enum EndStopHit
{
  noStop = 0,
  lowHit = 1,
  highHit = 2
};

enum IOStatus
{
  nothing = 0,
  byteAvailable = 1,
  atEoF = 2,
  clientLive = 4,
  clientConnected = 8
};


class InputOutput
{
public:
	void TakeInputFrom(InputOutput* altIp);
	void SendOutputTo(InputOutput* altOp);

protected:
	InputOutput* alternateInput;
	InputOutput* alternateOutput;
};

class Network: public InputOutput
{
public:
	Network();
	void Init();
	void Spin();
	int8_t Status(); // Returns OR of IOStatus
	int Read(char& b);
	void Write(char b);
	void Write(char* s);
	void Close();

private:
	byte mac[MAC_BYTES];
	byte ipAddress[IP_BYTES];
	EthernetServer* server;
	EthernetClient client;
	int8_t clientStatus;
};

class Line: public InputOutput
{
public:
	Line();
	void Init();
	void Spin();
	int8_t Status(); // Returns OR of IOStatus
	int Read(char& b);
	void Write(char b);
	void Write(char* s);

private:
};

class FileStore: public InputOutput
{
public:
	FileStore();
	int8_t Status(); // Returns OR of IOStatus
	int Read(char& b);
	void Write(char b);
	void Write(char* s);
	int Open(char* DevicePath, bool write);
	void Close();
	char* FileList(char* directory); // Returns a ,-separated list of all the files in the named directory (for example on an SD card).
	void GoToEnd(); // Position the file at the end (so you can write on the end).
	unsigned long Length(); // File size in bytes
	bool DeleteMe(); // Delete this file

private:
};




class Platform
{   
  public:
  
  Platform(RepRap* r);
  
//-------------------------------------------------------------------------------------------------------------

// These are the functions that form the interface between Platform and the rest of the firmware.

  void Init(); // Set the machine up after a restart.  If called subsequently this should set the machine up as if
               // it has just been restarted; it can do this by executing an actual restart if you like, but beware the 
               // loop of death...
  void Spin(); // This gets called in the main loop and should do any housekeeping needed
  
  void Exit(); // Shut down tidily.  Calling Init after calling this should reset to the beginning
  
  void Diagnostics();
  
  // Timing
  
  float Time(); // Returns elapsed seconds since some arbitrary time
  
  void SetInterrupt(float s); // Set a regular interrupt going every s seconds; if s is -ve turn interrupt off
  
  // Communications and data storage; opening something unsupported returns -1.
  
  Network* GetNetwork();
  Line* GetLine();

  char* FileList(char* directory); // Returns a ,-separated list of all the files in the named directory (for example on an SD card).
  //int OpenFile(char* fileName, bool write); // Open a local file (for example on an SD card).
  int OpenFile(char* directory, char* fileName, bool write); // Open a local file (for example on an SD card).
  void GoToEnd(int file); // Position the file at the end (so you can write on the end).
  bool Read(int file, char& b);     // Read a single byte from a file into b,
                                             // returned value is false for EoF, true otherwise
  void Write(int file, char* s);  // Write the string to a file.
  void Write(int file, char b);  // Write the byte b to a file.
  unsigned long Length(int file); // File size in bytes
  char* GetWebDir(); // Where the htm etc files are
  char* GetGCodeDir(); // Where the gcodes are
  char* GetSysDir();  // Where the system files are
  char* GetTempDir(); // Where temporary files are
  char* GetConfigFile(); // Where the configuration is stored (in the system dir).
  void Close(int file); // Close a file or device, writing any unwritten buffer contents first.
  bool DeleteFile(char* directory, char* fileName); // Delete a file
  
  //char ClientRead(); // Read a byte from the client
  //void SendToClient(char* message); // Send string to the host
  //void SendToClient(char b); // Send byte to the host
  //int ClientStatus(); // Check client's status
  //void DisconnectClient(); //Disconnect the client
  
  void Message(char type, char* message);        // Send a message.  Messages may simply flash an LED, or, 
                            // say, display the messages on an LCD. This may also transmit the messages to the host.
  //bool SerialAvailable();  // Byte available from (for example) USB?
  //bool SerialRead(char& b); // Read a serial byte into b; result is true unless no byte is available
  
  // Movement
  
  void SetDirection(byte drive, bool direction);
  void Step(byte drive);
  void Disable(byte drive); // There is no drive enable; drives get enabled automatically the first time they are used.
  float DriveStepsPerUnit(int8_t drive);
  float Acceleration(int8_t drive);
  float MaxFeedrate(int8_t drive);
  float InstantDv(int8_t drive);
  float HomeFeedRate(int8_t drive);
  EndStopHit Stopped(int8_t drive);
  float AxisLength(int8_t drive);
  
  float ZProbe();  // Return the height above the bed.  Returned value is negative if probing isn't implemented
  void ZProbe(float h); // Move to height h above the bed using the probe (if there is one).  h should be non-negative.
  
  // Heat and temperature
  
  float GetTemperature(int8_t heater); // Result is in degrees celsius
  void SetHeater(int8_t heater, const float& power); // power is a fraction in [0,1]
  //void SetStandbyTemperature(int8_t heater, const float& t);
  //void SetActiveTemperature(int8_t heater, const float& t);
  //float StandbyTemperature(int8_t heater);
  //float ActiveTemperature(int8_t heater);  
  float PidKp(int8_t heater);
  float PidKi(int8_t heater);
  float PidKd(int8_t heater);
  float FullPidBand(int8_t heater);
  float PidMin(int8_t heater);
  float PidMax(int8_t heater);
  float DMix(int8_t heater);
  bool UsePID(int8_t heater);
  float HeatSampleTime();

//-------------------------------------------------------------------------------------------------------
  
  private:
  
  float lastTime;
  
  bool active;
  
  // Load settings from local storage
  
  bool LoadFromStore();
  
  void InitialiseInterrupts();
  
  char* CombineName(char* result, char* directory, char* fileName);
  
  RepRap* reprap;
  
// DRIVES

  int8_t stepPins[DRIVES];
  int8_t directionPins[DRIVES];
  int8_t enablePins[DRIVES];
  bool disableDrives[DRIVES];
  int8_t lowStopPins[DRIVES];
  int8_t highStopPins[DRIVES];
  float maxFeedrates[DRIVES];  
  float accelerations[DRIVES];
  float driveStepsPerUnit[DRIVES];
  float instantDvs[DRIVES];

// AXES

  float axisLengths[AXES];
  float homeFeedrates[AXES];
  float headOffsets[AXES]; // FIXME - needs a 2D array
  
// HEATERS - Bed is assumed to be the first

  int GetRawTemperature(byte heater);

  int8_t tempSensePins[HEATERS];
  int8_t heatOnPins[HEATERS];
  float thermistorBetas[HEATERS];
  float thermistorSeriesRs[HEATERS];
  float thermistorInfRs[HEATERS];
  bool usePID[HEATERS];
  float pidKis[HEATERS];
  float pidKds[HEATERS];
  float pidKps[HEATERS];
  float fullPidBand[HEATERS];
  float pidMin[HEATERS];
  float pidMax[HEATERS];
  float dMix[HEATERS];
  float heatSampleTime;
  float standbyTemperatures[HEATERS];
  float activeTemperatures[HEATERS];

// Serial/USB

  Line* line;

// Files

  File* files;
  bool* inUse;
  char* webDir;
  char* gcodeDir;
  char* sysDir;
  char* tempDir;
  char* configFile;
  byte* buf[MAX_FILES];
  int bPointer[MAX_FILES];
  char fileList[FILE_LIST_LENGTH];
  char scratchString[STRING_LENGTH];
  
// Network connection

  Network* network;

  //void ClientMonitor();
  
  //byte mac[MAC_BYTES];
  //byte ipAddress[IP_BYTES];
  //EthernetServer* server;
  //EthernetClient client;
  //int clientStatus;
};

inline float Platform::Time()
{
  return TIME_FROM_REPRAP*(float)micros();
}

inline void Platform::Exit()
{
  active = false;
}

// Where the htm etc files are

inline char* Platform::GetWebDir()
{
  return webDir;
}

// Where the gcodes are

inline char* Platform::GetGCodeDir()
{
  return gcodeDir;
}

// Where the system files are

inline char* Platform::GetSysDir()
{
  return sysDir;
}

// Where the temporary files are

inline char* Platform::GetTempDir()
{
  return tempDir;
}


inline char* Platform::GetConfigFile()
{
  return configFile;
}

//****************************************************************************************************************

inline Network* Platform::GetNetwork()
{
	return network;
}

inline Line* Platform::GetLine()
{
	return line;
}

inline void Line::Init()
{
	alternateInput = NULL;
	alternateOutput = NULL;
}

inline void Line::Spin()
{
}

inline int8_t Line::Status()
{
//	if(alternateInput != NULL)
//		return alternateInput->Status();

	if(Serial.available() > 0)
		return byteAvailable;
	return nothing;
}

inline int Line::Read(char& b)
{
//  if(alternateInput != NULL)
//	return alternateInput->Read(b);

  int incomingByte = Serial.read();
  if(incomingByte < 0)
    return 0;
  b = (char)incomingByte;
  return true;
}

inline void Network::Init()
{
	alternateInput = NULL;
	alternateOutput = NULL;

	mac = MAC;

	// disable SD SPI while starting w5100
	// or you will have trouble
	pinMode(SD_SPI, OUTPUT);
	digitalWrite(SD_SPI,HIGH);

	ipAddress = { IP0, IP1, IP2, IP3 };
	//Ethernet.begin(mac, *(new IPAddress(IP0, IP1, IP2, IP3)));
	Ethernet.begin(mac, ipAddress);
	server->begin();

	//Serial.print("server is at ");
	//Serial.println(Ethernet.localIP());

	// this corrects a bug in the Ethernet.begin() function
	// even tho the call to Ethernet.localIP() does the same thing
	digitalWrite(ETH_B_PIN, HIGH);

	clientStatus = 0;
	client = 0;
}


inline int8_t Network::Status()
{
  return clientStatus;
}











// Serial input

// Byte available from (for example) USB?

//inline bool Platform::SerialAvailable()
//{
//  return Serial.available() > 0;
//}

// Read a serial byte into b; result is true unless no byte is available

//inline bool Platform::SerialRead(char& b)
//{
//  int incomingByte = Serial.read();
//  if(incomingByte < 0)
//    return false;
//  b = (char)incomingByte;
//  return true;
//}

//*****************************************************************************************************************

// Drive the RepRap machine - Movement

inline float Platform::DriveStepsPerUnit(int8_t drive)
{
  return driveStepsPerUnit[drive]; 
}

inline float Platform::Acceleration(int8_t drive)
{
  return accelerations[drive]; 
}

inline float Platform::InstantDv(int8_t drive)
{
  return instantDvs[drive]; 
}

inline void Platform::SetDirection(byte drive, bool direction)
{
  if(directionPins[drive] >= 0)
    digitalWrite(directionPins[drive], direction);  
}

inline void Platform::Step(byte drive)
{
  if(stepPins[drive] >= 0)
  {
    digitalWrite(stepPins[drive], 0);
    digitalWrite(stepPins[drive], 1);
  }
}

inline float Platform::HomeFeedRate(int8_t drive)
{
  return homeFeedrates[drive];
}

inline EndStopHit Platform::Stopped(int8_t drive)
{
  if(lowStopPins[drive] >= 0)
  {
    if(digitalRead(lowStopPins[drive]) == ENDSTOP_HIT)
      return lowHit;
  }
  if(highStopPins[drive] >= 0)
  {
    if(digitalRead(highStopPins[drive]) == ENDSTOP_HIT)
      return highHit;
  }
  return noStop; 
}

inline float Platform::AxisLength(int8_t drive)
{
  return axisLengths[drive];
}

inline float Platform::MaxFeedrate(int8_t drive)
{
  return maxFeedrates[drive];
}


//********************************************************************************************************

// Drive the RepRap machine - Heat and temperature

inline int Platform::GetRawTemperature(byte heater)
{
  if(tempSensePins[heater] >= 0)
    return analogRead(tempSensePins[heater]);
  return 0;
}

inline float Platform::HeatSampleTime()
{
  return heatSampleTime; 
}

inline bool Platform::UsePID(int8_t heater)
{
  return usePID[heater];
}


inline float Platform::PidKi(int8_t heater)
{
  return pidKis[heater]*heatSampleTime;
}

inline float Platform::PidKd(int8_t heater)
{
  return pidKds[heater]/heatSampleTime;
}

inline float Platform::PidKp(int8_t heater)
{
  return pidKps[heater];
}

inline float Platform::FullPidBand(int8_t heater)
{
  return fullPidBand[heater];
}

inline float Platform::PidMin(int8_t heater)
{
  return pidMin[heater];  
}

inline float Platform::PidMax(int8_t heater)
{
  return pidMax[heater]/PidKi(heater);
}

inline float Platform::DMix(int8_t heater)
{
  return dMix[heater];  
}


//*********************************************************************************************************

// Interrupts


inline void Platform::InitialiseInterrupts()
{
  pmc_set_writeprotect(false);
  pmc_enable_periph_clk((uint32_t)TC3_IRQn);
  TC_Configure(TC1, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
  TC1->TC_CHANNEL[0].TC_IER=TC_IER_CPCS;
  TC1->TC_CHANNEL[0].TC_IDR=~TC_IER_CPCS;
  SetInterrupt(STANDBY_INTERRUPT_RATE); 
}

inline void Platform::SetInterrupt(float s) // Seconds
{
  if(s <= 0.0)
  {
    //NVIC_DisableIRQ(TC3_IRQn);
    Message(HOST_MESSAGE, "Negative interrupt!\n");
    s = STANDBY_INTERRUPT_RATE;
  }
  uint32_t rc = (uint32_t)( (((long)(TIME_TO_REPRAP*s))*84l)/128l );
  TC_SetRA(TC1, 0, rc/2); //50% high, 50% low
  TC_SetRC(TC1, 0, rc);
  TC_Start(TC1, 0);
  NVIC_EnableIRQ(TC3_IRQn);
}

//***************************************************************************************

// Network connection

//inline int Platform::ClientStatus()
//{
//  return clientStatus;
//}
//
//inline void Platform::SendToClient(char b)
//{
//  if(client)
//  {
//    client.write(b);
//  } else
//    Message(HOST_MESSAGE, "Attempt to send byte to disconnected client.");
//}
//
//inline char Platform::ClientRead()
//{
//  if(client)
//    return client.read();
//
//  Message(HOST_MESSAGE, "Attempt to read from disconnected client.");
//  return '\n'; // good idea??
//}
//
//inline void Platform::ClientMonitor()
//{
//  clientStatus = 0;
//
//  if(!client)
//  {
//    client = server->available();
//    if(!client)
//      return;
//    //else
//      //Serial.println("new client");
//  }
//
//  clientStatus |= CLIENT;
//
//  if(!client.connected())
//    return;
//
//  clientStatus |= CONNECTED;
//
//  if (!client.available())
//    return;
//
//  clientStatus |= AVAILABLE;
//}
//
//inline void Platform::DisconnectClient()
//{
//  if (client)
//  {
//    client.stop();
//    //Serial.println("client disconnected");
//  } else
//      Message(HOST_MESSAGE, "Attempt to disconnect non-existent client.");
//}



#endif
