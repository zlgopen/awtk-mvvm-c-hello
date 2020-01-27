
#ifndef TK_PRODUCT_INFO_H
#define TK_PRODUCT_INFO_H

#include "tkc/str.h"

BEGIN_C_DECLS

/**
 * @class product_info_t
 *
 * @annotation ["model"]
 * product_info
 *
 */
typedef struct _product_info_t {
  /**
   * @property {str_t} name
   * @annotation ["readable"]
   * 名称。
   */
  str_t name;
  /**
   * @property {str_t} version
   * @annotation ["readable"]
   * 用户名。
   */
  str_t version;
  /**
   * @property {str_t} model
   * @annotation ["readable"]
   * 型号。
   */
  str_t model;
  /**
   * @property {str_t} serial_no
   * @annotation ["readable"]
   * 序列号。
   */
  str_t serial_no;
} product_info_t;

/**
 * @method product_info_create
 * 创建product_info对象。
 *
 * @annotation ["constructor"]
 * @return {product_info_t*} 返回product_info对象。
 */
product_info_t* product_info_create(void);

/**
 * @method product_info_destroy
 * 销毁product_info对象。
 *
 * @annotation ["destructor"]
 * @param {product_info_t*} product_info product_info对象。
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t product_info_destroy(product_info_t* product_info);

END_C_DECLS

#endif /*TK_PRODUCT_INFO_H*/
