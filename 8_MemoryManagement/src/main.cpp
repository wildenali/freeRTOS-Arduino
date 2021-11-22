#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  xTaskCreate(
    Task_Print1,    // Function to be called
    "Task_1",       // Name of task
    1500,           // 128,            // Stack size
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

  // Delete "setup and loop" task
  vTaskDelete(NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Task_Print1(void *param){
  (void) param;

  while (true)
  {
    int a = 1;
    int b[100];

    // Do something with array so it's not optimized out by the compiler
    for (int i = 0; i < 100; i++)
    {
      b[i] = a + 1;
    }
    Serial.println(b[0]);
    int *ptr = (int*)pvPortMalloc(1024 * sizeof(int));
    vPortFree(ptr);
  }
}

void Task_Print2(void *param){
  (void) param;

  while (true)
  {
    Serial.println("Task 2");
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}