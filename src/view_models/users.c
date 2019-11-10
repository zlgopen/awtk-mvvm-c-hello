#include "tkc/mem.h"
#include "tkc/utils.h"
#include "base/idle.h"
#include "mvvm/base/utils.h"
#include "mvvm/base/navigator.h"

#include "users.h"
#include "common/app_globals.h"

static int reload_cmp(const void* a, const void* b) {
  const user_t* user = (const user_t*)a;
  const char* filter = (const char*)b;
  if (filter == NULL) {
    return 0;
  }

  if (strstr(user->name.str, filter) != NULL) {
    return 0;
  } else {
    return -1;
  }
}

static int name_cmp_ascending(const void* a, const void* b) {
  const user_t* user1 = *(const user_t**)a;
  const user_t* user2 = *(const user_t**)b;

  return strcmp(user1->name.str, user2->name.str);
}

static int name_cmp_descending(const void* a, const void* b) {
  const user_t* user1 = *(const user_t**)a;
  const user_t* user2 = *(const user_t**)b;

  return strcmp(user2->name.str, user1->name.str);
}

static ret_t users_view_model_reload(users_view_model_t* vm) {
  darray_t* users = NULL;
  user_repository_t* r = app_globals_get_user_repository();

  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  users = &(vm->users);
  darray_clear(users);
  user_repository_find(r, reload_cmp, vm->filter.str, users);

  if (vm->ascending) {
    darray_sort(users, name_cmp_ascending);
  } else {
    darray_sort(users, name_cmp_descending);
  }

  view_model_array_notify_items_changed(VIEW_MODEL(vm));

  return RET_OK;
}

static bool_t user_can_exec_detail(user_t* user, const char* args) {
  return TRUE;
}

static ret_t user_detail(user_t* user) {
  navigator_request_t* req = navigator_request_create("user_detail", NULL);
  return_value_if_fail(req != NULL, RET_OOM);

  object_set_prop_pointer(OBJECT(req), REQ_ARG_USER, user);
  navigator_to_ex(req);
  object_unref(OBJECT(req));

  return RET_OK;
}

static ret_t user_add_on_result(navigator_request_t* req, const value_t* result) {
  user_repository_t* r = app_globals_get_user_repository();
  user_t* user = (user_t*)value_pointer(result);

  if (user_repository_add(r, user) != RET_OK) {
    log_debug("add user failed.\n");
  }

  return RET_OK;
}

/***************users_view_model***************/

ret_t users_view_model_remove(view_model_t* view_model, user_t* user) {
  user_repository_t* r = app_globals_get_user_repository();

  user_repository_remove(r, (tk_compare_t)user_cmp_with_name, user->name.str);

  return RET_OK;
}

ret_t users_view_model_add(view_model_t* view_model, user_t* user) {
  navigator_request_t* req = navigator_request_create("user_add", user_add_on_result);
  return_value_if_fail(req != NULL, RET_OOM);

  object_set_prop_pointer(OBJECT(req), REQ_ARG_USER, user);
  object_set_prop_pointer(OBJECT(req), "requester", view_model);
  navigator_to_ex(req);
  object_unref(OBJECT(req));

  return RET_OK;
}

uint32_t users_view_model_size(view_model_t* view_model) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, 0);

  return user_vm->users.size;
}

ret_t users_view_model_clear(view_model_t* view_model) {
  user_t* user = app_globals_get_current_user();
  user_repository_t* r = app_globals_get_user_repository();

  user_repository_remove(r, (tk_compare_t)user_cmp_with_name_not, user->name.str);

  return RET_OK;
}

user_t* users_view_model_get(view_model_t* view_model, uint32_t index) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, 0);

  if (index < users_view_model_size(view_model)) {
    return (user_t*)(user_vm->users.elms[index]);
  } else {
    log_debug("index(%u) >= size(%u)\n", index, users_view_model_size(view_model));
    return NULL;
  }
}

static ret_t users_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  uint32_t index = 0;
  user_t* user = NULL;
  view_model_t* vm = VIEW_MODEL(obj);
  users_view_model_t* user_vm = (users_view_model_t*)(vm);

  if (tk_str_eq(VIEW_MODEL_PROP_CURSOR, name)) {
    view_model_array_set_cursor(vm, value_int(v));
    return RET_OK;
  } else if (tk_str_eq("filter", name)) {
    str_from_value(&(user_vm->filter), v);
    users_view_model_reload(user_vm);
    return RET_OK;
  } else if (tk_str_eq("ascending", name)) {
    user_vm->ascending = value_bool(v);
    users_view_model_reload(user_vm);
    return RET_OK;
  }

  name = destruct_array_prop_name(name, &index);
  return_value_if_fail(name != NULL, RET_BAD_PARAMS);
  user = users_view_model_get(vm, index);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_eq("name", name)) {
    str_from_value(&(user->name), v);
  } else if (tk_str_eq("nick_name", name)) {
    str_from_value(&(user->nick_name), v);
  } else if (tk_str_eq("password", name)) {
    str_from_value(&(user->password), v);
  } else if (tk_str_eq("registered_time", name)) {
    user->registered_time = value_uint32(v);
  } else if (tk_str_eq("last_login_time", name)) {
    user->last_login_time = value_uint32(v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static ret_t users_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  uint32_t index = 0;
  user_t* user = NULL;
  view_model_t* vm = VIEW_MODEL(obj);
  users_view_model_t* user_vm = (users_view_model_t*)(vm);

  if (tk_str_eq(VIEW_MODEL_PROP_ITEMS, name)) {
    value_set_int(v, users_view_model_size(VIEW_MODEL(obj)));
    return RET_OK;
  } else if (tk_str_eq(VIEW_MODEL_PROP_CURSOR, name)) {
    value_set_int(v, VIEW_MODEL_ARRAY(obj)->cursor);
    return RET_OK;
  } else if (tk_str_eq("filter", name)) {
    value_set_str(v, user_vm->filter.str);
    return RET_OK;
  } else if (tk_str_eq("ascending", name)) {
    value_set_bool(v, user_vm->ascending);
    return RET_OK;
  }

  name = destruct_array_prop_name(name, &index);
  if (name == NULL) {
    return RET_FAIL;
  }

  user = users_view_model_get(vm, index);
  if (user == NULL) {
    return RET_FAIL;
  }

  if (tk_str_eq("name", name)) {
    value_set_str(v, user->name.str);
  } else if (tk_str_eq("nick_name", name)) {
    value_set_str(v, user->nick_name.str);
  } else if (tk_str_eq("password", name)) {
    value_set_str(v, user->password.str);
  } else if (tk_str_eq("registered_time", name)) {
    value_set_uint32(v, user->registered_time);
  } else if (tk_str_eq("last_login_time", name)) {
    value_set_uint32(v, user->last_login_time);
  } else if (tk_str_eq("style", name)) {
    value_set_str(v, index % 2 ? "odd" : "even");
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static bool_t users_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  uint32_t index = tk_atoi(args);
  view_model_t* vm = VIEW_MODEL(obj);
  user_t* user = NULL;

  if (tk_str_ieq(name, "add")) {
    return TRUE;
  } else if (tk_str_ieq(name, "clear")) {
    return users_view_model_size(vm) > 0;
  }

  user = users_view_model_get(vm, index);
  if (user == NULL) {
    return RET_FAIL;
  }

  if (tk_str_ieq(name, "remove")) {
    user_t* current_user = app_globals_get_current_user();
    return user != NULL && !tk_str_eq(user->name.str, current_user->name.str);
  } else if (tk_str_eq("detail", name)) {
    return user_can_exec_detail(user, args);
  } else {
    return FALSE;
  }
}

static ret_t users_view_model_exec(object_t* obj, const char* name, const char* args) {
  uint32_t index = tk_atoi(args);
  view_model_t* vm = VIEW_MODEL(obj);
  user_t* user = NULL;

  if (tk_str_ieq(name, "add")) {
    ENSURE(users_view_model_add(vm, user_create()) == RET_OK);
    return RET_ITEMS_CHANGED;
  } else if (tk_str_ieq(name, "clear")) {
    ENSURE(users_view_model_clear(vm) == RET_OK);
    return RET_ITEMS_CHANGED;
  }

  user = users_view_model_get(vm, index);
  if (user == NULL) {
    return RET_FAIL;
  }

  if (tk_str_ieq(name, "remove")) {
    ENSURE(users_view_model_remove(vm, user) == RET_OK);
    return RET_ITEMS_CHANGED;
  } else if (tk_str_eq("detail", name)) {
    return user_detail(user);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t users_view_model_on_destroy(object_t* obj) {
  user_repository_t* r = app_globals_get_user_repository();
  users_view_model_t* vm = (users_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  darray_deinit(&(vm->users));
  str_reset(&(vm->filter));
  user_repository_off(r, vm->event_id);

  return view_model_array_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_users_view_model_vtable = {
    .type = "user",
    .desc = "user manager",
    .is_collection = TRUE,
    .size = sizeof(users_view_model_t),
    .exec = users_view_model_exec,
    .can_exec = users_view_model_can_exec,
    .get_prop = users_view_model_get_prop,
    .set_prop = users_view_model_set_prop,
    .on_destroy = users_view_model_on_destroy};

static ret_t users_view_model_reload_async(const idle_info_t* info) {
  users_view_model_t* user_vm = (users_view_model_t*)(info->ctx);
  user_vm->reload_id = TK_INVALID_ID;

  users_view_model_reload(user_vm);

  return RET_REMOVE;
}

static ret_t users_view_model_on_repository_changed(void* ctx, event_t* e) {
  users_view_model_t* user_vm = (users_view_model_t*)(ctx);

  if (user_vm->reload_id == TK_INVALID_ID) {
    idle_queue(users_view_model_reload_async, ctx);
  }

  return RET_OK;
}

view_model_t* users_view_model_create(navigator_request_t* req) {
  user_repository_t* r = app_globals_get_user_repository();
  object_t* obj = object_create(&s_users_view_model_vtable);
  view_model_t* vm = view_model_array_init(VIEW_MODEL(obj));
  users_view_model_t* user_vm = (users_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  str_init(&(user_vm->filter), 100);
  darray_init(&(user_vm->users), 100, NULL, NULL);

  users_view_model_reload(user_vm);
  user_vm->event_id =
      user_repository_on(r, EVT_PROP_CHANGED, users_view_model_on_repository_changed, vm);

  return vm;
}
