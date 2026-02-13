# ⚙ ATABEY Autopilot Namespace-Class Listesi

Bu doküman, **Atabey İHA Otopilot yazılımının modül yapısını, namespace organizasyonunu ve temel sınıflarını** tanımlar.
Amaç; ekip içinde **isimlendirme karmaşasını önlemek**, mimariyi baştan kilitlemek ve UML diyagramları için **tek referans noktası** oluşturmaktır.

Yeni sınıf veya modül eklenirken bu liste referans alınmalıdır.

---

## 📜 Namespace Listesi

Ana modül:
```text
atabey
```

Alt modüller:

```text
atabey::core
atabey::drivers
atabey::control
atabey::comm
atabey::estimation 
atabey::utils        (opsiyonel)
```

---

# 📦 atabey::core

**Sistem orkestrasyonu & lifecycle**

**Sınıflar:**

* `Autopilot`
* `Scheduler`
* `SystemState`
* `HealthMonitor`
* `ParameterStore`
* `FlightModeManager`
* `FailsafeManager`

**Interface’ler (bağımlılık için):**

* `IController`
* `ISensor`
* `ICommLink`
* `IActuator`
* `IEstimator`

> Not: Core katmanı mümkün olduğunca **interface’ler üzerinden** diğer modüllere bağlanmalıdır.

---

# 📦 atabey::drivers

**Donanım soyutlama katmanı**

### Sensörler

* `ISensor`
* `ImuDriver`
* `GpsDriver`
* `BarometerDriver`
* `MagnetometerDriver`
* `AirspeedSensor`

### Aktüatörler

* `IActuator`
* `ServoDriver`
* `MotorDriver`

### Diğer

* `FlashStorage`
* `RcReceiver`
* `PowerMonitor`

> Not: Bu katman donanım bağımlıdır, üst katmanlar donanım detaylarını bilmemelidir.

---

# 📦 atabey::control

**Kontrol algoritmaları**

* `IController`
* `PID`
* `RateController`
* `AttitudeController`
* `PositionController`
* `AltitudeController`
* `NavigationController`
* `TakeoffController`
* `LandingController`

> Not: Kontrol katmanı doğrudan driver’lara değil, core üzerinden beslenen verilere dayanmalıdır.

---

# 📦 atabey::estimation

**Durum kestirimi**

* `IEstimator`
* `AttitudeEstimator`
* `PositionEstimator`
* `EkfEstimator`

---

# 📦 atabey::comm

**Haberleşme & protokoller**

* `ICommLink`
* `TelemetryLink`
* `MavlinkLink`
* `LoraLink`
* `GroundStationInterface`
* `CommandParser`
* `LogStream`

> Not: Protokol değişimleri (ör. MAVLink → custom protocol) bu katman içinde izole edilmelidir.

---

# 📦 atabey::utils

**Her kütüphane içinde kullanılan ortak veri yapıları ve araçlar**

* `Time`
* `MathUtils`
* `Vector3f`

> Not: `utils` bağımlılıkları tek yönlü olmalı; utils hiçbir modüle bağımlı olmamalıdır.

---

