#!/usr/bin/python3

from ultralytics import YOLO
import cv2
import serial

model = YOLO('yolov8n.pt')
model.export(format = 'ncnn')
ncnn_model = YOLO('yolov8n_ncnn_model')

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

target_id = None

bluedot_x = None
bluedot_y = None
greendot_x = None
greendot_y = None

is_first_run = True

# Serial communication setup
ser = serial.Serial('/dev/ttyUSB0', 9600)

while cap.isOpened():
    ret, frame = cap.read()
    annotated_frame = frame.copy()

    # Calculate center coordinates of the frame
    frame_height, frame_width, _ = frame.shape
    frame_center_x, frame_center_y = frame_width // 2, frame_height // 2

    # Save blue dot coordinates
    bluedot_x, bluedot_y = frame_center_x, frame_center_y

    # Draw blue dot at the center of the frame
    cv2.circle(annotated_frame, (bluedot_x, bluedot_y), 5, (255, 0, 0), -1)

    if target_id is None:
        results = ncnn_model(frame, classes=0)
        if len(results) > 0 and len(results[0].boxes) > 0:
            if len(results[0].boxes) > 1:
                # When there are multiple people
                largest_box = None
                largest_area = 0
                for box in results[0].boxes:
                    x1, y1, x2, y2 = box.xyxy[0]
                    area = (x2 - x1) * (y2 - y1)
                    if area > largest_area:
                        largest_box = box
                        largest_area = area
                if largest_box is not None:
                    target_id = largest_box.id
                    x1, y1, x2, y2 = largest_box.xyxy[0].tolist()
                    cv2.rectangle(annotated_frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 0, 255), 2)
                    center_x, center_y = (x1 + x2) // 2, (y1 + y2) // 2
                    
                    # Save green dot coordinates
                    greendot_x, greendot_y = center_x, center_y
                    
                    cv2.circle(annotated_frame, (int(greendot_x), int(greendot_y)), 5, (0, 255, 0), -1)
                    print(largest_box)
            else:
                # When there's only one person
                target_id = results[0].boxes[0].id
                x1, y1, x2, y2 = results[0].boxes[0].xyxy[0].tolist()
                cv2.rectangle(annotated_frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 0, 255), 2)
                center_x, center_y = (x1 + x2) // 2, (y1 + y2) // 2
                
                # Save green dot coordinates
                greendot_x, greendot_y = center_x, center_y
                
                cv2.circle(annotated_frame, (int(greendot_x), int(greendot_y)), 5, (0, 255, 0), -1)
                print(results[0].boxes[0])
    else:
        results = ncnn_model(frame, classes=0)
        for box in results[0].boxes:
            if box.id == target_id:
                x1, y1, x2, y2 = box.xyxy[0].tolist()
                cv2.rectangle(annotated_frame, (int(x1), int(y1)), (int(x2), int(y2)), (0, 0, 255), 2)
                center_x, center_y = (x1 + x2) // 2, (y1 + y2) // 2
                
                # Save green dot coordinates
                greendot_x, greendot_y = center_x, center_y
                
                cv2.circle(annotated_frame, (int(greendot_x), int(greendot_y)), 5, (0, 255, 0), -1)
                print(box)
                break

    print(greendot_x, bluedot_x, greendot_y, bluedot_y)

    # Serial data transmission    
    if(greendot_x == None or greendot_y == None):
        if not is_first_run:
            print('--------------------')
            print('Transmitted data: X')
            print('--------------------')
            ser.write(b'X')
        else:
            print('--------------------')
            print('Transmitted data: S')
            print('--------------------')
            ser.write(b'S')
    else:
        if abs(bluedot_x - greendot_x) < 190:
            if abs(bluedot_y - greendot_y) < 15:
                print('--------------------')
                print('Transmitted data: S')
                print('--------------------')
                ser.write(b'S')
            else:
                print('--------------------')
                print('Transmitted data: G')
                print('--------------------')
                ser.write(b'G')
        else:
            if greendot_x <= 75:
                print('--------------------')
                print('Transmitted data: Q')
                print('--------------------')
                ser.write(b'Q')
            elif greendot_x >= 565:
                print('--------------------')
                print('Transmitted data: P')
                print('--------------------')
                ser.write(b'P')
            elif greendot_x < bluedot_x:
                print('--------------------')
                print('Transmitted data: 1')
                print('--------------------')
                ser.write(b'1')
            else:
                print('--------------------')
                print('Transmitted data: 3')
                print('--------------------')
                ser.write(b'3')
                
        is_first_run = False
            
    (greendot_x, greendot_y) = (None, None)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# End serial communication
ser.close()

cv2.destroyAllWindows()
