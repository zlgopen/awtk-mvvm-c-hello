﻿/**
 * File:   user_repository.h
 * Author: AWTK Develop Team
 * Brief:  user repository interface.
 *
 * Copyright (c) 2018 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

static ret_t user_repository_dispatch_changed(user_repository_t* repo);

int user_cmp_with_name(object_t* user, const char* name) {
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL && user_user->name.str != NULL && name != NULL, -1);

  return strcmp(user_user->name.str, name);
}

int user_cmp_with_name_not(object_t* user, const char* name) {
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL && user_user->name.str != NULL && name != NULL, -1);

  return user_cmp_with_name(user, name) == 0 ? -1 : 0;
}

int user_cmp_selected(object_t* user, void* unused) {
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL, -1);

  return user_user->selected ? 0 : -1;
}

ret_t user_repository_save(user_repository_t* repo) {
  return_value_if_fail(repo != NULL && repo->save != NULL, RET_BAD_PARAMS);

  return repo->save(repo);
}

ret_t user_repository_load(user_repository_t* repo) {
  ret_t ret = RET_OK;
  return_value_if_fail(repo != NULL && repo->load != NULL, RET_BAD_PARAMS);

  ret = repo->load(repo);

  if (ret == RET_OK) {
    user_repository_dispatch_changed(repo);
  }

  return ret;
}

ret_t user_repository_add(user_repository_t* repo, const object_t* user) {
  ret_t ret = RET_OK;
  return_value_if_fail(repo != NULL && repo->add != NULL && user != NULL, RET_BAD_PARAMS);

  ret = repo->add(repo, user);

  if (ret == RET_OK) {
    user_repository_dispatch_changed(repo);
  }

  return ret;
}

ret_t user_repository_update(user_repository_t* repo, const object_t* user) {
  ret_t ret = RET_OK;
  return_value_if_fail(repo != NULL && repo->update != NULL && user != NULL, RET_BAD_PARAMS);

  ret = repo->update(repo, user);

  if (ret == RET_OK) {
    user_repository_dispatch_changed(repo);
  }

  return ret;
}

ret_t user_repository_remove(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  ret_t ret = RET_OK;
  return_value_if_fail(repo != NULL && repo->remove != NULL && cmp != NULL, RET_BAD_PARAMS);

  ret = repo->remove(repo, cmp, ctx);

  if (ret == RET_OK) {
    user_repository_dispatch_changed(repo);
  }

  return ret;
}

ret_t user_repository_find(user_repository_t* repo, tk_compare_t cmp, void* ctx, darray_t* users) {
  return_value_if_fail(repo != NULL && repo->find != NULL && cmp != NULL && users != NULL,
                       RET_BAD_PARAMS);

  return repo->find(repo, cmp, ctx, users);
}

object_t* user_repository_find_one(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  return_value_if_fail(repo != NULL && repo->find_one != NULL, NULL);

  return repo->find_one(repo, cmp, ctx);
}

object_t* user_repository_find_by_name(user_repository_t* repo, const char* name) {
  return user_repository_find_one(repo, (tk_compare_t)user_cmp_with_name, (void*)name);
}

uint32_t user_repository_on(user_repository_t* repo, uint32_t etype, event_func_t handler,
                            void* ctx) {
  object_t* obj = OBJECT(repo);
  return_value_if_fail(obj != NULL && handler != NULL, RET_BAD_PARAMS);

  if (obj != NULL) {
    return emitter_on((emitter_t*)obj, etype, handler, ctx);
  }

  return RET_FAIL;
}

ret_t user_repository_off(user_repository_t* repo, uint32_t id) {
  object_t* obj = OBJECT(repo);
  return_value_if_fail(obj != NULL, RET_BAD_PARAMS);

  if (obj != NULL) {
    return emitter_off((emitter_t*)obj, id);
  }

  return RET_OK;
}

static ret_t user_repository_dispatch_changed(user_repository_t* repo) {
  object_t* obj = OBJECT(repo);
  event_t e = event_init(EVT_PROP_CHANGED, repo);
  return_value_if_fail(obj != NULL, RET_BAD_PARAMS);

  if (obj != NULL) {
    return emitter_dispatch((emitter_t*)obj, &e);
  }

  return RET_OK;
}
