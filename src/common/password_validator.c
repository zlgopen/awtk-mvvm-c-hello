/**
 * File:   password_validator.c
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

#include "password_validator.h"
#include "mvvm/base/value_validator_delegate.h"

static bool_t is_valid_password(const value_t* value, str_t* msg) {
  const wchar_t* password = value_wstr(value);

  return password != NULL && wcslen(password) > 4;
}

static ret_t fix_password(value_t* value) {
  return RET_OK;
}

static void* create_password_validator(void) {
  return value_validator_delegate_create(is_valid_password, fix_password);
}

ret_t password_validator_init(void) {
  value_validator_register("password", create_password_validator);

  return RET_OK;
}
