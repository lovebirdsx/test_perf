// performance_test.js
const fs = require('fs');

// 记录时间的函数
function now() {
    return process.hrtime.bigint() / BigInt(1e6); // 毫秒
}

// CPU 测试：计算斐波那契数
function cpuTest(n) {
    function fib(x) {
        if (x < 2) return x;
        return fib(x - 1) + fib(x - 2);
    }
    const start = now();
    fib(n);
    const end = now();
    return end - start;
}

// 内存测试：创建和操作大数组
function memoryTest(size) {
    const start = now();
    let arr = [];
    for (let i = 0; i < size; i++) {
        arr[i] = i;
    }
    for (let i = 0; i < size; i++) {
        arr[i] = arr[i] * 2;
    }
    const end = now();
    return end - start;
}

// I/O 测试：写入和读取大文件
function ioTest(filename, sizeInMB) {
    return new Promise((resolve, reject) => {
        const start = now();
        // 写入
        const writeStream = fs.createWriteStream(filename);
        for (let i = 0; i < sizeInMB; i++) {
            writeStream.write('a'.repeat(1024) + '\n');
        }
        writeStream.end();
        writeStream.on('finish', () => {
            // 读取
            fs.readFile(filename, 'utf8', (err, data) => {
                if (err) {
                    reject(err);
                    return;
                }

                // 删除文件
                fs.unlinkSync(filename);
                const end = now();
                ioDuration = end - start;
                resolve(ioDuration);
            });
        });
    });
}

// 字符串处理测试：大量字符串连接
function stringTest(count) {
    const start = now();
    let s = '';
    for (let i = 0; i < count; i++) {
        s += 'a';
    }
    const end = now();
    return end - start;
}

// 打印报告
function printReport(results) {
    console.log(`${'JS 测试项'.padEnd(20)} ${'耗时(ms)'.padEnd(10)}`);
    console.log('-'.repeat(30));
    for (const [test, time] of Object.entries(results)) {
        console.log(`${test.padEnd(20)} ${time}`);
    }
}

// 运行所有测试
async function runTests() {
    let results = {};
    results.CPU_Test = cpuTest(40); // 40阶斐波那契
    results.Memory_Test = memoryTest(1000000); // 100万元素
    // I/O 测试需要异步处理
    results.IO_Test = await ioTest('test_io.js', 50);
    results.String_Test = stringTest(100000);
    printReport(results);
}

runTests();
