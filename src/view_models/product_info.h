
#ifndef TK_PRODUCT_INFO_H
#define TK_PRODUCT_INFO_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class product_info_t
 *
 * product_info
 *
 */
typedef struct _product_info_t{
  str_t name;
  str_t version;
  str_t model;
  str_t serial_no;
} product_info_t;

/**
 * @class product_info_view_model_t
 *
 * view model of product_info
 *
 */
typedef struct _product_info_view_model_t {
  view_model_t view_model;

  /*model object*/
  product_info_t* product_info;
} product_info_view_model_t;

/**
 * @method product_info_view_model_create
 * 创建product_info view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* product_info_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_PRODUCT_INFO_H*/
