
#ifndef TK_LOGIN_H
#define TK_LOGIN_H

#include "tkc/str.h"

BEGIN_C_DECLS

/**
 * @class login_t
 *
 * @annotation ["model"]
 * user login
 *
 */
typedef struct _login_t {
  /**
   * @property {str_t} name
   * @annotation ["readable", "writable"]
   * 用户名。
   */
  str_t name;
  /**
   * @property {str_t} password
   * @annotation ["readable", "writable"]
   * 密码。
   */
  str_t password;
} login_t;

/**
 * @method login_create
 * 创建login对象。
 *
 * @annotation ["constructor"]
 * @return {login_t*} 返回login对象。
 */
login_t* login_create(void);

/**
 * @method login_destroy
 * 销毁login对象。
 *
 * @annotation ["destructor"]
 * @param {login_t*} login login对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t login_destroy(login_t* login);

/**
 * @method login_can_auth
 * 检查auth命令是否可以执行。
 *
 * @param {login_t*} login login对象。
 *
 * @return {bool_t} 返回FALSE表示不能执行，否则表示可以执行。
 */
bool_t login_can_auth(login_t* login);

/**
 * @method login_auth
 * 认证。
 *
 * @annotation ["command"]
 * @param {login_t*} login login对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t login_auth(login_t* login);

END_C_DECLS

#endif /*TK_LOGIN_H*/
