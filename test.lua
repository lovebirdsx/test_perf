-- performance_test.lua

-- 用于高精度计时

-- 记录时间的函数
local function now()
    return os.clock() * 1000 -- 转换为毫秒
end

-- CPU 测试：计算斐波那契数
local function cpu_test(n)
    local function fib(x)
        if x < 2 then
            return x
        else
            return fib(x - 1) + fib(x - 2)
        end
    end
    local start_time = now()
    fib(n)
    local end_time = now()
    return end_time - start_time
end

-- 内存测试：创建和操作大表
local function memory_test(size)
    local start_time = now()
    local t = {}
    for i = 1, size do
        t[i] = i
    end
    for i = 1, size do
        t[i] = t[i] * 2
    end
    local end_time = now()
    return end_time - start_time
end

-- I/O 测试：写入和读取大文件
local function io_test(filename, size_in_mb)
    local start_time = now()
    -- 写入
    local file = io.open(filename, "w")
    for i = 1, size_in_mb * 1024 do
        file:write(string.rep("a", 1024), "\n")
    end
    file:close()
    -- 读取
    file = io.open(filename, "r")
    for line in file:lines() do
        -- 读取每一行
    end
    file:close()
    -- 删除文件
    os.remove(filename)
    local end_time = now()
    return end_time - start_time
end

-- 字符串处理测试：大量字符串连接
local function string_test(count)
    local start_time = now()
    local s = ""
    for i = 1, count do
        s = s .. "a"
    end
    local end_time = now()
    return end_time - start_time
end

-- 运行所有测试
local function run_tests()
    local results = {}
    results.CPU_Test = cpu_test(25) -- 40阶斐波那契
    results.Memory_Test = memory_test(1000000) -- 100万元素
    results.IO_Test = io_test("test_io.lua", 50) -- 50MB
    results.String_Test = string_test(100000)
    
    -- 打印报告
    print(string.format("%-20s %-10s", "Test Type", "Cost(ms)"))
    print(string.rep("-", 30))
    local keys = {"CPU_Test", "Memory_Test", "IO_Test", "String_Test"}
    for _, test in ipairs(keys) do
        print(string.format("%-20s %-10.2f", test, results[test]))
    end
end

run_tests()
