#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void Task_Print1(void *param);
void Task_Print2(void *param);

TaskHandle_t Task_Print1_Handle;
TaskHandle_t Task_Print2_Handle;

// Remeber if you DELETE the Task, then the Task can't running again

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  xTaskCreate(
    Task_Print1,          // Function to be called
    "Task_1",             // Name of task
    128,                  // Stack size
    NULL,                 // Parameter to pass to function
    1,                    // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Print1_Handle   // Task Handle
  );

  xTaskCreate(
    Task_Print2,          // Function to be called
    "Task_2",             // Name of task
    128,                  // Stack size
    NULL,                 // Parameter to pass to function
    2,                    // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Print2_Handle   // Task Handle
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Task_Print1(void *param){
  (void) param;

  int x = 0;
  while (1)
  {
    Serial.print("Task 1 ... ");
    Serial.println(++x);
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}

void Task_Print2(void *param){
  (void) param;

  int x = 0;
  while (1)
  {
    Serial.print("Task 2 ... ");
    Serial.println(++x);
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec

    if (x == 10)
    {
      vTaskDelete(Task_Print1_Handle);
      Serial.println("Delete Task 1 _ Task_Print1_Handle");
    }

    // even you resume the Task, it can't running again
    else if (x == 20)
    {
      vTaskResume(Task_Print1_Handle);
      Serial.println("Resume Task 1 _ Task_Print1_Handle");
    }
  }
}