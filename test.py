# performance_test.py

import time
import sys
import re

# 记录时间的函数
def now():
    return time.perf_counter() * 1000  # 毫秒

# CPU 测试：计算斐波那契数
def cpu_test(n):
    def fib(x):
        if x < 2:
            return x
        else:
            return fib(x-1) + fib(x-2)
    start = now()
    fib(n)
    end = now()
    return end - start

# 内存测试：创建和操作大列表
def memory_test(size):
    start = now()
    lst = list(range(size))
    lst = [x * 2 for x in lst]
    end = now()
    return end - start

# I/O 测试：写入和读取大文件
def io_test(filename, size_in_mb):
    start = now()
    # 写入
    with open(filename, 'w') as f:
        for _ in range(size_in_mb):
            f.write('a' * 1024 + '\n')
    # 读取
    with open(filename, 'r') as f:
        for _ in f:
            pass
    # 删除文件
    import os
    os.remove(filename)
    end = now()
    return end - start

# 字符串处理测试：大量字符串连接
def string_test(count):
    start = now()
    s = ''
    for _ in range(count):
        s += 'a'
    end = now()
    return end - start

# 打印报告
def print_report(results):
    print(f"{'Test Type':<20} {'Cost(ms)':<10}")
    print('-' * 30)
    for test, time_taken in results.items():
        print(f"{test:<20} {time_taken:<10.2f}")

# 运行所有测试
def run_tests():
    results = {}
    results['CPU_Test'] = cpu_test(25)  # 35阶斐波那契
    results['Memory_Test'] = memory_test(1000000)  # 100万元素
    results['IO_Test'] = io_test('test_io.py', 50)  # 50MB
    results['String_Test'] = string_test(100000)
    
    print_report(results)

if __name__ == "__main__":
    run_tests()
