#include <Keyboard.h>
#include <EEPROM.h>

//String bufferStr = "";
String last = "";
int defaultDelay = 0;

//按键1 默认Ctrl+c
const int buttonPin = 3;
//按键2 默认Ctrl+v
const int buttonPin2 = 2;

//按键1的命令串
String key_cmd1 = "";
//按键2的命令串
String key_cmd2 = "";

//命令字串解析临时数组
String buff_command[2];

/*
   wifi duck参考:
   https://github.com/gloglas/WifiDuckV2/blob/master/arduino_wifi_duckV2/arduino_wifi_duckV2.ino
   https://github.com/spacehuhn/wifi_ducky

   语句说明:
   https://github.com/SpacehuhnTech/WiFiDuck#scripting

   https://github.com/wobisheng/esp32s2_badusb/blob/main/esp32s2_badusb.ino
   
   EEPROM空间:  1KB
   代码最大空间: 28KB (Flash空间:32 KB (4K已用boolode))

   编译大小:12KB
   电流:35ma

   插上时,如果调试串口之前有打开,调试会有问题,需要重新打开串口!否则不正常!

   atmegau324u 在控制面板只要不设置"允许计算机关闭此设备以节约电源",休眠唤醒后能继续使用!
*/


void splitString(String message, String dot, String outmsg[], int len)
{
  int commaPosition, outindex = 0;
  for (int loop1 = 0; loop1 < len; loop1++)
    outmsg[loop1] = "";
  do {
    commaPosition = message.indexOf(dot);
    if (commaPosition != -1)
    {
      outmsg[outindex] = message.substring(0, commaPosition);
      //下一字串
      outindex = outindex + 1;
      //后移分隔符长度
      message = message.substring(commaPosition + dot.length(), message.length());
    }
    if (outindex >= len) break;
  }
  while (commaPosition >= 0);

  if (outindex < len)
    outmsg[outindex] = message;
}




void Line(String _line)
{
  int firstSpace = _line.indexOf(" ");

  //没有空格
  if (firstSpace == -1) Press(_line);

  //1.STRING
  else if (_line.substring(0, firstSpace) == "STRING") {
    for (int i = firstSpace + 1; i < _line.length(); i++)
      Keyboard.write(_line[i]);
  }
  //2.DELAY
  else if (_line.substring(0, firstSpace) == "DELAY") {
    int delaytime = _line.substring(firstSpace + 1).toInt();
    delay(delaytime);
  }
  //3.DEFAULTDELAY
  else if (_line.substring(0, firstSpace) == "DEFAULTDELAY")
    defaultDelay = _line.substring(firstSpace + 1).toInt();
  //4.REM
  else if (_line.substring(0, firstSpace) == "REM") {} //nothing :/
  //5.REPLAY
  else if (_line.substring(0, firstSpace) == "REPLAY") {
    int replaynum = _line.substring(firstSpace + 1).toInt();
    while (replaynum)
    {
      Line(last);
      --replaynum;
    }
  }
  //其它情况,例如组合键
  else
  {
    String remain = _line;

    while (remain.length() > 0) {
      int latest_space = remain.indexOf(" ");
      if (latest_space == -1) {
        Press(remain);
        remain = "";
      }
      else {
        Press(remain.substring(0, latest_space));
        remain = remain.substring(latest_space + 1);
      }
      delay(5);
    }
  }

  Keyboard.releaseAll();
  delay(defaultDelay);
}


void Press(String b) {
  if (b.length() == 1) Keyboard.press(char(b[0]));
  else if (b.equals("ENTER")) Keyboard.press(KEY_RETURN);
  else if (b.equals("CTRL")) Keyboard.press(KEY_LEFT_CTRL);
  else if (b.equals("SHIFT")) Keyboard.press(KEY_LEFT_SHIFT);
  else if (b.equals("ALT")) Keyboard.press(KEY_LEFT_ALT);
  else if (b.equals("GUI")) Keyboard.press(KEY_LEFT_GUI);
  else if (b.equals("UP") || b.equals("UPARROW")) Keyboard.press(KEY_UP_ARROW);
  else if (b.equals("DOWN") || b.equals("DOWNARROW")) Keyboard.press(KEY_DOWN_ARROW);
  else if (b.equals("LEFT") || b.equals("LEFTARROW")) Keyboard.press(KEY_LEFT_ARROW);
  else if (b.equals("RIGHT") || b.equals("RIGHTARROW")) Keyboard.press(KEY_RIGHT_ARROW);
  else if (b.equals("DELETE")) Keyboard.press(KEY_DELETE);
  else if (b.equals("PAGEUP")) Keyboard.press(KEY_PAGE_UP);
  else if (b.equals("PAGEDOWN")) Keyboard.press(KEY_PAGE_DOWN);
  else if (b.equals("HOME")) Keyboard.press(KEY_HOME);
  else if (b.equals("ESC")) Keyboard.press(KEY_ESC);
  else if (b.equals("BACKSPACE")) Keyboard.press(KEY_BACKSPACE);
  else if (b.equals("INSERT")) Keyboard.press(KEY_INSERT);
  else if (b.equals("TAB")) Keyboard.press(KEY_TAB);
  else if (b.equals("END")) Keyboard.press(KEY_END);
  else if (b.equals("CAPSLOCK")) Keyboard.press(KEY_CAPS_LOCK);
  else if (b.equals("F1")) Keyboard.press(KEY_F1);
  else if (b.equals("F2")) Keyboard.press(KEY_F2);
  else if (b.equals("F3")) Keyboard.press(KEY_F3);
  else if (b.equals("F4")) Keyboard.press(KEY_F4);
  else if (b.equals("F5")) Keyboard.press(KEY_F5);
  else if (b.equals("F6")) Keyboard.press(KEY_F6);
  else if (b.equals("F7")) Keyboard.press(KEY_F7);
  else if (b.equals("F8")) Keyboard.press(KEY_F8);
  else if (b.equals("F9")) Keyboard.press(KEY_F9);
  else if (b.equals("F10")) Keyboard.press(KEY_F10);
  else if (b.equals("F11")) Keyboard.press(KEY_F11);
  else if (b.equals("F12")) Keyboard.press(KEY_F12);
  else if (b.equals("SPACE")) Keyboard.press(' ');
  else Serial.println("not found :'" + b + "'(" + String(b.length()) + ")");
}


//解析cmd字符串
void analysis_cmd(String cmd)
{
  splitString(cmd, "$$$", buff_command, 2);
  key_cmd1 = buff_command[0];
  key_cmd2 = buff_command[1];
  Serial.println("key_cmd1='" + key_cmd1 + "'");
  Serial.println("key_cmd2='" + key_cmd2 + "'");
}

//执行键盘字符串命令
void do_key_cmd(String cmd)
{
  if (cmd.length() > 0) {

    //用; 做为每行的分界符
    cmd.replace("\\r\\n", "\n");

    while (cmd.length() > 0) {
      int latest_return = cmd.indexOf("\n");
      //没有分隔符,本行命令完全执行
      if (latest_return == -1) {
        Serial.println(">>> '" + cmd + "'");
        Line(cmd);
        cmd = "";
      }
      //有分隔符,先执行前段命令
      else
      {
        Serial.println(">> '" + cmd.substring(0, latest_return) + "'");
        Line(cmd.substring(0, latest_return));
        last = cmd.substring(0, latest_return);
        cmd = cmd.substring(latest_return + 1);
      }
    }

    Serial.println("done");
  }
}


void writeStringToEEPROM(int addr, const String& str) {
  int length = str.length();
  EEPROM.put(addr, length);

  //atmega 的int长度2
  for (int i = 0; i < length; i++) {
    EEPROM.write(addr + 2 + i, str[i]);
  }
}

String readStringFromEEPROM(int addr) {
  int length=0;
  EEPROM.get(addr,length );
  char charArray[length + 1];
  
  //atmega 的int长度2
  for (int i = 0; i < length; i++) {
    charArray[i] = EEPROM.read(addr + 2 + i);
  }

  charArray[length] = '\0';
  String str(charArray);

  return str;
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  Keyboard.begin();
  //delay(500);
  //无法输出!
  // Serial.println("start");
  //atmega 的int是 2字节
  //Serial.println("sizeof(int)=" + String(sizeof(int)));

   int byte_read=0;
   EEPROM.get(EEPROM.length() - 3, byte_read);

   //首次-1, FFFF
   //如果标志位不是100, 写入默认参数
   if (byte_read!= 100)
   {
      //写入默认, ctrl+c ctrl+v
      writeStringToEEPROM(0, "CTRL c\\r\\nDELAY 1000$$$CTRL v\\r\\nDELAY 1000");
      //写入标志位100
      EEPROM.put(EEPROM.length() - 3, 100);
      //setup函数内无法输出
      //Serial.println("writeStringToEEPROM Default");
   }      

   String cmd=  readStringFromEEPROM(0);
   analysis_cmd(cmd);   
}

//EEPROM: uint8_t read( int idx )
// template< typename T > T &get( int idx, T &t )
// template< typename T > const T &put( int idx, const T &t )

//示例:  CTRL c\r\nDELAY 1000$$$CTRL v\r\nDELAY 1000
//      F8\r\nDELAY 2000$$$CTRL b\r\nDELAY 100\r\nCTRL v\r\nDELAY 100\r\nENTER\r\nDELAY 2000
void loop() {
  if (Serial.available()) {
    //注:只能单个字符,不能用字符串
    String bufferStr = Serial.readStringUntil('\n');  //查找 \n, 读入\n前的字符串
    bufferStr = bufferStr.substring(0, bufferStr.length() - 1); //去掉串尾的 \r
    Serial.println("<<< '" + bufferStr + "'");

    if (bufferStr == "cmd")
    {
      Serial.println("cmd='" + readStringFromEEPROM(0) + "'");
    }
    else
    {
      Serial.println("writeStringToEEPROM='" + bufferStr + "'");
      writeStringToEEPROM(0, bufferStr);
      analysis_cmd(bufferStr);
    }
  }

  if (digitalRead(buttonPin) == LOW) {
    Serial.println("key1 press");
    do_key_cmd(key_cmd1);
    //delay(2000);
  }

  else if (digitalRead(buttonPin2) == LOW) {
    Serial.println("key2 press");
    do_key_cmd(key_cmd2);
    //delay(2000);
  } 
}
