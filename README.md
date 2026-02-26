# DriveSafe AI Co-Pilot

An edge-AI vehicle safety system that actively tracks driver alertness, blinks, yawn frequency, and head yaw/pitch distraction using computer vision. When microsleep or distraction exceeds safe limits, it instantly triggers high-intensity audio-haptic feedback via an ESP32 hardware companion.

## Features

- **Eye Aspect Ratio (EAR)**: Real-time geometric analysis of eyelid closure with sub-30ms latency.
- **Head Pose Estimation**: Identifies when the driver is looking down at a phone or away from the windshield.
- **Hardware Fail-Safe Alert**: Direct serial linkage to an ESP32 controlling vibration motors embedded in the steering wheel or seat.

## Requirements

```bash
pip install -r requirements.txt
python drivesafe_detector.py
```
