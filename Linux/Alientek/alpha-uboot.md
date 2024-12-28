

# 安装编译器

首先下载编译器

> [编译器](https://releases.linaro.org/components/toolchain/binaries/7.5-2019.12/arm-linux-gnueabihf/)

下载最新版 gcc7.5.0

![](C:\DATA\Embeded_learning_notes\Linux\Alientek\src\imgs\uboot-1.png)

安装编译依赖

```shell
sudo apt-get install -y libncurses5-dev lsb-core lib32stdc++6 bison flex lzop git
```

将编译器放入`/usr/local/arm`目录下，并添加到PATH中



# 拉取源码

```sh
git clone https://github.com/nxp-imx/uboot-imx.git uboot-imx
```

进入uboot目录，切换分支到最新版

```sh
cd uboot-imx
git chechkout imx_v2020.04_5.4.70_2.3.0
```



# 设置顶层Make file

将`ARCH`设置为`arm` ,`CROSS_COMPILE`设置为`arm-linux-gnueabihf-`

然后就可以开始编译



# 编译

编译前先配置

```sh
make mx6ull_14x14_evk_emmc_defconfig
```



# 移植

先将`configs/mx6ull_14x14_evk_emmc_defconfig` `include/configs/mx6ullevk.h`复制为`configs/mx6ull_14x14_alpha_emmc_defconfig` `include/configs/mx6ullalpha.h`

## 编辑 `configs/mx6ull_14x14_evk_emmc_defconfig`

- 找到`CONFIG_TARGET_MX6ULL_14X14_EVK=y`改为`CONFIG_TARGET_MX6ULL_14X14_ALPHA=y`，这是指定编译我们自己的板子

- 找到`CONFIG_SYS_EXTRA_OPTIONS="IMX_CONFIG=board/freescale/mx6ullevk/imximage.cfg"`改为`CONFIG_SYS_EXTRA_OPTIONS="IMX_CONFIG=board/freescale/mx6ullhello/imximage.cfg"`，这是指定我们板子的配置

- 找到`CONFIG_DEFAULT_DEVICE_TREE="imx6ull-14x14-evk-emmc"`改为`CONFIG_DEFAULT_DEVICE_TREE="imx6ull-14x14-alpha-emmc"`

- 找到`CONFIG_DM_74X164=y`改为`# CONFIG_DM_74X164=y`，官网EVK开发板使用了一个74LV594，我们的板子没有使用所以屏蔽掉

- 找到`CONFIG_SOFT_SPI=y`改为`# CONFIG_SOFT_SPI=y`，屏蔽掉软件模拟的SPI，这是官方驱动74LV594用的，我们自己的板子也用不到


## 修改头文件

`include/configs/mx6ullalpha.h`

将头文件的宏定义修改为`__MX6ULLALPHA_CONFIG_H`

添加自己开发板的设备树内容：

![](C:\DATA\Embeded_learning_notes\Linux\Alientek\src\imgs\uboot-2.png)



## 添加自己板子描述文件的文件夹：

```sh
cp board/freescale/mx6ullevk board/freescale/mx6ullalpha -r
```

将目录中的`mx6ullevk.c`修改为`mx6ullalpha.c`

修改`imximage.cfg`中`CONFIG_USE_IMXIMG_PLUGIN`宏下的`PLUGIN`条目，修改为：

`PLUGIN  board/freescale/mx6ullalpha/plugin.bin 0x00907000`

编辑 `Kconfig`,修改为：

```sh
if TARGET_MX6ULL_14X14_alpha || TARGET_MX6ULL_9X9_EVK

config SYS_BOARD
	default "mx6ullalpha"

config SYS_VENDOR
	default "freescale"

config SYS_CONFIG_NAME
	default "mx6ullalpha"

config SYS_TEXT_BASE
	default 0x87800000
endif

```

编辑`MAINTAINERS`文件：

```
MX6ULLALPHA BOARD
M:	Peng Fan <peng.fan@nxp.com>
S:	Maintained
F:	board/freescale/mx6ullalpha/
F:	include/configs/mx6ullalpha.h
F:	configs/mx6ull_14x14_alpha_emmc_defconfig
F:	configs/mx6ull_14x14_alpha_plugin_defconfig
F:	configs/mx6ulz_14x14_evk_defconfig

```

修改`MakeFile`将`obj-y`后面的值修改为`mx6ullalpha.o`





