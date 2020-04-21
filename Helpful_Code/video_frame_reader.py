#Give this the path to your video files and it will return a photo every 15th frame
import os
import cv2

pathOut = r"/home/auv-club-laptop/aren_ws/src/aren_videos/"
count = 0
counter = 1
listing = os.listdir(r'/home/auv-club-laptop/aren_ws/src/aren_videos')
for vid in listing:
    vid = r"/home/auv-club-laptop/aren_ws/src/aren_videos/"+vid
    cap = cv2.VideoCapture(vid)
    count = 0
    counter += 1
    success = True
    while success:
        success,image = cap.read()
        print('read a new frame:',success)
        if count%15 == 0 :
             cv2.imwrite(pathOut + 'frame%d.jpg'%count,image)
        count+=1
