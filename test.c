// performance_test.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 获取当前时间（毫秒）
double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

// CPU 测试：计算斐波那契数
long long fib(int n) {
    if (n < 2) return n;
    return fib(n-1) + fib(n-2);
}

double cpu_test(int n) {
    double start = get_time_ms();
    fib(n);
    double end = get_time_ms();
    return end - start;
}

// 内存测试：创建和操作大数组
double memory_test(int size) {
    double start = get_time_ms();
    int *arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        arr[i] = i;
    }
    for(int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
    free(arr);
    double end = get_time_ms();
    return end - start;
}

// I/O 测试：写入和读取大文件
double io_test(const char *filename, int size_in_mb) {
    double start = get_time_ms();
    // 写入
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("File open for writing failed");
        exit(1);
    }
    char buffer[1025];
    memset(buffer, 'a', 1024);
    buffer[1024] = '\n';
    for(int i = 0; i < size_in_mb; i++) {
        fwrite(buffer, 1, 1025, f);
    }
    fclose(f);
    // 读取
    f = fopen(filename, "r");
    if (!f) {
        perror("File open for reading failed");
        exit(1);
    }
    while(fgets(buffer, sizeof(buffer), f));
    fclose(f);
    // 删除文件
    remove(filename);
    double end = get_time_ms();
    return end - start;
}

// 字符串处理测试：大量字符串连接
double string_test(int count) {
    double start = get_time_ms();
    char *s = malloc(count + 1);
    
    for(int i = 0; i < count; i++) {
        s[i] = 'a';
    }
    s[count] = '\0'; // 添加字符串终止符

    double end = get_time_ms();
    free(s);
    return end - start;
}

// 打印报告
void print_report(double cpu, double memory, double io, double string) {
    printf("%-20s %-10s\n", "C 测试项", "耗时(ms)");
    printf("------------------------------\n");
    printf("%-20s %-10.2f\n", "CPU_Test", cpu);
    printf("%-20s %-10.2f\n", "Memory_Test", memory);
    printf("%-20s %-10.2f\n", "IO_Test", io);
    printf("%-20s %-10.2f\n", "String_Test", string);
}

int main() {
    double cpu = cpu_test(40); // 40阶斐波那契
    double memory = memory_test(1000000); // 100万元素
    double io = io_test("test_io.c", 50); // 50MB
    double string = string_test(100000);
    
    print_report(cpu, memory, io, string);
    return 0;
}
