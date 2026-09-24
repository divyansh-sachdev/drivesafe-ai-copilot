<div align="center">

# DriveSafe AI Co-Pilot

**Driver drowsiness detection via Eye Aspect Ratio with an ESP32 haptic alert companion**

![Domain](https://img.shields.io/badge/Domain-Computer_Vision-00F3FF?style=for-the-badge) ![Pipeline](https://img.shields.io/badge/Pipeline-Python_+_ESP32-9D00FF?style=for-the-badge) ![Method](https://img.shields.io/badge/Method-EAR_Temporal-0066FF?style=for-the-badge)

![Python](https://img.shields.io/badge/Python-0D1117?style=flat-square&logo=python&logoColor=white) ![OpenCV](https://img.shields.io/badge/OpenCV-0D1117?style=flat-square&logo=opencv&logoColor=white) ![MediaPipe](https://img.shields.io/badge/MediaPipe-0D1117?style=flat-square) ![NumPy](https://img.shields.io/badge/NumPy-0D1117?style=flat-square&logo=numpy&logoColor=white) ![ESP32](https://img.shields.io/badge/ESP32-0D1117?style=flat-square&logo=espressif&logoColor=white)

</div>

---

## Overview

A driver monitoring system that detects microsleep from eyelid geometry and fires a physical alert
through an ESP32 companion board driving vibration motors in the steering wheel or seat.

The detection method is Eye Aspect Ratio (EAR) — the ratio of vertical to horizontal eye landmark
distances, which collapses toward zero as the eyelid closes. The critical design decision is the
*temporal* threshold: a single low-EAR frame is a blink, which every driver does constantly. Only a
sustained run of consecutive low-EAR frames indicates microsleep, and that consecutive-frame
requirement is what separates a useful alarm from one the driver disables within a minute.

## Domain &amp; Techniques

| Layer | Implementation |
| :--- | :--- |
| **Landmark Geometry** | Eye Aspect Ratio computed as (&#8741;p2&minus;p6&#8741; + &#8741;p3&minus;p5&#8741;) / (2 &times; &#8741;p1&minus;p4&#8741;) over the eye landmark set |
| **Blink Rejection** | A configurable `consecutive_frames` counter (default 20) requires sustained closure before tripping — isolated low-EAR frames are discarded as normal blinks |
| **Thresholding** | `ear_threshold` default 0.25, below the nominal open-eye value of ~0.28 |
| **State Latching** | Alarm state latches on trip and clears when EAR recovers, so the alert does not chatter at the boundary |
| **Hardware Alert** | Serial link to an ESP32 (`DriverAlertBuzzer.ino`) driving buzzer and vibration output independently of the host machine |

## Pipeline

```
camera frame --> face landmarks --> eye landmark set
                                          |
                                          v
                    EAR = (|p2-p6| + |p3-p5|) / (2 * |p1-p4|)
                                          |
                                          v
                              [ EAR < 0.25 ? ]
                                    |      |
                                   no     yes
                                    |      |
                            reset counter  counter++
                                           |
                                    [ counter >= 20 consecutive frames ]
                                           |
                                          yes
                                           v
                              DROWSINESS ALARM --> serial --> ESP32
                                                              buzzer + haptic
```

## Requirements

```bash
pip install -r requirements.txt
python drivesafe_detector.py
```

## Repository Layout

| Path | Purpose |
| :--- | :--- |
| `drivesafe_detector.py` | `DrowsinessDetector` — EAR computation, consecutive-frame logic, alarm latching |
| `DriverAlertBuzzer.ino` | ESP32 companion firmware — buzzer and vibration motor driver |
| `requirements.txt` | Python dependencies |

## Project Status

**Implemented:** the detection state machine — EAR thresholding, consecutive-frame blink rejection,
and alarm latching — plus the ESP32 hardware alert path.

**Roadmap:** `compute_ear()` is currently a stub returning a nominal value, and `process_frame()`
accepts an injected EAR for testing the state machine in isolation. Wiring the real perception front
end is the outstanding work: MediaPipe Face Mesh supplies a 468-point 3D facial landmark set, from
which the six per-eye landmarks feed the existing EAR formula unchanged. Head-pose estimation
(solvePnP against the same landmark set) for distraction detection follows on the same input.

---

<div align="center">
  <sub>
    Part of the <b>AI + Robotics</b> engineering portfolio of
    <a href="https://github.com/divyansh-sachdev">Divyansh Sachdev</a><br>
    90+ national &amp; international competition wins &middot; IIT / NIT / IIIT podiums
  </sub>
</div>
