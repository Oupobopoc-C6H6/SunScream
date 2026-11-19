# SunScream — UV Monitoring and Sunscreen Analysis

SunScream is a UV-sensing project developed in two independent implementations for engineering coursework at the University of South Florida. Both use a GUVA-series ultraviolet sensor, but differ in their microcontroller, communication interface, and intended application.

The project explores embedded sensor acquisition, UV measurement and analysis, hardware design, and wired versus wireless communication. **These are two separate hardware/firmware designs**, not modes of a single device.

## Implementations

| | ESP32 UV Exposure Monitor | ATmega328P Sunscreen Analyzer |
| --- | --- | --- |
| Platform | ESP32-WROOM-32 | ATmega328P |
| Interface | Bluetooth serial to Android phone | Serial link to Python desktop GUI |
| Main function | Estimate and accumulate UV exposure; sound a threshold alert | Compare baseline and sunscreen-test UV measurements |
| Additional work | Outdoor sensor characterization, enclosure, circuit design | Desktop GUI and measurement workflow |
| Project details | [ESP32 implementation](esp32-exposure-monitor/README.md) | [ATmega328P implementation](atmega328p-sunscreen-analyzer/) |

### ESP32 — Wireless UV Exposure Monitor

This implementation combines a GUVA-S12SD UV sensor, an analog interface, an ESP32-WROOM-32, and a buzzer. The firmware samples the sensor, estimates UV exposure using an empirical relationship, and sends readings to an Android Bluetooth serial terminal. An audible alert activates when the accumulated estimate exceeds the firmware's experimental threshold.

Outdoor characterization compared ESP32 ADC readings with reported UV Index values. The team report includes the test methodology, regression analysis, results, limitations, enclosure design, and individual author contributions.

**[Explore the ESP32 implementation](esp32-exposure-monitor/README.md)** · **[Read the technical report](esp32-exposure-monitor/docs/SunScream.pdf)**

### ATmega328P — Desktop Sunscreen Analyzer

This separately developed version uses an ATmega328P to acquire UV sensor measurements and communicate with a Python/Tkinter GUI over serial. The GUI takes a baseline measurement, accepts a second measurement with a sunscreen-treated sample, and displays the relative reduction in measured UV response.

The software's percentage reduction is **not a validated SPF measurement**.

**[Explore the ATmega328P implementation](atmega328p-sunscreen-analyzer/)** · **[Python GUI instructions](atmega328p-sunscreen-analyzer/python-gui/README.md)**

## Repository layout

```text
SunScream/
├── README.md
├── atmega328p-sunscreen-analyzer/
│   ├── python-gui/
│   ├── UV_Sensor_Firmware/
│   ├── UV_Sensor_PCB/
│   └── ...
└── esp32-exposure-monitor/
    ├── CAD/
    ├── SunScreamFirmware/
    ├── SunScreamSchematic/
    ├── docs/
    │   └── SunScream.pdf
    └── README.md
```

The layout above uses the existing directory names where known. The two applications can be explored independently.

## Notes on interpretation

SunScream is an educational engineering prototype, **not a calibrated UV dosimeter or medical safety device**. Its UV Index estimates depend on the calibration setup and sensor behavior. The ESP32 report discusses high measurement variability and limited response at low reported UV Index values. The sunscreen comparison is a relative measurement and should not be presented as a certified SPF test.

## Attribution

The ESP32 work and its technical report were completed by **J. A. Groom, A. T. Carr, and C. C. Harmon**. See the [report](esp32-exposure-monitor/docs/SunScream.pdf) for the team members' individual contributions. The ATmega328P implementation was developed separately for embedded systems coursework.
