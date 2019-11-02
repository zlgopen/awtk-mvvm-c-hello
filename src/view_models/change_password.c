#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "change_password.h"


/***************change_password***************/;

static inline change_password_t* change_password_create(void) {
  change_password_t* change_password = TKMEM_ZALLOC(change_password_t);
  return_value_if_fail(change_password != NULL, NULL);

  str_init(&(change_password->old_password), 10);
  str_init(&(change_password->new_password), 10);
  str_init(&(change_password->confirm_password), 10);


  return change_password;
} 

static inline ret_t change_password_destroy(change_password_t* change_password) {
  return_value_if_fail(change_password != NULL, RET_BAD_PARAMS);

  str_reset(&(change_password->old_password));
  str_reset(&(change_password->new_password));
  str_reset(&(change_password->confirm_password));


  TKMEM_FREE(change_password);

  return RET_OK;
}

static bool_t change_password_can_exec_change(change_password_t* change_password, const char* args) {
  return TRUE;
}

static ret_t change_password_change(change_password_t* change_password, const char* args) {
  
  return RET_OBJECT_CHANGED;
}

/***************change_password_view_model***************/

static ret_t change_password_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* change_password = vm->change_password;

  if (tk_str_eq("old_password", name)) {
    str_from_value(&(change_password->old_password), v);
  } else if (tk_str_eq("new_password", name)) {
    str_from_value(&(change_password->new_password), v);
  } else if (tk_str_eq("confirm_password", name)) {
    str_from_value(&(change_password->confirm_password), v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static ret_t change_password_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* change_password = vm->change_password;

  if (tk_str_eq("old_password", name)) {
    value_set_str(v, change_password->old_password.str);
  } else if (tk_str_eq("new_password", name)) {
    value_set_str(v, change_password->new_password.str);
  } else if (tk_str_eq("confirm_password", name)) {
    value_set_str(v, change_password->confirm_password.str);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static bool_t change_password_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* change_password = vm->change_password;

  if (tk_str_eq("change", name)) {
    return change_password_can_exec_change(change_password, args);
  } else {
    return FALSE;
  }
}

static ret_t change_password_view_model_exec(object_t* obj, const char* name, const char* args) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* change_password = vm->change_password;

  if (tk_str_eq("change", name)) {
    return change_password_change(change_password, args);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t change_password_view_model_on_destroy(object_t* obj) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  change_password_destroy(vm->change_password);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_change_password_view_model_vtable = {
  .type = "change_password",
  .desc = "change current user password",
  .size = sizeof(change_password_view_model_t),
  .exec = change_password_view_model_exec,
  .can_exec = change_password_view_model_can_exec,
  .get_prop = change_password_view_model_get_prop,
  .set_prop = change_password_view_model_set_prop,
  .on_destroy = change_password_view_model_on_destroy
};

view_model_t* change_password_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_change_password_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  change_password_view_model_t* change_password_view_model = (change_password_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  change_password_view_model->change_password = change_password_create();
  ENSURE(change_password_view_model->change_password != NULL);

  return vm;
}
