
#ifndef TK_CHANGE_PASSWORD_H
#define TK_CHANGE_PASSWORD_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class change_password_t
 *
 * change current user password
 *
 */
typedef struct _change_password_t {
  str_t old_password;
  str_t new_password;
  str_t confirm_password;
} change_password_t;

/**
 * @class change_password_view_model_t
 *
 * view model of change_password
 *
 */
typedef struct _change_password_view_model_t {
  view_model_t view_model;

  /*model object*/
  change_password_t* change_password;
} change_password_view_model_t;

/**
 * @method change_password_view_model_create
 * 创建change_password view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* change_password_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_CHANGE_PASSWORD_H*/
