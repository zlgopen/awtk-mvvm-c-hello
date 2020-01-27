#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "product_info.h"

product_info_t* product_info_create(void) {
  product_info_t* product_info = TKMEM_ZALLOC(product_info_t);
  return_value_if_fail(product_info != NULL, NULL);

  str_set(&(product_info->name), "awtk-mvvm-demo");
  str_set(&(product_info->version), "1.0.0");
  str_set(&(product_info->model), "awtk-mvvm");
  str_set(&(product_info->serial_no), "111222333444");

  return product_info;
}

ret_t product_info_destroy(product_info_t* product_info) {
  return_value_if_fail(product_info != NULL, RET_BAD_PARAMS);

  str_reset(&(product_info->name));
  str_reset(&(product_info->version));
  str_reset(&(product_info->model));
  str_reset(&(product_info->serial_no));

  TKMEM_FREE(product_info);

  return RET_OK;
}
