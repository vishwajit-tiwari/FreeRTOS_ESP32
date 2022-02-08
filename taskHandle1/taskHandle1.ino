/**
 * FreeRTOS Task Demo 
 * 
 * Toggles LEDs AND Print "Welcome to Task Sheduler" to Console in seperate Task
 * 
 * Date : 07/02/2022
 * Author : Vishwajit Kumar Tiwari
 * License : 0BSD
*/

/*Use only one core of CPU*/
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
/*-----------------------------------*/


/*Some string to print*/
const char msg[] = "Welcome to Task Sheduler";
/*-------------------------------------------*/

/*Task handles*/
static TaskHandle_t task1_handle = NULL;
static TaskHandle_t task2_handle = NULL;
/*---------------------------------*/

//****************************************************************************************************************************************
// Tasks

/*Task: Print to Serial Terminal with Lower Priority*/
void startTask1(void *parameter) {
  
  /*Count number of charecters in string*/
  int msg_len = strlen(msg);

  //Print string to terminal
  while(1)
  {
    Serial.println();
    Serial.println(msg);
    for(int i= 0; i< msg_len; i++)
    {
      Serial.print(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
/*--------------------------------------------------*/

/*Task: Print to serial terminal with higher priority*/
void startTask2(void *parameter)
{
  while(1)
  {
    Serial.print("*");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
/*---------------------------------------------------*/

//****************************************************************************************************************************************
// Main (runs as its own task with priority 1 on core 1)


void setup() {
  
  // configure Serial (go slow so that we can watch preemption)
  Serial.begin(300);

  // Wait a moment to start (so we don't miss serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("----FreeRTOS Task Demo----");

  //print self priority 
  Serial.print("Setup and Loop task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.print(uxTaskPriorityGet(NULL));


  //Task to run forever
  xTaskCreatePinnedToCore(  
              
              startTask1,           //Pointer to the task entry function
              "task 1",             //A descriptive name for the task
              1024,                 //Stack size for task
              NULL,                 //Pointer that will be used as the parameter for the task being created
              1,                    //The priority at which the task should run
              &task1_handle,         //handle by which the created task can be referenced
              app_cpu);             //created task is not pinned to any CPU, and the scheduler can run it on any core available. 
                                    //Values 0 or 1 indicate the index number of the CPU which the task should be pinned to


  //Task to run once with higher priority
  xTaskCreatePinnedtoCore(
              
              startTask2,
              "Task 2",
              1024,
              NULL,
              2,
              &task2_handle,
              app_cpu);
}



void loop() {
  
  // Suspend the higher priority task for some intervals
  for(int i=0; i<3; i++)
  {
    vTaskSuspend(task2_handle);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(task2_handle);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  // Delete the lower priority task
  if(task1_handle != NULL)
  {
    vTaskDelete(task1_handle);
    task1_handle = NULL;
  }

}
