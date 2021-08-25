/**
 * File:   datetime_str_converter.h
 * Author: AWTK Develop Team
 * Brief:  datetime_str converter
 *
 * Copyright (c) 2019 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-11-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_DATETIME_STR_CONVERTER_H
#define TK_DATETIME_STR_CONVERTER_H

#include "mvvm/base/view_model.h"

BEGIN_C_DECLS

/**
 * @class datetime_str_converter_t
 * @annotation ["scriptable", "fake"]
 * 日期转换器。
 */

/**
 * @method datetime_str_converter_init
 * 日期转换器初始化。
 * @annotation ["static", "scriptable"]
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t datetime_str_converter_init(void);

END_C_DECLS

#endif /*TK_DATETIME_STR_CONVERTER_H*/
