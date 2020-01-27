
#ifndef TK_USER_ADD_H
#define TK_USER_ADD_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class user_add_t
 *
 * @annotation ["model"]
 * user add
 *
 */
typedef struct _user_add_t {
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
   * @property {str_t} confirm_password
   * @annotation ["readable", "writable"]
   * 确认密码。
   */
  str_t confirm_password;
} user_add_t;

/**
 * @method user_add_create
 * 创建user_add对象。
 *
 * @annotation ["constructor"]
 * @return {user_add_t*} 返回user_add对象。
 */
user_add_t* user_add_create(void);

/**
 * @method user_add_destroy
 * 销毁user_add对象。
 *
 * @annotation ["destructor"]
 * @param {user_add_t*} user_add user_add对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_add_destroy(user_add_t* user_add);

/**
 * @method user_add_can_add
 * 检查auth命令是否可以执行。
 *
 * @param {user_add_t*} user_add user_add对象。
 *
 * @return {bool_t} 返回FALSE表示不能执行，否则表示可以执行。
 */
bool_t user_add_can_add(user_add_t* user_add);

/**
 * @method user_add_add
 * 增加用户。
 *
 * @annotation ["command"]
 * @param {user_add_t*} user_add user_add对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_add_add(user_add_t* user_add);

END_C_DECLS

#endif /*TK_USER_ADD_H*/
