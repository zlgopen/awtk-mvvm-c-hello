﻿/**
 * File:   app_globals.c
 * Author: AWTK Develop Team
 * Brief:  app_globals
 *
 * Copyright (c) 2018 - 2019  Guangzhou ZHIYUAN Electronics Co.,Ltd.
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
 * 2019-11-01 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "app_globals.h"

static app_globals_t s_globals;

ret_t app_globals_init(user_repository_t* user_repository) {
  return_value_if_fail(s_globals.user_repository == NULL && user_repository != NULL, RET_FAIL);

  s_globals.user_repository = user_repository;
  user_repository_load(s_globals.user_repository);

  return RET_OK;
}

ret_t app_globals_deinit(void) {
  return_value_if_fail(s_globals.user_repository != NULL, RET_OOM);

  if (s_globals.current_user != NULL) {
    OBJECT_UNREF(s_globals.current_user);
  }

  OBJECT_UNREF(s_globals.user_repository);
  memset(&s_globals, 0x00, sizeof(s_globals));

  return RET_OK;
}

user_repository_t* app_globals_get_user_repository(void) {
  return s_globals.user_repository;
}

ret_t app_globals_set_current_user(object_t* user) {
  if (s_globals.current_user != NULL) {
    OBJECT_UNREF(s_globals.current_user);
  }

  s_globals.current_user = user_dup(user);

  return RET_OK;
}

object_t* app_globals_get_current_user(void) {
  return s_globals.current_user;
}
