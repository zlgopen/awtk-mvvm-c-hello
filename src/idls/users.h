﻿
#ifndef TK_USER_VIEW_MODEL_H
#define TK_USER_VIEW_MODEL_H

#include "tkc/darray.h"
#include "mvvm/base/view_model_array.h"

BEGIN_C_DECLS

#include "user.h"

/**
 * @class users_view_model_t
 *
 * view model of user
 *
 */
typedef struct _users_view_model_t {
  view_model_array_t view_model_array;

  /*model object*/
  darray_t users;
} users_view_model_t;

/**
 * @method users_view_model_create
 * 创建user view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* users_view_model_create(navigator_request_t* req);

/*public for test*/

user_t* user_create(void);

ret_t users_view_model_clear(view_model_t* view_model);
uint32_t users_view_model_size(view_model_t* view_model);
ret_t users_view_model_remove(view_model_t* view_model, uint32_t index);
ret_t users_view_model_add(view_model_t* view_model, user_t* user);
user_t* users_view_model_get(view_model_t* view_model, uint32_t index);

END_C_DECLS

#endif /*TK_USER_VIEW_MODEL_H*/
