#include "tkc/mem.h"
#include "tkc/utils.h"
#include "user_info.h"
#include "common/app_globals.h"

user_info_t* user_info_create(navigator_request_t* req) {
  user_info_t* user_info = TKMEM_ZALLOC(user_info_t);
  object_t* user = (object_t*)object_get_prop_pointer(OBJECT(req), REQ_ARG_USER);

  return_value_if_fail(user_info != NULL, NULL);

  str_init(&(user_info->name), 10);
  str_init(&(user_info->nick_name), 10);
  str_init(&(user_info->password), 10);

  if (user == NULL) {
    user = app_globals_get_current_user();
  }

  user_t* user_user = USER(user);
  str_set(&(user_info->name), user_user->name.str);
  str_set(&(user_info->nick_name), user_user->nick_name.str);
  str_set(&(user_info->password), user_user->password.str);
  user_info->registered_time = user_user->registered_time;
  user_info->last_login_time = user_user->last_login_time;

  return user_info;
}

ret_t user_info_destroy(user_info_t* user_info) {
  return_value_if_fail(user_info != NULL, RET_BAD_PARAMS);

  str_reset(&(user_info->name));
  str_reset(&(user_info->nick_name));
  str_reset(&(user_info->password));

  TKMEM_FREE(user_info);

  return RET_OK;
}
