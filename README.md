# ENGR103_Final

## Game Description
This is the BEAT BOXER, a handheld game where the player punches to the rhythm of the CPX. There are 5 levels, each with increasing speed and difficulty.
At the start of the game, an electronic voice saying "Start." indicates the beginning of the game. A rhythm will be played using light and audio, which the user will have to mimic by punching while holding the CPX in order to advance to the next level. The game ends when either the player misses a punch, or level 5 is completed. When the game ends, the user will recieve their score on the serial monitor, counting the number of levels they completed. 

## User Inputs
```
Accelerometer: Determines whether a punch was correctly thrown with the correct timing. Range will be set to LIS3DH_RANGE_8_G. Minimum threshhold for a punch to register will be a total acceleration of 10. 
```
```
CPX Switch: Controls wheter the CPX is muted. Values are either true or false. 
```

## User Outputs
```
Neopixels: Flash with the CPX sound to indicate rhythm. 
```
```
Audio: Buzzer sounds off at 440 hz to indicate rhythm. Can be muted using the switch.  
```
```
Speech: Electronic voice that says "start" to indicate the start of the game. 
```


