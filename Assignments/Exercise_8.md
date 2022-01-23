# Exercise 8 Heap and Atack Pointers

Compile your project code so it prints out the heap pointer and the stack pointer. Print out a global variable address. 
If you can find it, modify your linker file to swap your uninitialized variables and initialized variables. 
Verify it is as expected in the memory map. See how that changes your code output. 

Turn in your notes on what you found to Discord #assignment-submission by 9am on Jan 29th. 

Note: there will be more detailed hints on how to do this as the week goes on. If you get stuck, look in the Discord #homework-help for a Hints thread.

## Stack Pointers

Variables in functions are stored on the stack. Thank you [stackoverflow for the reminder on how to determine the address of a variable on the stack](https://stackoverflow.com/questions/20059673/print-out-value-of-stack-pointer),
which of course is the most recent stack pointer:

```
        void* p = NULL;
        volatile long myStackPointer = (long)((void*)&p);
```

VisualGDB has the capability of showing live FreeRTOS environment details:

Here the newly-allocated address of `p` has a value of `0x200013F0`:

![stack_pointer_example](./images/stack_pointer_example.png)

We can also observe that FreeRTOS apparently has (72-8 = 64) bytes of overhead on the stack, probably for the pre-emptive scheduler. 
Also shown is the stack starting in this thread at `0x200013e8`. 

The next value of the stack pointer was `0x200013e8` after allocation of `int *q`. (`0x200013F0 - 0x200013e8 = 8` byte change: the size of the `volatile long myStackPointer2`.

```
    void* p = NULL;
    volatile long myStackPointer = (long)((void*)&p);
    
    void* q = NULL;
    volatile long myStackPointer2 = (long)((void*)&q);

    int* r = (int*)0xAD;
    volatile long myStackPointer3 = (long)((void*)&r);
```

## Heap Size and Pointers

The heap size and pointers are a bit more interesting, particularly since the [Final Project](./Final_Project.md) is using and RTOS. The [FreeRTOS Memory Management](https://www.freertos.org/a00111.html) documentation was helpful here. 
In particular the [heap_4.c xPortGetFreeHeapSize()](https://github.com/STMicroelectronics/STM32CubeL4/blob/f93a2f74f8e9912405dbf1a297b6df0c423eddf2/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c#L315) found in the 
[Github.com/STMicroelectronics/STM32CubeL4](https://github.com/STMicroelectronics/STM32CubeL4/) library. This code was also found to have been installed via STH32Cube here:

```
C:\Users\gojimmypi\STM32Cube\Repository\STM32Cube_FW_L4_V1.17.1\Middlewares\Third_Party\FreeRTOS\Source\portable\MemMang
```



<< [Exercise 7](./Exercise_7.md) -- [Assignments](./README.md) --  [TBD]() >>