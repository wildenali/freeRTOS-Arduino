#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "semphr.h"


/*
https://microcontrollerslab.com/freertos-binary-semaphore-tasks-interrupt-synchronization-u-arduino/

In this example, we will create two tasks. One task turn-on LED and other task turns-off LED.
But both tasks can not execute at the same time. Because both share the same binary semaphore.
Both tasks have the same priority level. Therefore, the FreeRTOS scheduler will schedule both tasks in
a time-sharing or round-robin fashion.

If we do not use a binary semaphore to synchronize these tasks,
tasks will not execute according to the order we want and it will follow a haphazard form of round-robin scheduling.
We want to execute LedOnTask and after that LedOffTaks or vice versa. To maintain this order,
we have to synchronize both tasks using binary semaphore.
*/


#define  LED  13

SemaphoreHandle_t xBinarySemaphore;

void LedOnTask(void *pvParameters);
void LedoffTask(void *pvParameters);

void setup() {
  Serial.begin(9600);
  pinMode(LED ,OUTPUT);
  
  xBinarySemaphore = xSemaphoreCreateBinary();
  xTaskCreate(LedOnTask, "LedON", 100, NULL, 1, NULL);
  xTaskCreate(LedoffTask, "LedOFF", 100, NULL, 1, NULL);
  
  xSemaphoreGive(xBinarySemaphore);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void LedOnTask(void *pvParameters)
{
  while(1)
  {
   xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
   Serial.println("Inside LedOnTask");
   digitalWrite(LED,LOW);
   vTaskDelay(100);
   xSemaphoreGive(xBinarySemaphore);
  }
}

void LedoffTask(void *pvParameters)
{
  while(1)
  {
    xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);
    Serial.println("Inside LedffTask");
    digitalWrite(LED,HIGH);
    vTaskDelay(100);
    xSemaphoreGive(xBinarySemaphore);
  }
}