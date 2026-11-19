import tkinter as tk
import serial
import time

# Serial Setup
ard = serial.Serial()
ard.port = "COM9"
ard.baudrate = 115200
ard.open()

# Main Window
main = tk.Tk()
main.title("UV Health")
main.geometry("800x600")

# Function to reset interface
def reset():
    instruction.configure(
        text="Please place the sensor in direct sunlight and then press the baseline button"
    )
    info.configure(text="")
    btn.configure(text="Take Baseline", fg="black", command=baseline)

# Take baseline measurement
def baseline():
    global base
    ard.write("t".encode("utf-8"))
    time.sleep(0.2)
    try:
        base = float(ard.readline().decode("utf-8"))
    except:
        main.after(10, baseline)
        return
    print(base)
    info.configure(text=str(base))
    instruction.configure(
        text="Now that the baseline has been taken,\nplease apply sunscreen and press the button"
    )
    btn.configure(text="Take Experimental", command=experimental)

# Calculate SPF
def experimental():
    global base
    global SPF
    ard.write("t".encode("utf-8"))
    time.sleep(0.2)
    try:
        exp = float(ard.readline().decode("utf-8"))
    except:
        main.after(10, experimental)
        return
    SPF = (1 - (exp / base))*100
    info.configure(
        text=f"{SPF:.0f} is your approximate percent of UV Blocked\n(baseline: {base:.2f}, sunscreen: {exp:.2f})"
    )
    instruction.configure(
        text="SPF calculation complete.\nPress reset to try again."
    )
    btn.configure(text="Reset", command=reset)

# Center content in a frame
content = tk.Frame(main)
content.place(relx=0.5, rely=0.5, anchor="center")

# Large instructions
instruction = tk.Label(
    content,
    text="Please place the sensor in direct sunlight and then press the baseline button",
    font=("Arial", 16),
    justify="center",
)
instruction.pack(pady=20)

info = tk.Label(content, text="", font=("Arial", 18), fg="blue", justify="center")
info.pack(pady=20)

btn = tk.Button(content, text="Take Baseline", font=("Arial", 16), width=20, command=baseline)
btn.pack(pady=10)

# Run GUI
main.mainloop()
ard.close()
