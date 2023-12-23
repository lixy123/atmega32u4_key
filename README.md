# atmega32u4_key

一.功能:<br/>
   将设备插入电脑,当按下设备上的按键, 辅助输入键盘字符至电脑,例如Ctrl+c, Ctrl+v, Ctrl+Alt+Delete, 也可以是键盘输入组合,比如先按F5,输入abc,按回车等.

二.硬件:<br/>
1.CJMCU-Beetle Leonardo USB ATMEGA32U4<br/>
2.两个普通带冒子的按键(两引脚)<br/>
3.万能板,线<br/>
4.USB延长线 (用于连接电脑usb口与 CJMCU-Beetle Leonardo USB ATMEGA32U4, 如果连接笔记本,长度建议10cm, 如果连接台式机,长度建议60cm)<br/>

引脚连接<br/>
按键1  ATMEGA32U4<br/>
第一脚  GND<br/>
第二脚  SCL<br/>

按键2  ATMEGA32U4<br/>
第一脚  GND<br/>
第二脚  SDA<br/>

三.软件:<br/>
1.arduino  1.8.19<br/>

四.烧录方法:<br/>
1.插入设备<br/>
2.开发板选择: Arduino Leonardo<br/>
3.选择对应的端口<br/>
4.点击编译上传按钮<br/>

四.配置及使用<br/>
1.烧录完成后,拔出硬件重新插上. 默认按第一个键是Ctrl+c 复制. 按第二个键是Ctrl+v 粘贴<br/>
2.如果想更换两个按键的键盘功能,打开串口工具,波特率设置115200, 输入代表两个按键的指令并要有回车换行(\r\n), 两个按钮功能字符串用"$$$" 分隔<br/>
  指令参考:<br/>
  https://github.com/SpacehuhnTech/WiFiDuck#scripting<br/>

  样例1:<br/>
  CTRL c\r\nDELAY 1000$$$CTRL v\r\nDELAY 1000<br/>
  作用: 第一个键: Ctrl+c 休息1秒 第二个键: Ctrl+v 休息1秒<br/>

  样例1:<br/>
  F8\r\nDELAY 2000$$$CTRL b\r\nDELAY 100\r\nCTRL v\r\nDELAY 100\r\nENTER\r\nDELAY 2000<br/>
  作用: 第一个键: F8 休息2秒 第二个键: Ctrl+b 休息0.1秒 Ctrl+v 休息0.1秒 回车键 休息2秒<br/>
  
