/**
 * File:   users_view_model.c
 * Author: AWTK Develop Team
 * Brief:  users_view_model
 *
 * Copyright (c) 2020 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#include "users.h"
#include "mvvm/base/view_model.h"

#ifndef TK_USERS_VIEW_MODEL_H
#define TK_USERS_VIEW_MODEL_H

BEGIN_C_DECLS
/**
 * @class users_view_model_t
 *
 * view model of users
 *
 */

/**
 * @method users_view_model_create
 * 创建users view model对象。
 *
 * @annotation ["constructor"]
 * @param {navigator_request_t*} req 请求参数。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* users_view_model_create(navigator_request_t* req);

END_C_DECLS

#endif /*TK_USERS_VIEW_MODEL_H*/
