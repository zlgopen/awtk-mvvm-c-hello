
#ifndef TK_USER_INFO_H
#define TK_USER_INFO_H

#include "user.h"
#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class user_info_t
 *
 * @annotation ["model"]
 * user_info
 *
 */
typedef struct _user_info_t {
  /**
   * @property {str_t} name
   * @annotation ["readable"]
   * 用户名。
   */
  str_t name;
  /**
   * @property {str_t} nick_name
   * @annotation ["readable"]
   * 昵称。
   */
  str_t nick_name;
  /**
   * @property {str_t} password
   * @annotation ["readable"]
   * 密码。
   */
  str_t password;
  /**
   * @property {uint64_t} registered_time
   * @annotation ["readable"]
   * 注册时间。
   */
  time_t registered_time;
  /**
   * @property {uint64_t} last_login_time
   * @annotation ["readable"]
   * 最后登录时间。
   */
  time_t last_login_time;
} user_info_t;

/**
 * @method user_info_create
 * 创建user_info对象。
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req req对象。
 *
 * @return {user_info_t*} 返回user_info对象。
 */
user_info_t* user_info_create(navigator_request_t* req);

/**
 * @method user_info_destroy
 * 销毁user_info对象。
 *
 * @annotation ["destructor"]
 * @param {user_info_t*} user_info user_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_info_destroy(user_info_t* user_info);

END_C_DECLS

#endif /*TK_USER_INFO_H*/
