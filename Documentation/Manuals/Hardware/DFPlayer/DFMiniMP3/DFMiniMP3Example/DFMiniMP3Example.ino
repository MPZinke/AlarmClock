#include "DFMiniMp3.h"

//*****************************************************************************
class Mp3Notify; 
typedef DFMiniMp3<HardwareSerial, Mp3Notify> DfMp3; 
DfMp3 dfmp3(Serial1);

//*****************************************************************************
// implement a notification class,
// its member methods will get called
//
class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd) 
    {
        Serial.print("SD Card, ");
    }
    if (source & DfMp3_PlaySources_Usb) 
    {
        Serial.print("USB Disk, ");
    }
    if (source & DfMp3_PlaySources_Flash) 
    {
        Serial.print("Flash, ");
    }
    Serial.println(action);
  }
  static void OnError(DfMp3& mp3, uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
    Serial.println();
    Serial.print("Com Error ");
    Serial.println(errorCode);
  }
  static void OnPlayFinished(DfMp3& mp3, DfMp3_PlaySources source, uint16_t track)
  {
    Serial.print("Play finished for #");
    Serial.println(track);  
  }
  static void OnPlaySourceOnline(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3& mp3, DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};




//*****************************************************************************
void setup() 
{
  Serial.begin(115200);

  dfmp3.begin();
  
  dfmp3.setVolume(10);

  	Serial.print(String("i = ") + 1);
    dfmp3.playFolderTrack(1,1);
 
}


//*****************************************************************************
void loop() 
{
    delay(1000);  // Relax while playing music
}