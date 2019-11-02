/**
 * File:   datetime_str_converter.c
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

#include "datetime_str_converter.h"
#include "mvvm/base/value_converter_delegate.h"

static ret_t to_view(const value_t* from, value_t* to) {
  uint32_t dt = value_uint32(from);

  /*FIXME*/
  value_dup_str(to, "2019-11-02 12:00:00");

  return RET_OK;
}

static ret_t to_model(const value_t* from, value_t* to) {
  /*DO NOTHING*/
  return RET_OK;
}

static void* datetime_str_converter_create(void) {
  return value_converter_delegate_create(to_model, to_view);
}

ret_t datetime_str_converter_init(void) {
  value_converter_register("datetime_str", datetime_str_converter_create);

  return RET_OK;
}
