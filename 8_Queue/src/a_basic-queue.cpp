// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include <queue.h>

// void Task_Satu(void *param);
// void Task_Dua(void *param);

// QueueHandle_t queue_satu;

// void setup() {
//   Serial.begin(9600);
  
//   queue_satu = xQueueCreate(5, sizeof(int));
//   if (queue_satu == NULL) {
//     Serial.println("Queue can not be created");
//   }

//   xTaskCreate(Task_Satu, "Task Satu", 128, NULL, 1, NULL);
//   xTaskCreate(Task_Dua, "Task Dua", 128, NULL, 1, NULL);
//   vTaskStartScheduler();
// }

// void loop() {
// }

// void Task_Satu(void * pvParameters) {
//   int intensity = 0;
//   while(1) {
//     // Serial.println("Task_Satu");
//     if (xQueueReceive(queue_satu, &intensity, portMAX_DELAY) == pdPASS) {
//       Serial.print("Task_Satu: ");
//       Serial.println(intensity);
//     }
//   }
// }

// void Task_Dua(void * pvParameters) {
//   int current_intensity = 0; 
//   while(1) {
//     current_intensity++;
//     Serial.print("Task_Dua : ");
//     Serial.println(current_intensity);
//     xQueueSend(queue_satu, &current_intensity, portMAX_DELAY);
//     vTaskDelay( 1000 / portTICK_PERIOD_MS );
//   }
// }