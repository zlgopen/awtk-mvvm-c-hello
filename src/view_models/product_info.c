#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "product_info.h"


/***************product_info***************/;

static inline product_info_t* product_info_create(void) {
  product_info_t* product_info = TKMEM_ZALLOC(product_info_t);
  return_value_if_fail(product_info != NULL, NULL);

  str_set(&(product_info->name), "awtk-mvvm-demo");
  str_set(&(product_info->version), "1.0.0");
  str_set(&(product_info->model), "awtk-mvvm");
  str_set(&(product_info->serial_no), "111222333444");


  return product_info;
} 


static inline int product_info_cmp(product_info_t* a, product_info_t* b) {
  return_value_if_fail(a != NULL && b != NULL, -1);
  return strcmp(a->name.str, b->name.str);
}


static inline ret_t product_info_destroy(product_info_t* product_info) {
  return_value_if_fail(product_info != NULL, RET_BAD_PARAMS);

  str_reset(&(product_info->name));
  str_reset(&(product_info->version));
  str_reset(&(product_info->model));
  str_reset(&(product_info->serial_no));


  TKMEM_FREE(product_info);

  return RET_OK;
}

/***************product_info_view_model***************/

static ret_t product_info_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  product_info_view_model_t* vm = (product_info_view_model_t*)(obj);
  product_info_t* product_info = vm->product_info;

  if (tk_str_eq("name", name)) {
    str_from_value(&(product_info->name), v);
  } else if (tk_str_eq("version", name)) {
    str_from_value(&(product_info->version), v);
  } else if (tk_str_eq("model", name)) {
    str_from_value(&(product_info->model), v);
  } else if (tk_str_eq("serial_no", name)) {
    str_from_value(&(product_info->serial_no), v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static ret_t product_info_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  product_info_view_model_t* vm = (product_info_view_model_t*)(obj);
  product_info_t* product_info = vm->product_info;

  if (tk_str_eq("name", name)) {
    value_set_str(v, product_info->name.str);
  } else if (tk_str_eq("version", name)) {
    value_set_str(v, product_info->version.str);
  } else if (tk_str_eq("model", name)) {
    value_set_str(v, product_info->model.str);
  } else if (tk_str_eq("serial_no", name)) {
    value_set_str(v, product_info->serial_no.str);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static bool_t product_info_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  return FALSE;
}

static ret_t product_info_view_model_exec(object_t* obj, const char* name, const char* args) {
  return RET_NOT_IMPL;
}


static ret_t product_info_view_model_on_destroy(object_t* obj) {
  product_info_view_model_t* vm = (product_info_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  product_info_destroy(vm->product_info);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_product_info_view_model_vtable = {
  .type = "product_info",
  .desc = "product_info",
  .size = sizeof(product_info_view_model_t),
  .exec = product_info_view_model_exec,
  .can_exec = product_info_view_model_can_exec,
  .get_prop = product_info_view_model_get_prop,
  .set_prop = product_info_view_model_set_prop,
  .on_destroy = product_info_view_model_on_destroy
};

view_model_t* product_info_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_product_info_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  product_info_view_model_t* product_info_view_model = (product_info_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  product_info_view_model->product_info = product_info_create();
  ENSURE(product_info_view_model->product_info != NULL);

  return vm;
}
