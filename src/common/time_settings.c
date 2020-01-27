#include "tkc/mem.h"
#include "tkc/utils.h"
#include "tkc/date_time.h"
#include "mvvm/base/utils.h"
#include "time_settings.h"
#include "mvvm/base/navigator.h"

/***************time_settings***************/;

time_settings_t* time_settings_create(void) {
  date_time_t dt;
  time_settings_t* time_settings = TKMEM_ZALLOC(time_settings_t);
  return_value_if_fail(time_settings != NULL, NULL);

  date_time_init(&dt);
  time_settings->year = dt.year;
  time_settings->month = dt.month;
  time_settings->day = dt.day;
  time_settings->hour = dt.hour;
  time_settings->minute = dt.minute;
  time_settings->second = dt.second;

  return time_settings;
}

ret_t time_settings_destroy(time_settings_t* time_settings) {
  return_value_if_fail(time_settings != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(time_settings);

  return RET_OK;
}

ret_t time_settings_apply(time_settings_t* time_settings) {
  date_time_t dt;

  date_time_init(&dt);
  dt.year = time_settings->year;
  dt.month = time_settings->month;
  dt.day = time_settings->day;
  dt.hour = time_settings->hour;
  dt.minute = time_settings->minute;
  dt.second = time_settings->second;

  date_time_set(&dt);

  return RET_OBJECT_CHANGED;
}
