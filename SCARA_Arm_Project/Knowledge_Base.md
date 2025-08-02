# AI作业批改机械臂 - 核心知识库

*本文档旨在系统性地梳理完成本项目所需的所有核心知识模块，并提供精选的学习资源，作为您的个人学习路径图。*

---

## **第一部分：硬件基础 (The Body)**

### **模块1: 3D打印与机械结构**
*   **你需要知道什么:**
    1.  **STL文件:** 什么是STL文件？它是如何描述一个三维模型的？
    2.  **切片软件 (Slicer):** 了解切片软件（如Cura, PrusaSlicer）的基本作用：将STL模型转换为3D打印机可以读取的G-code指令。你需要理解几个核心参数：层高(Layer Height)、填充(Infill)、速度(Speed)、支撑(Support)。
    3.  **打印材料:** 了解PLA、PETG、ABS等常用3D打印材料的基本特性和适用场景。本项目使用PLA即可。
    4.  **机械装配:** 理解螺丝规格（如M3, M5）、轴承型号、以及如何使用热熔螺母来增强塑料件的连接强度。
*   **精选资源:**
    *   **[视频] 3D打印入门终极指南 (YouTube, Maker's Muse):** [https://www.youtube.com/watch?v=nb-1b8_5j1I](https://www.youtube.com/watch?v=nb-1b8_5j1I)
    *   **[文章] Cura切片软件核心参数详解 (All3DP):** [https://all3dp.com/2/cura-settings-cheat-sheet-all-settings-explained/](https://all3dp.com/2/cura-settings-cheat-sheet-all-settings-explained/)

### **模块2: 步进电机及其驱动**
*   **你需要知道什么:**
    1.  **工作原理:** 步进电机为什么能精确地转动一个“步长”？它和普通直流电机的区别是什么？
    2.  **关键参数:** 理解NEMA 17的含义（安装法兰尺寸），1.8°/步的意义，以及保持扭矩(Holding Torque)的重要性。
    3.  **驱动器:** 为什么电机不能直接连到ESP32上？理解驱动器（如A4988）的作用：接收控制信号，并为电机提供足够大的电流。 
    4.  **TMC2209的优越性:** 了解我们选择TMC2209而不是A4988的深层原因：它的`StealthChop2™`技术能让电机运行极其安静，这对于桌面产品是决定性的用户体验提升。
*   **精选资源:**
    *   **[视频] 步进电机工作原理的绝佳可视化 (YouTube, Lesics):** [https://www.youtube.com/watch?v=bCEiI_O1-sU](https://www.youtube.com/watch?v=bCEiI_O1-sU)
    *   **[文章/视频] TMC2209 vs A4988深度对比 (YouTube, Teaching Tech):** [https://www.youtube.com/watch?v=dOJb_b35O_g](https://www.youtube.com/watch?v=dOJb_b35O_g)

### **模块3: 电路与布线 (The Nervous System)**
*   **你需要知道什么:**
    1.  **RAMPS 1.4是什么:** 了解它是一个用于Arduino Mega 2560的、集成了电机驱动插槽、电源接口和传感器接口的“扩展板(Shield)”。它的出现是为了方便3D打印机的DIY，解决复杂的布线和功率驱动问题。
    2.  **为什么我们不需要它:** 因为我们选择了更现代、更集成的ESP32主控，并且我们的项目复杂度可控（仅3个电机）。使用RAMPS 1.4 + Mega 2560的方案对我们来说体积过于庞大且没有必要。
    3.  **我们的方案:** 我们将采用一种更灵活、更紧凑的方式。我们会用杜邦线直接连接ESP32和TMC2209驱动器，并在一块小小的“洞洞板(Perfboard)”上完成24V电源的分配工作。这能让我们把电子系统做得尽可能小，为未来的工业设计留出空间。
*   **精选资源:**
    *   **[视频] RAMPS 1.4 Explained (YouTube, Teaching Tech):** [https://www.youtube.com/watch?v=s_N92_eS94Q](https://www.youtube.com/watch?v=s_N92_eS94Q)

---

## **第二部分：嵌入式软件 (The Brainstem)**

### **模块4: ESP32与Arduino IDE**
*   **你需要知道什么:**
    1.  **ESP32是什么:** 了解它是一款集成了Wi-Fi和蓝牙的强大微控制器，是物联网和机器人项目的热门选择。
    2.  **Arduino IDE:** 如何配置Arduino IDE来为ESP32编写、编译和上传代码。
    3.  **核心函数:** 掌握`pinMode()`, `digitalWrite()`, `delayMicroseconds()`等基本函数。
    4.  **串口通信:** 掌握`Serial.begin()`, `Serial.println()`, `Serial.read()`，这是ESP32与电脑（或上层主控）沟通的唯一方式。
*   **精选资源:**
    *   **[教程] ESP32入门指南 (Random Nerd Tutorials):** [https://randomnerdtutorials.com/getting-started-with-esp32/](https://randomnerdtutorials.com/getting-started-with-esp32/)

### **模块5: G-code (机器人的“乐谱”)**
*   **你需要知道什么:**
    1.  **它是什么:** G-code是数控领域的标准指令语言。我们用它来精确描述机械臂末端的运动轨迹。
    2.  **核心指令:** 了解最基础的指令，如 `G0` (快速移动), `G1` (直线插补移动), `G28` (回零), `F` (速度), `X/Y/Z` (坐标)。
    3.  **在本项目中的作用:** 我们的Python上位机负责生成G-code（例如，写一个“A”字的轨迹），然后通过串口发送给ESP32。ESP32的固件则负责解析这些G-code，并将其转换为电机需要执行的脉冲信号。
*   **精选资源:**
    *   **[文章] G-code入门教程 (RepRap Wiki):** [https://reprap.org/wiki/G-code](https://reprap.org/wiki/G-code)

### **模块6: 机械臂运动学 (The Soul)**
*   **你需要知道什么:**
    1.  **坐标系:** 理解笛卡尔坐标系 (X, Y) 和关节坐标系 (角度1, 角度2)的区别。
    2.  **正向运动学 (Forward Kinematics):** 已知两个关节的角度，计算出机械臂末端（笔尖）的(X, Y)坐标。这个相对简单，主要用作验证。
    3.  **逆向运动学 (Inverse Kinematics):** **这是核心！** 已知笔尖想去的(X, Y)坐标，反向计算出两个关节应该转动到什么角度。这是所有绘图和书写功能的基础。
*   **精选资源:**
    *   **[视频] SCARA机器人逆向运动学数学推导 (YouTube):** [https://www.youtube.com/watch?v=r_i4H2An2aQ](https://www.youtube.com/watch?v=r_i4H2An2aQ) (这个视频可能有点硬核，但能让你理解底层数学原理)
    *   **[代码示例] Arduino SCARA Robot Arm Inverse Kinematics (GitHub):** (我会在后续为您寻找并推荐最简洁易懂的示例代码)

---

## **第三部分：系统架构与AI (The Cerebrum)**

### **模块7: 上位机与下位机 (CEO与车间主任)**
*   **你需要知道什么:**
    1.  **定义:** 理解这种经典的分层控制架构。**上位机** (我们的MacBook) 负责思考、视觉、AI等复杂任务；**下位机** (我们的ESP32) 负责快速、精确地执行硬件控制。
    2.  **协同工作:** 上位机通过串口发送G-code等指令，下位机接收并执行，然后可以返回状态。这种“解耦”让系统每一层都只专注于自己最擅长的事，使整个项目更稳定、更易于扩展。

### **模块8: Python串口通信与控制**
*   **你需要知道什么:** 如何使用Python的`pyserial`库，向ESP32发送G-code指令，并接收返回的状态信息。

### **模块9: 计算机视觉 (OpenCV)**
*   **你需要知道什么:** 如何使用Python的`opencv-python`库，调用摄像头拍照，并对图像进行处理，例如：识别作业本的边框，定位题目区域。

### **模块10: AI集成**
*   **你需要知道什么:** 如何将图像中的题目区域，发送给您之前`studyHelper`项目中的AI模型，并接收返回的“对”或“错”的判断结果。

---

## **第四部分：开发环境与工具链**

### **模块11: 关于开发电脑的选择 (macOS vs. Windows)**
*   **结论:** **无需切换，您的MacBook完全胜任本项目。**
*   **详细说明:**
    1.  **跨平台工具:** 本项目所需的核心软件，包括 **Arduino IDE** (固件开发), **Cura/PrusaSlicer** (3D打印切片), 以及 **Python** (上层控制与AI)，全部都完美支持macOS。
    2.  **我们的优势:** 我们将开发自己的、基于Python的跨平台上位机软件，因此我们不依赖于作者提供的任何Windows小程序，这让我们的项目具有更好的移植性和开放性。
    3.  **潜在问题:** 唯一的“小插曲”可能是某些USB转串口芯片(如CH340)需要在macOS上首次使用时手动安装一个驱动程序。这是一个简单的、一次性的操作。