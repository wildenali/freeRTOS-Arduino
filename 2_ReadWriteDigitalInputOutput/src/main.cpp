#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void Task_ReadDigitalInput(void *param);
void Task_WriteDigitalOutput(void *param);

TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

int button_pin  = 2;           // pin 2
int led_pin     = LED_BUILTIN;    // led builtin

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);

  xTaskCreate(
    Task_ReadDigitalInput,        // Function to be called
    "Task Read Digital Input",    // Name of task
    128,                          // Stack size
    NULL,                         // Parameter to pass to function
    1,                            // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle1
  );

  xTaskCreate(
    Task_WriteDigitalOutput,      // Function to be called
    "Task Write Digital Output",  // Name of task
    128,                          // Stack size
    NULL,                         // Parameter to pass to function
    2,                            // Priority, (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    &Task_Handle2
  );
}

void loop() {
  // put your main code here, to run repeatedly:
}

void Task_ReadDigitalInput(void *param){
  (void) param;

  while (1)
  {
    int x = digitalRead(button_pin);
    Serial.println(x);
    vTaskDelay(1000/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}

void Task_WriteDigitalOutput(void *param){
  (void) param;

  while (1)
  {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);  // delay each 1 sec
    digitalWrite(led_pin, LOW);
    vTaskDelay(100/portTICK_PERIOD_MS);  // delay each 1 sec
  }
}