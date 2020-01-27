﻿
/*This file is generated by code generator*/

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "product_info_view_model.h"

static ret_t product_info_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  product_info_t* product_info = ((product_info_view_model_t*)(obj))->product_info;

  if (tk_str_eq("name", name)) {
     
     return RET_OK;
  } else if (tk_str_eq("version", name)) {
     
     return RET_OK;
  } else if (tk_str_eq("model", name)) {
     
     return RET_OK;
  } else if (tk_str_eq("serial_no", name)) {
     
     return RET_OK;
  }
  
  return RET_NOT_FOUND;
}


static ret_t product_info_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  product_info_t* product_info = ((product_info_view_model_t*)(obj))->product_info;

  if (tk_str_eq("name", name)) {
     value_set_str(v, product_info->name.str);
     return RET_OK;
  } else if (tk_str_eq("version", name)) {
     value_set_str(v, product_info->version.str);
     return RET_OK;
  } else if (tk_str_eq("model", name)) {
     value_set_str(v, product_info->model.str);
     return RET_OK;
  } else if (tk_str_eq("serial_no", name)) {
     value_set_str(v, product_info->serial_no.str);
     return RET_OK;
  }

  return RET_NOT_FOUND;
}


static bool_t product_info_view_model_can_exec(object_t* obj, const char* name, const char* args) {

  return FALSE;
}

static ret_t product_info_view_model_exec(object_t* obj, const char* name, const char* args) {

  return RET_NOT_FOUND;
}

static ret_t product_info_view_model_on_destroy(object_t* obj) {
  product_info_view_model_t* vm = (product_info_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  product_info_destroy(vm->product_info);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_product_info_view_model_vtable = {
  .type = "product_info_view_model_t",
  .desc = "product_info_view_model_t",
  .size = sizeof(product_info_view_model_t),
  .exec = product_info_view_model_exec,
  .can_exec = product_info_view_model_can_exec,
  .get_prop = product_info_view_model_get_prop,
  .set_prop = product_info_view_model_set_prop,
  .on_destroy = product_info_view_model_on_destroy
};

view_model_t* product_info_view_model_create_with(product_info_t* product_info) {
  object_t* obj = object_create(&s_product_info_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  product_info_view_model_t* product_info_view_model = (product_info_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  product_info_view_model->product_info = product_info;

  return vm;
}

ret_t product_info_view_model_attach(view_model_t* vm, product_info_t* product_info) {
  product_info_view_model_t* product_info_view_model = (product_info_view_model_t*)(vm);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  product_info_view_model->product_info = product_info;

  return RET_OK;
}

view_model_t* product_info_view_model_create(navigator_request_t* req) {
  product_info_t* product_info = product_info_create();
  return_value_if_fail(product_info != NULL, NULL);

  return product_info_view_model_create_with(product_info);
}
