# Programmable Oblivious PRF & multi-party PSI 基于可编程不经意伪随机数的多方隐私求交算法库

本算法库是基于[osu-crypto/MultipartyPSI](https://github.com/osu-crypto/MultipartyPSI)的增强实现，主要增强了如下功能：

- 支持读取文件数据
- 支持多机通信

该算法的原论文来自 [CCS 2017](http://dl.acm.org/xxx) : **Practical Multi-party Private Set Intersection from Symmetric-Key Techniques**[[ePrint](https://eprint.iacr.org/2017/xxx)]

## 验证情况

- 机器配置： 1C 2G (Intel(R) Core(TM) i7-8665U CPU @ 1.90GHz)
- 数量：3台（3方）
- 数据集大小：8条
- 数据长度：128bit
- 3方求交耗时：1.035 s

## 创新特性
### 1. 核心算法：可编程OPRF(Programmable Oblivious PRF)
对于可编程OPRF(Programmable Oblivious PRF), 此算法库包含以下实现:
* Table-based OPPRF
* Polynomial-based  OPPRF
* BloomFilter-based OPPRF

### 2. 安全性
此算法库在**增强半诚实模型**和**标准半诚实模型**中实现了多方 PSI (nPSI)。

## 使用方法

### 依赖库
- 支持 C++14 的 C++ 编译器
- [`Boost`](https://sourceforge.net/projects/boost/)
- [`Miracl`](https://github.com/miracl/MIRACL)
- [`NTL`](http://www.shoup.net/ntl/) 
- [`libOTe`](https://github.com/osu-crypto/libOTe)

*注：对于`libOTe`，它需要支持`PCLMUL`、`AES-NI`和`SSE4.1`的CPU。 可选：`nasm` 用于改进 SHA1 性能。*

### 1. 克隆代码

`git clone https://github.com/JasonCeng/MultipartyPSI-Pro.git`

### 2. 安装依赖
代码已经在 Windows (Microsoft Visual Studio) 和 Linux 上进行了测试。**安装所需的库：**

- windows: 

1. 打开 PowerShell
2. `cd ./thirdparty`
3. `.\all_win.ps1` (该脚本适用于 Visual Studio 2015。对于其他版本，您应该修改 [`MSBuild`](https://github.com/osu-crypto/MultipartyPSI/blob/implement/thirdparty/win/getNTL.ps1#L3) 脚本中的几个地方。)

- linux: 

1. `cd ./thirdparty`
2. `bash .\all_linux.get`.   

*注意：如果您遇到构建 boost、miracl 和 libOTe 的 `all_win.ps1` 或 `all_linux.get` 的问题，请按照 [`libOTe`](https://github.com/osu-crypto) 上的更多手动说明进行操作)*

### 3. 编译

- Windows:
1. 按顺序构建 `cryptoTools、libOTe` 和` libOPRF `项目。
2. 为` bOPRFmain `项目添加参数（例如：-u）
3. 运行` bOPRFmain `
 
- Linux:
1. make (依赖: `CMake`, `Make`, `g++`)
2. 单元测试: `./bin/frontend.exe -u`

### 4. 运行
输出包括`online/offline/total`平均运行时长。

#### 参数列表:
```shell
-u		单元测试：computes PSI of 5 paries, 2 dishonestly colluding, each with set size 2^12 in semihonest setting
-n		参与方数量
-p		参与方ID，ID最大的参与方为结果接收方
-m		set size
-t		恶意参与方数量(在不诚实模型设置中生效)
-a		以增强半诚实模型模式运行。默认使用Table-based OPPRF算法。
			0: Table-based; 1: POLY-seperated; 2-POLY-combined; 3-BloomFilter
-r		当 r = 1 时使用优化的3方PSI算法
-f		输入数据的文本文件(绝对路径或相对路径均可以)
-ip		其他参与方ip，且相对顺序需与-p的编号保持一致。比如-p 0所带的-ip的顺序需为<-p 1 ip>,<-p 2 ip>
```		
#### 示例: 
##### 1. 单元测试

```shell
./bin/frontend.exe -u
```
	
##### 2. nPSI

在半诚实模型设置中，计算3方的PSI，其中包含2个不诚实方，数据存储在`data.bin`中。

三台机器的ip分别是：`192.168.1.10,192.168.1.11,192.168.1.12`

```shell
# 机器1：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data.bin -ip 192.168.1.11,192.168.1.12 > log01.log

# 机器2：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin -ip 192.168.1.10,192.168.1.12 > log02.log

# 机器3：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data.bin -ip 192.168.1.10,192.168.1.11 > log03.log
```

*注意：`-ip`后所带的`ip`为其他参与方`ip`，且相对顺序需与`-p`的编号保持一致。比如`-p 0`所带的`-ip`的顺序需为`<-p 1 ip>,<-p 2 ip>`*

### 5. 总结
```shell
1. git clone https://github.com/JasonCeng/MultipartyPSI-Pro.git  
2. cd thirdparty/
3. bash all_linux.get 
4. cd ..
5. cmake .
6. make -j
7. 在三台机器上执行：
# 机器1：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 0 -f ./data.bin -ip 192.168.1.11,192.168.1.12 > log01.log

# 机器2：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 1 -f ./data.bin -ip 192.168.1.10,192.168.1.12 > log02.log

# 机器3：
./bin/frontend.exe -n 3 -t 2 -m 12 -p 2 -f ./data.bin -ip 192.168.1.10,192.168.1.11 > log03.log
```
	
## 帮助
有关构建或运行该算法库的任何问题，请联系 [JasonCeng](https://www.cnblogs.com/JasonCeng/) by mail: zengzhaochuangx@qq.com
