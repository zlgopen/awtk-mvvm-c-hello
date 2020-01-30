﻿
/*This file is generated by code generator*/

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "change_password_view_model.h"

static ret_t change_password_view_model_set_prop(object_t* obj, const char* name,
                                                 const value_t* v) {
  change_password_t* achange_password = ((change_password_view_model_t*)(obj))->achange_password;

  if (tk_str_ieq("old_password", name)) {
    str_set(&(achange_password->old_password), value_str(v));

    return RET_OK;
  } else if (tk_str_ieq("new_password", name)) {
    str_set(&(achange_password->new_password), value_str(v));

    return RET_OK;
  } else if (tk_str_ieq("confirm_password", name)) {
    str_set(&(achange_password->confirm_password), value_str(v));

    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static ret_t change_password_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  change_password_t* achange_password = ((change_password_view_model_t*)(obj))->achange_password;

  if (tk_str_ieq("old_password", name)) {
    value_set_str(v, achange_password->old_password.str);
    return RET_OK;
  } else if (tk_str_ieq("new_password", name)) {
    value_set_str(v, achange_password->new_password.str);
    return RET_OK;
  } else if (tk_str_ieq("confirm_password", name)) {
    value_set_str(v, achange_password->confirm_password.str);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}

static bool_t change_password_view_model_can_exec(object_t* obj, const char* name,
                                                  const char* args) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* achange_password = vm->achange_password;
  if (tk_str_ieq("change", name)) {
    return change_password_can_change(achange_password);
  }
  return FALSE;
}

static ret_t change_password_view_model_exec(object_t* obj, const char* name, const char* args) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  change_password_t* achange_password = vm->achange_password;
  if (tk_str_ieq("change", name)) {
    return change_password_change(achange_password);
  }
  return RET_NOT_FOUND;
}

static ret_t change_password_view_model_on_destroy(object_t* obj) {
  change_password_view_model_t* vm = (change_password_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  change_password_destroy(vm->achange_password);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_change_password_view_model_vtable = {
    .type = "change_password_view_model_t",
    .desc = "change_password_view_model_t",
    .size = sizeof(change_password_view_model_t),
    .exec = change_password_view_model_exec,
    .can_exec = change_password_view_model_can_exec,
    .get_prop = change_password_view_model_get_prop,
    .set_prop = change_password_view_model_set_prop,
    .on_destroy = change_password_view_model_on_destroy};

view_model_t* change_password_view_model_create_with(change_password_t* achange_password) {
  object_t* obj = object_create(&s_change_password_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  change_password_view_model_t* change_password_view_model = (change_password_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  change_password_view_model->achange_password = achange_password;

  return vm;
}

ret_t change_password_view_model_attach(view_model_t* vm, change_password_t* achange_password) {
  change_password_view_model_t* change_password_view_model = (change_password_view_model_t*)(vm);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  change_password_view_model->achange_password = achange_password;

  return RET_OK;
}

view_model_t* change_password_view_model_create(navigator_request_t* req) {
  change_password_t* achange_password = change_password_create();
  return_value_if_fail(achange_password != NULL, NULL);

  return change_password_view_model_create_with(achange_password);
}
