#include "tkc/mem.h"
#include "tkc/utils.h"
#include "mvvm/base/utils.h"
#include "users.h"

static bool_t user_can_exec_view(user_t* user, const char* args) {
  return TRUE;
}

static ret_t user_view(user_t* user, const char* args) {
  
  return RET_OBJECT_CHANGED;
}


static bool_t user_can_exec_edit(user_t* user, const char* args) {
  return TRUE;
}

static ret_t user_edit(user_t* user, const char* args) {
  
  return RET_OBJECT_CHANGED;
}


/***************users_view_model***************/

ret_t users_view_model_remove(view_model_t* view_model, uint32_t index) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, RET_BAD_PARAMS);

  return darray_remove_index(&(user_vm->users), index);
}

ret_t users_view_model_add(view_model_t* view_model, user_t* user) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL && user != NULL, RET_BAD_PARAMS);

  return darray_push(&(user_vm->users), user);
}

uint32_t users_view_model_size(view_model_t* view_model) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, 0); 

  return user_vm->users.size;
}

ret_t users_view_model_clear(view_model_t* view_model) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, 0); 

  return darray_clear(&(user_vm->users));
}

user_t* users_view_model_get(view_model_t* view_model, uint32_t index) {
  users_view_model_t* user_vm = (users_view_model_t*)(view_model);
  return_value_if_fail(user_vm != NULL, 0); 

  return_value_if_fail(user_vm != NULL && index < users_view_model_size(view_model), NULL);

  return (user_t*)(user_vm->users.elms[index]);
}

static ret_t users_view_model_set_prop(object_t* obj, const char* name, const value_t* v) {
  uint32_t index = 0;
  user_t* user = NULL;
  view_model_t* vm = VIEW_MODEL(obj);

  if (tk_str_eq(VIEW_MODEL_PROP_CURSOR, name)) {
    view_model_array_set_cursor(vm, value_int(v));

    return RET_OK;
  }

  name = destruct_array_prop_name(name, &index);
  return_value_if_fail(name != NULL, RET_BAD_PARAMS);
  user = users_view_model_get(vm, index);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_eq("name", name)) {
    str_from_value(&(user->name), v);
  } else if (tk_str_eq("nick_name", name)) {
    str_from_value(&(user->nick_name), v);
  } else if (tk_str_eq("password", name)) {
    str_from_value(&(user->password), v);
  } else if (tk_str_eq("registered_time", name)) {
    user->registered_time =  value_uint32(v);
  } else if (tk_str_eq("last_login_time", name)) {
    user->last_login_time =  value_uint32(v);
  } else if (tk_str_eq("expired_time", name)) {
    user->expired_time =  value_uint32(v);
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static ret_t users_view_model_get_prop(object_t* obj, const char* name, value_t* v) {
  uint32_t index = 0;
  user_t* user = NULL;
  view_model_t* vm = VIEW_MODEL(obj);

  if (tk_str_eq(VIEW_MODEL_PROP_ITEMS, name)) {
    value_set_int(v, users_view_model_size(VIEW_MODEL(obj)));

    return RET_OK;
  } else if (tk_str_eq(VIEW_MODEL_PROP_CURSOR, name)) {
    value_set_int(v, VIEW_MODEL_ARRAY(obj)->cursor);

    return RET_OK;
  }

  name = destruct_array_prop_name(name, &index);
  return_value_if_fail(name != NULL, RET_BAD_PARAMS);
  user = users_view_model_get(vm, index);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_eq("name", name)) {
    value_set_str(v, user->name.str);
  } else if (tk_str_eq("nick_name", name)) {
    value_set_str(v, user->nick_name.str);
  } else if (tk_str_eq("password", name)) {
    value_set_str(v, user->password.str);
  } else if (tk_str_eq("registered_time", name)) {
    value_set_uint32(v, user->registered_time);
  } else if (tk_str_eq("last_login_time", name)) {
    value_set_uint32(v, user->last_login_time);
  } else if (tk_str_eq("expired_time", name)) {
    value_set_uint32(v, user->expired_time);
  } else if (tk_str_eq("style", name)) {
    value_set_str(v, index % 2 ? "odd" : "even");
  } else {
    log_debug("not found %s\n", name);
    return RET_NOT_FOUND;
  }
  
  return RET_OK;
}


static bool_t users_view_model_can_exec(object_t* obj, const char* name, const char* args) {
  uint32_t index = tk_atoi(args);
  view_model_t* vm = VIEW_MODEL(obj);
  user_t* user = NULL;

  if (tk_str_ieq(name, "add")) {
    return TRUE;
  } else if (tk_str_ieq(name, "clear")) {
    return users_view_model_size(vm) > 0;
  }

  user = users_view_model_get(vm, index);
  return_value_if_fail(user != NULL, FALSE);

  if (tk_str_ieq(name, "remove")) {
    return index < users_view_model_size(vm);
  } else if (tk_str_eq("view", name)) {
    return user_can_exec_view(user, args);
  } else if (tk_str_eq("edit", name)) {
    return user_can_exec_edit(user, args);
  } else {
    return FALSE;
  }
}

static ret_t users_view_model_exec(object_t* obj, const char* name, const char* args) {
  uint32_t index = tk_atoi(args);
  view_model_t* vm = VIEW_MODEL(obj);
  user_t* user = NULL;

  if (tk_str_ieq(name, "add")) {
    ENSURE(users_view_model_add(vm, user_create()) == RET_OK);
    return RET_ITEMS_CHANGED;
  } else if (tk_str_ieq(name, "clear")) {
    ENSURE(users_view_model_clear(vm) == RET_OK);
    return RET_ITEMS_CHANGED;
  }

  user = users_view_model_get(vm, index);
  return_value_if_fail(user != NULL, RET_BAD_PARAMS);

  if (tk_str_ieq(name, "remove")) {
    ENSURE(users_view_model_remove(vm, index) == RET_OK);
    return RET_ITEMS_CHANGED;
  } else if (tk_str_eq("view", name)) {
    return user_view(user, args);
  } else if (tk_str_eq("edit", name)) {
    return user_edit(user, args);
  } else {
    log_debug("not found %s\
", name);
    return RET_NOT_FOUND;
  }
}

static ret_t users_view_model_on_destroy(object_t* obj) {
  users_view_model_t* vm = (users_view_model_t*)(obj);
  return_value_if_fail(vm != NULL, RET_BAD_PARAMS);
  
  users_view_model_clear(VIEW_MODEL(obj));
  darray_deinit(&(vm->users));

  return view_model_array_deinit(VIEW_MODEL(obj));
}

static const object_vtable_t s_users_view_model_vtable = {
  .type = "user",
  .desc = "user manager",
  .is_collection = TRUE,
  .size = sizeof(users_view_model_t),
  .exec = users_view_model_exec,
  .can_exec = users_view_model_can_exec,
  .get_prop = users_view_model_get_prop,
  .set_prop = users_view_model_set_prop,
  .on_destroy = users_view_model_on_destroy
};

view_model_t* users_view_model_create(navigator_request_t* req) {
  object_t* obj = object_create(&s_users_view_model_vtable);
  view_model_t* vm = view_model_array_init(VIEW_MODEL(obj));
  users_view_model_t* user_vm = (users_view_model_t*)(vm);

  return_value_if_fail(vm != NULL, NULL);

  darray_init(&(user_vm->users), 100, 
    (tk_destroy_t)user_destroy, (tk_compare_t)user_cmp);

  return vm;
}
