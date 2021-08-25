#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "mvvm/base/navigator.h"

#include "user_add.h"
#include "common/app_globals.h"

/***************user_add***************/;

user_add_t* user_add_create(void) {
  user_add_t* user_add = TKMEM_ZALLOC(user_add_t);
  return_value_if_fail(user_add != NULL, NULL);

  str_init(&(user_add->name), 10);
  str_init(&(user_add->nick_name), 10);
  str_init(&(user_add->password), 10);
  str_init(&(user_add->confirm_password), 10);

  return user_add;
}

ret_t user_add_destroy(user_add_t* user_add) {
  return_value_if_fail(user_add != NULL, RET_BAD_PARAMS);

  str_reset(&(user_add->name));
  str_reset(&(user_add->nick_name));
  str_reset(&(user_add->password));
  str_reset(&(user_add->confirm_password));

  TKMEM_FREE(user_add);

  return RET_OK;
}

bool_t user_add_can_add(user_add_t* user_add) {
  return user_add->name.size > 0 && user_add->password.size > 0 &&
         str_eq(&(user_add->password), user_add->confirm_password.str);
}

ret_t user_add_add(user_add_t* user_add) {
  value_t v;
  object_t* user = NULL;
  user_repository_t* r = app_globals_get_user_repository();

  if (user_repository_find_by_name(r, user_add->name.str) != NULL) {
    navigator_toast("User exist.", 3000);

    return RET_OK;
  }

  user = user_create();
  user_t* user_user = USER(user);
  value_set_pointer(&v, user);

  str_set(&(user_user->name), user_add->name.str);
  str_set(&(user_user->nick_name), user_add->nick_name.str);
  str_set(&(user_user->password), user_add->confirm_password.str);
  if (user_repository_add(r, user) != RET_OK) {
    log_debug("add user failed.\n");
  }
  OBJECT_UNREF(user);
  navigator_back();

  return RET_OK;
}
