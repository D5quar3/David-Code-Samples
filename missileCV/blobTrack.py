#! /usr/bin/python2.7

import numpy

from launcherCommands import *

launcher = Launcher_Commands()

class Blob_Track:
    
    def distanceFromCenter(self, centroid):
        center = (320,240)
        if centroid:
            return tuple(numpy.subtract(center, centroid))
    
    def findTarget(self, distance):
        if distance:
            if distance[0] > 30:
                launcher.send_move(launcher.LEFT, 25)
            if distance[0] < -30:
                launcher.send_move(launcher.RIGHT, 25)
            if distance[1] > 30:
                launcher.send_move(launcher.UP, 25)
            if distance[1] < -30:
                launcher.send_move(launcher.DOWN, 25)
    
    def lockOn(self, distance):
        if distance:
            inRange = 1
            if distance[0] < 30 and distance[0] > -30 and distance[1] < 30 and distance[1] > -30:
                return inRange 

    def fire(self):
        launcher.send_cmd(launcher.FIRE)
