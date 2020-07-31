const { series } = require('gulp');
const logger = require('gulplog')
const fs = require('fs');
const path = require('path');

class Util {
    static getFolderFiles(folderpath, extension) {
        var extensions = [];
        if (extension) {
            (extension.indexOf("|") > 0) ? extensions = extension.split("|") : extensions.push(extension);
        }
        if (!fs.existsSync(folderpath)) return [];
        var results = [];
        var files = fs.readdirSync(folderpath);
        for (var name of files) {
            var curPath = folderpath + '/' + name;
            if (fs.statSync(curPath).isDirectory()) {
                results = results.concat(Util.getFolderFiles(curPath, extension));
            } else {
                if (extensions.length) {
                    if (extensions.indexOf(path.extname(name)) == -1) continue;
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
                //logger.info(iconv.decode(data,'gbk'));
                logger.info(data.toString());
            }
            function stderrHandler(data) {
                //logger.info(iconv.decode(data,'gbk'));	
                logger.info(data.toString());
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
    //对比文件系统和历史记录
    function compare(systemFiles, history) {
        var list = history.concat();
        function getIndex(list, file) {
            for (var i = 0; i < list.length; i++) {
                if (list[i].file == file) {
                    return i;
                }
            }
            return -1;
        }
        //变更列表
        var changed = [];
        //新文件列表
        var added = [];
        for (var name in systemFiles) {
            var info = systemFiles[name];
            for (var ext in info) {
                var filePath = info[ext];
                var modifiedTime = fs.statSync(filePath).mtimeMs;
                var index = getIndex(list, filePath);
                if (index >= 0) {
                    //logger.info("history:", list[index], "cur:", modifiedTime)
                    if (list[index].modifiedTime != modifiedTime) {
                        list[index].modifiedTime = modifiedTime
                        changed.push(list[index]);
                    }
                    list.splice(index, 1);
                } else {
                    added.push({
                        file: filePath,
                        modifiedTime: modifiedTime
                    });
                }
            }
        }
        //移除列表
        var resmoved = list.concat();
        for (var item of resmoved) {
            for (var i = 0; i < history.length; i++) {
                if (history[i] == item) {
                    history.splice(i, 1);
                    break;
                }
            }
        }
        //添加新文件到记录
        history.push(...added);
        //返回变更和新文件合并的列表
        return changed.concat(added);
    }

    async function createO(file, records) {
        logger.info(`[compile] now compile: ${file} >> ${file.replace('.cpp', '.o')} ...`)
        await Util.runCmd(`g++ -c ${file} -o ${file.replace('.cpp', '.o')}`);
        if (records) records += file + " ";
        return records;
    }

    //读取编译记录
    var history = [];
    if (fs.existsSync('.compile')) {
        history = JSON.parse(fs.readFileSync('.compile', 'utf-8').toString())
    }
    //读取文件系统
    var files = Util.getFolderFiles("src", ".cpp|.h");
    var systemFiles = [];
    for (var file of files) {
        var name = path.basename(file)
        var ext = path.extname(file)
        if (!systemFiles[name]) systemFiles[name] = {};
        systemFiles[name][ext] = file;
    }
    //获取链接库列表
    var results = compare(systemFiles, history);
    if (results.length) {
        var actionhistory = [];
        //编译链接库
        for (var item of results) {
            if (item.file.indexOf('src/main.cpp') >= 0) continue;
            if (actionhistory.indexOf(item.file) >= 0) continue;
            if (path.extname(item.file) == '.h') {
                var cppPath = item.file.replace('.h', '.cpp');
                if (fs.existsSync(cppPath)) {
                    await createO(cppPath);
                    actionhistory.push(cppPath);
                }
            } else if (path.extname(item.file) == '.cpp') {
                await createO(item.file);
                actionhistory.push(item.file);
            }
        }
    }
    //编译所有链接库
    var mergefiled = "";
    for (var item of history) {
        if(path.extname(item.file)==".h") continue;
        mergefiled += item.file.replace('.cpp', '.o') + " ";
    }
    if (!fs.existsSync('./bin')) {
        fs.mkdirSync("./bin");
    }
    logger.info(`[compile] now compile: src/main.cpp >> src/main.o ...`)
    await Util.runCmd(`g++ -c src/main.cpp -o src/main.o`);
    logger.info(`[compile] create main.exe... {${mergefiled}}`);
    await Util.runCmd(`g++ ${mergefiled} -o bin/main.exe`);
    logger.info("[compile] compile complete.");
    //更新编译历史记录
    fs.writeFileSync('.compile', JSON.stringify(history), 'utf-8');
}
async function compileforce() {
    //读取文件系统
    var files = Util.getFolderFiles("src", ".cpp");
    //编译链接库
    for (var file of files) {
        if (file.indexOf('src/main.cpp') >= 0) continue;
        logger.info(`[compile] now compile: ${file} >> ${file.replace('.cpp', '.o')} ...`)
        await Util.runCmd(`g++ -c ${file} -o ${file.replace('.cpp', '.o')}`);
        mergefiled += file.replace('.cpp', '.o') + " ";
    }
    //编译所有链接库
    var mergefiled = "";
    for (var file of files) {
        mergefiled += file.replace('.cpp', '.o') + " ";
    }
    if (!fs.existsSync('./bin')) {
        fs.mkdirSync("./bin");
    }
    logger.info(`[compile] now compile: src/main.cpp >> src/main.o ...`)
    await Util.runCmd(`g++ -c src/main.cpp -o src/main.o`);
    logger.info(`[compile] create main.exe... {${mergefiled}}`);
    await Util.runCmd(`g++ ${mergefiled} -o bin/main.exe`);
    logger.info("[compile] compile complete.");
    //更新编译历史记录
    //fs.writeFileSync('.compile', JSON.stringify(history), 'utf-8');
}
exports.compileforce = compileforce;
exports.compile = compile;
exports.default = series(compile);