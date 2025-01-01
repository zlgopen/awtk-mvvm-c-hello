/**
 * File:   datetime_str_converter.c
 * Author: AWTK Develop Team
 * Brief:  datetime_str converter
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
 * 2019-11-02 Li XianJing <xianjimli@hotmail.com> created
 *
 */
#include <time.h>
#include "datetime_str_converter.h"
#include "mvvm/base/value_converter_delegate.h"

static ret_t to_view(const value_t* from, value_t* to) {
#ifndef AWTK_WEB
  char str[64];
  struct tm* time_info = NULL;
  time_t t = value_uint32(from);

  time_info = localtime(&t);
  strftime(str, sizeof(str), "%Y-%m-%d %H:%M:%S", time_info);

  value_dup_str(to, str);
#else
  value_set_str(to, "2020-01-01 12:12:00");
#endif
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
