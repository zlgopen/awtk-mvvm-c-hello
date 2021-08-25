/**
 * File:   users_view_model.c
 * Author: AWTK Develop Team
 * Brief:  users_view_model
 *
 * Copyright (c) 2020 - 2021  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2021-06-03 Liu YuXin <liuyuxin@zlg.cn> created
 *
 */

#include "users_view_model.h"
#include "mvvm/base/view_model_object_wrapper.h"

view_model_t* users_view_model_create(navigator_request_t* req) {
  object_t* users = users_create();
  return_value_if_fail(users != NULL, NULL);
  view_model_t* vm = view_model_object_wrapper_create(users);

  emitter_on(EMITTER(users), EVT_ITEMS_CHANGED, (event_func_t)emitter_dispatch, vm);

  users_reload(users);

  return vm;
}
