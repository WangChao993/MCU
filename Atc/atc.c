#include "atc.h"

/**
  * @brief  Initializes the ATC handle structure.
  * @param  hAtc: Pointer to the ATC handle.
  * @param  hUart: Pointer to the UART handle.
  * @param  BufferSize: Size of the RX buffer. It needs 2X memory.
  * @param  pName: Name identifier for the ATC.
  * @retval true if initialization is successful, false otherwise.
  */
 bool ATC_Init(ATC_HandleTypeDef* hAtc, const char* pName, void (*send)(const char *str))
 {
   bool answer = false;
   do
   {
     if (hAtc == NULL)
     {
       break;
     }
     memset(hAtc, 0, sizeof(ATC_HandleTypeDef));
     if (pName != NULL)
     {
       strncpy(hAtc->Name, pName, sizeof(hAtc->Name) - 1);
     }
     if (send != NULL)
     {
       hAtc->send = send;
     }
     answer = true;
    }while (0);

    return answer;
}
/**
  * @brief  Sets the ATC event handlers.
  * @param  hAtc: Pointer to the ATC handle.
  * @param  psEvents: Pointer to the event handler structure.
  * @retval true if events are set successfully, false otherwise.
  */
 bool ATC_SetEvents(ATC_HandleTypeDef* hAtc, const ATC_EventTypeDef* psEvents)
 {
   bool answer = false;
   uint32_t ev = 0;
   do
   {
     if (hAtc == NULL)
     {
       break;
     }
     if (psEvents == NULL)
     {
       break;
     }
     while ((psEvents[ev].Event != NULL) && (psEvents[ev].EventCallback != NULL))
     {
       ev++;
     }
     hAtc->psEvents = (ATC_EventTypeDef*)psEvents;
     hAtc->EventCount = ev;
     answer = true;
 
   } while (0);
 
   return answer;
 }

 /**
  * @brief  Set callback for command.
  * @param  hAtc: Pointer to the ATC handle.
  * @param  psCmds: Pointer to the command callback.
  * @retval bool true if succeed.
  */
bool ATC_SetCommands(ATC_HandleTypeDef *hAtc, const ATC_CmdTypeDef *psCmds)
{
  bool answer = false;
  uint32_t cmd = 0;
  do
  {
    if (hAtc == NULL || psCmds == NULL)
    {
      break;
    }
    // Count the number of commands (terminated by {NULL, NULL})
    while (psCmds[cmd].pCmd != NULL && psCmds[cmd].CmdCallback != NULL)
    {
      cmd++;
    }
    hAtc->psCmds = (ATC_CmdTypeDef*) psCmds;
    hAtc->CmdCount = cmd;
    answer = true;

  } while (0);

  return answer;
}


void ATC_CheckEvents(ATC_HandleTypeDef* hAtc,   char *rx_data)
{
 // if (hAtc->RxIndex > 0)
  {
    bool command_processed = false;
    bool event_processed = false;
    // 1. Check for AT commands first
    for (uint32_t i = 0; i < hAtc->CmdCount; i++)
    {
      const char *prefix = hAtc->psCmds[i].pCmd;
      if (strncmp(rx_data, prefix, strlen(prefix)) == 0)
      {
        // Extract arguments (e.g., "ON" from "AT+LED=ON")
        const char *args = rx_data + strlen(prefix);
        char response[64];
        hAtc->psCmds[i].CmdCallback(args, response);
        // Send response (use TX buffer)
        if (hAtc->send != NULL)
        {
          hAtc->send(response);
        }
        
        // snprintf((char*) hAtc->pTxBuff, hAtc->Size, "%s\r\n", response);
        // ATC_TxRaw(hAtc, hAtc->pTxBuff, strlen((char*) hAtc->pTxBuff));
        command_processed = true;
        break;
      }
    }
    // 2. If no command matched, check for events (original behavior)
    if (!command_processed)
    {
      for (uint32_t ev = 0; ev < hAtc->EventCount; ev++)
      {
        // char *found = strstr(rx_data, hAtc->psEvents[ev].Event);
        // if (found != NULL)
        // {
        //   hAtc->psEvents[ev].EventCallback(found);
        //   event_processed = true;
        //   break;
        // }
        const char *cmd =  hAtc->psEvents[ev].Event;
        if (strncmp(rx_data, cmd, strlen(cmd)) == 0)
        {
          hAtc->psEvents[ev].EventCallback(rx_data);
          event_processed = true;
          break;
        }
      }
    }
    if ((!command_processed) && (!event_processed))
    {
      if (hAtc->send != NULL)
      {
        hAtc->send("NO command +ERROR");
      }
      
      // snprintf((char*) hAtc->pTxBuff, hAtc->Size, "%s\r\n", "+ERROR");
      // ATC_TxRaw(hAtc, hAtc->pTxBuff, strlen((char*) hAtc->pTxBuff));
    }
    // ATC_RxFlush(hAtc); // Clear buffer after processing
  }
}
