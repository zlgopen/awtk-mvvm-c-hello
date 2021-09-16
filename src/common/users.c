#include "tkc/mem.h"
#include "tkc/utils.h"
#include "tkc/object_default.h"
#include "base/idle.h"
#include "mvvm/base/utils.h"
#include "mvvm/base/navigator.h"
#include "common/app_globals.h"

#include "users.h"

static int reload_cmp(const void* a, const void* b) {
  const object_t* user = (const object_t*)a;
  const char* filter = (const char*)b;

  if (filter == NULL) {
    return 0;
  }

  if (strstr(USER(user)->name.str, filter) != NULL) {
    return 0;
  } else {
    return -1;
  }
}

static int name_cmp_ascending(const void* a, const void* b) {
  const object_t* user1 = (const object_t*)a;
  const object_t* user2 = (const object_t*)b;

  return strcmp(USER(user1)->name.str, USER(user2)->name.str);
}

static int name_cmp_descending(const void* a, const void* b) {
  const object_t* user1 = (const object_t*)a;
  const object_t* user2 = (const object_t*)b;

  return strcmp(USER(user2)->name.str, USER(user1)->name.str);
}

static ret_t users_user_init(void* ctx, const void* data) {
  users_t* users = USERS(ctx);
  user_t* user = USER((object_t*)data);

  user->selected = FALSE;

  if (user->event_id == 0) {
    user->event_id = emitter_on(EMITTER(user), EVT_PROP_CHANGED, emitter_forward, users);
  }

  return RET_OK;
}

static uint32_t users_get_items(object_t* users) {
  return_value_if_fail(users != NULL, 0);

  return USERS(users)->users.size;
}

static object_t* users_get(object_t* users, uint32_t index) {
  users_t* users_users = USERS(users);
  return_value_if_fail(users_users != NULL, NULL);

  if (index < users_get_items(users)) {
    return (object_t*)(users_users->users.elms[index]);
  } else {
    return NULL;
  }
}

ret_t users_reload(object_t* users) {
  darray_t* arr = NULL;
  users_t* users_users = USERS(users);
  return_value_if_fail(users_users != NULL, RET_BAD_PARAMS);

  arr = &(users_users->users);
  darray_clear(arr);
  user_repository_find(users_users->r, reload_cmp, users_users->filter.str, arr);

  if (users_users->ascending) {
    darray_sort(arr, name_cmp_ascending);
  } else {
    darray_sort(arr, name_cmp_descending);
  }
  darray_foreach(arr, users_user_init, users_users);
  emitter_dispatch_simple_event(EMITTER(users_users), EVT_ITEMS_CHANGED);

  return RET_OK;
}

static ret_t users_detail(object_t* users, uint32_t index) {
  object_t* user = users_get(users, index);
  navigator_request_t* req = navigator_request_create("user_detail", NULL);
  return_value_if_fail(req != NULL, RET_OOM);

  object_set_prop_pointer(OBJECT(req), REQ_ARG_USER, user);
  navigator_to_ex(req);
  object_unref(OBJECT(req));

  return RET_OK;
}

static bool_t users_can_remove(object_t* users, uint32_t index) {
  return_value_if_fail(users != NULL, FALSE);

  object_t* user = users_get(users, index);
  if (user == NULL) {
    return FALSE;
  }

  return !tk_str_eq(USER(user)->name.str, "admin");
}

static ret_t users_remove(object_t* users, uint32_t index) {
  object_t* user = users_get(users, index);
  return_value_if_fail(users != NULL && user != NULL, RET_BAD_PARAMS);

  user_repository_remove(USERS(users)->r, (tk_compare_t)user_cmp_with_name, USER(user)->name.str);

  return RET_OK;
}

static uint32_t users_get_selected_items(object_t* users) {
  uint32_t i = 0;
  uint32_t nr = 0;
  users_t* users_users = USERS(users);
  return_value_if_fail(users_users != NULL, 0);

  for (i = 0; i < users_users->users.size; i++) {
    object_t* iter = (object_t*)(users_users->users.elms[i]);
    if (USER(iter)->selected) {
      nr++;
    }
  }

  return nr;
}

static ret_t users_clear(object_t* users) {
  object_t* user = app_globals_get_current_user();
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  if (user != NULL) {
    user_repository_remove(USERS(users)->r, (tk_compare_t)user_cmp_with_name_not,
                           USER(user)->name.str);
  } else {
    user_repository_remove(USERS(users)->r, (tk_compare_t)compare_always_equal, NULL);
  }

  return RET_OK;
}

static bool_t users_can_remove_selected(object_t* users) {
  return users_get_selected_items(users) > 0;
}

static ret_t users_remove_selected(object_t* users) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  user_repository_remove(USERS(users)->r, (tk_compare_t)user_cmp_selected, NULL);

  return RET_OK;
}

static ret_t users_on_repository_changed(void* ctx, event_t* e) {
  users_reload((object_t*)(ctx));

  return RET_OK;
}

static ret_t users_set_filter(object_t* users, const char* filter) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  str_set(&(USERS(users)->filter), filter);
  users_reload(users);

  return RET_OK;
}

static ret_t users_set_ascending(object_t* users, bool_t ascending) {
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  USERS(users)->ascending = ascending;
  users_reload(users);

  return RET_OK;
}

static ret_t users_destroy(object_t* obj) {
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  darray_deinit(&(users->users));
  str_reset(&(users->filter));
  user_repository_off(users->r, users->event_id);

  return RET_OK;
}

static ret_t users_get_prop(object_t* obj, const char* name, value_t* v) {
  int32_t index = -1;
  object_t* sub = NULL;
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  sub = object_get_child_object(obj, name, &name);
  if (sub != NULL) {
    return object_get_prop(sub, name, v);
  }

  if (tk_str_ieq("filter", name)) {
    value_set_str(v, users->filter.str);
    return RET_OK;
  } else if (tk_str_ieq("ascending", name)) {
    value_set_bool(v, users->ascending);
    return RET_OK;
  } else if (tk_str_ieq("items", name)) {
    value_set_object(v, obj);
    return RET_OK;
  } else if (tk_str_ieq("size", name) || tk_str_ieq("#size", name)) {
    value_set_uint32(v, users->users.size);
    return RET_OK;
  } else if (tk_str_ieq("selected_items", name)) {
    value_set_uint32(v, users_get_selected_items(obj));
    return RET_OK;
  } else if (tk_str_start_with(name, "[")) {
    const char* prop = strstr(name, "]");
    if (prop != NULL && name[0] == '[') {
      index = tk_atoi(name + 1);
    }
    if (index >= 0) {
      object_t* user = users_get(obj, index);
      if (user != NULL) {
        value_set_object(v, user);
        return RET_OK;
      }
    }
  }

  return RET_NOT_FOUND;
}

static ret_t users_set_prop(object_t* obj, const char* name, const value_t* v) {
  int32_t index = -1;
  object_t* sub = NULL;
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  sub = object_get_child_object(obj, name, &name);
  if (sub != NULL) {
    return object_set_prop(sub, name, v);
  }

  if (tk_str_ieq("filter", name)) {
    return users_set_filter(obj, value_str(v));
  } else if (tk_str_ieq("ascending", name)) {
    return users_set_ascending(obj, value_bool(v));
  } else if (tk_str_ieq("items", name)) {
    return RET_OK;
  } else if (tk_str_ieq("selected_items", name)) {
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static bool_t users_can_exec(object_t* obj, const char* name, const char* args) {
  int32_t index = -1;
  object_t* sub = NULL;
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  sub = object_get_child_object(obj, name, &name);
  if (sub != NULL) {
    return object_can_exec(sub, name, args);
  }

  if (args != NULL) {
    object_t* a = object_default_create();
    tk_command_arguments_to_object(args, a);
    index = object_get_prop_int32(a, "index", -1);
    OBJECT_UNREF(a);
  }

  if (tk_str_ieq("clear", name)) {
    return TRUE;
  } else if (tk_str_ieq("remove_selected", name)) {
    return users_can_remove_selected(obj);
  } else if (tk_str_ieq("detail", name)) {
    return TRUE;
  } else if (tk_str_ieq("remove", name) && index != -1) {
    return users_can_remove(obj, index);
  } else if (tk_str_ieq("set_filter", name)) {
    return TRUE;
  }

  return FALSE;
}

static ret_t users_exec(object_t* obj, const char* name, const char* args) {
  int32_t index = -1;
  object_t* sub = NULL;
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL, RET_BAD_PARAMS);

  sub = object_get_child_object(obj, name, &name);
  if (sub != NULL) {
    return object_exec(sub, name, args);
  }

  if (args && strstr(args, "index")) {
    object_t* a = object_default_create();
    tk_command_arguments_to_object(args, a);
    index = object_get_prop_int32(a, "index", -1);
    OBJECT_UNREF(a);
  }

  if (tk_str_ieq("clear", name)) {
    return users_clear(obj);
  } else if (tk_str_ieq("remove_selected", name)) {
    return users_remove_selected(obj);
  } else if (tk_str_ieq("detail", name) && index != -1) {
    return users_detail(obj, index);
  } else if (tk_str_ieq("remove", name) && index != -1) {
    return users_remove(obj, index);
  } else if (tk_str_ieq("set_filter", name)) {
    return users_set_filter(obj, args);
  }

  return RET_NOT_FOUND;
}

static const object_vtable_t s_users_vtable = {.type = "users",
                                               .desc = "users",
                                               .size = sizeof(users_t),
                                               .is_collection = TRUE,
                                               .on_destroy = users_destroy,
                                               .compare = NULL,
                                               .get_prop = users_get_prop,
                                               .set_prop = users_set_prop,
                                               .remove_prop = NULL,
                                               .foreach_prop = NULL,
                                               .can_exec = users_can_exec,
                                               .exec = users_exec,
                                               .clone = NULL};

object_t* users_create_with_repository(user_repository_t* r) {
  object_t* obj = object_create(&s_users_vtable);
  users_t* users = USERS(obj);
  return_value_if_fail(users != NULL && r != NULL, NULL);

  users->r = r;
  str_init(&(users->filter), 100);
  darray_init(&(users->users), 100, NULL, NULL);

  users->event_id = user_repository_on(r, EVT_PROP_CHANGED, users_on_repository_changed, users);

  return obj;
}

object_t* users_create(void) {
  return users_create_with_repository(app_globals_get_user_repository());
}

users_t* users_cast(object_t* obj) {
  return_value_if_fail(obj != NULL && obj->vt == &s_users_vtable, NULL);
  return (users_t*)(obj);
}