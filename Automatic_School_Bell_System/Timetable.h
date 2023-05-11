#ifndef Timetable_h
#define Timetable_h
#include "Arduino.h"

class Timetable{
  protected:
    bool timetableType; // if user uses cycles or days
    bool haveExceptions; // have days where period times are different
    int startingHour; 
    int startingMinutes;
    int periodTime;
    int breakTimeHour;
    int breakTimeMinutes;
    int breakTimeDuration;
    int lunchTimeHour;
    int lunchTimeMinutes;
    int lunchTimeDuration;
    int endingHour;
    int endingMinutes;  
};

#endif