
#ifndef TK_TIME_SETTINGS_H
#define TK_TIME_SETTINGS_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class time_settings_t
 *
 * @annotation ["model"]
 * time settings
 *
 */
typedef struct _time_settings_t {
  /**
   * @property {uint32_t} year
   * @annotation ["readable", "writable"]
   * 年。
   */
  uint32_t year;
  /**
   * @property {uint32_t} month
   * @annotation ["readable", "writable"]
   * 月。
   */
  uint32_t month;
  /**
   * @property {uint32_t} day
   * @annotation ["readable", "writable"]
   * 日。
   */
  uint32_t day;
  /**
   * @property {uint32_t} hour
   * @annotation ["readable", "writable"]
   * 时。
   */
  uint32_t hour;
  /**
   * @property {uint32_t} minute
   * @annotation ["readable", "writable"]
   * 分。
   */
  uint32_t minute;
  /**
   * @property {uint32_t} second
   * @annotation ["readable", "writable"]
   * second。
   */
  uint32_t second;
} time_settings_t;

/**
 * @method time_settings_create
 * 创建time_settings对象。
 *
 * @annotation ["constructor"]
 * @return {time_settings_t*} 返回time_settings对象。
 */
time_settings_t* time_settings_create(void);

/**
 * @method time_settings_destroy
 * 销毁time_settings对象。
 *
 * @annotation ["destructor"]
 * @param {time_settings_t*} time_settings time_settings对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_settings_destroy(time_settings_t* time_settings);

/**
 * @method time_settings_apply
 * 保存。
 *
 * @annotation ["command"]
 * @param {time_settings_t*} time_settings time_settings对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t time_settings_apply(time_settings_t* time_settings);

END_C_DECLS

#endif /*TK_TIME_SETTINGS_H*/
