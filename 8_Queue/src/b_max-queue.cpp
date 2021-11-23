// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include <queue.h>

// // Konsep antrian
// // Antrian di FreeRTOS max ada antrian, lebih dari itu akan penuh, tunggu kosong dulu, baru bisa masuk antrian lagi

// void Task_AmbilQueue(void *param);
// void Task_KirimQueue(void *param);

// QueueHandle_t queue_satu;

// void setup() {
//   Serial.begin(9600);
  
//   queue_satu = xQueueCreate(5, sizeof(int));
//   if (queue_satu == NULL) {
//     Serial.println("Queue can not be created");
//   }

//   xTaskCreate(Task_AmbilQueue, "Task AmbilQueue", 128, NULL, 1, NULL);
//   xTaskCreate(Task_KirimQueue, "Task KirimQueue", 128, NULL, 1, NULL);
//   // vTaskStartScheduler();
// }

// void loop() {}

// void Task_AmbilQueue(void * pvParameters) {
//   int number = 0;
//   while(1) {
//     if (xQueueReceive(queue_satu, (void *)&number, 0) == pdTRUE) {
//       Serial.print("Task_AmbilQueue: ");
//       Serial.println(number);
//     }
//     Serial.println(number);
//     vTaskDelay(1000/portTICK_PERIOD_MS);
//   }
// }

// void Task_KirimQueue(void * pvParameters) {
//   int num = 0; 
//   while(1) {
//     // Try to add item to queue for 10 ticks, fail if queue is full
//     // xQueueSend(queue_satu, (void *)&num, 10);
//     // num++;

//     if (xQueueSend(queue_satu, (void *)&num, 10) != pdTRUE)
//     {
//       Serial.println("Queue Full");
//     }
//     num++;
//     vTaskDelay(100 / portTICK_PERIOD_MS);
//   }
// }