
#ifndef TK_CHANGE_PASSWORD_H
#define TK_CHANGE_PASSWORD_H

#include "tkc/str.h"

BEGIN_C_DECLS

/**
 * @class change_password_t
 *
 * @annotation ["model"]
 * change current user password
 *
 */
typedef struct _change_password_t {
  /**
   * @property {str_t} old_password
   * @annotation ["readable", "writable"]
   * 旧密码。
   */
  str_t old_password;
  /**
   * @property {str_t} new_password
   * @annotation ["readable", "writable"]
   * 新密码。
   */
  str_t new_password;
  /**
   * @property {str_t} confirm_password
   * @annotation ["readable", "writable"]
   * 确认密码。
   */
  str_t confirm_password;
} change_password_t;

/**
 * @method change_password_create
 * 创建change_password对象。
 *
 * @annotation ["constructor"]
 * @return {change_password_t*} 返回change_password对象。
 */
change_password_t* change_password_create(void);

/**
 * @method change_password_destroy
 * 销毁change_password对象。
 *
 * @annotation ["destructor"]
 * @param {change_password_t*} change_password change_password对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t change_password_destroy(change_password_t* change_password);

/**
 * @method change_password_can_change
 * 检查change命令是否可以执行。
 *
 * @param {change_password_t*} change_password change_password对象。
 *
 * @return {bool_t} 返回FALSE表示不能执行，否则表示可以执行。
 */
bool_t change_password_can_change(change_password_t* change_password);

/**
 * @method change_password_change
 * 修改密码。
 *
 * @annotation ["command"]
 * @param {change_password_t*} change_password change_password对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t change_password_change(change_password_t* change_password);

END_C_DECLS

#endif /*TK_CHANGE_PASSWORD_H*/
