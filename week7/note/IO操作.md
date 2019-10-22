## 程序运行时间

### cpu：

> cpu时间 = 指令条数（）+ ISA(指令集结构)+cpu主频

- ### 指令条数

  - 算法

  - 编译器

- ISA

  - 不同指令集实现的机器指令的方式存在差别
  - RISC：ARM
  - CISC：Intel
  - Mips:龙芯

- 主频

  - 芯片工艺
    - 功耗
    - 纳米级
  - ISA

## 类UNIX系统中的c标准

### 标准：

- C语言中的头文件
  - 规定基本应用接口（函数）的原型
  - 不同版本的os可根据自身的运用领域具体实现
  - 流行标准
    - ANSI C
    - IEEE posix
- 实现标准
  - SVRX：商用版本
  - BSD：免费版本

### 基本文件操作：

- 不带缓存的：

  - creat

  - open

  - ...

  - **并不是说不带缓存，而是缓存由用户设定以完成系统I/O操作，且设定的缓存大小影响程序性能**

    如：

    ```c
    write(fd,buffer,sizeof(fd));
    ```

> - 通过文件描述符来实现I/O
> - 这套I/O操作是os内核直接提供

- 基于FILE流的：
  - fopen
  - fclose
  - ...

### 标准的I/O库：

- I/O缓存区的大小不由用户设定

- 对不带缓存I/O操作封装

- 不带I/O的操作是通过文件描述符

- 直接访问内核中的打开文件列表

- 为避免对内核数据结构直接操作：

  - 设定一个struct FILE结构体

    ```c
    struct FILE{
        private:
        	用户打开文件列表（size/time/offset);
        	buffer;
        public:
        	fopen(xxx);
        	fclose(xxx);
    }
    ```

***思考传统c中面向对象的思想：***

1. 重载的问题
2. 等等



## 文件类型

### 常态文件（可出现在文件目录树中）：

- 普通文件
- 目录文件
- 套接字文件
- 设备文件

### FIFO文件：

- 暂态文件：
  - 不在文件目录树中
  - 仅存在内存中，关机消失
- 解决进程间通信问题

### 阻塞：

> 请求发生后对程序的影响以区分阻塞非阻塞状态

若相关请求未被相应，则程序进入忙等模式

### 非阻塞：

若请求未被满足，则执行下一步

### 请求与程序后继操作直接的关系：

- 同步：
  - 请求是后继操作的前提，即必须完成请求才能继续完成工作
  - 请求为**因**，后继为**果**
- 异步：
  - 请求发出后，可直接运行后继操作，无需等待
  - 两者无**因果**，程序采用中断方式响应



## I/O操作

### 系统I/O，不带缓冲



### 标准I/O库，缓冲由库设定（512、1024B)

- 由C语言定义

- 运行在用户态

- 是对系统I/O的封装

- ```c
  struct FILE{
      int fd;
      int operation; 	// 文件指针位置
      char *buf;
      // 通过函数指针添加成员函数
      FILE *(*fopen)(){
        *fread(){};
        *fwrite(){};
      };
  }
  ```

- 进制只与缓冲I/O，而内存缓冲在满足某些条件（1. 缓冲区满 2.遇到\n 3.使用fflush（）强制操作 4. 使用fclose() 5.程序结束）时，才将数据与硬盘进行交互（效率高）

- 仅能操作磁盘文件

### 系统I/O由os内核提供函数接口（POSIX标准）

> 1. 可操作各种类型文件
> 2. 对文件I/O是立即执行的

### 缓冲在派生进程中的验证

#### 例一

编写如下程序

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

char buf[] = {"write to stdout\n"};

int main()
{
    pid_t id;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    perror("can't write");
    printf("printf\n");
    id = fork();
    if(id < 0)
    perror("fork error");
    exit(0);
}
```

则他的输出效果就应该是

```shell
write to stdout
printf
```

之所以这个结果是因为printf中的\n已经清空了缓冲区，所以派生进程时，printf这句话并没有被复制一份

> 稍稍修改一下

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
char buf[] = {"write to stdout\n"};
int main()
{
    pid_t id;
    if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
    perror("can't write");
    printf("printf "); //注意这里我们把换行符\n替换为一个空格
    id = fork();
    if(id < 0)
    perror("fork error");
    exit(0);
}
```

输出结果为

```shell
write to stdout
printf
printf
```

#### 例二

> 编写如下程序

```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int globa = 4;

int main (void )
{
pid_t pid;
int vari = 5;
printf ("before fork\n" );
    // fork会返回两个值，给父进程》0的值，给子进程=0的值
if ((pid = fork()) < 0){
  printf ("fork error\n");
  exit (0);
}else if (pid == 0){
  globa++ ;
  vari--;
  printf("Child changed\n");
}else
  printf("Parent did not changde\n");
  printf("globa = %d vari = %d\n",globa,vari);
  exit(0);
}
```

> 输出结果

```shell
[root@happy bin]# ./simplefork
before fork
Child changed
globa = 5 vari = 4
Parent did not changde
globa = 4 vari = 5

重定向到文件时before fork输出两边
[root@happy bin]# ./simplefork>temp
[root@happy bin]# cat temp
before fork
Child changed
globa = 5 vari = 4
before fork
Parent did not changde
globa = 4 vari = 5
```

分析：

分析直接运行程序时标准输出是行缓冲的，很快被新的一行冲掉。而重定向后，标准输出是全缓冲的。当调用fork时before fork这行仍保存在缓冲中，并随着数据段复制到子进程缓冲中。这样，这一行就分别进入父子进程的输出缓冲中，余下的输出就接在了这一行的后面。