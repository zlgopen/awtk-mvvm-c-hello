
#ifndef TK_USERS_H
#define TK_USERS_H

#include "tkc/str.h"
#include "tkc/darray.h"
#include "tkc/object.h"
#include "common/user.h"
#include "common/user_repository.h"

BEGIN_C_DECLS

#include "user.h"

/**
 * @class users_t
 * @parent emitter_t
 * 用户管理。
 * @annotation ["collection:user_t", "model"]
 *
 */
typedef struct _users_t {
  object_t obj;

  /**
   * @property {str_t} filter
   * @annotation ["readable", "writable"]
   * 过滤规则。
   */
  str_t filter;

  /**
   * @property {bool_t} ascending
   * @annotation ["readable", "writable"]
   * 按升序排列。
   */
  bool_t ascending;

  /**
   * @property {uint32_t} items
   * @annotation ["fake", "readable"]
   * 用户数。
   */

  /**
   * @property {uint32_t} selected_items
   * @annotation ["fake", "readable"]
   * 当前选中的用户数。
   */

  darray_t users;
  uint32_t event_id;
  user_repository_t* r;
} users_t;

/**
 * @method users_create
 * 创建users的obj对象。
 *
 * @annotation ["constructor"]
 *
 * @return {object_t*} 返回users的obj对象。
 */
object_t* users_create(void);

/**
 * @method users_create_with_repository
 * 创建users的obj对象。
 *
 * @annotation ["constructor"]
 * @param {user_repository_t*} r repository对象。
 *
 * @return {object_t*} 返回users的obj对象。
 */
object_t* users_create_with_repository(user_repository_t* r);

/**
 * @method users_cast
 * 转换为users对象。
 *
 * @annotation ["cast"]
 * @param {object_t*} obj object。
 *
 * @return {users_t*} 返回users对象。
 */
users_t* users_cast(object_t* obj);

/* helper function */
ret_t users_reload(object_t* users);

#define USERS(obj) users_cast(obj)

END_C_DECLS

#endif /*TK_USERS_H*/
