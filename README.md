# 🍺 Alcohol Detection System using LPC17xx Microcontroller

An **Embedded C project** built on the **LPC17xx ARM Cortex-M3 microcontroller** to detect alcohol concentration using a sensor and provide alerts via **LCD display** and **buzzer**.  

This project demonstrates how **microcontrollers interface with sensors, ADC, and peripherals** to build a real-world **safety system**.

---

## 📌 Features
- 🚗 Detects alcohol concentration in real-time using an alcohol/gas sensor.  
- 📟 Displays alcohol percentage on a 16x2 LCD.  
- 🚨 Activates buzzer alert when alcohol exceeds a threshold.  
- ⚡ Efficient use of ADC and peripheral libraries for LPC17xx.  

---

## 🛠️ Hardware Requirements
- **LPC17xx (ARM Cortex-M3) Microcontroller**  
- **MQ-3 Alcohol/Gas Sensor**  
- **16x2 LCD Display**  
- **Buzzer**  
- **Resistors, Breadboard, Power Supply**  

---

## 💻 Software Requirements
- **Embedded C**  
- **Keil uVision IDE** (ARM toolchain)  
- **Flash Magic** (for programming LPC17xx)  
- (Optional) **Proteus / Multisim** for simulation  

---

📦 Project Root    
|── 📂 src/    
|   |── main.c    
|      
|── 📂 docs/      
|   |── block_diagram.png    
|   |── prerequisites.png    
|   |── output_1.png    
|   |── output_2.png    
|   |── output_3.png      
|    
|── 📄 README.md    
|── 📄 LICENSE      


---

## ⚙️ Working Principle
1. The **MQ-3 sensor** detects alcohol vapors and generates an analog signal.  
2. The **LPC17xx ADC** converts this analog signal into a digital value.  
3. The value is processed to calculate alcohol concentration.  
4. The **LCD** displays the percentage, while the **buzzer** alerts when the threshold is exceeded.  

---

## 📸 Demo
(Add images or GIFs here if you have circuit photos or simulation screenshots.)  

---

## 🔮 Future Improvements
- 📡 Integrate with **GSM / Wi-Fi module** to send alerts remotely.  
- 🚦 Add **ignition lock system** for vehicles.  
- 📊 Log alcohol concentration data for monitoring.  

---

## 📜 License
This project is licensed under the **MIT License** – feel free to use and modify.  

