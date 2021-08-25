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
#include <time.h>
#include "user_repository_mem.h"

static ret_t user_repository_mem_save(user_repository_t* repo) {
  return RET_OK;
}

static ret_t user_repository_mem_gen(user_repository_t* repo) {
  uint32_t i = 0;
#ifndef AWTK_WEB
  uint32_t nr = 100000;
#else
  uint32_t nr = 100;
#endif
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  object_t* admin = user_create();
  object_t* awtk = user_create();

  user_t* user_admin = USER(admin);
  user_t* user_awtk = USER(awtk);

  if (user_admin != NULL) {
    str_set(&(user_admin->name), "admin");
    str_set(&(user_admin->password), "1234");
    str_set(&(user_admin->nick_name), "Administrator");
    user_admin->registered_time = time(0);

    darray_push(&(r->users), admin);
  }

  if (user_awtk != NULL) {
    str_set(&(user_awtk->name), "awtk");
    str_set(&(user_awtk->password), "1234");
    str_set(&(user_awtk->nick_name), "awtk");
    user_awtk->registered_time = time(0);

    darray_push(&(r->users), awtk);
  }

  for (i = 0; i < nr; i++) {
    char name[32] = {0};
    object_t* user = user_create();

    user_t* user_user = USER(user);

    tk_snprintf(name, sizeof(name), "user%d", i);
    str_set(&(user_user->name), name);
    str_set(&(user_user->password), "1234");
    str_set(&(user_user->nick_name), name);
    user_user->registered_time = time(0);

    darray_push(&(r->users), user);
  }

  return RET_OK;
}

static ret_t user_repository_mem_load(user_repository_t* repo) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);

  darray_clear(&(r->users));

  return user_repository_mem_gen(repo);
}

static ret_t user_repository_mem_add(user_repository_t* repo, const object_t* user) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  object_t* dup = user_dup(user);
  return_value_if_fail(dup != NULL, RET_OOM);

  return darray_push(&(r->users), dup);
}

static ret_t user_repository_mem_update(user_repository_t* repo, const object_t* user) {
  object_t* find = NULL;
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL && user_user->name.str != NULL, RET_BAD_PARAMS);

  find = user_repository_find_by_name(repo, user_user->name.str);
  return_value_if_fail(find != NULL, RET_NOT_FOUND);

  return user_copy(find, user) != NULL ? RET_OK : RET_FAIL;
}

static ret_t user_repository_mem_remove(user_repository_t* repo, tk_compare_t cmp, void* ctx) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(repo != NULL, RET_BAD_PARAMS);

  return darray_remove_all(&(r->users), cmp, ctx);
}

static ret_t user_repository_mem_find(user_repository_t* repo, tk_compare_t cmp, void* ctx,
                                      darray_t* users) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(r != NULL && users != NULL, RET_BAD_PARAMS);

  return darray_find_all(&(r->users), cmp, ctx, users);
}

static object_t* user_repository_mem_find_one(user_repository_t* repo, tk_compare_t cmp,
                                              void* ctx) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(repo);
  return_value_if_fail(r != NULL, NULL);

  darray_clear(&(r->matched));
  darray_find_all(&(r->users), cmp, ctx, &(r->matched));

  if (r->matched.size > 0) {
    return (object_t*)(r->matched.elms[0]);
  } else {
    return NULL;
  }
}

static ret_t user_repository_mem_destroy(object_t* obj) {
  user_repository_mem_t* r = USER_REPOSITORY_MEM(obj);
  return_value_if_fail(r != NULL, RET_BAD_PARAMS);

  darray_deinit(&(r->users));
  darray_deinit(&(r->matched));

  return RET_OK;
}

static ret_t user_repository_mem_get_prop(object_t* obj, const char* name, value_t* v) {
  user_repository_mem_t* repo_mem = USER_REPOSITORY_MEM(obj);
  return_value_if_fail(repo_mem != NULL, RET_BAD_PARAMS);

  if (tk_str_ieq(name, "users")) {
    value_set_pointer(v, &(repo_mem->users));
    return RET_OK;
  } else if (tk_str_ieq(name, "matched")) {
    value_set_pointer(v, &(repo_mem->matched));
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t user_repository_mem_set_prop(object_t* obj, const char* name, const value_t* v) {
  user_repository_mem_t* repo_mem = USER_REPOSITORY_MEM(obj);

  return RET_NOT_FOUND;
}

static bool_t user_repository_mem_can_exec(object_t* obj, const char* name, const char* args) {
  user_repository_mem_t* repo_mem = USER_REPOSITORY_MEM(obj);
  return_value_if_fail(repo_mem != NULL, FALSE);

  if (tk_str_ieq("save", name)) {
    return TRUE;
  } else if (tk_str_ieq("load", name)) {
    return TRUE;
  }

  return FALSE;
}

static ret_t user_repository_mem_exec(object_t* obj, const char* name, const char* args) {
  user_repository_mem_t* repo_mem = USER_REPOSITORY_MEM(obj);
  return_value_if_fail(repo_mem != NULL, RET_FAIL);

  if (tk_str_ieq("save", name)) {
    return user_repository_mem_save(USER_REPOSITORY(repo_mem));
  } else if (tk_str_ieq("load", name)) {
    return user_repository_mem_load(USER_REPOSITORY(repo_mem));
  }

  return RET_NOT_FOUND;
}

static ret_t user_destroy(void* data) {
  object_t* obj = OBJECT(data);
  return_value_if_fail(obj != NULL, -1);

  OBJECT_UNREF(obj);

  return RET_OK;
}

static int user_compare(const void* a, const void* b) {
  object_t* obj_a = OBJECT(a);
  object_t* obj_b = OBJECT(b);
  return_value_if_fail(obj_a != NULL && obj_b != NULL, -1);

  return object_compare(obj_a, obj_b);
}

static const object_vtable_t s_user_repository_mem_vtable = {
    .type = "user_repository_mem",
    .desc = "user_repository_mem",
    .size = sizeof(user_repository_mem_t),
    .is_collection = FALSE,
    .on_destroy = user_repository_mem_destroy,
    .compare = NULL,
    .get_prop = user_repository_mem_get_prop,
    .set_prop = user_repository_mem_set_prop,
    .remove_prop = NULL,
    .foreach_prop = NULL,
    .can_exec = user_repository_mem_can_exec,
    .exec = user_repository_mem_exec,
    .clone = NULL};

user_repository_t* user_repository_mem_create(void) {
  object_t* obj = object_create(&s_user_repository_mem_vtable);
  user_repository_mem_t* repo = USER_REPOSITORY_MEM(obj);
  return_value_if_fail(repo != NULL, NULL);

  darray_init(&(repo->users), 100, user_destroy, user_compare);
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
