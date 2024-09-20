# Real-Time-User-Motion-Detection-Algorithm

![image](https://github.com/user-attachments/assets/206ca974-7b8f-4c10-8ab1-d16bb9db2a63)
![image](https://github.com/user-attachments/assets/5642e5c4-d13c-4fc2-90dd-15d7a697aeff)


H/W
크기 : 48cm*23cm*66cm
무게 : 22kg
프로세서 : Arm Cortex-A76, ATmega 128

S/W
OS : Windows, Ubuntu 23.10
개발TOOL : Visual Studio Code, CodeVisionAVR, Android Studio

- SBC(Raspberry Pi 5)
Raspberry Pi 5에 연결된 카메라로 촬영한 Image에서 매 프레임마다 사용자를인식하고, 프레임의 중간점 좌표와 Object Detection을 통한 사용자 bounding box의 중간점 좌표를 비교하여 사용자와 캐리어 간의 상대적 위치를 파악한다.
이를 통해 사용자의 움직임 방향에 따른 연산으로, 캐리어가 사용자를 따라올 수있도록 제어 data를 출력한다.
Raspberry Pi 5에서 생성된 제어 data는 시리얼통신을 통해 ATmega128로 전송되고 ATmega128은 수신한 데이터를 기반으로모터를 제어하여 캐리어의 움직임을 조정한다.
사용자와의 거리, 움직임 방향 등 각 상황에 맞는 데이터 값에 따라 PWM을 통해 모터의 속도와 방향을 제어함으로써 캐리어가 사용자를 적절히 따라갈 수 있도록 한다.
사용자와 캐리어간의 위치가 일정 수준 이상 가까운 경우 캐리어가 정지할 수 있고, 사용자 추적 중 카메라 상에서 사용자를 감지하지 못하게 되는 상황에서는 마찬가지로 캐리어를 정지하고 소리를 울려 추적 불가 상황임을 사용자에게 알린다.
1) Object Detection(객체 인식)Raspberry Pi 5에 객체 인식 모델을 사용하여 웹캠에 사용자가 나타나면 처음카메라 프레임 상에 보인 사람을 캐리어 사용자로 간주하고 id를 부여한다.
이때프레임 상에 사람이 여럿인 경우에는 bounding box를 씌었을 때 bounding box가가장 크게 씌어지는 즉, 캐리어와 가장 거리가 가까운 사람을 사용자로 간주하고마찬가지로 id를 부여한다.
그 후 사용자에게만 bounding box를 그리도록 하고사용자를 추적한다.
![image](https://github.com/user-attachments/assets/d641079a-4f20-4cc6-8278-8572ce908963)

(직진)
사용자에게 그려진 bounding box의 greendot_x, greendot_y의 값과 카메라 프레임의 bluedot_x, bluedot_y의 값을 이용하여 bluedot_x – greendot_x < 190이고bluedot_y – greendot_y >= 15이면 직진 하도록 한다.
![image](https://github.com/user-attachments/assets/d59fc64e-0e34-4a84-b4ee-48f1a2f82d1b)

(좌회전)
사용자에게 그려진 bounding box의 greendot_x, greendot_y의 값과 카메라 프레임의 bluedot_x, bluedot_y의 값을 이용하여 bluedot_x > greendot_x이면 좌회전하도록 한다.
![image](https://github.com/user-attachments/assets/03c778c3-8f0d-4ba6-8a0b-b19af3ef0a2c)

(우회전)
사용자에게 그려진 bounding box의 greendot_x, greendot_y의 값과 카메라 프레임의 bluedot_x, bluedot_y의 값을 이용하여 bluedot_x < greendot_x이면 우회전하도록 한다.
![image](https://github.com/user-attachments/assets/ddff1524-1f04-4a4e-8d0c-196ad7d610b0)

(정지)
사용자에게 그려진 bounding box의 greendot_x, greendot_y의 값과 카메라 프레임의 bluedot_x, bluedot_y의 값을 이용하여 카메라에 사용자가 잡히지 않을 때(greendot_x = None, greendot_y = None일 때) 또는 bluedot_x – greendot_x < 190이고 bluedot_y – greendot_y < 15이면 정지 하도록 한다.
![image](https://github.com/user-attachments/assets/2152eb11-d5e6-45b1-a6f5-cd4dae74f3dc)

