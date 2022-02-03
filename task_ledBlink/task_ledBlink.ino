
/*----Use only core-1 for demo purpose----*/

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
/*----------------------------------------*/


/*----------Pins-----------------------*/
//static const int led_1 = LED_BUILTIN;
static const int led_1 = 23;
//static const int led_2 = 22;
/*-------------------------------------*/


/*----Our task 1: Blink an LED-1 at rate_1----*/

void toggleLED_1(void * parameter) 
{
  while(1) 
  {
    digitalWrite(led_1, HIGH);
    Serial.println("LED-1 is ON");
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    digitalWrite(led_1, LOW);
    Serial.println("LED-1 is OFF");
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
/*-------------------------------------------*/


/*----Our task 2: Blink an LED-2 at rate_2----*/

void toggleLED_1_rate_2(void * parameter) 
{
  while(1) 
  {
    digitalWrite(led_1, HIGH);
    Serial.println("LED-1 rate_2 is ON");
    vTaskDelay(300 / portTICK_PERIOD_MS);
    
    digitalWrite(led_1, LOW);
    Serial.println("LED-1 rate_2 is OFF");
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}
/*-------------------------------------------*/


void setup() {

  /*Configure pins*/
  pinMode(led_1, OUTPUT);
  Serial.begin(115200);
  
  BaseType_t task_fd, task_fd2;   /*Return type of Task Create function*/
  
  
  /*Task to run forever*/
  task_fd = xTaskCreatePinnedToCore (        // Use xTaskCreate() in Vanilla FreeRTOS
                    
                        toggleLED_1,         // Function to be called 
                        "Toggle LED-1",      // Name of the task
                        1024,                // Stack size (Bytes in ESP32, Words in FreeRTOS)
                        NULL,                // Parameters to pass to functions
                        1,                   // Task priority (0 to configMAX_PRIORITIES -1 i.e. (0 to 25-1))
                        NULL,                // Task handle 
                        app_cpu);            // Run on one core for demo purpose (ESP32 only)

  /*If this was Vanilla FreeRTOS, you'd want to call vTaskStartScheduler() in*/
  /*main after setting up your tasks*/

  if(task_fd == pdPASS) {
    Serial.println("Task Toggle LED-1 created successfully");
  }
  else {
    Serial.println("Toggle LED-1 task faild");
  }
  /*----------------------------------------------------------------------*/

  /*--------------------------------Task 2---------------------------------*/
  task_fd2 = xTaskCreatePinnedToCore (toggleLED_1_rate_2, "Toggle LED-1 rate_2", 1024, NULL, 1, NULL, app_cpu);
  
  if(task_fd2 == pdPASS) {
      Serial.println("Task Toggle LED-1 rate_2 created successfully");
  }
  else {
      Serial.println("Toggle LED-1 rate_2 task faild");  
  }
  /*-----------------------------------------------------------------------*/

}

void loop() {
  // put your main code here, to run repeatedly:

}
