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
            return driver.elementById('current_window')
                  .text().should.become("User Manager System")
                  .elementById('user')
                  .setText("admin")
                  .elementById('user')
                  .text().should.become("admin")
                  .elementById('password')
                  .setText("1234")
                  .elementById('password')
                  .text().should.become("1234")
                  .elementById('ok')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("Amin Home")
                  .sleep(1000)
                  .elementById('settings')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("System Settings")
                  .elementById('time')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("Time Settings")
                  .elementById('cancel')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("System Settings")
                  .back().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("User Manager System")
      });

      it("home_admin_system_settings_about", function () {
            return driver.elementById('current_window')
                  .text().should.become("User Manager System")
                  .elementById('user')
                  .setText("admin")
                  .elementById('user')
                  .text().should.become("admin")
                  .elementById('password')
                  .setText("1234")
                  .elementById('password')
                  .text().should.become("1234")
                  .elementById('ok')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("Amin Home")
                  .sleep(1000)
                  .elementById('settings')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("System Settings")
                  .elementById('about')
                  .click().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("About...")
                  .back().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("System Settings")
                  .back().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("Amin Home")
                  .back().sleep(1000)
                  .elementById('current_window')
                  .text().should.become("User Manager System")
      });
});
