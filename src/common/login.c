#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "mvvm/base/navigator.h"

#include "login.h"
#include "app_globals.h"

/***************login***************/;

login_t* login_create(void) {
  login_t* login = TKMEM_ZALLOC(login_t);
  return_value_if_fail(login != NULL, NULL);

  str_init(&(login->name), 10);
  str_init(&(login->password), 10);
  str_set(&(login->name), "admin");
  str_set(&(login->password), "1234");

  return login;
}

ret_t login_destroy(login_t* login) {
  return_value_if_fail(login != NULL, RET_BAD_PARAMS);

  str_reset(&(login->name));
  str_reset(&(login->password));

  TKMEM_FREE(login);

  return RET_OK;
}

bool_t login_can_auth(login_t* login) {
  if (login->name.size > 0 && login->password.size > 0) {
      user_repository_t* r = app_globals_get_user_repository();
      object_t* user = user_repository_find_by_name(r, login->name.str);
      if (user != NULL) {
          return TRUE;
      }
  }
  
  return FALSE;
}

static ret_t login_navigator_to(const char* target, object_t* user) {
  navigator_request_t* req = navigator_request_create(target, NULL);
  return_value_if_fail(req != NULL, RET_OOM);

  object_set_prop_pointer(OBJECT(req), REQ_ARG_USER, user);
  navigator_to_ex(req);
  object_unref(OBJECT(req));

  return RET_OK;
}

ret_t login_auth(login_t* login) {
  user_repository_t* r = app_globals_get_user_repository();
  object_t* user = user_repository_find_by_name(r, login->name.str);
  user_t* user_user = USER(user);
  return_value_if_fail(user_user != NULL, RET_OK);

  if (user_auth(user, login->password.str) == RET_OK) {
    user_user->last_login_time = time(0);
    if (user_is_admin(user)) {
      navigator_to("admin_home");
    } else {
      login_navigator_to("user_home", user);
    }
    app_globals_set_current_user(user);
    user_repository_update(r, user);
  } else {
    navigator_toast("Invalid user or password!", 3000);
  }

  return RET_OK;
}
