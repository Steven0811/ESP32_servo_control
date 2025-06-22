import requests

ESP32_IP = "YOUR_ESP32_IP_HERE"

def send_command(servo_id, angle):
    url = f"http://{ESP32_IP}/move?servo={servo_id}&angle={angle}"
    try:
        response = requests.get(url)
        print(f"Response: {response}")
    except Exception as e:
        print(f"An error occured: {e}")

while True:
    servo_id, angle = input().split()
    send_command(servo_id, angle)