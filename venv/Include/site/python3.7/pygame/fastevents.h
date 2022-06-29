#ifndef _FASTEVENTS_H_
#define _FASTEVENTS_H_


#include "SDL.h"

#ifdef __cplusplus
extern "C" {
#endif

  int FE_Init(void);                     
  void FE_Quit(void);                    

  void FE_PumpEvents(void);              
  int FE_PollEvent(SDL_Event *event);    
  int FE_WaitEvent(SDL_Event *event);    
  int FE_PushEvent(SDL_Event *event);    

  char *FE_GetError(void);               
#ifdef __cplusplus
}
#endif

#endif
