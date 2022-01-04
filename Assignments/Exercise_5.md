# Exercise 5: State Machine Socumentation

- 1 Start putting together a plan for your final project. Given the chapter, the main goal is to
put together state machine documentation. This can be a flowchart or (preferably) a
state table. You may also need to create the diagrams from Lesson 2 to flesh out the
design. Note: this design planning, thinking through the system, what you have and
what you need. Keep in mind that these will not be the final version!

** State  **|** Action **|** Display **|** Sensor **|** Off **|**   Mode  **|** Button **|** Timeout **
:----------:|:----------:|:-----------:|:----------:|:-------:|:-----------:|:----------:|:-----------:
Start       |        init|  Hello      |READ\_WEIGHT|         |             |            | 
CHOOSE\_MODE| Show Mode  |   read      |READ\_WEIGHT|         |             |            | 
GOODBYE     | Save       |        BYE  |            |         |             |            | 
RUN         |  Get Weight|  Show Weight|READ\_WEIGHT| GOODBYE | CHOOSE\_MODE|            | RUN
TARE        | init sensor| Show Tare   |READ\_WEIGHT| GOODBYE | CHOOSE\_MODE|            | RUN
RESET       |  clear tare|  Show Reset |CLEAR\_TARE | GOODBYE | CHOOSE\_MODE|            | RUN
OFF         |            |Show Shutdown|  x         |  x      | x           |            | x    

- 2 Extra credit: Al Sweigart wrote many small games in Python. They are keyboard input so
they don’t have very fancy graphics. As with toys, most games have a huge state
machine. Document the state machine for one of the games, suggested examples are
blackjack.py, conwaysgameoflife.py, snailrace.py, zombiebitefight.py,and montyhall.py.
You do not need it to run to play the game but if you do and don’t have python set up,
you can put them in a new Python notebook at https://colab.research.google.com/

<< [Exercise 4](./Exercise_4.md) -- [Assignments](./README.md) -- [tbd]() >>