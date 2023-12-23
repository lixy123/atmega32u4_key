# atmega32u4_key

一.功能:<br/>
   据说软件工程师平时工作只需要两个按键就能工作, Ctrl+c, Ctrl+v<br/>
   当然,这是一个笑话,不过这两个键确实是高频繁的按键, 软件工程师时间宝贵，如果做成硬件,每天节约几秒,长年下来能节省不少时间.<br/>
   淘宝上有现成的卖,输入关键字“复制粘贴 程序员 小键盘”，20-50元不等,自已做一个也不难.<br/>
   将设备插入电脑usb口, 按设备上的按键自动将预定义的键盘字符组合输出到电脑,例如输出Ctrl+c, Ctrl+v, Ctrl+Alt+Delete等, 也可以配置成键盘输入组合,例如先按F5,再输入abc,再按回车等.<br/>

二.硬件:<br/>
1.CJMCU-Beetle Leonardo USB ATMEGA32U4<br/>
2.两个普通带冒子的按键(两引脚)<br/>
3.万能板,线<br/>
4.USB延长线 (用于连接电脑usb口与 CJMCU-Beetle Leonardo USB ATMEGA32U4, 如果连接笔记本,长度建议10cm, 如果连接台式机,长度建议60cm)<br/>

<img src= 'https://github.com/lixy123/atmega32u4_key/blob/main/keyboard.jpg?raw=true' /> <br/>


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

五.配置及使用<br/>
1.烧录完成后,拔出硬件重新插上. 默认按第一个键是Ctrl+c 复制. 按第二个键是Ctrl+v 粘贴, 如果想重新设置两键功能,见第2步<br/>
2.如果想更换两个按键的键盘功能,打开串口工具,波特率设置115200, 输入代表两个按键的指令并回车换行(\r\n), 两个按钮功能字符串用"$$$" 分隔<br/>
  指令参考:<br/>
  https://github.com/SpacehuhnTech/WiFiDuck#scripting<br/>

  样例1:<br/>
  CTRL c\r\nDELAY 1000$$$CTRL v\r\nDELAY 1000<br/>
  作用: 第一个键: Ctrl+c 休息1秒 第二个键: Ctrl+v 休息1秒<br/>

  样例1:<br/>
  F8\r\nDELAY 2000$$$CTRL b\r\nDELAY 100\r\nCTRL v\r\nDELAY 100\r\nENTER\r\nDELAY 2000<br/>
  作用: 第一个键: F8 休息2秒 第二个键: Ctrl+b 休息0.1秒 Ctrl+v 休息0.1秒 回车键 休息2秒<br/>
3. 如果休眠唤醒后按键功能失灵, 可能是休眠时将usb设备关停,唤醒后usb设备没正常加载.<br/>
   检查控制面板,找到设备管理器, 检查确保 USB输入设备的属性的 "允许计算机关闭此设备节能" 不要选中.<br/>
  
