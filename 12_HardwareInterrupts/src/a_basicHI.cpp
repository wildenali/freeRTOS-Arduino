#include <Arduino.h>
#include <Arduino_FreeRTOS.h>


void Task_Print1(void *param);
void Task_Print2(void *param);
void Task_Print3(void *param);
static void ExternalInterrupt();

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;
TaskHandle_t Task_Handle3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  /* Use INT0(pin2) falling edge interrupt for resuming tasks */
  attachInterrupt(digitalPinToInterrupt(2), ExternalInterrupt, FALLING); 

  xTaskCreate(
    Task_Print1,    // Function to be called
    "Task_1",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    3,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
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

  xTaskCreate(
    Task_Print3,    // Function to be called
    "Task_3",       // Name of task
    128,            // Stack size
    NULL,           // Parameter to pass to function
    1,              // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle3
  );
}

void loop() {
  // Hooked to IDle task, it will run whenever CPU is idle
  Serial.println(F("Loop function"));
  delay(1000);
}

static void ExternalInterrupt()
{
  static int count = 0;
  BaseType_t taskYieldRequired = 0;

  if (count <= 3)
  {
    count++;
  }

  switch (count)
  {
  case 1:
    Serial.println(F("ISR Resuming Task_1"));
    taskYieldRequired = xTaskResumeFromISR(Task_Handle1);
    Serial.println(F("Leaving ISR"));
    break;
  
  case 2:
    Serial.println(F("ISR Resuming Task_2"));
    taskYieldRequired = xTaskResumeFromISR(Task_Handle2);
    Serial.println(F("Leaving ISR"));
    break;
  
  case 3:
    Serial.println(F("ISR Resuming Task_3"));
    taskYieldRequired = xTaskResumeFromISR(Task_Handle3);
    Serial.println(F("Leaving ISR"));
    break;
  
  default:
    break;
  }

  if (taskYieldRequired == 1)   // If the taskYield is required then trigger the same
  {
    taskYIELD();
  }
  
  
}

void Task_Print1(void *param){
  Serial.println("Task 1");
  vTaskDelete(NULL);
}

void Task_Print2(void *param){
  Serial.println("Task 2");
  vTaskDelete(NULL);
}

void Task_Print3(void *param){
  Serial.println(F("Task3 Running, Suspending all tasks"));
  vTaskSuspend(Task_Handle1); //Suspend Task1
  vTaskSuspend(Task_Handle2); //Suspend Task2
  vTaskSuspend(NULL);         //Suspend Own Task

  Serial.println(F("Back in Task3, Deleting Itself"));
  vTaskDelete(Task_Handle3);
}