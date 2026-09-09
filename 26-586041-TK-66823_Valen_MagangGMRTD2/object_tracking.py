import cv2
from ultralytics import YOLO

model = YOLO("yolov8n.pt")

target_objects = {
    "bottle",
    "spoon",
    "cell phone",
}

cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Webcam tidak dapat dibuka!")
    exit()

while True:

    ret, frame = cap.read()

    if not ret:
        print("Frame webcam tidak dapat dibaca!")
        break

    # Deteksi menggunakan YOLO
    results = model(frame, verbose=False)

    # Ambil hasil deteksi
    for result in results:

        boxes = result.boxes

        for box in boxes:

            confidence = float(box.conf[0])

            class_id = int(box.cls[0])

            class_name = model.names[class_id]

            # Hanya tampilkan 3 objek yang ditentukan
            if class_name not in target_objects:
                continue

            # Koordinat bounding box
            x1, y1, x2, y2 = map(int, box.xyxy[0])

        
            cv2.rectangle(
                frame,
                (x1, y1),
                (x2, y2),
                (0, 255, 0),
                2
            )

           
            label = f"{class_name} {confidence:.2f}"

            cv2.putText(
                frame,
                label,
                (x1, y1 - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.6,
                (0, 255, 0),
                2
            )

    
    cv2.imshow("YOLOv8n Object Detection", frame)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break


cap.release()
cv2.destroyAllWindows()