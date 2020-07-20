
#ifndef TK_TIME_SETTINGS_H
#define TK_TIME_SETTINGS_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class time_settings_t
 *
 * time settings
 *
 */
typedef struct _time_settings_t {
  uint32_t year;
  uint32_t month;
  uint32_t day;
  uint32_t hour;
  uint32_t minute;
  uint32_t second;
} time_settings_t;

/**
 * @class time_settings_view_model_t
 *
 * view model of time_settings
 *
 */
typedef struct _time_settings_view_model_t {
  view_model_t view_model;

  /*model object*/
  time_settings_t* time_settings;
} time_settings_view_model_t;

/**
 * @method time_settings_view_model_create
 * 创建time_settings view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* time_settings_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_TIME_SETTINGS_H*/
