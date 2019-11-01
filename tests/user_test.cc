#include "common/user.h"
#include "gtest/gtest.h"

TEST(User, basic) {
  user_t* u1 = user_create();
  user_t* u2 = user_create();

  str_set(&(u1->name), "admin");
  str_set(&(u2->name), "awtk");

  ASSERT_EQ(user_equal(u1, u1), TRUE);
  ASSERT_EQ(user_equal(u2, u2), TRUE);
  ASSERT_EQ(user_equal(u1, u2), FALSE);
  ASSERT_EQ(user_copy(u1, u2), u1);
  ASSERT_EQ(user_equal(u1, u2), TRUE);

  user_destroy(u1);
  user_destroy(u2);
}
