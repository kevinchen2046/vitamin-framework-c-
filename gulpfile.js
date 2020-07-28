const { series } = require('gulp');
const logger=require('gulplog')
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
    function compare(files, history) {
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
        for (var file of files) {
            var modifiedTime = fs.statSync(file).mtimeMs;
            var index = getIndex(list, file);
            if (index >= 0) {
                //logger.info("history:", list[index], "cur:", modifiedTime)
                if (list[index].modifiedTime != modifiedTime) {
                    list[index].modifiedTime = modifiedTime
                    changed.push(list[index]);
                }
                list.splice(index, 1);
            } else {
                added.push({
                    file: file,
                    modifiedTime: modifiedTime
                });
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
    //读取编译记录
    var history = [];
    if (fs.existsSync('.compile')) {
        history = JSON.parse(fs.readFileSync('.compile', 'utf-8').toString())
    }
    //读取文件系统
    var files = Util.getFolderFiles("src", ".cpp");
    //获取链接库列表
    var results = compare(files, history);
    if (results.length) {
        //编译链接库
        for (var item of results) {
            logger.info(`[compile] now compile: ${item.file} >> ${item.file.replace('.cpp', '.o')} ...`)
            await Util.runCmd(`g++ -c ${item.file} -o ${item.file.replace('.cpp', '.o')}`);
            mergefiled += item.file.replace('.cpp', '.o') + " ";
        }
        //编译所有链接库
        var mergefiled = "";
        for (var item of history) {
            mergefiled += item.file.replace('.cpp', '.o') + " ";
        }
        logger.info(`[compile] create main.exe...`)
        await Util.runCmd(`g++ ${mergefiled} -o bin/main.exe`);
        logger.info("[compile] compile complete.");
    } else {
        logger.info("[compile] files not changed...");
    }
    //更新编译历史记录
    fs.writeFileSync('.compile', JSON.stringify(history), 'utf-8');
}

exports.compile = compile;
exports.default = series(compile);