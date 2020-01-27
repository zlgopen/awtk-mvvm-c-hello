/**
 * File:   user.h
 * Author: AWTK Develop Team
 * Brief:  user
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2019-11-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_USER_H
#define TK_USER_H

#include "tkc/str.h"
#include "tkc/mem.h"
#include "tkc/utils.h"

BEGIN_C_DECLS

/**
 * @class user_t
 *
 * @annotation ["model"]
 * user info
 */
typedef struct _user_t {
  /**
   * @property {str_t} name
   * @annotation ["readable", "writable"]
   * 用户名。
   */
  str_t name;
  /**
   * @property {str_t} nick_name
   * @annotation ["readable", "writable"]
   * 昵称。
   */
  str_t nick_name;
  /**
   * @property {str_t} password
   * @annotation ["readable", "writable"]
   * 密码。
   */
  str_t password;
  /**
   * @property {uint64_t} registered_time
   * @annotation ["readable", "writable"]
   * 注册时间。
   */
  time_t registered_time;
  /**
   * @property {uint64_t} last_login_time
   * @annotation ["readable", "writable"]
   * 最后登录时间。
   */
  time_t last_login_time;
} user_t;

/**
 * @method user_create
 * 创建user对象。
 *
 * @annotation ["constructor"]
 * @return {user_t*} 返回user对象。
 */
user_t* user_create(void);

/**
 * @method user_destroy
 * 销毁user对象。
 *
 * @annotation ["destructor"]
 * @param {user_t*} user user对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_destroy(user_t* user);

user_t* user_copy(user_t* user, const user_t* other);
user_t* user_dup(const user_t* user);

ret_t user_auth(user_t* user, const char* password);
bool_t user_equal(user_t* user, user_t* other);
int user_cmp(user_t* a, user_t* b);
bool_t user_is_admin(user_t* user);

END_C_DECLS

#endif /*TK_USER_H*/
