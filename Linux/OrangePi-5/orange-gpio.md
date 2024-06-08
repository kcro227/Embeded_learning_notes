# wiringpi
OrangePi5默认安装了wiringpi库，使用``` gpio readall ```可以查看26pin排针的引脚号和功能。
在.c文件中加入``` wiringpi.h```，并在编译时设置编译参数,如：```gcc hello.c -o hello -L lib -l wiringpi -l pthread```
即可类似arduino的方式使用GPIO，如``` digitalwrite(pin,value) ```

# 内核态
