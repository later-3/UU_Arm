
# SCARA臂电路连接图 v1.0

*基于`x3.ino`代码分析绘制*

```mermaid
graph TD
    subgraph ESP32
        D26((GPIO 26))
        D16((GPIO 16))
        D25((GPIO 25))
        D27((GPIO 27))
        D17((GPIO 17))
        D14((GPIO 14))
        D13((GPIO 13))
        D5((GPIO 5))
        GND1(GND)
    end

    subgraph Driver1 [电机1驱动 (大臂)]
        STEP1(STEP)
        DIR1(DIR)
        GND_D1(GND)
    end

    subgraph Driver2 [电机2驱动 (小臂)]
        STEP2(STEP)
        DIR2(DIR)
        GND_D2(GND)
    end

    subgraph Driver3 [电机3驱动 (底座)]
        STEP3(STEP)
        DIR3(DIR)
        GND_D3(GND)
    end

    subgraph Switch1 [限位开关1 (主臂)]
        SIG1(Signal)
        GND_S1(GND)
    end

    subgraph Switch2 [限位开关2 (副臂)]
        SIG2(Signal)
        GND_S2(GND)
    end

    D26 --> STEP1
    D16 --> DIR1
    D25 --> STEP2
    D27 --> DIR2
    D17 --> STEP3
    D14 --> DIR3
    D13 --> SIG1
    D5 --> SIG2
    GND1 --> GND_D1
    GND1 --> GND_D2
    GND1 --> GND_D3
    GND1 --> GND_S1
    GND1 --> GND_S2

    style ESP32 fill:#4CAF50,stroke:#333,stroke-width:2px
    style Driver1 fill:#2196F3,stroke:#333,stroke-width:2px
    style Driver2 fill:#2196F3,stroke:#333,stroke-width:2px
    style Driver3 fill:#2196F3,stroke:#333,stroke-width:2px
    style Switch1 fill:#FFC107,stroke:#333,stroke-width:2px
    style Switch2 fill:#FFC107,stroke:#333,stroke-width:2px

```

### **说明:**

1.  **驱动器连接:**
    *   ESP32的GPIO引脚分别连接到三个步进电机驱动器的`STEP`和`DIR`引脚。
    *   所有模块的`GND`（地线）必须连接在一起（共地）。
2.  **限位开关连接:**
    *   限位开关是一个简单的开关，一端接ESP32的GPIO引脚，另一端接地(GND)。代码中`INPUT_PULLUP`表示ESP32内部会接一个上拉电阻，当开关未按下时引脚为高电平，按下（开关闭合接地）后变为低电平。
3.  **电源连接 (重要！):**
    *   **此图未画出电源部分。** 通常，你需要一个12V或24V的直流电源。
    *   电源的 **正极 (+)** 连接到所有步进电机驱动器的 `VMOT` 引脚。
    *   电源的 **负极 (-)** 连接到所有模块的 `GND`。
    *   ESP32本身由USB或一个5V稳压器供电，**切勿将12V/24V直接接到ESP32的5V或3.3V引脚！**
