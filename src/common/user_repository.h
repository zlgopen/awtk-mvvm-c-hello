/**
 * File:   user_repository.h
 * Author: AWTK Develop Team
 * Brief:  user repository interface.
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
 * 2019-10-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_USER_REPOSITORY_H
#define TK_USER_REPOSITORY_H

#include "tkc/darray.h"
#include "tkc/emitter.h"
#include "common/user.h"

BEGIN_C_DECLS

struct _user_repository_t;
typedef struct _user_repository_t user_repository_t;

typedef ret_t (*user_repository_save_t)(user_repository_t* repo);
typedef ret_t (*user_repository_load_t)(user_repository_t* repo);
typedef ret_t (*user_repository_add_t)(user_repository_t* repo, const user_t* user);
typedef ret_t (*user_repository_update_t)(user_repository_t* repo, const user_t* user);
typedef ret_t (*user_repository_remove_t)(user_repository_t* repo, tk_compare_t cmp, void* ctx);
typedef ret_t (*user_repository_find_t)(user_repository_t* repo, tk_compare_t cmp, void* ctx,
                                        darray_t* users);
typedef user_t* (*user_repository_find_one_t)(user_repository_t* repo, tk_compare_t cmp, void* ctx);
typedef ret_t (*user_repository_destroy_t)(user_repository_t* repo);

/**
 * @class user_repository_t
 * 负责User的持久化和查询。
 *
 */
struct _user_repository_t {
  emitter_t* emitter;

  user_repository_save_t save;
  user_repository_load_t load;
  user_repository_add_t add;
  user_repository_update_t update;
  user_repository_remove_t remove;
  user_repository_find_t find;
  user_repository_find_one_t find_one;
  user_repository_destroy_t destroy;
};

/**
 * @method user_repository_save
 * 保存数据。
 *
 * @param {user_repository_t*} repo User持久化对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_save(user_repository_t* repo);

/**
 * @method user_repository_load
 * 加载数据。
 *
 * @param {user_repository_t*} repo User持久化对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_load(user_repository_t* repo);

/**
 * @method user_repository_add
 * 增加User对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {const user_t*} user User对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_add(user_repository_t* repo, const user_t* user);

/**
 * @method user_repository_update
 * 更新User对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {const user_t*} user User对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_update(user_repository_t* repo, const user_t* user);

/**
 * @method user_repository_remove
 * 删除满足条件User对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {tk_compare_t} cmp 比较函数。
 * @param {void*} ctx 比较函数的上下文。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_remove(user_repository_t* repo, tk_compare_t cmp, void* ctx);

/**
 * @method user_repository_find
 * 查找满足条件User对象。
 *
 *> 调用者需要调用darray_reset释放users数组。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {tk_compare_t} cmp 比较函数。
 * @param {void*} ctx 比较函数的上下文。
 * @param {darray_t*} users 返回满足条件的User对象接口。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_find(user_repository_t* repo, tk_compare_t cmp, void* ctx, darray_t* users);

/**
 * @method user_repository_find_one
 * 查找第一个满足条件User对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {tk_compare_t} cmp 比较函数。
 * @param {void*} ctx 比较函数的上下文。
 *
 * @return {user_t*} 返回User对象。
 */
user_t* user_repository_find_one(user_repository_t* repo, tk_compare_t cmp, void* ctx);

/**
 * @method user_repository_find_by_name
 * 查找第一个满足条件User对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 * @param {const char*} name User名称。
 *
 * @return {user_t*} 返回User对象。
 */
user_t* user_repository_find_by_name(user_repository_t* repo, const char* name);

/**
 * @method user_repository_on
 * 注册指定事件的处理函数。
 * @param {user_repository_t*} repo User持久化对象。
 * @param {uint32_t} type 事件类型。
 * @param {event_func_t} on_event 事件处理函数。
 * @param {void*} ctx 事件处理函数上下文。
 *
 * @return {uint32_t} 返回id，用于user_repository_off。
 */
uint32_t user_repository_on(user_repository_t* repo, uint32_t etype, event_func_t handler,
                            void* ctx);

/**
 * @method user_repository_off
 * 注销指定事件的处理函数。
 * @param {user_repository_t*} repo User持久化对象。
 * @param {uint32_t} id user_repository_on返回的ID。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_off(user_repository_t* repo, uint32_t id);

/**
 * @method user_repository_destroy
 * 销毁User持久化对象。
 *
 * @param {user_repository_t*} repo User持久化对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t user_repository_destroy(user_repository_t* repo);

#define USER_REPOSITORY(repo) ((user_repository_t*)(repo))

/*helper functions*/
int user_cmp_with_name(user_t* user, const char* name);
int user_cmp_with_name_not(user_t* user, const char* name);

END_C_DECLS

#endif /*TK_USER_REPOSITORY_H*/
