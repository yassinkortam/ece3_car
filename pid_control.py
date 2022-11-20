import time
import numpy as np
import pandas as pd

def pidControl(pidConsts):
    KP = pidConsts[0]
    KI = pidConsts[1]
    KD = pidConsts[2]

#____________Initial conditions____________
    TIMEOUT = 2
    L = 7 #length of sensor array in cm
    W = 10 #width of the car in cm
    V = 5 #speed cm/s
    B = 10 #baud rate 
    VB = V/B #speed cm/cycle

    pos = [0,-12] #car starting position
    diff = 0 #initial wheel speed differebce
    heading = np.pi/2 #initial heading
    absErr = 0 #absolute error

    prev_e = 0
    integral = 0
    s = time.time()

    #load the track
    df = pd.read_csv("track.csv")
    track_x = np.array(df["X"].to_list())
    track_y = np.array(df["Y"].to_list())

#____________Drive functions____________

    #heading of car
    def phi(vdiff, heading):
        heading += (2/W)*vdiff
        return heading

    #velocity vector of car
    def v(heading):
        return VB*np.cos(heading),  VB*np.sin(heading)

    #coordinates of car
    def p(heading, pos):
        x, y = v(heading)
        pos[0] = pos[0] + x
        pos[1] = pos[1] + y
        return pos[0], pos[1]

    #nearest point on track 
    def pl(x, y, tx, ty):
        distances = np.array([((tx[i] - x)**2 + (ty[i] - y)**2) for i in range(len(tx))])
        return track_x[np.argmin(distances)], ty[np.argmin(distances)]

    #calculate error
    def err(pos, tx, ty):
        cx, cy = pl(pos[0], pos[1], tx, ty)
        ex = cx - pos[0]
        ey = cy - pos[1]
        e = (ex**2 + ey**2)**0.5
        if e > L:
            e = L
        if ex >= 0:
            return -1*e
        else:
            return e

#____________PID Control____________
    
    while(pos[0] < 260 and time.time() - s < TIMEOUT):

        #find the car position
        heading = phi(diff, heading)
        pos[0], pos[1] = p(heading, pos)

        #find error
        e = err(pos, track_x, track_y)

        #find wheel speed difference
        prop = KP*e
        int = KI*integral
        der = KD*(e - prev_e)
        diff = prop + int + der

        #update pid
        integral += e
        prev_e = e

        absErr += abs(e)
    
    return absErr