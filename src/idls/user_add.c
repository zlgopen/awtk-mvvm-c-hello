#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "user_add.h"

/***************user_add***************/;

static inline user_add_t* user_add_create(void) {
  user_add_t* user_add = TKMEM_ZALLOC(user_add_t);
  return_value_if_fail(user_add != NULL, NULL);

  str_init(&(user_add->name), 10);
  str_init(&(user_add->nick_name), 10);
  str_init(&(user_add->password), 10);
  str_init(&(user_add->confirm_password), 10);

  return user_add;
}

static inline ret_t user_add_destroy(user_add_t* user_add) {
  return_value_if_fail(user_add != NULL, RET_BAD_PARAMS);

  str_reset(&(user_add->name));
  str_reset(&(user_add->nick_name));
  str_reset(&(user_add->password));
  str_reset(&(user_add->confirm_password));

  TKMEM_FREE(user_add);

  return RET_OK;
}

static bool_t user_add_can_exec_add(user_add_t* user_add, const char* args) {
  return TRUE;
}

static ret_t user_add_add(user_add_t* user_add, const char* args) {
  return RET_OBJECT_CHANGED;
}

/***************user_add_view_model***************/

static ret_t user_add_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* user_add = vm->user_add;

  if (tk_str_eq("name", name)) {
    str_from_value(&(user_add->name), v);
  } else if (tk_str_eq("nick_name", name)) {
    str_from_value(&(user_add->nick_name), v);
  } else if (tk_str_eq("password", name)) {
    str_from_value(&(user_add->password), v);
  } else if (tk_str_eq("confirm_password", name)) {
    str_from_value(&(user_add->confirm_password), v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static ret_t user_add_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* user_add = vm->user_add;

  if (tk_str_eq("name", name)) {
    value_set_str(v, user_add->name.str);
  } else if (tk_str_eq("nick_name", name)) {
    value_set_str(v, user_add->nick_name.str);
  } else if (tk_str_eq("password", name)) {
    value_set_str(v, user_add->password.str);
  } else if (tk_str_eq("confirm_password", name)) {
    value_set_str(v, user_add->confirm_password.str);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static bool_t user_add_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* user_add = vm->user_add;

  if (tk_str_eq("add", name)) {
    return user_add_can_exec_add(user_add, args);
  } else {
    return FALSE;
  }
}

static ret_t user_add_view_model_exec(object_t* obj, const char* name, const char* args) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* user_add = vm->user_add;

  if (tk_str_eq("add", name)) {
    return user_add_add(user_add, args);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t user_add_view_model_on_destroy(object_t* obj) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  user_add_destroy(vm->user_add);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_user_add_view_model_vtable = {
    .type = "user_add",
    .desc = "user add",
    .size = sizeof(user_add_view_model_t),
    .exec = user_add_view_model_exec,
    .can_exec = user_add_view_model_can_exec,
    .get_prop = user_add_view_model_get_prop,
    .set_prop = user_add_view_model_set_prop,
    .on_destroy = user_add_view_model_on_destroy};

view_model_t* user_add_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_user_add_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  user_add_view_model_t* user_add_view_model = (user_add_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  user_add_view_model->user_add = user_add_create();
  ENSURE(user_add_view_model->user_add != NULL);

  return vm;
}
