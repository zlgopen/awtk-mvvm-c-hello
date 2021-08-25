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
#include "tkc/object.h"

BEGIN_C_DECLS

/**
 * @class user_t
 *
 * @annotation ["model"]
 * user info
 */
typedef struct _user_t {
  object_t obj;
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
  /**
   * @property {bool_t} selected
   * @annotation ["readable", "writable"]
   * 是否被选中。
   */
  bool_t selected;

  /*private*/
  uint32_t event_id;
} user_t;

/**
 * @method user_create
 * 创建user的obj对象。
 *
 * @annotation ["constructor"]
 * @return {object_t*} 返回user的obj对象。
 */
object_t* user_create(void);

/**
 * @method user_cast
 * 转换为user对象。
 *
 * @annotation ["cast"]
 * @param {object_t*} obj object。
 *
 * @return {user_t*} 返回user对象。
 */
user_t* user_cast(object_t* obj);

#define USER(obj) user_cast(obj)

/**
 * @method user_copy
 * export for test only
 */
object_t* user_copy(object_t* user, const object_t* other);

/**
 * @method user_equal
 * export for test only
 */
bool_t user_equal(object_t* user, object_t* other);

object_t* user_dup(const object_t* user);
ret_t user_auth(object_t* user, const char* password);
bool_t user_is_admin(object_t* user);

END_C_DECLS

#endif /*TK_USER_H*/
