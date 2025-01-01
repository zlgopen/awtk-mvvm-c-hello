/**
 * File:   user.h
 * Author: AWTK Develop Team
 * Brief:  user
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
 * 2019-11-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/utils.h"
#include "common/user.h"

object_t* user_copy(object_t* user, const object_t* other) {
  user_t* user_user = USER(user);
  user_t* user_other = USER(other);
  return_value_if_fail(user_user != NULL && user_other != NULL, NULL);

  if (user_user == user_other) {
    return user;
  }

  user_user->registered_time = user_other->registered_time;
  user_user->last_login_time = user_other->last_login_time;

  str_set(&(user_user->name), user_other->name.str);
  str_set(&(user_user->nick_name), user_other->nick_name.str);
  str_set(&(user_user->password), user_other->password.str);

  return user;
}

bool_t user_equal(object_t* user, object_t* other) {
  bool_t ret = FALSE;
  user_t* user_user = USER(user);
  user_t* user_other = USER(other);
  return_value_if_fail(user_user != NULL && user_other != NULL, NULL);

  if (user_user == user_other) {
    return TRUE;
  }

  ret = user_user->registered_time == user_other->registered_time &&
        user_user->last_login_time == user_other->last_login_time &&
        str_eq(&(user_user->name), user_other->name.str) &&
        str_eq(&(user_user->nick_name), user_other->nick_name.str) &&
        str_eq(&(user_user->password), user_other->password.str);

  return ret;
}

object_t* user_dup(const object_t* user) {
  return_value_if_fail(user != NULL, NULL);

  object_t* other = user_create();
  return_value_if_fail(other != NULL, NULL);

  return user_copy(other, user);
}

ret_t user_auth(object_t* user, const char* password) {
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL && password != NULL, RET_BAD_PARAMS);

  return str_eq(&(user_user->password), password) == TRUE ? RET_OK : RET_FAIL;
}

bool_t user_is_admin(object_t* user) {
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL, FALSE);

  return str_eq(&(user_user->name), "admin");
}

static ret_t user_destroy(object_t* obj) {
  return_value_if_fail(obj != NULL, RET_BAD_PARAMS);

  user_t* user = USER(obj);

  str_reset(&(user->name));
  str_reset(&(user->nick_name));
  str_reset(&(user->password));

  if (user->event_id != 0) {
    emitter_off(EMITTER(user), user->event_id);
    user->event_id = 0;
  }

  return RET_OK;
}

static int32_t user_compare(object_t* obj, object_t* other) {
  return_value_if_fail(obj != NULL && other != NULL, -1);
  user_t* a = USER(obj);
  user_t* b = USER(other);
  return strcmp(a->name.str, b->name.str);
}

static ret_t user_get_prop(object_t* obj, const char* name, value_t* v) {
  user_t* user = USER(obj);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_ieq(name, "name")) {
    value_set_str(v, user->name.str);
    return RET_OK;
  } else if (tk_str_ieq(name, "nick_name")) {
    value_set_str(v, user->nick_name.str);
    return RET_OK;
  } else if (tk_str_ieq(name, "password")) {
    value_set_str(v, user->password.str);
    return RET_OK;
  } else if (tk_str_ieq("registered_time", name)) {
    value_set_uint64(v, user->registered_time);
    return RET_OK;
  } else if (tk_str_ieq("last_login_time", name)) {
    value_set_uint64(v, user->last_login_time);
    return RET_OK;
  } else if (tk_str_ieq("selected", name)) {
    value_set_bool(v, user->selected);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t user_set_prop(object_t* obj, const char* name, const value_t* v) {
  user_t* user = USER(obj);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_ieq("name", name)) {
    str_set(&(user->name), value_str(v));
    return RET_OK;
  } else if (tk_str_ieq("nick_name", name)) {
    str_set(&(user->nick_name), value_str(v));
    return RET_OK;
  } else if (tk_str_ieq("password", name)) {
    str_set(&(user->password), value_str(v));
    return RET_OK;
  } else if (tk_str_ieq("registered_time", name)) {
    user->registered_time = value_uint64(v);
    return RET_OK;
  } else if (tk_str_ieq("last_login_time", name)) {
    user->last_login_time = value_uint64(v);
    return RET_OK;
  } else if (tk_str_ieq("selected", name)) {
    user->selected = value_bool(v);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static bool_t user_can_exec(object_t* obj, const char* name, const char* args) {
  return FALSE;
}

static ret_t user_exec(object_t* obj, const char* name, const char* args) {
  return RET_NOT_FOUND;
}

static const object_vtable_t s_user_vtable = {.type = "user",
                                              .desc = "user",
                                              .size = sizeof(user_t),
                                              .is_collection = FALSE,
                                              .on_destroy = user_destroy,
                                              .compare = user_compare,
                                              .get_prop = user_get_prop,
                                              .set_prop = user_set_prop,
                                              .remove_prop = NULL,
                                              .foreach_prop = NULL,
                                              .can_exec = user_can_exec,
                                              .exec = user_exec,
                                              .clone = NULL};

object_t* user_create(void) {
  object_t* obj = object_create(&s_user_vtable);
  return_value_if_fail(obj != NULL, NULL);

  user_t* user = USER(obj);
  str_init(&(user->name), 10);
  str_init(&(user->nick_name), 10);
  str_init(&(user->password), 10);
  user->event_id = 0;

  return obj;
}

user_t* user_cast(object_t* obj) {
  return_value_if_fail(obj != NULL && obj->vt == &s_user_vtable, NULL);
  return (user_t*)(obj);
}
