#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"

#include "login.h"
#include "app_globals.h"


/***************login***************/;

static inline login_t* login_create(void) {
  login_t* login = TKMEM_ZALLOC(login_t);
  return_value_if_fail(login != NULL, NULL);

  str_init(&(login->name), 10);
  str_init(&(login->password), 10);


  return login;
} 

static inline ret_t login_destroy(login_t* login) {
  return_value_if_fail(login != NULL, RET_BAD_PARAMS);

  str_reset(&(login->name));
  str_reset(&(login->password));


  TKMEM_FREE(login);

  return RET_OK;
}

static bool_t login_can_exec_auth(login_t* login, const char* args) {
  return login->name.size > 0 && login->password.size > 0;
}

static ret_t login_auth(login_t* login, const char* args) {
  user_repository_t* r = app_globals_get_user_repository();
  user_t* user = user_repository_find_by_name(r, login->name.str);
  return_value_if_fail(user != NULL, RET_OK);

  if(user_auth(user, login->password.str) == RET_OK) {

  }

  return RET_OK;
}

/***************login_view_model***************/

static ret_t login_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  login_view_model_t* vm = (login_view_model_t*)(obj);
  login_t* login = vm->login;

  if (tk_str_eq("name", name)) {
    str_from_value(&(login->name), v);
  } else if (tk_str_eq("password", name)) {
    str_from_value(&(login->password), v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static ret_t login_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  login_view_model_t* vm = (login_view_model_t*)(obj);
  login_t* login = vm->login;

  if (tk_str_eq("name", name)) {
    value_set_str(v, login->name.str);
  } else if (tk_str_eq("password", name)) {
    value_set_str(v, login->password.str);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static bool_t login_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  login_view_model_t* vm = (login_view_model_t*)(obj);
  login_t* login = vm->login;

  if (tk_str_eq("auth", name)) {
    return login_can_exec_auth(login, args);
  } else {
    return FALSE;
  }
}

static ret_t login_view_model_exec(object_t* obj, const char* name, const char* args) {
  login_view_model_t* vm = (login_view_model_t*)(obj);
  login_t* login = vm->login;

  if (tk_str_eq("auth", name)) {
    return login_auth(login, args);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
}

static ret_t login_view_model_on_destroy(object_t* obj) {
  login_view_model_t* vm = (login_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);

  login_destroy(vm->login);

  return view_model_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_login_view_model_vtable = {
  .type = "login",
  .desc = "user login",
  .size = sizeof(login_view_model_t),
  .exec = login_view_model_exec,
  .can_exec = login_view_model_can_exec,
  .get_prop = login_view_model_get_prop,
  .set_prop = login_view_model_set_prop,
  .on_destroy = login_view_model_on_destroy
};

view_model_t* login_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_login_view_model_vtable);
  view_model_t* vm = view_model_init(VIEW_MODEL(obj));
  login_view_model_t* login_view_model = (login_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  login_view_model->login = login_create();
  ENSURE(login_view_model->login != NULL);

  return vm;
}
