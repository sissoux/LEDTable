#include "Clock.h"

Clock::Clock() {}


TimeChangeType Clock::UpdateTime()
{
  uint8_t PrevHour = Hour;
  uint8_t PrevMinute = Minute;
  if ((UnixTimeStamp % 3600) / 60 != Minute)
  {
    Hour = ((UnixTimeStamp+7200)  % 86400L) / 3600;
    Minute = (UnixTimeStamp  % 3600) / 60;
    //fxTrigger = true;
  }
  if (PrevHour != Hour) return HourChange;
  if (Minute % 5 == 0) return FiveMinutes;
  if (PrevMinute != Minute) return MinuteChange;
  return NoChange;
}

