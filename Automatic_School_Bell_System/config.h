
/**
  Automatic-School-Bell

  Copyright (C) 2023, Tinashe Marshall Chaterera.
  Released under the MIT License.

  System Configuration File.
*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
  Your school timetable type: DAYS or CYCLES
  DAYS are set as the default
*/
#define TIMETABLE_TYPE DAYS

/**
  For how long should we show the bell ring during periods?
*/
const int BELL_PERIOD_RING_TIME = 3000; /* ms */

/**
  For how long should the bell ring when starting and ending the day?
*/
const int BELL_LONG_RING_TIME = 5000; /* ms */

/**
  Which hour do you start your school day?
*/
const int DEFAULT_STARTING_HOUR = 7; /* hours */

/**
  Which minute(s) do you start your school day?
*/
const int DEFAULT_STARTING_MINUTES = 30; /* minutes */

/**
  How long are your class periods?
*/
const int DEFAULT_PERIOD_TIME = 30; /* minutes */

/**
  Which hour do you start your break time?
*/
const int DEFAULT_BREAK_HOUR = 10; /* hours */

/**
  Which minute(s) do you start your break time?
*/
const int DEFAULT_BREAK_MINUTES = 30; /* minutes */

/**
  How long is your break time?
*/
const int DEFAULT_BREAK_TIME = 30; /* minutes */

/**
  Which hour do you start your lunch time?
*/
const int DEFAULT_LUNCH_HOUR = 13; /* hours */

/**
  Which minute(s) do you start your lunch time?
*/
const int DEFAULT_LUNCH_MINUTES = 0; /* minutes */

/**
  How long is your lunch time?
*/
const int DEFAULT_LUNCH_TIME = 60; /* minutes */

/**
  Which hour do you end your school day?
*/
const int DEFAULT_ENDING_HOUR = 16; /* hours */

/**
  Which minute(s) do you end your school day?
*/
const int DEFAULT_ENDING_MINUTES = 0; /* minutes */

#endif /* __CONFIG_H__ */