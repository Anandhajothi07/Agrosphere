# AgroSphere

Welcome to the **Agrosphere Projects Repository**! This repository serves as a comprehensive hub for our innovative agricultural automation projects, aiming to revolutionize farming practices with cutting-edge technology. Below are the highlights of our projects:

---

## 🚜 **Automated Irrigation System**

### Overview
This project automates irrigation based on soil moisture levels to optimize water usage and promote sustainable farming.

### Key Features
- **Mobile App Control**: Manage irrigation remotely using the "Way of Water" app.
- **Real-Time Monitoring**: View soil moisture levels and system status through the app.
- **Adafruit IO Integration**: Uses Adafruit IO for communication between hardware and software.
- **User-Friendly Interface**: Intuitive app design with toggle switches and live data visualization.

### Technology Stack
- **Hardware**: Soil moisture sensors, relay, and microcontroller (ESP32).
- **Software**: Flutter for the mobile app, Adafruit IO for IoT connectivity.

---

## 🌱 **Automated Soil Test Report Generator (AGRISPHERE)**

### Overview
AGRISPHERE is an automated solution to provide farmers with comprehensive soil health reports, including NPK levels, pH, EC, temperature, and humidity.

### Key Features
- **Real-Time Data Collection**: Measures NPK nutrient levels using sensors.
- **Mobile App Integration**: Delivers soil health reports and recommendations directly to the farmer's smartphone.
- **Custom Recommendations**: Provides fertilizer suggestions based on crop and location.

### Technology Stack
- **Hardware**: NPK sensors, microcontroller (ESP32).
- **Software**: Mobile app for analysis and visualization, integrated with IoT backend.

---

## 🍅 **Automated Disease Prediction Model**

### Overview
This project identifies plant diseases by analyzing leaf colors and anomalies, helping farmers take timely preventive measures.

### Key Features
- **ESP32 Camera Integration**: Captures real-time images of plant leaves.
- **Machine Learning Model**: Detects diseases based on leaf anomalies.
- **Mobile App Notification**: Alerts farmers about detected diseases with suggested actions.
- **Cloud Storage**: Stores and retrieves leaf images for processing.

### Technology Stack
- **Hardware**: ESP32 with an integrated camera module.
- **Software**: Machine learning model for disease detection, cloud-based storage, and mobile app for notifications.

---

## 📂 Repository Structure
```plaintext
.
├── Automated_Irrigation_System
│   ├── Hardware_Design
│   ├── App_Code (Way of Water)
│   └── Docs
├── AGRISPHERE
│   ├── Sensor_Integration
│   ├── App_Code
│   └── Docs
├── Disease_Prediction_Model
│   ├── ML_Model
│   ├── ESP32_Code
│   └── Docs
└── README.md
```

---

## 🤝 Contributing
We welcome contributions to enhance these projects! Please follow the guidelines in `CONTRIBUTING.md` to submit your changes or propose new features.

---

## 📜 License
This repository is licensed under the [MIT License](LICENSE). Feel free to use and modify the code for non-commercial purposes.

---

We hope these projects make a meaningful impact on modern agriculture. Happy farming! 🌾

