#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>

// Konsep antrian
// Antrian di FreeRTOS max ada antrian, lebih dari itu akan penuh, tunggu kosong dulu, baru bisa masuk antrian lagi

// Define a Array
int pinReadArray[4]={0,0,0,0};

void TaskAnalogReadPin0(void *pvParameters);
void TaskAnalogReadPin1(void *pvParameters);
void TaskSerial(void *pvParameters);
void TaskBlink(void *pvParameters);

QueueHandle_t arrayQueue;

void setup() {
  Serial.begin(9600);
  
  arrayQueue = xQueueCreate(10,  // Queue length
                              sizeof(int)  // Queue item size
                              );
  if (arrayQueue != NULL) {
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

    // Create other task that publish data in the queue if it was created.
    xTaskCreate(TaskAnalogReadPin1, // Task function
                "AnalogReadPin1", // Task name
                128,  // Stack size
                NULL, 
                1, // Priority
                NULL);
    
    xTaskCreate(TaskBlink, // Task function
                "Blink", // Task name
                128, // Stack size 
                NULL, 
                0, // Priority
                NULL );
  }
}

void loop() {}


/**
 * Analog read task for Pin A0
 * Reads an analog input on pin 0 and send the readed value through the queue.
 * See Blink_AnalogRead example.
 */
void TaskAnalogReadPin0(void *pvParameters)
{
    (void) pvParameters;
    for (;;){
        pinReadArray[0]=0;
        pinReadArray[1]=analogRead(A0);
        /**
         * Post an item on a queue.
         * https://www.freertos.org/a00117.html
         */
        xQueueSend(arrayQueue,&pinReadArray,portMAX_DELAY);
        // One tick delay (15ms) in between reads for stability
        vTaskDelay(1);
    }
}


/**
 * Analog read task for Pin A1
 * Reads an analog input on pin 1 and send the readed value through the queue.
 * See Blink_AnalogRead example.
 */
void TaskAnalogReadPin1(void *pvParameters)
{
    (void) pvParameters;
    for (;;){
        pinReadArray[2]=1;
        pinReadArray[3]=analogRead(A1);
        /**
         * Post an item on a queue.
         * https://www.freertos.org/a00117.html
         */
        xQueueSend(arrayQueue,&pinReadArray,portMAX_DELAY);
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
    
    for (;;){
        if(xQueueReceive(arrayQueue,&pinReadArray,portMAX_DELAY) == pdPASS ){
            Serial.print("PIN:");
            Serial.println(pinReadArray[0]);
            Serial.print("value:");
            Serial.println(pinReadArray[1]);
            Serial.print("PIN:");
            Serial.println(pinReadArray[2]);
            Serial.print("value:");
            Serial.println(pinReadArray[3]);
            vTaskDelay(500/portTICK_PERIOD_MS);
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