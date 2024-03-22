# PicoReminder

This project is a simple reminder application for the Raspberry Pi Pico W board that uses the onboard led and a button. I created this to remind myself that I had already done something earlier in the day.

## Description

This application sets an alarm for 4 AM every day. When the alarm time is reached, the application will turn on the onboard LED and listen for a button press. If the button is pressed, the alarm will be turned off and the LED will be turned off.

Written in C++ using the PlatformIO framework. 
It uses the built-in RTC to keep track of the current date and time, and it can set an alarm at a specific time.

## Getting Started

### Prerequisites

- PlatformIO Core. You can download it from [here](https://platformio.org/install/cli). Or you can use the PlatformIO extension for VSCode.
- Raspberry Pi Pico W board.

### Installation

1. Clone this repository to your local machine using `git clone <repo_url>`.
2. Navigate to the project directory.
3. Run `platformio run` to compile the project.
4. Run `platformio run --target upload` to upload the compiled code to your board.

### Usage

Set the current time by changing the `current_datetime` variable in the `src/main.cpp` file.