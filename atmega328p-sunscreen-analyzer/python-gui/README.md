# SunScream — UV Sunscreen Evaluation GUI

A Python desktop interface for the **ATmega328P-based SunScream implementation**, developed for an embedded systems course. The interface communicates with the microcontroller over a serial connection and compares a baseline UV sensor reading with a second reading taken with a sunscreen-treated sample.

This folder contains the **desktop software** for the sunscreen comparison application. SunScream also had a separate ESP-based Bluetooth UV exposure monitor; that implementation uses different hardware and firmware and is not covered by this GUI.

## Features

- Requests UV sensor measurements from the microcontroller over a serial port.
- Guides the user through taking a baseline measurement and a sunscreen-treated experimental measurement.
- Calculates the **relative percentage reduction in the measured UV signal**.
- Displays both measurements and the resulting percentage in a Tkinter window.
- Supports resetting the interface for another comparison.

> **Measurement limitation:** The calculated percentage is a relative attenuation measurement from this sensor setup, **not a validated sunscreen SPF rating**. The variable named `SPF` in the original code stores the percentage of signal reduction, not an SPF factor.

## Requirements

- Python 3 with Tkinter support (typically included in standard Windows Python installations)
- [pyserial](https://pyserial.readthedocs.io/) (`requirements.txt`)
- Compatible ATmega328P hardware and GUVA UV sensing circuit
- Microcontroller firmware that implements the serial request/response behavior described below
- USB/serial connection to the microcontroller

The current Python code is configured for **Windows COM9**. No serial-port selection interface is implemented.

## Installation

From this directory, install the dependency:

```powershell
python -m pip install -r requirements.txt
```

On Windows, use `py -m pip install -r requirements.txt` if `python` is not recognized.

To launch the GUI:

```powershell
python main.py
```

The serial device must be available when the program starts: `main.py` opens the port **before** creating the GUI window.

## Serial configuration

The connection settings are hard-coded near the beginning of `main.py`:

```python
ard.port = "COM9"
ard.baudrate = 115200
```

Change `COM9` to the serial port assigned to your controller (check **Device Manager → Ports (COM & LPT)** on Windows). The microcontroller firmware must use the same baud rate.

**Serial request/response:**

1. Python sends one UTF-8 encoded character: `t`.
2. Python waits 0.2 seconds.
3. Python attempts to read one line using `readline()`.
4. The received line is decoded as UTF-8 and parsed as a floating-point number.

For reliable operation, firmware should return a **numeric, newline-terminated** measurement for each request. The GUI assumes a readable numeric response; it does not document or enforce measurement units.

## Using the application

1. Connect the ATmega328P-based UV sensor hardware to the computer.
2. Confirm the serial port and 115200 baud configuration match the firmware.
3. Start `main.py`.
4. Place the sensor in direct sunlight as instructed by the interface, and select **Take Baseline**.
5. Apply sunscreen to the experimental test sample and select **Take Experimental**, keeping other measurement conditions as consistent as possible.
6. Read the displayed percentage of measured UV signal blocked, along with the baseline and experimental readings.
7. Select **Reset** to take a new pair of readings.

The interface calculates:

\[
\text{Measured UV reduction (\%)} = \left(1 - \frac{\text{Experimental reading}}{\text{Baseline reading}}\right) \times 100
\]

For example, if the baseline reading is `100` and the experimental reading is `25`, the measured signal reduction is `75%`.

## Project structure

```text
python-gui/
├── main.py           # Tkinter GUI and serial measurement logic
├── requirements.txt  # External Python dependency
└── README.md         # Setup, usage, and serial protocol
```

## Current limitations

The implementation is preserved as originally written. Known limitations include:

- **Fixed serial port:** `COM9` must be changed manually for other computers.
- **Hardware required:** No demonstration or simulated-data mode is available.
- **No serial timeout:** If a valid numeric line is not received, `readline()` can block indefinitely.
- **Retry behavior:** Failed parsing triggers another measurement attempt; the code does not impose a maximum retry count.
- **No zero-baseline handling:** A baseline of zero will cause a division-by-zero error during the comparison.
- **Limited error handling:** An unavailable port prevents startup, and unexpected serial communication errors may not be handled gracefully.
- **Single-measurement comparison:** The GUI uses one baseline reading and one experimental reading, with no averaging or uncertainty estimate.

These limitations are useful starting points for future improvements, but they are **not** addressed by this README or the requirements file.

## Scope

This is the desktop interface for the **ATmega328P SunScream sunscreen evaluation implementation**. It does not implement the ESP-based Bluetooth/phone monitor or provide cumulative UV exposure visualization in the uploaded `main.py`.
