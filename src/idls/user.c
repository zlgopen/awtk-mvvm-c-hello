#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "user.h"

/***************user***************/;

static inline user_t* user_create(void) {
  user_t* user = TKMEM_ZALLOC(user_t);
  return_value_if_fail(user != NULL, NULL);

  awtk - mvvm - demo;
  1.0.0;
  awtk - mvvm;
  111122223333;

  return user;
}

static inline int user_cmp(user_t* a, user_t* b) {
  return_value_if_fail(a != NULL && b != NULL, -1);
  return strcmp(a->name.str, b->name.str);
}

static inline ret_t user_destroy(user_t* user) {
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  str_reset(&(user->name));
  str_reset(&(user->version));
  str_reset(&(user->model));
  str_reset(&(user->serial_no));

  TKMEM_FREE(user);

  return RET_OK;
}

/***************user_view_model***************/

static ret_t user_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  user_view_model_t* vm = (user_view_model_t*)(obj);
  user_t* user = vm->user;

  if (tk_str_eq("name", name)) {
    str_from_value(&(user->name), v);
  } else if (tk_str_eq("version", name)) {
    str_from_value(&(user->version), v);
  } else if (tk_str_eq("model", name)) {
    str_from_value(&(user->model), v);
  } else if (tk_str_eq("serial_no", name)) {
    str_from_value(&(user->serial_no), v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static ret_t user_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  user_view_model_t* vm = (user_view_model_t*)(obj);
  user_t* user = vm->user;

  if (tk_str_eq("name", name)) {
    value_set_str(v, user->name.str);
  } else if (tk_str_eq("version", name)) {
    value_set_str(v, user->version.str);
  } else if (tk_str_eq("model", name)) {
    value_set_str(v, user->model.str);
  } else if (tk_str_eq("serial_no", name)) {
    value_set_str(v, user->serial_no.str);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }

  return RET_OK;
}

static bool_t user_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  return FALSE;
}

static ret_t user_view_model_exec(object_t* obj, const char* name, const char* args) {
  return RET_NOT_IMPL;
}

static ret_t user_view_model_on_destroy(object_t* obj) {
  user_view_model_t* vm = (user_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  user_destroy(vm->user);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_user_view_model_vtable = {.type = "user",
                                                         .desc = "user manager",
                                                         .size = sizeof(user_view_model_t),
                                                         .exec = user_view_model_exec,
                                                         .can_exec = user_view_model_can_exec,
                                                         .get_prop = user_view_model_get_prop,
                                                         .set_prop = user_view_model_set_prop,
                                                         .on_destroy = user_view_model_on_destroy};

view_model_t* user_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_user_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  user_view_model_t* user_view_model = (user_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  user_view_model->user = user_create();
  ENSURE(user_view_model->user != NULL);

  return vm;
}
