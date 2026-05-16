#include "atc.h"


// ATC handle
ATC_HandleTypeDef hAtc;

// Command handler for setting LED state
void Handle_LED(const char* args, char* response)
{
  puts(args);
  if (strcmp(args, "ON") == 0)
  {   
     
    strcpy(response, "SET_LED_ON\r\n");
    //strcpy(response, "+OK");
  }
  else if (strcmp(args, "OFF") == 0)
  {
    
    strcpy(response, "SET_LED_OFF\r\n");
  }
  else
  {
    strcpy(response, "+ERROR\n");
  }
}

void set_demo(const char* args, char* response)
{
  puts(args);

  int32_t data;
  if(sscanf(args, "%d", &data) == 1)
  {  
    sprintf(response, "SET_DEMO=%d\r\n", data);
  }
  else
  {
    strcpy(response, "+ERROR\r\n demo:AT+DEMO=123");
  }
}
// Command handler for querying LED state
void Handle_GetLED(const char* args, char* response)
{
  uint8_t led_state = 0;
  strcpy(response, (led_state == 0) ? "+LED:ON\n" : "+LED:OFF\n");
}

// Command table
const ATC_CmdTypeDef at_commands[] =
{
  {"AT+LED?", Handle_GetLED},  // Query LED state: "AT+LED?" -> "+LED:ON"
  {"AT+LED=", Handle_LED},     // Set LED state: "AT+LED=ON" -> "+OK"
  {"AT+DEMO=", set_demo},     // Set demo: "AT+DEMO=123" -> "+OK"
  {NULL, NULL}                 // Terminator
};

void Handle_LED_On(const char* args)
{
  puts(args);
}
void Handle_LED_Off(const char* args)
{
  puts(args);
}
const ATC_EventTypeDef at_events[] =
{
  {"+LED:ON", Handle_LED_On},
  {"+LED:OFF", Handle_LED_Off},
  {NULL, NULL}
};
 

void send(const char* str)
{
  printf("%s\r\n", str);
}
int main(void)
{
  ATC_HandleTypeDef atc;

  ATC_Init(&atc, "ATC", send);
  //
  ATC_SetCommands(&atc, at_commands);
  ATC_SetEvents(&atc, at_events);
  //
  printf("ATC_Project\n");
  ATC_CheckEvents(&atc, "AT+LED?");
  //
  ATC_CheckEvents(&atc, "AT+LED=ON");
  //
  ATC_CheckEvents(&atc, "AT+LED=OFF");
  //
  ATC_CheckEvents(&atc, "AT+LED=OFF");
  //
  ATC_CheckEvents(&atc, "AT+DEMO= 123");
  ATC_CheckEvents(&atc, "AT+DEMO=45.6");
  //
  //
  ATC_CheckEvents(&atc, "+LED:ON");
  //
  ATC_CheckEvents(&atc, "+LED:OFF12");



  puts("ATC_Project"); 

  //
  return 0;
}
