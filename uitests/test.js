"use strict";

require("./helpers/setup");

let wd = require("wd"),
      _ = require('underscore'),
      Q = require('q'),
      serverConfigs = require('./helpers/appium-servers');
let startApp = require("./helpers/start-app").startApp;

const appName = '../bin/demo'
describe("awtk simple", function () {
      let driver;
      let allPassed = true;
      this.timeout(300000);

      before(async function () {
            let serverConfig = serverConfigs.local;
            driver = wd.promiseChainRemote(serverConfig);
            require("./helpers/logging").configure(driver);

            await startApp(appName);

            let desired = _.clone(require("./helpers/caps").awtk);
            return driver.init(desired);
      });

      after(function () {
         return driver.quit()
      });

      afterEach(function () {
            allPassed = allPassed && this.currentTest.state === 'passed';
      });

      it("home_admin_system_settings_time", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('settings').click().sleep(1000)
                  .elementById('current_window').text().should.become("System Settings")
                  .elementById('time').click().sleep(1000)
                  .elementById('current_window').text().should.become("Time Settings")
                  .elementById('cancel').click().sleep(1000)
                  .elementById('current_window').text().should.become("System Settings")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });

      it("home_admin_system_settings_about", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('settings').click().sleep(1000)
                  .elementById('current_window').text().should.become("System Settings")
                  .elementById('about').click().sleep(1000)
                  .elementById('current_window').text().should.become("About...")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("System Settings")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });

      it("home_admin_system_settings_user_manager", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('usermanager').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager")
                  .elementById('items').text().should.become("100002")
                  .elementById('filter').setText("1234").sleep(500)
                  .elementById('items').text().should.become("20")
                  .elementById('filter').setText("").sleep(500)
                  .elementById('items').text().should.become("100002")
                  .elementById('clear').click().sleep(1000)
                  .elementById('items').text().should.become("1")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });

      it("home_admin_system_settings_user_manager_add_cancel", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('usermanager').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager")
                  .elementById('clear').click().sleep(1000)
                  .elementById('add').click().sleep(1000)
                  .elementById('current_window').text().should.become("User New")
                  .elementById('name').setText("jim")
                  .elementById('cancel').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager")
                  .elementById('items').text().should.become("1")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });
      
      it("home_admin_system_settings_user_manager_add_ok", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('usermanager').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager")
                  .elementById('clear').click().sleep(1000)
                  .elementById('add').click().sleep(1000)
                  .elementById('current_window').text().should.become("User New")
                  .elementById('name').setText("lixianjing")
                  .elementById('name').text().should.become("lixianjing")
                  .elementById('nick_name').setText("jim")
                  .elementById('nick_name').text().should.become("jim")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('confirm_password').setText("1234")
                  .elementById('confirm_password').text().should.become("1234")
                  .elementById('add').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager")
                  .elementById('items').text().should.become("2")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });


      it("home_admin_system_settings_my_profile", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .elementById('user_home').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Home")
                  .elementById('name').text().should.become("admin")
                  .elementById('nick_name').text().should.become("Administrator")
                  .elementById('change_password').click().sleep(1000)

                  .elementById('current_window').text().should.become("Change Password")
                  .elementById('old_password').setText("1234")
                  .elementById('old_password').text().should.become("1234")
                  .elementById('new_password').setText("abcd")
                  .elementById('new_password').text().should.become("abcd")
                  .elementById('confirm_password').setText("abcd")
                  .elementById('confirm_password').text().should.become("abcd")
                  .elementById('change').click().sleep(3000)
                  
                  .elementById('current_window').text().should.become("User Manager System")
                  
                  .elementById('user').setText("admin")
                  .elementById('user').text().should.become("admin")
                  .elementById('password').setText("abcd")
                  .elementById('password').text().should.become("abcd")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });

      it("normal_user", function () {
            return driver.elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("lixianjing")
                  .elementById('user').text().should.become("lixianjing")
                  .elementById('password').setText("1234")
                  .elementById('password').text().should.become("1234")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Home")
                  .elementById('name').text().should.become("lixianjing")
                  .elementById('nick_name').text().should.become("jim")
                  .elementById('change_password').click().sleep(1000)
                  .elementById('current_window').text().should.become("Change Password")
                  .elementById('old_password').setText("1234")
                  .elementById('old_password').text().should.become("1234")
                  .elementById('new_password').setText("abcd")
                  .elementById('new_password').text().should.become("abcd")
                  .elementById('confirm_password').setText("abcd")
                  .elementById('confirm_password').text().should.become("abcd")
                  .elementById('change').click().sleep(3000)
                  
                  .elementById('current_window').text().should.become("User Manager System")
                  .elementById('user').setText("lixianjing")
                  .elementById('user').text().should.become("lixianjing")
                  .elementById('password').setText("abcd")
                  .elementById('password').text().should.become("abcd")
                  .elementById('ok').click().sleep(1000)
                  .elementById('current_window').text().should.become("User Home")
                  .back().sleep(1000)
                  .elementById('current_window').text().should.become("User Manager System")
      });
});
