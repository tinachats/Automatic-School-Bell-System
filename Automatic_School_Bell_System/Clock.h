/**
  Automatic-School-Bell

  Copyright (C) 2023, Tinashe Marshall Chaterera.
  Released under the MIT License.

  The Clock class manages the clock time and the alarm state machine.
*/

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <RTClib.h>
#include "config.h"

enum AlarmState {
  ALARM_DISABLED,
  ALARM_OFF,
  ALARM_ACTIVE,
  ALARM_STOPPED,
};

class Clock {
  public:
    Clock();
    void begin();

    /* Clock management */
    DateTime now();
    void incrementMinute();
    void incrementHour();

    /* Alarm Management */
    bool alarmEnabled();
    DateTime alarmTime();
    bool alarmActive();
    void toggleAlarm();
    void stopAlarm();
    void incrementAlarmHour();
    void incrementAlarmMinute();

  protected:
    bool _isAlarmDueTime();

  #if USE_RTC /* USE_RTC */
    RTC_DS3231 rtc;
  #else /* USE_RTC */
    RTC_Millis _rtc;
  #endif 

  byte _alarm_hour;
  byte _alarm_minute;
  AlarmState _alarm_state;
  unsigned long _alarm_snooze_time;
};

#endif /* __CLOCK_H__ */