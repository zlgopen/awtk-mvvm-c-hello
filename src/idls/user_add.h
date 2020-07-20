
#ifndef TK_USER_ADD_H
#define TK_USER_ADD_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class user_add_t
 *
 * user add
 *
 */
typedef struct _user_add_t {
  str_t name;
  str_t nick_name;
  str_t password;
  str_t confirm_password;
} user_add_t;

/**
 * @class user_add_view_model_t
 *
 * view model of user_add
 *
 */
typedef struct _user_add_view_model_t {
  view_model_t view_model;

  /*model object*/
  user_add_t* user_add;
} user_add_view_model_t;

/**
 * @method user_add_view_model_create
 * 创建user_add view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* user_add_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_USER_ADD_H*/
