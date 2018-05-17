from calculations import *
import cv2


boundaries = [[0, 25], [26, 75], [125, 175]]
path = "../Images/face_example.png"

for lower, upper in boundaries:
    # calculate mask
    mask_path = CalculateMask(path, lower, upper)

    # read image from recieved mask_path
   # mask = cv2.imread(mask_path)

    # display mask
    #cv2.imshow(mask)
