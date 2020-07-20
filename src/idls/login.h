
#ifndef TK_LOGIN_H
#define TK_LOGIN_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class login_t
 *
 * user login
 *
 */
typedef struct _login_t {
  str_t name;
  str_t password;
} login_t;

/**
 * @class login_view_model_t
 *
 * view model of login
 *
 */
typedef struct _login_view_model_t {
  view_model_t view_model;

  /*model object*/
  login_t* login;
} login_view_model_t;

/**
 * @method login_view_model_create
 * 创建login view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* login_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_LOGIN_H*/
