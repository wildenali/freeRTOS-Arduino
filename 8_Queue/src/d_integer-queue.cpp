#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Konsep antrian
// Antrian di FreeRTOS max ada antrian, lebih dari itu akan penuh, tunggu kosong dulu, baru bisa masuk antrian lagi

void TaskAnalogReadPin0(void *pvParameters);
void TaskSerial(void *pvParameters);
void TaskBlink(void *pvParameters);

QueueHandle_t integerQueue;

void setup() {
  Serial.begin(9600);
  
  integerQueue = xQueueCreate(10,  // Queue length
                              sizeof(int)  // Queue item size
                              );
  if (integerQueue != NULL) {
    Serial.println("Queue created");
    // Create task that consumes the queue if it was created.
    xTaskCreate(TaskSerial, // Task function
                "Serial", // A name just for humans
                128,  // This stack size can be checked & adjusted by reading the Stack Highwater
                NULL, 
                2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
                NULL);


    // Create task that publish data in the queue if it was created.
    xTaskCreate(TaskAnalogReadPin0, // Task function
                "AnalogReadPin0", // Task name
                128,  // Stack size
                NULL, 
                1, // Priority
                NULL);
  }


  xTaskCreate(TaskBlink, // Task function
              "Blink", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              NULL );

  // vTaskStartScheduler();
}

void loop() {}


/**
 * Analog read task
 * Reads an analog input on pin 0 and send the readed value through the queue.
 * See Blink_AnalogRead example.
 */
void TaskAnalogReadPin0(void *pvParameters)
{
  (void) pvParameters;
  
  for (;;)
  {
    // Read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    /**
     * Post an item on a queue.
     * https://www.freertos.org/a00117.html
     */
    xQueueSend(integerQueue, &sensorValue, portMAX_DELAY);

    // One tick delay (15ms) in between reads for stability
    vTaskDelay(1);
  }
}

/**
 * Serial task.
 * Prints the received items from the queue to the serial monitor.
 */
void TaskSerial(void * pvParameters) {
  (void) pvParameters;

  // Init Arduino serial
  Serial.begin(9600);

  // Wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  while (!Serial) {
    vTaskDelay(1);
  }

  int valueFromQueue = 0;

  for (;;) 
  {

    /**
     * Read an item from a queue.
     * https://www.freertos.org/a00118.html
     */
    if (xQueueReceive(integerQueue, &valueFromQueue, portMAX_DELAY) == pdPASS) {
      Serial.println(valueFromQueue);
    }
  }
}

/* 
 * Blink task. 
 * See Blink_AnalogRead example. 
 */
void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  pinMode(LED_BUILTIN, OUTPUT);

  for (;;)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay( 250 / portTICK_PERIOD_MS );
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay( 250 / portTICK_PERIOD_MS );
  }
}
