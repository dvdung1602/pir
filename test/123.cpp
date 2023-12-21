#include <WiFi.h>
#include <HTTPClient.h>
#include<Arduino.h>
#include"time.h"
#include<NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "ESP";
const char* password = "12345678";
const char* serverIP = "192.168.1.71";
const int serverPort = 8080;
const char *ntpServer = "pool.ntp.org";
unsigned long epochTime;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
#define LED_PIN 2
#define Pir 34
#define NUM 100                // số lưọng mẫu 1 lần gửi
#define TIMER 10               // chu kì lấy mẫu
#define SPLIT "+"              // phân cách giữa 2 mẫu 

String formattedDate;
String dayStamp;
long timeStamp;


int Volt = 0;
//     QueueHandle_t WifiQueue,ReadQueue;
SemaphoreHandle_t WifiSemaphore;
HTTPClient http;
String Write;
unsigned long getTime()
{
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return (0);
  }
  time(&now);
  return now;
}
void Wifi(void*Para)  // send data to sever 
{
  while (1)
  {
    uint32_t httpResponseCode;
    if(xSemaphoreTake(WifiSemaphore,portMAX_DELAY) == pdPASS)
    {
      int EspID = 1;
      Serial.println(Write);
      httpResponseCode = http.POST(Write);
       digitalWrite(LED_PIN, HIGH);
      //  uint32_t Time = millis();
      // Serial.printf(">> %d ",Time);
      //   Time = millis() - Time;
      //   Serial.printf("%d \n",Time);
      if(httpResponseCode > 0)
      {
        Serial.printf(">>%02d [%s]\n",httpResponseCode,http.getString());
      };
       String response = http.getString();
       Serial.println(response);
    
    
      if (response.indexOf("HTTP/1.1 200 OK") == 1) {
       digitalWrite(LED_PIN, LOW);
       delay(200);
       //Serial.print("HTTP Request failed, error: ");
       //   Serial.println(httpResponseCode);
      }
    } 
      vTaskDelay(1);
    }
  }

void Read(void*Para)   //   read data from PIR, build strig " Write" send to  task wifi 
{
  TickType_t GetTick = xTaskGetTickCount();
  uint8_t Counter = 0;
  while (1)
  {
    if(Counter == 0)
    {
      Write = "esp-id=0";
      Write = Write  + "&vol=";
      Volt = analogRead(Pir);
      Write = Write  + String(Volt);
      Counter ++;
    }
    Volt = analogRead(Pir);
    Write = Write + SPLIT + String(Volt);
    Counter++;
    if(Counter == NUM)
    { epochTime = getTime();
      Write = Write + "&time=" + String(epochTime) + "\n";
      BaseType_t Interrupt = pdFALSE;
      xSemaphoreGiveFromISR(WifiSemaphore,&Interrupt);
      Counter = 0;
          }
    vTaskDelayUntil(&GetTick,TIMER/portTICK_PERIOD_MS);
  }
}
void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..."); // connecting wf
  pinMode(LED_PIN,OUTPUT);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  };
  Serial.println("Connected to WiFi");
  configTime(0,0,ntpServer);
  pinMode(Pir,INPUT);
  http.begin("http://"+String(serverIP)+":"+String(serverPort));
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.setTimeout(1);
  // WifiQueue = xQueueCreate(10,40);
  //ReadQueue = xQueueCreate(10,40);
  WifiSemaphore = xSemaphoreCreateBinary();
  xTaskCreatePinnedToCore(Wifi,"Wifi",10000,NULL,2,NULL,1);  // tạo tác vụ wifi gắn vào core 1
  xTaskCreatePinnedToCore(Read,"Read",10000,NULL,2,NULL,0);  // tạo tác vụ đọc dữ liệu gắn vào core 0
}
void loop()
{
  // while(!timeClient.update()) {
  //   timeClient.forceUpdate();
  // }
  // // The formattedDate comes with the following format:
  // // 2018-05-28T16:00:13Z
  // // We need to extract date and time
  // // formattedDate = timeClient.getFormattedDate();
  // timeStamp = timeClient.getEpochTime();
  
  // Serial.println(timeStamp);
  // delay(1000);
  
}