#! /usr/bin/python2.7

import time
import sys
from SimpleCV import *

class Blob_Detect:

    def pictureCondition(self,img):
        return img.invert()

    def shapeFilter(self, blobArray, circleThreshold = .2):
        if circleThreshold < 0:
            print("Invalid Value")
            sys.exit(1)
        if blobArray:
            return blobArray.filter([blob.isCircle(circleThreshold) for blob in blobArray])

    def sizeFilter(self, circleArray, minRadius, maxRadius):
        if circleArray:
            for circle in circleArray:
                if circle.radius() > minRadius and circle.radius() < maxRadius:
                    return circle

    def findCenter(self, circle):
        if circle:
            return circle.centroid()

    def drawCircles(self, nimg, circle, color = SimpleCV.Color.BLUE):
        nimg.drawCircle((320,240),5,SimpleCV.Color.RED)
        nimg.drawCircle((320,240),30,SimpleCV.Color.GREEN)
        if circle:
            nimg.drawCircle((circle.centroid()),10,color)
        nimg.show()

