/**
 * File:   app_globals.h
 * Author: AWTK Develop Team
 * Brief:  app_globals
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

#ifndef TK_APP_GLOBALS_H
#define TK_APP_GLOBALS_H

#include "common/user_repository.h"

BEGIN_C_DECLS

/**
 * @class app_globals_t
 *
 * 一些全局单例对象。
 *
 */
typedef struct _app_globals_t {
  object_t* current_user;
  user_repository_t* user_repository;
} app_globals_t;

/**
 * @method app_globals_init
 * 初始化。
 * @param {user_repository_t*} user_repository repository对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t app_globals_init(user_repository_t* user_repository);

/**
 * @method app_globals_deinit
 * ~初始化。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t app_globals_deinit(void);

/**
 * @method app_globals_get_user_repository
 * 获取user repository对象。
 *
 * @return {user_repository_t*} 返回user repository对象。
 */
user_repository_t* app_globals_get_user_repository(void);

/**
 * @method app_globals_get_current_user
 * 获取当前登录用户。
 *
 * @return {object_t*} 返回user对象。
 */
object_t* app_globals_get_current_user(void);

/**
 * @method app_globals_set_current_user
 * 设置当前登录用户。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t app_globals_set_current_user(object_t* user);

#define REQ_ARG_USER "user"

END_C_DECLS

#endif /*TK_APP_GLOBALS_H*/
