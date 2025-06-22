# 使用STA模式控制servo
## 步驟
1. 將 ESP32 以 USB 模式連接電腦

2. 將此 repo clone 進 WSL 並使用 VScode 開啟

3. 待 PlatformIO IDE 設定完成後將 ```src/main.cpp``` 的 ```ssid``` 與 ```password``` 設定為欲連接的 WiFi 名稱與密碼

4. 按下 upload 將程式燒錄進 ESP32

5. 待燒錄完成後按下 monitor 可以看到 ESP32 的 IP

    ![ESP32_IP_log](https://github.com/Steven0811/ESP32_servo_control/blob/STA_connection_control/.github/assets/ESP32_IP_log.png)

6. 拔掉 ESP32 與電腦連接的 USB 並按下 ESP32 上的 EN 按鈕

7. 將 ```control_servo/main.py``` 的 ```ESP32_IP``` 更改為剛剛看到的 IP

8. 成功連接後即可透過 Python 發送 HTTP request 控制 servo
    - url 格式為 ```http://{ESP32_IP}/move?servo={servo_id}&angle={angle}``` ，其中 ```ESP32_IP``` 為剛剛查看的 ESP32 IP，```servo_id``` 為欲控制 servo 的編號， ```angle``` 為此 servo 旋轉的角度