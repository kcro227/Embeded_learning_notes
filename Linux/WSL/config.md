# 内核编译

## 添加USB驱动
1.克隆微软内核镜像
> ![](./1.png)

2.安装库
> ```sudo apt install libncurses-dev -y```

3.安装编译工具
> ```sudo apt install build-essential flex bison libssl-dev libelf-dev dwarves make gcc -y```

4.编辑配置文件
> ```sudo make menuconfig KCONFIG_CONFIG=Microsoft/config-wsl```
> 进入Device Drivers -> USB support -> Support for Host-side USB ，
> 选中 USB Mass Storage support和弹出的所有驱动


5.进入源码目录
> 执行 ```sudo make -j$(nproc) bzImage KCONFIG_CONFIG=Microsoft/config-wsl```


6.注意事项
> 如果提示 bc not found，则需要安装bc
> ```sudo apt-get install bc```
> 然后重新编译


7.编译完成
> 将bzImage文件复制到windows下，在C:/Users/<username>下新建.wslconfig文件，填入以下内容：
``` 
> [WSL2]
> kernel=path/to/your/file # 此为内核路径，即bzimage文件的路径
```

## 第二种方法

首先安装工具链
```bash
sudo apt install build-essential flex bison libssl-dev libelf-dev libncurses-dev autoconf libudev-dev libtool
```

然后复制当前内核的设置：
```bash
sudo cp /proc/config.gz config.gz
sudo gunzip config.gz
sudo mv config .config
```
然后 ```sudo make menuconfig ```
配置完后编译内核
```bash
sudo make -j 12 && sudo make modules_install -j 12 && sudo make install -j 12
```

编译usbip
```bash
cd tools/usb/usbip
sudo ./autogen.sh
sudo ./configure
sudo make install -j 12
```
复制工具链
```bash
sudo cp libsrc/.libs/libusbip.so.0 /lib/libusbip.so.0
```

在自己的目录下新建一个脚本，用于加载内核模块：
```bash
#!/bin/bash
sudo modprobe usbcore
sudo modprobe usb-common
sudo modprobe hid-generic
sudo modprobe hid
sudo modprobe usbnet
sudo modprobe cdc_ether
sudo modprobe usbserial
sudo modprobe usb-storage
sudo modprobe cdc-acm
sudo modprobe ftdi_sio
sudo modprobe usbip-core
sudo modprobe vhci-hcd
```
在执行前赋予可执行权限即可
然后关闭子系统
在powershell中输入
```bash
wsl --shutdown
```
然后执行新建的脚本，即可

