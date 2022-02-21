# IoT BBQ STM32

## Build from Visual Studio

The [IoT_BBQ_STM32](https://github.com/gojimmypi/IoT_BBQ/blob/main/IoT_BBQ_STM32/IoT_BBQ_STM32.sln) is a Visual Studio 2019 solution file with a SysProgs VisualGDB extension project.

Build simply by right-click and build...

![sysprogs_visualgdb_build.png](../images/sysprogs_visualgdb_build.png)


## Build from a batch file:

Assumes toolchain is installed in: `c:\SysGCC\arm-eabi\bin\arm-none-eabi-gcc.exe`

```
SET WORKSPACE=C:\workspace\
c:
if not exist "%WORKSPACE%" mkdir "%WORKSPACE%"

cd "%WORKSPACE%"
if exist "%WORKSPACE%" goto error

git clone https://github.com/gojimmypi/IoT_BBQ.git
cd "%WORKSPACE%"
cd IoT_BBQ\IoT_BBQ_STM32


goto done
:error
echo Error 

:done
echo done!

```

For more information, see [Final Project](../Assignments/Final_Project.md).

Testing the new [Include diagrams in your Markdown files with Mermaid](https://github.blog/2022-02-14-include-diagrams-markdown-files-mermaid/) feature:

```mermaid
  graph TD;
      A-->B;
      A-->C;
      B-->D;
      C-->D;
```


```mermaid
graph TD
    A[Startup] -->|Init| B(Start Threads)
    B --> LED1[LED1 Blinky]
    B --> LED2[LED2 Blinky]
    B --> UART
    B --> DISPLAY
    B --> PWM[PWM]
    LED1 --> ShowWeight[Display Weight]
    ShowWeight --> ShowPressure[Display Pressure]
    ShowPressure --> Blinky1State{LED_GetMode}
    Blinky1State --> |IsBlinking| LED1_blink[LED1 Blink]
    Blinky1State --> |AlwaysOn| LED1_On[LED1 On]
    Blinky1State --> |AlwaysOff| LED1_Off[LED1 Off]
    Blinky1State --> |default| LED1_default[Set Mode IsBlinking]
    LED1_blink --> ShowWeight
    LED1_On --> ShowWeight
    LED1_Off --> ShowWeight
    LED1_default --> ShowWeight
    PWM -->|One| D[experiments]
```

```mermaid
graph TD
    A[Startup] -->|Init| B(Start Threads)
    B --> LED1[LED1 Blinky]
    B --> LED2[LED2 Blinky]
    B --> UART
    B --> DISPLAY_Thread1[Display]
    B --> PWM[PWM]

    LED1 --> ShowWeight[Display Weight]
    ShowWeight --> ShowPressure[Display Pressure]
    ShowPressure --> Blinky1State{LED_GetMode}
    Blinky1State --> |IsBlinking| LED1_blink[LED1 Blink]
    Blinky1State --> |AlwaysOn| LED1_On[LED1 On]
    Blinky1State --> |AlwaysOff| LED1_Off[LED1 Off]
    Blinky1State --> |default| LED1_default[Set Mode IsBlinking]
    LED1_blink --> ShowWeight
    LED1_On --> ShowWeight
    LED1_Off --> ShowWeight
    LED1_default --> ShowWeight

    LED2 --> Blinky2State{LED_GetMode}
    Blinky2State --> |IsBlinking| LED2_blink[blink_Count = 1]
    Blinky2State --> |AlwaysOn| LED2_On[blink_Count = 2]
    Blinky2State --> |AlwaysOff| LED2_Off[blink_Count = 3]
    Blinky2State --> |default| LED2_default[blink_Count = 4]
    LED2_blink --> LED2
    LED2_On --> LED2
    LED2_Off --> LED2
    LED2_default --> LED2

    DISPLAY_Thread1 --> InitDisplay
    InitDisplay --> CheckForLongPress{Long Press?}
    CheckForLongPress --> |yes|Tare
    CheckForLongPress --> |no|ShowWeightDisplay
    Tare --> ShowWeightDisplay
    ShowWeightDisplay --> CheckForLongPress


    PWM -->|One| D[experiments]


```  


```mermaid
graph TD
    A[Startup] -->|Init| B(Start Threads)
    B --> LED1[LED1 Blinky]
    B --> LED2[LED2 Blinky]
    B --> UART
    B --> DISPLAY_Thread1[Display]
    B --> PWM[PWM]
```


```mermaid
graph TD
    LED1 --> ShowWeight[Display Weight]
    ShowWeight --> ShowPressure[Display Pressure]
    ShowPressure --> Blinky1State{LED_GetMode}
    Blinky1State --> |IsBlinking| LED1_blink[LED1 Blink]
    Blinky1State --> |AlwaysOn| LED1_On[LED1 On]
    Blinky1State --> |AlwaysOff| LED1_Off[LED1 Off]
    Blinky1State --> |default| LED1_default[Set Mode IsBlinking]
    LED1_blink --> ShowWeight
    LED1_On --> ShowWeight
    LED1_Off --> ShowWeight
    LED1_default --> ShowWeight
```