# 说明
此项目通过ESP8266直连HomeKit控制Aqara六键无线场景开关来联动米家

通过此项目，可解决HomeKit联动米家、Aqara控制米家的问题（Aqara控制米家还需要虚拟设备配合来完成）


# 材料
首先你需要准备一个ESP8266开发板

![image](https://img.alicdn.com/imgextra/i4/2613443097/O1CN01Ku8MWj1YkTMVaa5GB_!!2613443097.jpg)


其次还需要Aqara&Opple六键无线场景开关一个（拆解）

# 工具
链接：https://pan.baidu.com/s/1J6O2J-2MBaQnINAP1W3gSw?pwd=sssv 
提取码：sssv

# 引脚
无线场景第1键  接  开发板的D0

无线场景第2键  接  开发板的D1

无线场景第3键  接  开发板的D5

无线场景第4键  接  开发板的D6

无线场景第5键  接  开发板的D7

无线场景第6键  接  开发板的D2

# 教程

https://www.bilibili.com/read/readlist/rl543714

# 配网
当供电后将创建WIFI，连接可自动弹出配网页面，如未弹出可连接wifi后浏览器访问：http://192.168.4.1

HomeKit配对八位数码在配网页面中已显示，如果未显示就是：123-11-111，如果显示请按照显示的码来填写配对

# 写入固件
将HM.bin写入0x00000
![image](https://img.alicdn.com/imgextra/i1/2613443097/O1CN01CeiRWQ1YkTMf7g6cD_!!2613443097.png)

# Arduino
![image](https://img.alicdn.com/imgextra/i4/2164592911/O1CN01Kwq2g21XNHhCVy6Kb_!!2164592911.png)

# 联系方式
V：m805500091
