/**
 * File:   user_repository_mem.h
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

#include "user_repository_mem.h"

static ret_t user_repository_mem_save(user_repository_t* repo) {
  return RET_OK;
}

static ret_t user_repository_mem_gen(user_repository_t* repo) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  user_t* admin = user_create();
  user_t* awtk = user_create();

  if(admin != NULL) {
    str_set(&(admin->name), "admin");
    str_set(&(admin->password), "1234");
    str_set(&(admin->nick_name), "Administrator");
    darray_push(&(r->users), admin);
  }
  
  if(awtk != NULL) {
    str_set(&(awtk->name), "awtk");
    str_set(&(awtk->password), "1234");
    str_set(&(awtk->nick_name), "awtk");
    darray_push(&(r->users), awtk);
  }

  return RET_OK;
}

static ret_t user_repository_mem_load(user_repository_t* repo) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);

  darray_clear(&(r->users));
  
  return user_repository_mem_gen(repo);
}

static ret_t user_repository_mem_add(user_repository_t* repo, const user_t* user) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  user_t* dup = user_dup(user);
  return_value_if_fail(dup != NULL, RET_OOM);

  return darray_push(&(r->users), dup);
}

static ret_t user_repository_mem_update(user_repository_t* repo, const user_t* user) {
  user_t* find = NULL;
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(user != NULL && user->name.str != NULL, RET_BAD_PARAMS);

  find = user_repository_find_by_name(repo, user->name.str);
  return_value_if_fail(find != NULL, RET_NOT_FOUND);

  return user_copy(find, user) != NULL ? RET_OK : RET_FAIL;
}

static ret_t user_repository_mem_remove(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(repo != NULL, RET_BAD_PARAMS);

  return darray_remove_all(&(r->users), cmp, ctx);
}

static ret_t user_repository_mem_find(user_repository_t* repo, tk_compare_t cmp, void* ctx, darray_t* users) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(r != NULL && users != NULL, RET_BAD_PARAMS);

  return darray_find_all(&(r->users), cmp, ctx, users);
}

static user_t* user_repository_mem_find_one(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(r != NULL, NULL);

  darray_clear(&(r->matched));
  darray_find_all(&(r->users), cmp, ctx, &(r->matched));

  if(r->matched.size > 0) {
    return (user_t*)(r->matched.elms[0]);
  } else {
    return NULL;
  }
}

static ret_t user_repository_mem_destroy(user_repository_t* repo) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);

  darray_deinit(&(r->users));
  darray_deinit(&(r->matched));

  return RET_OK;
}

user_repository_t* user_repository_mem_create(void) {
  user_repository_mem_t* repo = TKMEM_ZALLOC(user_repository_mem_t);
  return_value_if_fail(repo != NULL, NULL);

  darray_init(&(repo->users), 100, (tk_destroy_t)user_destroy, (tk_compare_t)user_cmp);
  darray_init(&(repo->matched), 10, NULL, NULL);

  repo->user_repository.save = user_repository_mem_save;
  repo->user_repository.load = user_repository_mem_load;
  repo->user_repository.add = user_repository_mem_add;
  repo->user_repository.update = user_repository_mem_update;
  repo->user_repository.remove = user_repository_mem_remove;
  repo->user_repository.find = user_repository_mem_find;
  repo->user_repository.find_one = user_repository_mem_find_one;

  return USER_REPOSITORY(repo);
}

