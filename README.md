# 使用AP模式控制servo
## 步驟
1. 將 ESP32 以 USB 模式連接電腦

2. 將此 repo clone 進 WSL 並使用 VScode 開啟

3. 待 PlatformIO IDE 設定完成後按下 upload 將程式燒錄進 ESP32

4. 拔掉 ESP32 與電腦連接的 USB 並按下 ESP32 上的 EN 按鈕

5. 查看電腦 WiFi 並連接名為 ```ESP32-Servo``` 的 WiFi，密碼預設為 ```12345678```
    - 可打開 terminal 輸入 ```ipconfig``` 查看 WiFi 的預設閘道是否為 ```192.168.4.1```，此為 ESP32 的固定 IP

    ![ipconfig](https://github.com/Steven0811/ESP32_servo_control/blob/AP_connection_control/.github/assets/ipconfig.png)

6. 成功連接後即可透過 Python 發送 HTTP request 控制 servo
    - url 格式為 ```http://{ESP32_IP}/move?servo={servo_id}&angle={angle}``` ，其中 ```ESP32_IP``` 預設為 ```192.168.4.1```，```servo_id``` 為欲控制 servo 的編號， ```angle``` 為此 servo 旋轉的角度
    - ```angle``` 可輸入的數值為 0 ~ 1000
    
    ![result](https://github.com/Steven0811/ESP32_servo_control/blob/AP_connection_control/.github/assets/result.png)