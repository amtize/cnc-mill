
import cv2
import numpy as np
from calculations import *
from matplotlib import pyplot as plt

im = cv2.imread('../Images/test.png')

img = im

imgray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
ret,thresh = cv2.threshold(imgray,127,255,0)
_, contours, _ = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

cv2.drawContours(img, contours, -1, (0,255,0), 2)

for contour in contours:
    x, y = contour.T
    print(contour)
    print("PENIS")
    plt.scatter(x,y)
plt.show()
for cnt in contours:
    new = ResizeContour(cnt, 10)
    x, y = new.T
    print(new)
    print("PENIS")
    print(x)
    plt.scatter(x,y)



plt.show()

#cnt = contours[4]
#cv2.drawContours(img, [cnt], 0, (0,255,0), 3)

cv2.imwrite("kkk.png",img)

cv2.waitKey(0)
