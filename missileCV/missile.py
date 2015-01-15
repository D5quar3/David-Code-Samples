#! /usr/bin/python2.7

import time

from blobDetect import *
from blobTrack  import *
from launcherCommands import *

cam = Camera(1)
bd = Blob_Detect()
bt = Blob_Track()
launcher = Launcher_Commands()
i = 0
while i < 2000:
    img   = cam.getImage()
    nimg  = bd.pictureCondition(img)
    blobs = nimg.findBlobs()
    circles = bd.shapeFilter(blobs)
    circle = bd.sizeFilter(circles,50, 100)
    bd.drawCircles(nimg, circle)
    centroid = bd.findCenter(circle)
    distance = bt.distanceFromCenter(centroid)
    bt.findTarget(distance)
    if bt.lockOn(distance):
        certainty +=1
    else:
        certainty = 0
    if certainty > 10:
        print "fire!"
        bt.fire()
        sys.exit(0)
    time.sleep(.05)
