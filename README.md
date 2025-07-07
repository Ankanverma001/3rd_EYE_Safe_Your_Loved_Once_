# 👁️ 3rd EYE Smartwatch
---

### ✅ `README.md`

```markdown
# 3rd Eye Smartwatch ⌚🛡️  
**An open-source, safety-focused IoT smartwatch powered by Arduino Nano.**

The 3rd Eye Smartwatch is a wearable device designed for real-time SOS alerting, location tracking, and health monitoring. It combines GSM communication, GPS tracking, a camera, and health sensors—all built on a custom zero-PCB layout. Ideal for personal safety, senior citizens, and vulnerable groups.

---

## 🚀 Features

- 🆘 **SOS Button** – Instantly sends SMS with location to a predefined number
- 📷 **Built-in Camera** – Captures images on command (OV2640)
- 🌍 **GPS Tracking** – Real-time location with NEO-6M GPS
- 📶 **GSM Module (SIM800L)** – Sends alerts via SMS/HTTP
- 💓 **Health Monitoring** – Reads pulse and SpO₂ using MAX30102
- 🔋 **Rechargeable** – Powered by Li-Po battery with TP4056 module
- 📟 **OLED Display** – Visual interface with 0.96" I2C OLED
- 💡 **Zero PCB** – Compact and fully handwired for small footprint

---

## 🔩 Hardware Components

| Component            | Description                                |
|----------------------|--------------------------------------------|
| Arduino Nano         | Core microcontroller                       |
| SIM800L              | GSM module for SMS and HTTP alerts         |
| NEO-6M GPS           | GPS module for location tracking           |
| OV2640 Camera        | SPI camera module                          |
| MAX30102             | Pulse oximeter and heart rate sensor       |
| SSD1306 OLED         | 0.96" I2C display                          |
| TP4056 Module        | Battery charging circuit                   |
| MT3608 Boost Converter | Boosts 3.7V to 5V                         |
| Li-Po Battery        | 3.7V, 1000 mAh                             |
| Buttons              | Power, SOS, Camera                         |
| Zero PCB + Wires     | For circuit construction                   |

---

## 📁 Repository Structure

```

3rd-eye-smartwatch/
├── firmware/            # Arduino code (.ino file)
│   └── Third\_Eye.ino
├── hardware/            # Circuit diagrams and images
│   ├── schematic.pdf
│   └── pcb\_layout.png
├── docs/                # Extra documentation
│   └── images/
├── LICENSE
└── README.md

```

---

## 📷 Preview

![watch-photo](docs/images/assembled_watch.jpg)

---

## 🧠 Working Principle

1. On startup, the watch initializes GSM, GPS, OLED, camera, and health sensors.
2. Pressing the **SOS** button:
   - Sends a pre-programmed SMS to your emergency contact
   - SMS includes a **Google Maps link** with your live location
   - Optional: Triggers a camera snapshot
3. Health data is logged and displayed periodically.
4. Powered by a Li-Po battery, recharged via micro-USB.

---

## 🔌 Wiring Diagram

Refer to `hardware/schematic.pdf` for full pin connections.

| Module      | Nano Pins       |
|-------------|------------------|
| SIM800L     | TX → D2, RX ← D3 |
| GPS (NEO-6M)| TX → D4          |
| OLED        | SDA → A4, SCL → A5 |
| MAX30102    | SDA → A4, SCL → A5 |
| OV2640      | SPI Pins         |
| Buttons     | D7 (SOS), D8 (CAM) |

---

## 🛠️ Getting Started

### Prerequisites
- Arduino IDE
- Required Libraries:
  - `TinyGPS++`
  - `Adafruit_GFX` and `Adafruit_SSD1306`
  - `MAX30105`
  - `OV2640 SPI` Library

### Uploading the Code

1. Connect Arduino Nano via USB.
2. Select **Board:** "Arduino Nano"  
   **Processor:** "ATmega328P (Old Bootloader)"
3. Open `firmware/Third_Eye.ino`.
4. Upload to the board.

---

## 🧪 Testing

- Insert a working SIM card with SMS balance.
- Power the device using Li-Po or USB.
- Wait for GSM and GPS modules to lock in.
- Press SOS to test the alert system.

---

## 📄 License

This project is licensed under the MIT License.  
See the [LICENSE](LICENSE) file for details.

---

## 🙌 Contribution

Pull requests, feature suggestions, and forks are welcome!  
Create an issue for bug reports or enhancements.

---

## 🧑‍💻 Author

**Ankan Verma**  
