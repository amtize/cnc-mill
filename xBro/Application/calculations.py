import cv2
import numpy as np
import math
from matplotlib import pyplot as plt
from bro_code import WriteBroCodeMove


BOUNDRIES = []

LOWER_BOUNDRY = 0
UPPER_BOUNDRY = 60


def CalculateMask(path, lower_boundary=0, upper_boundary=60):
    """
    CalculateMask calculates a mask for an image based on the received lower and upper boundary.

            Authors:    Tarjei Græsdal, Ove Nicolai Dalheim
            Version:    1.3
            Date:       09.05.18

    Only works on black and white images. Colored images might return unexpected results.
    This functions writes three images, one being the original, one being the mask and one being the result of the
    bitwise_and function between the original and the mask.

    Parameters
    ----------
    path : string
        The path for the image to calculate the mask on
    lower_boundary : int
        Lower bounding RGB value that will be included in the mask
    upper_boundary : int
        Upper bounding RGB value that will be included in the mask


    Returns
    -------
    mask : string
        The path of the mask image written by this function


    Dependencies
    ------------
    OpenCV 3.4.1 or newer

    """

    # read from path to obtain image object
    img = cv2.imread(path,)

    # generate numpy arrays for RGB values
    lower = np.array([lower_boundary, lower_boundary, lower_boundary], dtype="uint8")
    upper = np.array([upper_boundary, upper_boundary, upper_boundary], dtype="uint8")


    # find the colors within the specified boundaries
    mask = cv2.inRange(img, lower, upper)

    # apply the mask
    output = cv2.bitwise_and(img, img, mask=mask)

    # write original image, masked image and result of applying the mask
    cv2.imwrite(path[:-4] + '_original.png',        img)
    cv2.imwrite(path[:-4] + '_mask.png',            mask)
    cv2.imwrite(path[:-4] + '_output.png',         output)

    # return path to mask
    return path[:-4] + '_mask.png'


def CalculateHoughLines(path):
    img = cv2.imread(path)
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray,50,150,apertureSize=3)
    minLineLength = 100
    maxLineGap = 100
    lines = cv2.HoughLinesP(edges,1,np.pi/180,100,minLineLength,maxLineGap)
    if lines is None:
        return ""
    for line in lines:
        for x1,y1,x2,y2 in line:
            cv2.line(img,(x1,y1),(x2,y2),(0,255,0),2)
    cv2.imwrite(path[:-4] + '_hough.png',img)


    edges = cv2.Canny(img,100,200)

    return path[:-4] + '_hough.png'

def CalculateContours(mask):
    """
    CalculateContours finds all the contours on an input image.

            Authors:    Tarjei Graesdal, Ove Nicolai Dalheim
            Version:    1.1
            Date:       03.05.18

    Works on images that are non-binary (not masks), but might return unexpected results.

    Parameters
    ----------
    mask : string
        The path of the mask image written by this function


    Returns
    -------
    contours : list of contour objects
        The calculated contours. One contour is a list of points.


    Dependencies
    ------------
    OpenCV 3.4.1 or newer

    """

    # read image from given path
    im = cv2.imread(mask)

    # force image to be black and white, needed for next function
    imgray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)

    # force image to be binary, cv2.imread does not store binary image object.
    ret, thresh = cv2.threshold(imgray, 127, 255, 0)

    # fetch list of contours
    _, contours, _ = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    # draw contours on image object and write image for debugging purposes
    cv2.drawContours(im, contours, -1, (0, 255, 0), 3)
    cv2.imwrite(mask[:-4] + "_contours.png", im)

    #return list of contours
    return contours


def CalculateBroCodeFromContour(contour, depth):
    """
    CalculateBroCodeFromContour calculates bro-codes based on an input contour.

            Authors:    Tarjei Græsdal, Ove Nicolai Dalheim
            Version:    1.8
            Date:       13.05.18

    It is a recursive method. The base case is when the ResizeContour() function call returns None. It will generate milling paths for milling out the contour itself and everything inside the contour.

    Parameters
    ----------
    contour : list
        The contour that will be used to calculate and generate bro-codes
    depth : int
        The depth (z value) that the bro-codes will have


    Returns
    -------
    bro_code_txt : string
        The bro_codes that have been calculated and generated


    Dependencies
    ------------
    OpenCV 3.4.1 or newer

    """
    if contour is None:
        return ""

    bro_code_txt = ""
    x = 0
    y = 0
    #Move to first location 
    x0 = contour[0][0][0]
    y0 = contour[0][0][1]
    bro_code_txt += WriteBroCodeMoveAbsolute([x0, y0, 0])


    #Move to all points in contour
    for cnt in contour:
        x = cnt[0][0]
        y = cnt[0][1]
        z = depth
        bro_code_txt += WriteBroCodeMoveAbsolute([x, y, z])

    #Move to z = 0
    bro_code_txt += WriteBroCodeMoveAbsolute([x0, y0, depth])
    bro_code_txt += WriteBroCodeMoveAbsolute([x0, y0, 0])

    #new_cnt = ResizeContour(contour, 10)
    #bro_code_txt += CalculateBroCodeFromContour(new_cnt, depth)

    return bro_code_txt

def ResizeContour(contour, offset):
    x_c, y_c = getCenterOfMass(np.array(contour))
    if cv2.contourArea(np.array(contour)) <= 10 * 4:
        return None

    new_contour = []
    for cnt in contour:
        x = cnt[0][0]
        y = cnt[0][1]

        angle = getAngle(x, y, x_c, y_c)
        factor_x = math.cos(angle)
        factor_y = math.sin(angle)

        offset_x = factor_x * offset
        offset_y = factor_y * offset

        if not IsInside(np.array(contour), x + offset_x, y + offset_y):
            x -= offset_x
            y -= offset_y
        else:
            x += offset_x
            y += offset_y
        new_contour.append([[int(x), int(y)]])

    return new_contour

def getAngle(x1, y1, x2, y2):
    return math.atan2(y2-y1, x2-x1)

def getCenterOfMass(contour):
    x,y,w,h = getBoundingRect(contour)
    x_c = x + w / 2
    y_c = y + h / 2
    return x_c, y_c

def getBoundingRect(contour):
    x,y,w,h = cv2.boundingRect(contour)
    return x,y,w,h

def IsInside(contour, x, y):
    return cv2.pointPolygonTest(contour, (x,y), False) #+1 = inside, 0 = on, -1 = outside


def ShiftVector(vector, amount, bounding_rects):
    pass
