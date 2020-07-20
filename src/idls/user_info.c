#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "user_info.h"

/***************user_info***************/;

static inline user_info_t* user_info_create(void) {
  user_info_t* user_info = TKMEM_ZALLOC(user_info_t);
  return_value_if_fail(user_info != NULL, NULL);

  str_init(&(user_info->name), 10);
  str_init(&(user_info->nick_name), 10);
  str_init(&(user_info->password), 10);

  return user_info;
}

static inline ret_t user_info_destroy(user_info_t* user_info) {
  return_value_if_fail(user_info != NULL, RET_BAD_PARAMS);

  str_reset(&(user_info->name));
  str_reset(&(user_info->nick_name));
  str_reset(&(user_info->password));

  TKMEM_FREE(user_info);

  return RET_OK;
}

static bool_t user_info_can_exec_change_password(user_info_t* user_info, const char* args) {
  return TRUE;
}

static ret_t user_info_change_password(user_info_t* user_info, const char* args) {
  return RET_OBJECT_CHANGED;
}

/***************user_info_view_model***************/

static ret_t user_info_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  user_info_view_model_t* vm = (user_info_view_model_t*)(obj);
  user_info_t* user_info = vm->user_info;

  if (tk_str_eq("name", name)) {
    str_from_value(&(user_info->name), v);
  } else if (tk_str_eq("nick_name", name)) {
    str_from_value(&(user_info->nick_name), v);
  } else if (tk_str_eq("password", name)) {
    str_from_value(&(user_info->password), v);
  } else if (tk_str_eq("registered_time", name)) {
    user_info->registered_time = value_uint32(v);
  } else if (tk_str_eq("last_login_time", name)) {
    user_info->last_login_time = value_uint32(v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static ret_t user_info_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  user_info_view_model_t* vm = (user_info_view_model_t*)(obj);
  user_info_t* user_info = vm->user_info;

  if (tk_str_eq("name", name)) {
    value_set_str(v, user_info->name.str);
  } else if (tk_str_eq("nick_name", name)) {
    value_set_str(v, user_info->nick_name.str);
  } else if (tk_str_eq("password", name)) {
    value_set_str(v, user_info->password.str);
  } else if (tk_str_eq("registered_time", name)) {
    value_set_uint32(v, user_info->registered_time);
  } else if (tk_str_eq("last_login_time", name)) {
    value_set_uint32(v, user_info->last_login_time);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static bool_t user_info_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  user_info_view_model_t* vm = (user_info_view_model_t*)(obj);
  user_info_t* user_info = vm->user_info;

  if (tk_str_eq("change_password", name)) {
    return user_info_can_exec_change_password(user_info, args);
  } else {
    return FALSE;
  }
}

static ret_t user_info_view_model_exec(object_t* obj, const char* name, const char* args) {
  user_info_view_model_t* vm = (user_info_view_model_t*)(obj);
  user_info_t* user_info = vm->user_info;

  if (tk_str_eq("change_password", name)) {
    return user_info_change_password(user_info, args);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t user_info_view_model_on_destroy(object_t* obj) {
  user_info_view_model_t* vm = (user_info_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  user_info_destroy(vm->user_info);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_user_info_view_model_vtable = {
    .type = "user_info",
    .desc = "user info",
    .size = sizeof(user_info_view_model_t),
    .exec = user_info_view_model_exec,
    .can_exec = user_info_view_model_can_exec,
    .get_prop = user_info_view_model_get_prop,
    .set_prop = user_info_view_model_set_prop,
    .on_destroy = user_info_view_model_on_destroy};

view_model_t* user_info_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_user_info_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  user_info_view_model_t* user_info_view_model = (user_info_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  user_info_view_model->user_info = user_info_create();
  ENSURE(user_info_view_model->user_info != NULL);

  return vm;
}
