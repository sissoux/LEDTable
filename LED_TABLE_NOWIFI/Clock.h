#ifndef Clock_h
#define Clock_h
#include "Arduino.h"

typedef enum{
  HourChange,
  FiveMinutes,
  MinuteChange,
  NoChange
}TimeChangeType;

class Clock
{
  public:
    Clock();
    uint32_t UnixTimeStamp = 3000;   //Elapsed seconds since jan 1st 1970, not to mix with NTP TimeStamp, since 1900
    uint32_t LastUnixTimeStamp = 3000;   //to Parse time only if new value
    uint8_t Hour = 0;
    uint8_t Minute = 4;
    boolean HasBeenSync = false;

    TimeChangeType UpdateTime();
};
#endif
