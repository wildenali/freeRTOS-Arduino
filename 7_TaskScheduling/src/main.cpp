#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// https://www.youtube.com/watch?v=95yUbClyf3E&list=PLXyB2ILBXW5FLc7j2hLcX6sAGbmH0JxX8&index=3

// Some string to print
const char msg[] = "helow coy, cek dulu ini itu";

void Task_Print1(void *param);
void Task_Print2(void *param);

// Task handles
static TaskHandle_t Task_Handle1 = NULL;
static TaskHandle_t Task_Handle2 = NULL;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(300);

  xTaskCreate(
    Task_Print1,    // Function to be called
    "Task_1",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle1
  );

  xTaskCreate(
    Task_Print2,    // Function to be called
    "Task_2",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    2,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle2
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Task_Print1(void *param){
  (void) param;

  int msg_len = strlen(msg);

  while (1)
  {
    Serial.println("Task 1");
    for (int i = 0; i < msg_len; i++)
    {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}

void Task_Print2(void *param){
  (void) param;

  while (1)
  {
    Serial.print("*");
    vTaskDelay(100/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}