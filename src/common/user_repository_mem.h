/**
 * File:   user_repository_mem.h
 * Author: AWTK Develop Team
 * Brief:  user repository interface base on memory.
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

#ifndef TK_USER_REPOSITORY_MEM_H
#define TK_USER_REPOSITORY_MEM_H

#include "tkc/darray.h"
#include "user_repository.h"

BEGIN_C_DECLS

/**
 * @class user_repository_mem_t
 * 基于内存实现user_repository接口。
 *
 */
typedef struct _user_repository_mem_t {
  user_repository_t user_repository;
  darray_t users;
  darray_t matched;
} user_repository_mem_t;

/**
 * @method user_repository_mem_create
 * 创建User持久化对象（该对象使用OBJECT_UNREF释放）。
 *
 * @param {user_repository_t*} repo User持久化对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
user_repository_t* user_repository_mem_create(void);

#define USER_REPOSITORY_MEM(repo) ((user_repository_mem_t*)(repo))

END_C_DECLS

#endif /*TK_USER_REPOSITORY_MEM_H*/
