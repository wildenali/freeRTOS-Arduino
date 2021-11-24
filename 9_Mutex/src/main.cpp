#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>


// Globals
static int shared_ver = 0;
static SemaphoreHandle_t mutex;

void Task_Satu(void *param);
void Task_Dua(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Create mutex before starting tasks
  mutex = xSemaphoreCreateMutex();

  xTaskCreate(
    Task_Satu,    // Function to be called
    "Task_1",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle1
  );

  xTaskCreate(
    Task_Dua,    // Function to be called
    "Task_2",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle2
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}


void Task_Satu(void *param){
  (void) param;

  int x = 0;
  while (1)
  {
    if (xSemaphoreTake(mutex, 0) == pdTRUE) // 0 adalah 0 tick
    {
      x = shared_ver;
      x++;
      vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
      shared_ver = x;

      // Give mutex after critical section
      xSemaphoreGive(mutex);

      Serial.print("Task One ... ");
      Serial.println(shared_ver);
    }
    else {
      // Do something else
    }
  }
}

void Task_Dua(void *param){
  (void) param;

  int x = 0;
  while (1)
  {
    if (xSemaphoreTake(mutex, 0) == pdTRUE) // 0 adalah 0 tick
    {
      x = shared_ver;
      x++;
      vTaskDelay(random(100, 500) / portTICK_PERIOD_MS);
      shared_ver = x;

      // Give mutex after critical section
      xSemaphoreGive(mutex);

      Serial.print("Task Two ... ");
      Serial.println(shared_ver);
    }
    else {
      // Do something else
    }
  }
}