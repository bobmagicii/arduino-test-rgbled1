# Arduino: Double RGB LED Controller

Once it boots it does an RGB "Test" blinking Red, then Green, then Blue,
followed by two blinks of white. After all LEDs report ready both are put into
sligtly offset RGB Rainbow sequences forever.

# Hardware

* RGB LED 1
	* Pins: 7, 6, 5
	* Resistors: 1K (x3)

* RGB LED 2
	* Pins: 10, 9, 8
	* Resistors: 1K (x3)

# About

* Using Visual Studio Code with the Arduino extension by Microsoft:
  > https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino

* Uses "Array" library from the build in lib manager:
  > https://github.com/janelia-arduino/Array

* Uses "LibPrintf" from built-in lib manager:
  > https://github.com/embeddedartistry/arduino-printf

* Also "LibPrintf" uses:
  > https://github.com/mpaland/printf

# Instructions

1. Load the project folder in Visual Studio Code.
2. Hit CTRL+ALT+R (Rebuild) to make sure it compiles cleanly.
3. Hit CTRL+ALT+U (Update) to compile and board it.
4. After it boots, it will run through its little dance.
