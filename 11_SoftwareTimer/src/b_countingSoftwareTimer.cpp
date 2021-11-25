// #include <Arduino.h>
// #include <Arduino_FreeRTOS.h>
// #include <timers.h>

// // Settings
// static const TickType_t dim_delay = 5000 / portTICK_PERIOD_MS;

// // Pins (change this if your Arduino board does not have LED_BUILTIN defined)
// static const int led_pin = LED_BUILTIN;

// // Globals
// static TimerHandle_t one_shot_timer = NULL;

// //*****************************************************************************
// // Callbacks

// // Turn off LED when timer expires
// void autoDimmerCallback(TimerHandle_t xTimer) {
//   digitalWrite(led_pin, LOW);
// }

// //*****************************************************************************
// // Tasks

// // Echo things back to serial port, turn on LED when while entering input
// void doCLI(void *parameters) {

//   char c;

//   // Configure LED pin
//   pinMode(led_pin, OUTPUT);

//   while (1) {

//     // See if there are things in the input serial buffer
//     if (Serial.available() > 0) {

//       // If so, echo everything back to the serial port
//       c = Serial.read();
//       Serial.print(c);

//       // Turn on the LED
//       digitalWrite(led_pin, HIGH);

//       // Start timer (if timer is already running, this will act as
//       // xTimerReset() instead)
//       xTimerStart(one_shot_timer, portMAX_DELAY);
//     }
//   }
// }

// //*****************************************************************************

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);

//   // Wait a moment to start (so we don't miss Serial output)
//   Serial.println();
//   Serial.println("---FreeRTOS Timer Solution---");

//   // Create a one-shot timer
//   one_shot_timer = xTimerCreate(
//                       "One-shot timer",     // Name of timer
//                       dim_delay,            // Period of timer (in ticks)
//                       pdFALSE,              // Auto-reload
//                       (void *)0,            // Timer ID
//                       autoDimmerCallback);  // Callback function

//   // Start command line interface (CLI) task
//   xTaskCreate(doCLI,
//                 "Do CLI",
//                 1024,
//                 NULL,
//                 1,
//                 NULL);

//   // Delete "setup and loop" task
//   vTaskDelete(NULL);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }









#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <timers.h>
#include <task.h>

/* The periods assigned to the one-shot and auto-reload timers are 6 second and one econd respectively. */
#define mainONE_SHOT_TIMER_PERIOD pdMS_TO_TICKS( 3333 )
#define mainAUTO_RELOAD_TIMER_PERIOD pdMS_TO_TICKS( 500 )

//create reference hanlders for one-shot and auto-relaod timers
TimerHandle_t xAutoReloadTimer, xOneShotTimer;
BaseType_t xTimer1Started, xTimer2Started;


static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
  TickType_t xTimeNow;
  /* Obtain the current tick count. */
  xTimeNow = xTaskGetTickCount();
  /* Output a string to show the time at which the callback was executed. */
  Serial.print("One-shot timer callback executing ");
  Serial.println(xTimeNow/31);
}

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
  TickType_t xTimeNow;
  /* Obtain the current tick count. */
  xTimeNow = xTaskGetTickCount();
  /* Output a string to show the time at which the callback was executed. */
  Serial.print("Auto-reload timer callback executing ");
  Serial.println( xTimeNow/31 );
}

void setup()
{
  Serial.begin(9600); // Enable serial communication library.

  /* Create the one shot timer, storing the handle to the created timer in xOneShotTimer. */
  xOneShotTimer = xTimerCreate(
                      /* Text name for the software timer - not used by FreeRTOS. */
                      "OneShot",
                      /* The software timer's period in ticks. */
                      mainONE_SHOT_TIMER_PERIOD,
                      /* Setting uxAutoRealod to pdFALSE creates a one-shot software timer. */
                      pdFALSE,
                      /* This example does not use the timer id. */
                      0,
                      /* The callback function to be used by the software timer being created. */
                      prvOneShotTimerCallback );

  /* Create the auto-reload timer, storing the handle to the created timer in xAutoReloadTimer. */
  xAutoReloadTimer = xTimerCreate(
                      /* Text name for the software timer - not used by FreeRTOS. */
                      "AutoReload",
                      /* The software timer's period in ticks. */
                      mainAUTO_RELOAD_TIMER_PERIOD,
                      /* Setting uxAutoRealod to pdTRUE creates an auto-reload timer. */
                      pdTRUE,
                      /* This example does not use the timer id. */
                      0,
                      /* The callback function to be used by the software timer being created. */
                      prvAutoReloadTimerCallback );
  
  /* Check the software timers were created. */
  if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
  {
    /* Start the software timers, using a block time of 0 (no block time). The scheduler has
    not been started yet so any block time specified here would be ignored anyway. */
    xTimer1Started = xTimerStart( xOneShotTimer, 0 );
    xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );
    /* The implementation of xTimerStart() uses the timer command queue, and xTimerStart()
    will fail if the timer command queue gets full. The timer service task does not get
    created until the scheduler is started, so all commands sent to the command queue will
    stay in the queue until after the scheduler has been started. Check both calls to
    xTimerStart() passed. */
    if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
    {
      /* Start the scheduler. */
      vTaskStartScheduler();
    }
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
}