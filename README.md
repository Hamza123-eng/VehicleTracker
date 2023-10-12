# I2C C++ Driver for ESP32

This C++ I2C driver is designed for ESP32 microcontrollers and provides thread-safe communication over I2C using a binary semaphore mechanism. It includes generic command execution functions, allowing users to send various I2C commands in a START-STOP-DATA format.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Installation](#installation)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Introduction

This I2C driver is tailored for ESP32 microcontrollers and facilitates seamless I2C communication with slave devices. It ensures thread safety by utilizing a binary semaphore mechanism, enabling multiple applications to send data over I2C concurrently without conflicts.

## Features

- Thread-safe I2C communication using binary semaphore.
- Support for generic command execution (START-STOP-DATA format).
- Functionality to set the slave address.
- Default values set for maximum efficiency.

## Usage

To use this I2C driver in your ESP32 project:

1. Clone or download the driver from the repository.
2. Integrate the driver into the 'components' folder of your ESP32 project.
3. Utilize the provided functions to send I2C commands and communicate with the slave devices.

## Installation

To integrate this I2C driver into your ESP32 project, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone https://gitlab.com/epteck-pk/ept-teams/digital-bravo/ept-products/ept-libs/esp-idf/idf-cpp-template.git -b component/i2c

```
