
#ifndef TK_USER_INFO_H
#define TK_USER_INFO_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class user_info_t
 *
 * user info
 *
 */
typedef struct _user_info_t {
  str_t name;
  str_t nick_name;
  str_t password;
  uint32_t registered_time;
  uint32_t last_login_time;
} user_info_t;

/**
 * @class user_info_view_model_t
 *
 * view model of user_info
 *
 */
typedef struct _user_info_view_model_t {
  view_model_t view_model;

  /*model object*/
  user_info_t* user_info;
} user_info_view_model_t;

/**
 * @method user_info_view_model_create
 * 创建user_info view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* user_info_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_USER_INFO_H*/
