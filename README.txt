　　該個專案為 C/S 架構的演示程式。演示內容為：通過本端的 Gui 程式，遠程控制遠端的 Raspberry 上的 Led 燈具；此中遠程控制方式為 HttpApi 和 WebSocket。

　　程式 Client 部分，使用 C++ Qt Widget 進行實作，基於 Qt 特性能實現跨平台兼容。程式 Server 部分，使用 Java 下的 Jetty、Jersey 進行簡單實作，佈署於 Raspberry 單晶片上面。程式 Led 控制部分，使用 GPIO 通過 PIGPIO 進行實作。PIGPIO 為 C Library，使用 Jni 加工成為 Java Library，以供 Java 編寫的 Server 調用。
　　此中涉及 Http 和 WebSocket 通訊；使用 Java 實現其中 Server 部分，使用 C++ Qt 實現其中 Client 部分。

　　演示重心在於 TestDemo2022_WebClient、TestDemo2022_JniGpio。TestDemo2022_WebClient 為 C++ Qt Widget 程式專案。TestDemo2022_JniGpio 為 Jni 下的 C 程式庫專案，此中可以當作 GPIO 的驅動程式庫。
