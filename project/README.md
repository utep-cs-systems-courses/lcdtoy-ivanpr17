# LCD Toy

### Description
Project mimics a toy. Uses lcd screen, plays music, and uses switches to make
music and move shapes that are in the lcd screen 

### Downloading Project
After connecting the msp430 to the computer and once within the project
folder, run these commands:

```
make
make load
```
- Note: make sure the Makefile in the main is also made

### Running the Project
Once the project is running on the msp430, there are 4 implemented to use
switches. Below are the what the switches do:

- SW1 : Plays a loose (very loose) rendition of The Legend of Zelda theme
- SW2 : advances state of shapes in lcd screen to depict movement
- SW3 : Prints "Lab 3" String and unique shape
- SW4 : Plays a found item chime

### Cleaning Project Folder
```
make clean
```

### File Descriptions
- Buzzer files: Sets up buzzer and makes methods callable from other files. contains 2 different songs
- ShapeMotion files: Turns on the lcd screen and draws shapes on it.
- Switches files: Turns on and modifies code output based on user input
- main: makes sure everything is initialized correctly.

