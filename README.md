# ESP-IDF C++ Template with FreeRTOS Addon

## Introduction

This project provides a C++ template for ESP-IDF (Espressif IoT Development Framework) with an added FreeRTOS (Real-Time Operating System) addon. It includes a LED and GPIO class for easy hardware interaction. Additionally, there's an example application demonstrating how to blink an LED using the GPIO class and FreeRTOS threads.

## Author

- **Name:** Hamza Islam
- **Organization:** Epteck

## Getting Started

### Prerequisites

- Install ESP-IDF: Follow the [ESP-IDF Installation Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) to set up the ESP-IDF development environment.

### Clone the Repository

Clone this repository to your local development environment:

```bash
git clone https://gitlab.com/epteck-pk/ept-teams/digital-bravo/ept-products/ept-libs/esp-idf/idf-cpp-template.git
cd idf-cpp-template
idf.py build
idf.py flash monitor
```
