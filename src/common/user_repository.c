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

#include "user_repository.h"

int user_cmp_with_name(user_t* user, const char* name) {
  return_value_if_fail(user != NULL && user->name.str != NULL && name != NULL, -1);

  return strcmp(user->name.str, name);
}

ret_t user_repository_save(user_repository_t* repo) {
  return_value_if_fail(repo != NULL && repo->save != NULL, RET_BAD_PARAMS);

  return repo->save(repo);
}

ret_t user_repository_load(user_repository_t* repo) {
  return_value_if_fail(repo != NULL && repo->load != NULL, RET_BAD_PARAMS);

  return repo->load(repo);
}

ret_t user_repository_add(user_repository_t* repo, const user_t* user) {
  return_value_if_fail(repo != NULL && repo->add != NULL && user != NULL, RET_BAD_PARAMS);

  return repo->add(repo, user);
}

ret_t user_repository_update(user_repository_t* repo, const user_t* user) {
  return_value_if_fail(repo != NULL && repo->update != NULL && user != NULL, RET_BAD_PARAMS);

  return repo->update(repo, user);
}

ret_t user_repository_remove(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  return_value_if_fail(repo != NULL && repo->remove != NULL && cmp != NULL, RET_BAD_PARAMS);

  return repo->remove(repo, cmp, ctx);
}

ret_t user_repository_find(user_repository_t* repo, tk_compare_t cmp, void* ctx, darray_t* users) {
  return_value_if_fail(repo != NULL && repo->find != NULL && cmp != NULL && users != NULL, RET_BAD_PARAMS);

  return repo->find(repo, cmp, ctx, users);
}

user_t* user_repository_find_one(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  return_value_if_fail(repo != NULL && repo->find_one != NULL, NULL);

  return repo->find_one(repo, cmp, ctx);
}

user_t* user_repository_find_by_name(user_repository_t* repo, const char* name) {
  return user_repository_find_one(repo, (tk_compare_t)user_cmp_with_name, (void*)name);
}


ret_t user_repository_destroy(user_repository_t* repo) {
  return_value_if_fail(repo != NULL && repo->destroy != NULL, RET_BAD_PARAMS);

  return repo->destroy(repo);
}

