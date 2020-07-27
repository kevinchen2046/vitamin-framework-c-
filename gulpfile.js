const { series } = require('gulp');
const fs = require('fs');
const path = require('path');

class Util {
    static getFolderFiles(folderpath, extension) {
        if (!fs.existsSync(folderpath)) return [];
        var results = [];
        var files = fs.readdirSync(folderpath);
        for (var name of files) {
            var curPath = folderpath + '/' + name;
            if (fs.statSync(curPath).isDirectory()) {
                results = results.concat(Util.getFolderFiles(curPath, extension));
            } else {
                if (extension != undefined) {
                    if (path.extname(name) != extension) continue;
                }
                results.push(curPath);
            }
        }
        return results;
    }

    static async runCmd(cmd, method) {
        return new Promise((relove, reject) => {
            var childProcess = require('child_process');
            //var iconv = require('iconv-lite');
            var handler = childProcess.exec(cmd, {
                encoding: 'buffer',
                timeout: 0, /*子进程最长执行时间 */
                maxBuffer: 1024 * 1024
            });
            function stdotHandler(data) {
                //console.log(iconv.decode(data,'gbk'));
                console.log(data.toString());
            }
            function stderrHandler(data) {
                //console.log(iconv.decode(data,'gbk'));	
                console.log(data.toString());
            }
            function exitHandler(code) {
                handler.stdout.removeListener('data', stdotHandler);
                handler.stderr.removeListener('data', stderrHandler);
                handler.removeListener('exit', exitHandler);
                if (code == 0) {
                    relove();
                    if (method) method();
                } else {
                    reject();
                }
            }
            handler.stdout.on('data', stdotHandler);
            handler.stderr.on('data', stderrHandler);
            handler.on('exit', exitHandler);
        });
    }
}

async function compile() {
    var files = ['main.cpp'].concat(Util.getFolderFiles("src", ".cpp"));
    var mergefiled = "";
    for (var file of files) {
        console.log(`编译: ${file} >> ${file.replace('.cpp', '.o')} ...`)
        await Util.runCmd(`g++ -c ${file} -o ${file.replace('.cpp', '.o')}`);
        mergefiled += file.replace('.cpp', '.o') + " ";
    }
    console.log(`生成 main.exe...`)
    await Util.runCmd(`g++ ${mergefiled} -o main.exe`);
    console.log("编译完成.");
}

exports.compile = compile;
exports.default = series(compile);