# 前期准备
> 为了给WSL使用宿主机的网络（如VPN），则可以进行如下设置：
> ## 1.打开VPN的允许本地链接选项
> ## 2.配置WSL的代理设置
> ## 3.配置防火墙
> 
# 1.打开VPN的允许本地链接选项
> 根据自己所使用的软件进行配置。此略。
# 2.配置WSL代理设置
> 此项设置有一下几步
> - 1，进入wsl下的主目录，使用```sudo vim ~/.bashrc``` 对.bashrc进行编辑，将如下代码添加到文末：
>   ```
>     # add for proxy
>     export hostip=$(ip route | grep default | awk '{print $3}')
>     export sock_hostport=10808
>     export http_hostport=10809
>     alias proxy='
>     export HTTPS_PROXY="http://${hostip}:${http_hostport}";
>     export HTTP_PROXY="http://${hostip}:${http_hostport}";
>     export ALL_PROXY="socks5://${hostip}:${sock_hostport}";
>     export all_proxy="socks5://${hostip}:${sock_hostport}";
>           '
>     alias unproxy='
>     unset HTTPS_PROXY;
>     unset HTTP_PROXY;
>     unset ALL_PROXY;
>     unset all_proxy;
>     '
>     alias echoproxy='
>     echo $HTTPS_PROXY;
>     echo $HTTP_PROXY;
>     echo $ALL_PROXY;
>     echo $all_proxy;
>       '  
>     ```
>     添加之后保存，然后重启终端或者执行```source ~/.bashrc ```
>   - 2 终端上分布执行执行：
>     ```
>       sudo rm /etc/resolv.conf
>       sudo bash -c 'echo "nameserver 8.8.8.8" > /etc/resolv.conf'
>       sudo bash -c 'echo "[network]" > /etc/wsl.conf'
>       sudo bash -c 'echo "generateResolvConf = false" >> /etc/wsl.conf'
>       sudo chattr +i /etc/resolv.conf
>     
>     ```
>     其中 ```8.8.8.8 ```为DNS服务器地址，可修改为腾讯云的```119.29.29.29 ```       
>   至此，WSL部分结束。
# 3.配置防火墙
> 此部分可能不一定会成功，建议多尝试。
> - 1.在具有管理员权限的power shell下执行：
>   ```
>       New-NetFirewallRule -DisplayName "WSL" -Direction Inbound  -InterfaceAlias "vEthernet (WSL)"  -Action Allow
>   ```




# 自此，就可以检验是否配置成功了。在每次需要使用到宿主机的网络时，需要执行：``` proxy ```命令