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

#ifndef AWTK_WEB
#include "automation_agent/automation_agent.h"
#endif/*AWTK_WEB*/

#include "view_models/users_view_model.h"
#include "view_models/login_view_model.h"
#include "view_models/user_add_view_model.h"
#include "view_models/user_info_view_model.h"
#include "view_models/product_info_view_model.h"
#include "view_models/time_settings_view_model.h"
#include "view_models/change_password_view_model.h"
#include "assets.inc"
#include "common/app_globals.h"
#include "common/password_validator.h"
#include "common/user_repository_mem.h"
#include "common/datetime_str_converter.h"

#include "table_view_register.h"
#include "slidable_row_register.h"
#include "table_client_custom_binder.h"

ret_t application_init() {
  mvvm_init();
#ifndef AWTK_WEB
  socket_init();
  automation_agent_start(8000);
#endif/*AWTK_WEB*/

  table_view_register();
  slidable_row_register();
  table_client_custom_binder_register();
  password_validator_init();
  datetime_str_converter_init();
  app_globals_init(user_repository_mem_create());
 
#if !defined(ANDROID) && !defined(IOS)
  window_open("system_bar");
#endif

  view_model_factory_register("users", users_view_model_create);
  view_model_factory_register("login", login_view_model_create);
  view_model_factory_register("user_add", user_add_view_model_create);
  view_model_factory_register("user_info", user_info_view_model_create);
  view_model_factory_register("product_info", product_info_view_model_create);
  view_model_factory_register("time_settings", time_settings_view_model_create);
  view_model_factory_register("change_password", change_password_view_model_create);
  
  return navigator_to("login");
}

#include "mvvm/mvvm.h"

ret_t application_exit() {
  log_debug("application_exit\n");
#ifndef AWTK_WEB
  automation_agent_stop();
  socket_deinit();
#endif/*AWTK_WEB*/
  mvvm_deinit();
  return RET_OK;
}

#include "awtk_main.inc"
