　　該個專案為 C/S 架構的演示程式。演示內容為：通過本端的 Gui 程式，遠程控制遠端的 Raspberry 上的 Led 燈具；此中遠程控制方式 HttpApi。
　　程式 Client 部分，使用 C++ Qt Widget 進行實作，基於 Qt 特性能實現跨平台兼容。程式 Server 部分，使用 Java Jarsey 進行簡單實作，佈署於 Raspberry 單晶片上面。Led 通過 GPIO 使用 PIGPIO 進行控制。
　　演示重心在於 TestDemo2022_WebClient，此為 C++ Qt Widget 程式專案。其他部分會以儘量簡單的方式實現。
