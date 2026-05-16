#ifndef ATC_H
#define ATC_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include<stdio.h>


typedef struct
{
  char*                      pCmd;
  void                       (*CmdCallback)(const char* args, char* response); 

} ATC_CmdTypeDef;

typedef struct
{
  char*                      Event;
  void                       (*EventCallback)(const char*);

} ATC_EventTypeDef;

typedef struct
{

  char                       Name[8];
  ATC_EventTypeDef*          psEvents;
  uint32_t                   EventCount;
  ATC_CmdTypeDef*            psCmds;     
  uint32_t                   CmdCount;  
  //
  void  (*send)(const char *str);

} ATC_HandleTypeDef;

bool    ATC_Init        (ATC_HandleTypeDef* hAtc, const char* pName, void (*send)(const char *str));
bool    ATC_SetEvents   (ATC_HandleTypeDef* hAtc, const ATC_EventTypeDef* psEvents);
bool    ATC_SetCommands (ATC_HandleTypeDef* hAtc, const ATC_CmdTypeDef* psCmds);
//
void ATC_CheckEvents(ATC_HandleTypeDef* hAtc,   char *rx_data);

#endif
