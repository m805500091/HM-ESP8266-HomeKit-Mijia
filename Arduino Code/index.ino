#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <arduino_homekit_server.h>
#include <LittleFS.h>


String readConfig();
void writeConfig(String data);
void deleteConfig();

//AP名称
const char* AP_NAME = "HM-WIFI";
//DNS端口号
const byte DNS_PORT = 53;
//AP-IP地址
IPAddress apIP(192, 168, 4, 1);
//创建dnsServer实例
DNSServer dnsServer;
//创建WebServer
ESP8266WebServer server(80);

//配网页面代码
const char* page_html = "<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport'content='width=device-width, initial-scale=1.0, user-scalable=no'><title>配网页面</title><style>*{padding:0;margin:0}input[type=button],input[type=submit],input[type=file],button{cursor:pointer;-webkit-appearance:none}.header{padding:0;margin:0;font-size:17px;background:rgba(0,0,0,0.8);text-align:center;line-height:50px;height:50px;color:#fff}.inputtext{height:33px;line-height:28px;width:100%;border:1px solid#d0cece;margin:10px 0;border-radius:2px;color:#444;font-size:14px}.spantitle{font-size:16px;color:#222;margin:4px 0;font-weight:bold}.spantitle i{font-size:10px;color:#777;font-style:normal;margin-left:10px}.submit{background:#fa9013;border:none;margin-top:20px;padding:10px 31px;border-radius:3px;font-size:15px;font-weight:bold;color:#fff}.homekit{margin-top:20px;text-align:center;margin-bottom:40px}.homekit img{width:100px}.toolsubmit{background:#fa9013;border:none;margin-top:20px;padding:8px 20px;border-radius:3px;font-size:13px;font-weight:bold;color:#fff}.zuozhe{text-align:center;color:#888;font-size:12px}.homekit span{font-size:18px;color:#000}html,body{font-family:'helvetica neue','Hiragino Sans GB','冬青黑','Microsoft YaHei','微软雅黑',arial,sans-serif!important}</style></head><body id='body'><div class='header'>请完善配网信息</div><div style='padding: 20px;'><div class='homekit'><img src='data:image/png;base64,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'><br/><span>HM互通模块<br/><span style='font-size:14px'>HomeKit配对码：12311111</span></span></div><form name='input'action='/'method='POST'style='padding-top:20px'><span class='spantitle'>WIFI名称:<i>请注意大小写</i></span><input class='inputtext'type='text'name='ssid'><span class='spantitle'>WIFI密码:<i>请注意大小写</i></span><input class='inputtext'type='text'name='password'><input class='submit'type='submit'value='连接WIFI'></form></div><hr/><div style='padding: 20px;'><div style='margin-bottom: 20px;'><span class='spantitle'>工具:</span></div><div><a class='toolsubmit' href='/reset_home_kit'>重置HomeKit</a> <a class='toolsubmit' href='/reset_wifi'>重置配网</a></div></div><div style='padding: 20px;' id='html' class='zuozhe'>固件作者：805500091</div></body><script src='https://public.immmmmm.cn/distribution_network.js'></script></html>";

//访问主页回调函数
void handleRoot() {
  server.send(200, "text/html", page_html);
}


void handleResetWifi() {
  deleteConfig();
  server.send(200, "text/html", "<meta charset='UTF-8'><meta name='viewport'content='width=device-width, initial-scale=1.0, user-scalable=no'>清除WIFI配置信息成功");
  delay(2000);
  Serial.println("准备重启中...");
  Serial.println();
  //重启
  ESP.reset();
}


void handleResetHomeKit() {
  homekit_storage_reset();
  server.send(200, "text/html", "<meta charset='UTF-8'><meta name='viewport'content='width=device-width, initial-scale=1.0, user-scalable=no'>HomeKit重置成功，设备正在重启");
  delay(2000);
  Serial.println("准备重启中...");
  Serial.println();
  //重启
  ESP.reset();
}


//Post回调函数
void handleRootPost() {
  Serial.println("post data:");
  String qsid = server.arg("ssid");
  String pass = server.arg("password");
  Serial.println("");
  Serial.println(qsid);
  Serial.println(pass);
  Serial.println("");
  if (qsid.length() > 0 && pass.length() > 0) {
    writeConfig(qsid + " " + pass);
  } else {
    Serial.println("POST参数有误");
    server.send(200, "text/html", "<meta charset='UTF-8'><meta name='viewport'content='width=device-width, initial-scale=1.0, user-scalable=no'>请填写完整的wifi账号密码");
    return;
  }
  //返回保存成功页面
  server.send(200, "text/html", "<meta charset='UTF-8'><meta name='viewport'content='width=device-width, initial-scale=1.0, user-scalable=no'>WIFI信息保存成功，设备将重启连网<br/>稍后请打开HomeKit家庭添加您的HM模块设备");
  delay(2000);
  Serial.println("准备重启中...");
  Serial.println();

  //重启
  ESP.reset();
}


//初始化基础
void initBasic(void) {
  Serial.begin(115200);
  // 断开之前链接的WIFI
  WiFi.disconnect();
  // 挂载文件服务
  if (!LittleFS.begin()) {
    Serial.println();
    Serial.println("init LittleFS err");
  }
}

//初始化AP模式
void initSoftAP(void) {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  if (WiFi.softAP(AP_NAME)) {
    Serial.println();
    Serial.println("ap ok");
  }
}

//初始化WebServer
void initWebServer(void) {
  //设置主页回调函数
  server.on("/", HTTP_GET, handleRoot);
  server.on("/reset_wifi", HTTP_GET, handleResetWifi);
  server.on("/reset_home_kit", HTTP_GET, handleResetHomeKit);
  //设置无法响应的http请求的回调函数
  server.onNotFound(handleRoot);
  //设置Post请求回调函数
  server.on("/", HTTP_POST, handleRootPost);
  //启动WebServer
  server.begin();
  Serial.println();
  Serial.println("HTTP ok");
}


//初始化DNS服务器
void initDNS(void) {
  //判断将所有地址映射到esp8266的ip上是否成功
  if (dnsServer.start(DNS_PORT, "*", apIP)) {
    Serial.println("");
    Serial.println("DNS ok.");
  } else {
    Serial.println("");
    Serial.println("DNS err.");
  }
}


// 连接wifi
void connectNewWifi(void) {

  String s = readConfig();
  String ssid = "";
  String pass = "";
  if (s.length() > 0) {
    ssid = Split(s, " ", 0);
    pass = Split(s, " ", 1);
  }
  Serial.println("local ssid");
  Serial.println(ssid);
  Serial.println("local pass");
  Serial.println(pass);
  WiFi.begin(ssid, pass);
  // 链接WIFI
  Serial.println("");
  Serial.print("wifi link ...");
  int count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    count++;
    if (count > 20) { //如果10秒内没有连上，就开启Web配网 可适当调整这个时间
      initSoftAP();
      initDNS();
      break; // 跳出 防止无限初始化
    }
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {   //如果连接上 就输出IP信息 防止未连接上break后会误输出
    Serial.println(WiFi.localIP());
  }
}


String Split(String str, String fen, int index)
{
  int weizhi;
  String temps[str.length()];
  int i = 0;
  do
  {
    weizhi = str.indexOf(fen);
    if (weizhi != -1)
    {
      temps[i] =  str.substring(0, weizhi);
      str = str.substring(weizhi + fen.length(), str.length());
      i++;
    }
    else {
      if (str.length() > 0)
        temps[i] = str;
    }
  }
  while (weizhi >= 0);
  if (index > i)return "-1";
  return temps[index];
}


String readConfig()
{
  Serial.println("read config start");
  File file = LittleFS.open("/config.txt", "r");
  if (!file) {
    Serial.println("no config file");
    return "";
  }
  //  Serial.println("读取到的数据如下：");
  //  Serial.println(file.readString());

  String s = file.readString();
  file.close();
  return s;
}

void writeConfig(String data)
{
  Serial.println("write config start");
  File file = LittleFS.open("/config.txt", "w");
  file.print(data);
  delay(1);
  file.close();
  Serial.println("write config ok");
}

void deleteConfig()
{
  Serial.println("del config start");
  LittleFS.remove("/config.txt");
  Serial.println("del config ok");
}


#define LOG_D(fmt, ...)   printf_P(PSTR(fmt "\n") , ##__VA_ARGS__);



extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on1;
extern "C" homekit_characteristic_t cha_switch_on2;
extern "C" homekit_characteristic_t cha_switch_on3;

extern "C" homekit_characteristic_t cha_switch_on4;
extern "C" homekit_characteristic_t cha_switch_on5;
extern "C" homekit_characteristic_t cha_switch_on6;

extern "C" homekit_characteristic_t cha_switch_on7;
extern "C" homekit_characteristic_t cha_switch_on8;
extern "C" homekit_characteristic_t cha_switch_on9;

extern "C" homekit_characteristic_t cha_switch_on10;
extern "C" homekit_characteristic_t cha_switch_on11;
extern "C" homekit_characteristic_t cha_switch_on12;

extern "C" homekit_characteristic_t cha_switch_on13;
extern "C" homekit_characteristic_t cha_switch_on14;
extern "C" homekit_characteristic_t cha_switch_on15;

extern "C" homekit_characteristic_t cha_switch_on16;
extern "C" homekit_characteristic_t cha_switch_on17;
extern "C" homekit_characteristic_t cha_switch_on18;

static uint32_t next_heap_millis = 0;


//引脚说明
/******
 16 -> #D0
  5 -> #D1
 14 -> #D5
 12 -> #D6
 13 -> #D7
  4 -> #D2
*******/

#define PIN_SWITCH1 16
#define PIN_SWITCH2 5
#define PIN_SWITCH3 14
#define PIN_SWITCH4 12
#define PIN_SWITCH5 13
#define PIN_SWITCH6 4


/********第一键***********/
void cha_switch_on_setter1(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH1,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH1, HIGH );
  bool switch_is_on = false;
  cha_switch_on1.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on1, cha_switch_on1.value);
}

void cha_switch_on_setter2(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH1,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH1, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH1,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH1, HIGH );
  bool switch_is_on = false;
  cha_switch_on2.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on2, cha_switch_on2.value);
}

void cha_switch_on_setter3(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH1, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH1,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on3.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on3, cha_switch_on3.value);
}
/********第一键***********/


/********第二键***********/
void cha_switch_on_setter4(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH2,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH2, HIGH );
  bool switch_is_on = false;
  cha_switch_on4.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on4, cha_switch_on4.value);
}

void cha_switch_on_setter5(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH2,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH2, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH2,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH2, HIGH );
  bool switch_is_on = false;
  cha_switch_on5.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on5, cha_switch_on5.value);
}

void cha_switch_on_setter6(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH2, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH2,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on6.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on6, cha_switch_on6.value);
}
/********第二键***********/


/********第三键***********/
void cha_switch_on_setter7(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH3,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH3, HIGH );
  bool switch_is_on = false;
  cha_switch_on7.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on7, cha_switch_on7.value);
}

void cha_switch_on_setter8(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH3,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH3, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH3,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH3, HIGH );
  bool switch_is_on = false;
  cha_switch_on8.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on8, cha_switch_on8.value);
}

void cha_switch_on_setter9(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH3, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH3,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on9.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on9, cha_switch_on9.value);
}
/********第三键***********/



/********第四键***********/
void cha_switch_on_setter10(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH4,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH4, HIGH );
  bool switch_is_on = false;
  cha_switch_on10.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on10, cha_switch_on10.value);
}

void cha_switch_on_setter11(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH4,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH4, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH4,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH4, HIGH );
  bool switch_is_on = false;
  cha_switch_on11.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on11, cha_switch_on11.value);
}

void cha_switch_on_setter12(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH4, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH4,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on12.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on12, cha_switch_on12.value);
}
/********第四键***********/




/********第五键***********/
void cha_switch_on_setter13(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH5,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH5, HIGH );
  bool switch_is_on = false;
  cha_switch_on13.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on13, cha_switch_on13.value);
}

void cha_switch_on_setter14(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH5,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH5, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH5,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH5, HIGH );
  bool switch_is_on = false;
  cha_switch_on14.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on14, cha_switch_on14.value);
}

void cha_switch_on_setter15(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH5, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH5,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on15.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on15, cha_switch_on15.value);
}
/********第五键***********/




/********第六键***********/
void cha_switch_on_setter16(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH6,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH6, HIGH );
  bool switch_is_on = false;
  cha_switch_on16.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on16, cha_switch_on16.value);
}

void cha_switch_on_setter17(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH6,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH6, HIGH );
  delay(50);
  digitalWrite(PIN_SWITCH6,  LOW  );
  delay(50);
  digitalWrite(PIN_SWITCH6, HIGH );
  bool switch_is_on = false;
  cha_switch_on17.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on17, cha_switch_on17.value);
}

void cha_switch_on_setter18(const homekit_value_t value) {
  digitalWrite(PIN_SWITCH6, LOW );
  delay(1300);
  digitalWrite(PIN_SWITCH6,  HIGH  );
  bool switch_is_on = false;
  cha_switch_on18.value.bool_value = switch_is_on;
  homekit_characteristic_notify(&cha_switch_on18, cha_switch_on18.value);
}
/********第六键***********/




void my_homekit_setup() {
  pinMode(PIN_SWITCH1, OUTPUT);
  digitalWrite(PIN_SWITCH1, HIGH);
  pinMode(PIN_SWITCH2, OUTPUT);
  digitalWrite(PIN_SWITCH2, HIGH);
  pinMode(PIN_SWITCH3, OUTPUT);
  digitalWrite(PIN_SWITCH3, HIGH);
  pinMode(PIN_SWITCH4, OUTPUT);
  digitalWrite(PIN_SWITCH4, HIGH);
  pinMode(PIN_SWITCH5, OUTPUT);
  digitalWrite(PIN_SWITCH5, HIGH);
  pinMode(PIN_SWITCH6, OUTPUT);
  digitalWrite(PIN_SWITCH6, HIGH);

  cha_switch_on1.setter = cha_switch_on_setter1;
  cha_switch_on2.setter = cha_switch_on_setter2;
  cha_switch_on3.setter = cha_switch_on_setter3;

  cha_switch_on4.setter = cha_switch_on_setter4;
  cha_switch_on5.setter = cha_switch_on_setter5;
  cha_switch_on6.setter = cha_switch_on_setter6;

  cha_switch_on7.setter = cha_switch_on_setter7;
  cha_switch_on8.setter = cha_switch_on_setter8;
  cha_switch_on9.setter = cha_switch_on_setter9;

  cha_switch_on10.setter = cha_switch_on_setter10;
  cha_switch_on11.setter = cha_switch_on_setter11;
  cha_switch_on12.setter = cha_switch_on_setter12;

  cha_switch_on13.setter = cha_switch_on_setter13;
  cha_switch_on14.setter = cha_switch_on_setter14;
  cha_switch_on15.setter = cha_switch_on_setter15;

  cha_switch_on16.setter = cha_switch_on_setter16;
  cha_switch_on17.setter = cha_switch_on_setter17;
  cha_switch_on18.setter = cha_switch_on_setter18;

  arduino_homekit_setup(&config);
}


void my_homekit_loop() {
  arduino_homekit_loop();
  const uint32_t t = millis();
  if (t > next_heap_millis) {
    next_heap_millis = t + 5 * 1000;
    LOG_D("Free heap: %d, HomeKit clients: %d",
          ESP.getFreeHeap(), arduino_homekit_connected_clients_count());
  }
}




void setup() {
  initBasic();
  initWebServer();
  connectNewWifi();
  if (WiFi.status() == WL_CONNECTED) {
    my_homekit_setup();
  }
}


void loop() {
  server.handleClient();
  dnsServer.processNextRequest();
  if (WiFi.status() == WL_CONNECTED) {
    my_homekit_loop();
    delay(10);
  }
  
  if (WiFi.status() != WL_CONNECTED) {
	  connectNewWifi();
  }
}
