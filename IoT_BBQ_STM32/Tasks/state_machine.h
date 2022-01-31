// state_machine.h
#pragma once

#ifndef _state_machine_h
#define _state_machine_h

#ifdef __cplusplus
extern "C" {
#endif

    int state_machine_VERSION();

    enum AppState { Startup, Running, Demo, Sleeping, Error };

    
    enum AppState GetAppState();
    int SetAppState(enum AppState NewState);

#ifdef __cplusplus
}
#endif     

#endif // _state_machine_h
