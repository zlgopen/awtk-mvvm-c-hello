/**
 * File:   application.c
 * Author: AWTK Develop Team
 * Brief:  application
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
 * 2019-10-29 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "mvvm/mvvm.h"
#include "view_models/login.h"
#include "view_models/user_info.h"
#include "common/app_globals.h"

ret_t application_init() {
  app_globals_init();

  view_model_factory_register("login", login_view_model_create);
  view_model_factory_register("user_info", user_info_view_model_create);

  return navigator_to("login");
}

#include "awtk_main.c"
