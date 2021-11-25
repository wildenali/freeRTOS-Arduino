// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include "semphr.h"


// /*
// https://microcontrollerslab.com/freertos-binary-semaphore-tasks-interrupt-synchronization-u-arduino/

// */


// #define  LED  13

// SemaphoreHandle_t interruptSemaphore;

// void TaskLedon(void *pvParameters);
// void TaskLedoff(void *pvParameters);
// void interruptHandler();

// void setup() {
//   Serial.begin(9600);
//   pinMode(LED ,OUTPUT);
  
//   xTaskCreate(TaskLedon, "LedON", 100, NULL, 1, NULL);
//   xTaskCreate(TaskLedoff, "LedOFF", 100, NULL, 1, NULL);

//   interruptSemaphore = xSemaphoreCreateBinary();
//   if (interruptSemaphore != NULL) 
//   {
//     attachInterrupt(digitalPinToInterrupt(2), interruptHandler, HIGH);
//   }
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// void interruptHandler() 
// { 
//   Serial.println("Semaphore is given");
//   BaseType_t  xHigherPriorityTaskWoken  pdFALSE;
//   xSemaphoreGiveFromISR(interruptSemaphore, &xHigherPriorityTaskWoken);
// }

// void TaskLedon(void *pvParameters)
// {
//   (void) pvParameters;

//   for (;;) 
//     {
//       if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) 
//       {
//         Serial.println("TaskLedon Received Semaphore");
//         digitalWrite(LED_BUILTIN, HIGH);
//       }
//     }
//   }

// void TaskLedoff(void *pvParameters)
// {
//   (void) pvParameters;
//   for (;;) 
//   {
//     if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS)
//     {
//       Serial.println("TaskLedoff Received Semaphore");
//       digitalWrite(LED_BUILTIN, LOW);
//     }
//   }
// }