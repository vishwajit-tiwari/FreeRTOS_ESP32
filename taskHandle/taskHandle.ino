/*Use only one core of CPU*/
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
/*-------------------------------------*/

/*Some string to print*/
const char *msg = "Welcome to Task Sheduler";
/*------------------------------------------*/

/*Task handles*/
static TaskHandle_t task_1 = NULL;
static TaskHandle_t task_2 = NULL;
/*---------------------------------*/

/*Task: Print to Serial Terminal with Lower Priority*/
void startTask1(void *parameter) {
  
  /*Count number of charecters in string*/
  int msg_len = strlen(msg);

  //Print string to terminal
  while(1)
  {
    Serial.println();
    for(int i= 0; i< msg_len; i++)
    {
      Serial.println(msg[i]);
    }
    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
