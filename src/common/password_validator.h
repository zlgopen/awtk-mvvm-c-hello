/**
 * File:   password_validator.h
 * Author: AWTK Develop Team
 * Brief:  password validator
 *
 * Copyright (c) 2019 - 2025 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-11-03 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_PASSWORD_VALIDATOR_H
#define TK_PASSWORD_VALIDATOR_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class password_validator_t
 * @annotation ["scriptable", "fake"]
 * 密码校验器。
 */

/**
 * @method password_validator_init
 * 密码校验器初始化。
 * @annotation ["static", "scriptable"]
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t password_validator_init(void);

END_C_DECLS

#endif /*TK_PASSWORD_VALIDATOR_H*/
