var path = require('path');
var fs = require('fs');
const { spawn } = require('child_process');

async function startApp(app) {
  let options = {};
  const filename = path.normalize(path.resolve(app));
  options.cwd = path.dirname(path.dirname(filename)); 

  console.log("cwd: " + options.cwd);
  console.log("start app: " + filename);

  const child = spawn(filename, [], options);
  process.stdin.pipe(child.stdin)

  const logName = path.basename(filename) + '.log'
  const log = fs.openSync(logName, 'w+');
  
  child.on('error', function (code, signal) {
    console.log(filename + ' error');
    fs.closeSync(log);
  });
  child.on('exit', function (code, signal) {
    console.log(filename + ` exited ${code} ${signal}`);
    fs.closeSync(log);
  });

  child.stdout.on('data', (data) => {
    fs.writeSync(log, data);
    fs.fsyncSync(log);
  });

  await new Promise(r => setTimeout(r, 5000));
}

exports.startApp = startApp;
