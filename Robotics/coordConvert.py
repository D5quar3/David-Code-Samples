#!/usr/bin/python2.7

import math
import numpy

class CoordConvert:
    hFov =  50 * math.pi/180.0 #horizontal field of view
    vFov =  37 * math.pi/180.0 #vertical field of view
    hRes = 635 #horizontal resolution
    vRes = 453 #vertical resolution
    Theta = 40 * math.pi/180.0 #angle of declination
    phi = -(Theta + math.pi/2) #vertical to declination of camera
    p1 = numpy.matrix([[0],
                       [22.5],
                       [61]]) #height of camera
    R = numpy.matrix([[1, 0, 0], 
                      [0, math.cos(phi), -(math.sin(phi))],
                      [0, math.sin(phi),  math.cos(phi)]]) #rotational 
    h = 2 * math.tan(vFov/2) #height raster window in cm
    w = 2 * math.tan(hFov/2) #width of raster window in cm

    def rasterToRobot(self, objX, objY):
        x2 = (objX - (self.hRes/2)) * (self.w/self.hRes)
        y2 = (objY - (self.vRes/2)) * (self.h/self.vRes)
        v2 = numpy.matrix([[x2], 
                           [y2], 
                            [1]])
        v1 = self.R * v2
        z1 = v1[2,0]
        gamma = -(self.p1[2,0]/z1)
        u = self.p1 + (gamma * v1)
        return u
    
    def robotToWorld(self, robotPosX, robotPosY, robotObjX, robotObjY, angle):
        robotObj = numpy.matrix([[robotObjX],
                                 [robotObjY]])
        robotPos = numpy.matrix([[robotPosX],
                                 [robotPosY]])
        R1 = ([[math.cos(angle), -math.sin(angle)],
               [math.sin(angle), math.cos(angle)]])
        P0 = R1 * robotObj
        P1 = P0 + robotPos
        return P1
    
    def worldToRobot(self, robotPosX, robotPosY, worldObjX, worldObjY, angle):
        robotPos = numpy.matrix([[robotPosX],
                                 [robotPosY]])
        worldObj = numpy.matrix([[worldObjX],
                                 [worldObjY]])
        RT = numpy.matrix([[math.cos(angle), math.sin(angle)],
                           [-math.sin(angle), math.cos(angle)]])
        VR = RT * (worldObj - robotPos)
        return VR