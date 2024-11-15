﻿
/*This file is generated by code generator*/

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "user_add_view_model.h"

static ret_t user_add_view_model_set_prop(tk_object_t* obj, const char* name, const value_t* v) {
  user_add_t* auser_add = ((user_add_view_model_t*)(obj))->auser_add;

  if (tk_str_ieq("name", name)) {
    str_set(&(auser_add->name), value_str(v));

    return RET_OK;
  } else if (tk_str_ieq("nick_name", name)) {
    str_set(&(auser_add->nick_name), value_str(v));

    return RET_OK;
  } else if (tk_str_ieq("password", name)) {
    str_set(&(auser_add->password), value_str(v));

    return RET_OK;
  } else if (tk_str_ieq("confirm_password", name)) {
    str_set(&(auser_add->confirm_password), value_str(v));

    return RET_OK;
  }
  
  return RET_NOT_FOUND;
}


static ret_t user_add_view_model_get_prop(tk_object_t* obj, const char* name, value_t* v) {
  user_add_t* auser_add = ((user_add_view_model_t*)(obj))->auser_add;

  if (tk_str_ieq("name", name)) {
    value_set_str(v, auser_add->name.str);
    return RET_OK;
  } else if (tk_str_ieq("nick_name", name)) {
    value_set_str(v, auser_add->nick_name.str);
    return RET_OK;
  } else if (tk_str_ieq("password", name)) {
    value_set_str(v, auser_add->password.str);
    return RET_OK;
  } else if (tk_str_ieq("confirm_password", name)) {
    value_set_str(v, auser_add->confirm_password.str);
    return RET_OK;
  }

  return RET_NOT_FOUND;
}


static bool_t user_add_view_model_can_exec(tk_object_t* obj, const char* name, const char* args) {
 
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* auser_add = vm->auser_add;
  if (tk_str_ieq("add", name)) {
    return user_add_can_add(auser_add);
  }
  return FALSE;
}

static ret_t user_add_view_model_exec(tk_object_t* obj, const char* name, const char* args) {
 
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  user_add_t* auser_add = vm->auser_add;
  if (tk_str_ieq("add", name)) {
    return user_add_add(auser_add);
  }
  return RET_NOT_FOUND;
}

static ret_t user_add_view_model_on_destroy(tk_object_t* obj) {
  user_add_view_model_t* vm = (user_add_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  
  user_add_destroy(vm->auser_add);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_user_add_view_model_vtable = {
  .type = "user_add_view_model_t",
  .desc = "user_add_view_model_t",
  .size = sizeof(user_add_view_model_t),
  .is_collection = FALSE,
  .on_destroy = user_add_view_model_on_destroy,
  .compare = NULL,
  .get_prop = user_add_view_model_get_prop,
  .set_prop = user_add_view_model_set_prop,
  .remove_prop = NULL,
  .foreach_prop = NULL,
  .clear_props = NULL,
  .find_prop = NULL,
  .find_props = NULL,
  .can_exec = user_add_view_model_can_exec,
  .exec = user_add_view_model_exec,
  .clone = NULL
};

view_model_t* user_add_view_model_create_with(user_add_t* auser_add) {
  tk_object_t* obj = tk_object_create(&s_user_add_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  user_add_view_model_t* user_add_view_model = (user_add_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  user_add_view_model->auser_add = auser_add;
  

  return vm;
}

ret_t user_add_view_model_attach(view_model_t* vm, user_add_t* auser_add) {
  user_add_view_model_t* user_add_view_model = (user_add_view_model_t*)(vm);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  user_add_view_model->auser_add = auser_add;

  return RET_OK;
}

view_model_t* user_add_view_model_create(navigator_request_t* req) {
  user_add_t* auser_add = user_add_create();
  return_value_if_fail(auser_add != NULL, NULL);

  return user_add_view_model_create_with(auser_add);
}
