
#ifndef TK_USERS_H
#define TK_USERS_H

#include "tkc/str.h"
#include "tkc/darray.h"
#include "tkc/emitter.h"
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
  emitter_t emitter;

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
 * 创建users对象。
 *
 * @annotation ["constructor"]
 *
 * @return {users_t*} 返回users对象。
 */
users_t* users_create(void);

/**
 * @method users_create_with_repository
 * 创建users对象。
 *
 * @annotation ["constructor"]
 * @param {user_repository_t*} r repository对象。
 *
 * @return {users_t*} 返回users对象。
 */
users_t* users_create_with_repository(user_repository_t* r);

/**
 * @method users_destroy
 * 销毁users对象。
 *
 * @annotation ["destructor"]
 * @param {users_t*} users users对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_destroy(users_t* users);

/**
 * @method users_clear
 * 清除全部数据。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_clear(users_t* users);

/**
 * @method users_remove_selected
 * 删除选中的数据。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_remove_selected(users_t* users);

/**
 * @method users_can_remove_selected
 * 检查remove_selected命令是否可以执行。
 *
 * @param {users_t*} users users对象。
 *
 * @return {bool_t} 返回FALSE表示不能执行，否则表示可以执行。
 */
bool_t users_can_remove_selected(users_t* users);

/**
 * @method users_detail
 * 显示指定序数用户的详细信息。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 * @param {uint32_t} index 序数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_detail(users_t* users, uint32_t index);

/**
 * @method users_remove
 * 删除指定序数的用户。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 * @param {uint32_t} index 序数。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_remove(users_t* users, uint32_t index);

/**
 * @method users_can_remove
 * 检查remove命令是否可以执行。
 *
 * @param {users_t*} users users对象。
 * @param {uint32_t} index 序数。
 *
 * @return {bool_t} 返回FALSE表示不能执行，否则表示可以执行。
 */
bool_t users_can_remove(users_t* users, uint32_t index);

/**
 * @method users_get_items
 * 获取用户数。
 *
 * @param {users_t*} users users对象。
 *
 * @return {uint32_t} 返回用户数。
 */
uint32_t users_get_items(users_t* users);

/**
 * @method users_get_selected_items
 * 获取选中的用户数。
 *
 * @param {users_t*} users users对象。
 *
 * @return {uint32_t} 返回用户数。
 */
uint32_t users_get_selected_items(users_t* users);

/**
 * @method users_set_filter
 * 设置过滤规则。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 * @param {const char*} filter 过滤规则。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_set_filter(users_t* users, const char* filter);

/**
 * @method users_set_ascending
 * 设置为升序。
 *
 * @annotation ["command"]
 * @param {users_t*} users users对象。
 * @param {bool_t} ascending 是否为升序。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t users_set_ascending(users_t* users, bool_t ascending);

/**
 * @method users_get
 * 获取指定序数的用户。
 *
 * @param {users_t*} users users对象。
 * @param {uint32_t} index 序数。
 *
 * @return {user_t*} 返回user对象。
 */
user_t* users_get(users_t* users, uint32_t index);

END_C_DECLS

#endif /*TK_USERS_H*/
