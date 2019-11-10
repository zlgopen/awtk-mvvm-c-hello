#include "tkc/mem.h"
#include "tkc/utils.h"
#include "tkc/date_time.h"
#include "mvvm/base/utils.h"
#include "time_settings.h"
#include "mvvm/base/navigator.h"

/***************time_settings***************/;

static inline time_settings_t* time_settings_create(void) {
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

static inline ret_t time_settings_destroy(time_settings_t* time_settings) {
  return_value_if_fail(time_settings != NULL, RET_BAD_PARAMS);

  TKMEM_FREE(time_settings);

  return RET_OK;
}

static bool_t time_settings_can_exec_apply(time_settings_t* time_settings, const char* args) {
  return TRUE;
}

static ret_t time_settings_apply(time_settings_t* time_settings, const char* args) {
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

/***************time_settings_view_model***************/

static ret_t time_settings_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  time_settings_view_model_t* vm = (time_settings_view_model_t*)(obj);
  time_settings_t* time_settings = vm->time_settings;

  if (tk_str_eq("year", name)) {
    time_settings->year = value_uint32(v);
  } else if (tk_str_eq("month", name)) {
    time_settings->month = value_uint32(v);
  } else if (tk_str_eq("day", name)) {
    time_settings->day = value_uint32(v);
  } else if (tk_str_eq("hour", name)) {
    time_settings->hour = value_uint32(v);
  } else if (tk_str_eq("minute", name)) {
    time_settings->minute = value_uint32(v);
  } else if (tk_str_eq("second", name)) {
    time_settings->second = value_uint32(v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static ret_t time_settings_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  time_settings_view_model_t* vm = (time_settings_view_model_t*)(obj);
  time_settings_t* time_settings = vm->time_settings;

  if (tk_str_eq("year", name)) {
    value_set_uint32(v, time_settings->year);
  } else if (tk_str_eq("month", name)) {
    value_set_uint32(v, time_settings->month);
  } else if (tk_str_eq("day", name)) {
    value_set_uint32(v, time_settings->day);
  } else if (tk_str_eq("hour", name)) {
    value_set_uint32(v, time_settings->hour);
  } else if (tk_str_eq("minute", name)) {
    value_set_uint32(v, time_settings->minute);
  } else if (tk_str_eq("second", name)) {
    value_set_uint32(v, time_settings->second);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static bool_t time_settings_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  time_settings_view_model_t* vm = (time_settings_view_model_t*)(obj);
  time_settings_t* time_settings = vm->time_settings;

  if (tk_str_eq("apply", name)) {
    return time_settings_can_exec_apply(time_settings, args);
  } else {
    return FALSE;
  }
}

static ret_t time_settings_view_model_exec(object_t* obj, const char* name, const char* args) {
  time_settings_view_model_t* vm = (time_settings_view_model_t*)(obj);
  time_settings_t* time_settings = vm->time_settings;

  if (tk_str_eq("apply", name)) {
    if (time_settings_apply(time_settings, args) == RET_OK) {
      navigator_toast("time changed!", 3000);
    } else {
      navigator_toast("change time failed!", 3000);
    }

    return RET_OK;
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t time_settings_view_model_on_destroy(object_t* obj) {
  time_settings_view_model_t* vm = (time_settings_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  time_settings_destroy(vm->time_settings);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_time_settings_view_model_vtable = {
    .type = "time_settings",
    .desc = "time settings",
    .size = sizeof(time_settings_view_model_t),
    .exec = time_settings_view_model_exec,
    .can_exec = time_settings_view_model_can_exec,
    .get_prop = time_settings_view_model_get_prop,
    .set_prop = time_settings_view_model_set_prop,
    .on_destroy = time_settings_view_model_on_destroy};

view_model_t* time_settings_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_time_settings_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  time_settings_view_model_t* time_settings_view_model = (time_settings_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  time_settings_view_model->time_settings = time_settings_create();
  ENSURE(time_settings_view_model->time_settings != NULL);

  return vm;
}
