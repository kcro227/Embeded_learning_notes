# ǰ��׼��
> Ϊ�˸�WSLʹ�������������磨��VPN��������Խ����������ã�
> ## 1.��VPN������������ѡ��
> ## 2.����WSL�Ĵ�������
> ## 3.���÷���ǽ
> 
# 1.��VPN������������ѡ��
> �����Լ���ʹ�õ�����������á����ԡ�
# 2.����WSL��������
> ����������һ�¼���
> - 1������wsl�µ���Ŀ¼��ʹ��```sudo vim ~/.bashrc``` ��.bashrc���б༭�������´�����ӵ���ĩ��
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
>     ���֮�󱣴棬Ȼ�������ն˻���ִ��```source ~/.bashrc ```
>   - 2 �ն��Ϸֲ�ִ��ִ�У�
>     ```
>       sudo rm /etc/resolv.conf
>       sudo bash -c 'echo "nameserver 8.8.8.8" > /etc/resolv.conf'
>       sudo bash -c 'echo "[network]" > /etc/wsl.conf'
>       sudo bash -c 'echo "generateResolvConf = false" >> /etc/wsl.conf'
>       sudo chattr +i /etc/resolv.conf
>     
>     ```
>     ���� ```8.8.8.8 ```ΪDNS��������ַ�����޸�Ϊ��Ѷ�Ƶ�```119.29.29.29 ```       
>   ���ˣ�WSL���ֽ�����
# 3.���÷���ǽ
> �˲��ֿ��ܲ�һ����ɹ�������ೢ�ԡ�
> - 1.�ھ��й���ԱȨ�޵�power shell��ִ�У�
>   ```
>       New-NetFirewallRule -DisplayName "WSL" -Direction Inbound  -InterfaceAlias "vEthernet (WSL)"  -Action Allow
>   ```




# �Դˣ��Ϳ��Լ����Ƿ����óɹ��ˡ���ÿ����Ҫʹ�õ�������������ʱ����Ҫִ�У�``` proxy ```����