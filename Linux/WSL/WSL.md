# �ں˱���

## ���USB����
1.��¡΢���ں˾���
> ![](./1.png)   

2.��װ��
> ```sudo apt install libncurses-dev```

3.�༭�����ļ�
> ```sudo make menuconfig KCONFIG_CONFIG=Microsoft/config-wsl```
> ����Device Drivers -> USB support -> Support for Host-side USB ��
> ѡ�� USB Mass Storage support�͵�������������

4.��װ���빤��
> ```sudo apt install build-essential flex bison libssl-dev libelf-dev dwarves```

5.����Դ��Ŀ¼
> ִ�� ```make -j$(nproc) bzImage KCONFIG_CONFIG=Microsoft/config-wsl```

6.ע������
> �����ʾ bc not found������Ҫ��װbc
> ```sudo apt-get install bc```
> Ȼ�����±���
> 