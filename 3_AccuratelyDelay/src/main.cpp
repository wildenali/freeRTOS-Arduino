#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// Delay ini lebih akurat dibanding delay biasanya

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

  // Accurately Delay
  TickType_t getTick;
  getTick = xTaskGetTickCount();    // the getTick will get time from systick of OS

  int x = 0;
  while (1)
  {
    Serial.print("Task 1 ... ");
    Serial.println(++x);
    vTaskDelayUntil(&getTick, 1000/portTICK_PERIOD_MS);
  }
}

void Task_Print2(void *param){
  (void) param;

  while (1)
  {
    Serial.println("Task 2");
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}