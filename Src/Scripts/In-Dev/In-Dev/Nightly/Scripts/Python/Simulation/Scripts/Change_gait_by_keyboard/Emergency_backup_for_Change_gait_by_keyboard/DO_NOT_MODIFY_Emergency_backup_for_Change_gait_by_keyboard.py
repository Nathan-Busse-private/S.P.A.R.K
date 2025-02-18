
import pybullet as p
import time
import numpy as np
    


def setEnv():
    # set gravity
    # set camera angle
    p.setGravity(0,0,-9.81)
    p.setRealTimeSimulation(1)
    #Point the camera at the robot at the desired angle and distance
    p.resetDebugVisualizerCamera( cameraDistance=1.5, cameraYaw=-30, cameraPitch=-30, cameraTargetPosition=[0.0, 0.0, 0.25]) 

def createHill():
    #Scenery e.g. an inclined box
    boxHalfLength = 2.5
    boxHalfWidth = 2.5
    boxHalfHeight = 0.2
    sh_colBox = p.createCollisionShape(p.GEOM_BOX,halfExtents=[boxHalfLength,boxHalfWidth,boxHalfHeight])
    mass = 1
    block=p.createMultiBody(baseMass=0,baseCollisionShapeIndex = sh_colBox,
                            basePosition = [-2,4,-0.1],baseOrientation=[0.0,0.1,0.0,1])
                    
def createDogJoints():
    #Dog robot part shapes
    # second plank red in color.#first coordinate length,width,height
    base_body = p.createCollisionShape(p.GEOM_BOX,halfExtents=[0.45, 0.08, 0.02])
    ## weight of the load
    package_weight = p.createCollisionShape(p.GEOM_BOX,halfExtents=[0.1, 0.08, 0.05])
    # two blue hinges on the side to which joints attach
    roll_joint = p.createCollisionShape(p.GEOM_BOX,halfExtents=[0.02, 0.02, 0.02])
    # the green joint (1st joint) .. if long then centro of mass goes bad
    hip_joint = p.createCollisionShape(p.GEOM_BOX,halfExtents=[0.02, 0.02, 0.02])
    # the middle joint
    knee_joint = p.createCollisionShape(p.GEOM_BOX,halfExtents=[0.02, 0.02, 0.02])
    # the foot joint
    foot_joint = p.createCollisionShape(p.GEOM_SPHERE,radius=0.04)

    linkCollisionShapeIndices=[roll_joint, hip_joint, knee_joint, foot_joint,
                            roll_joint, hip_joint, knee_joint, foot_joint,
                            roll_joint, hip_joint, knee_joint, foot_joint,
                            roll_joint, hip_joint, knee_joint, foot_joint,
                            package_weight]
    return base_body, linkCollisionShapeIndices

def designJoints(botCenterToFront, botWidthfmCenter,xoffh, yoffh, botCenterToBack, upperLegLength,lowerLegLength):
    linkPositions=[[botCenterToFront, botWidthfmCenter, 0], [xoffh, yoffh, 0], [0, 0, -upperLegLength], [0, 0, -lowerLegLength],
                [botCenterToFront, -botWidthfmCenter, 0], [xoffh, -yoffh, 0], [0, 0, -upperLegLength], [0, 0, -lowerLegLength],
                [botCenterToBack, botWidthfmCenter, 0], [xoffh, yoffh, 0], [0, 0, -upperLegLength], [0, 0, -lowerLegLength],
                [botCenterToBack, -botWidthfmCenter, 0], [xoffh, -yoffh, 0], [0, 0, -upperLegLength], [0, 0, -lowerLegLength],
                [0,0,+0.029]]
    
    #indices determine for each link which other link it is attached to
    # for example 3rd index = 2 means that the front left knee jjoint is attached to the front left hip
    indices=[0, 1, 2, 3,
            0, 5, 6, 7,
            0, 9,10,11,
            0,13,14,15,
            0]
    #Most joint are revolving. The prismatic joints are kept fixed for now
    jointTypes=[p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_PRISMATIC,
                p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_PRISMATIC,
                p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_PRISMATIC,
                p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_REVOLUTE, p.JOINT_PRISMATIC,
                p.JOINT_PRISMATIC]
    #revolution axis for each revolving joint
    axis=[[1,0,0], [0,1,0], [0,1,0], [0,0,1],
        [1,0,0], [0,1,0], [0,1,0], [0,0,1],
        [1,0,0], [0,1,0], [0,1,0], [0,0,1],
        [1,0,0], [0,1,0], [0,1,0], [0,0,1],
        [0,0,1]]
    
    return linkPositions,indices,jointTypes,axis

#Function to calculate roll, hip and knee angles from the x,y,z coords of the foot wrt the hip.
## inverse kinematics
def xyztoang(x,y,z,yoffh,upperLegLength,lowerLegLength):
    dyz=np.sqrt(y**2+z**2)
    lyz=np.sqrt(dyz**2-yoffh**2)
    gamma_yz=-np.arctan(y/z)
    gamma_h_offset=-np.arctan(-yoffh/lyz)
    gamma=gamma_yz-gamma_h_offset
    
    lxzp=np.sqrt(lyz**2+x**2)
    n=(lxzp**2-lowerLegLength**2-upperLegLength**2)/(2*upperLegLength)
    beta=-np.arccos(n/lowerLegLength)
    
    alfa_xzp=-np.arctan(x/lyz)
    alfa_off=np.arccos((upperLegLength+n)/lxzp)
    alfa=alfa_xzp+alfa_off
    if any( np.isnan([gamma,alfa,beta])):
        print(x,y,z,yoffh,upperLegLength,lowerLegLength)
    return [gamma,alfa,beta]


#Rotation matrix for yaw only between robot-frame and world-frame
##[cos(t),-sin(t),0,][sin(t),cos((t)),0][0,0,1]
def RotYawr(theta):
    Rhor=np.array([[np.cos(theta),-np.sin(theta),0], [np.sin(theta),np.cos(theta),0], [0,0,1]])
    return Rhor


def setlegsxyz(xvec,yvec,zvec,eachMotorSpeed,botCenterToFront,botWidthfmCenter,yoffh,upperLegLength,lowerLegLength,dog,botCenterToBack):
    a=xyztoang(xvec[0]-botCenterToFront,yvec[0]-botWidthfmCenter,zvec[0],yoffh,upperLegLength,lowerLegLength)  #(x,y,z,yoffh,upperLegLength,lowerLegLength)
    spd=1
    joint=0
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[0],force=1000,maxVelocity=spd)
    joint=1
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[1],force=1000,maxVelocity=eachMotorSpeed[0])
    joint=2
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[2],force=1000,maxVelocity=eachMotorSpeed[0])

    a=xyztoang(xvec[1]-botCenterToFront,yvec[1]+botWidthfmCenter,zvec[1],-yoffh,upperLegLength,lowerLegLength)  #(x,y,z,yoffh,upperLegLength,lowerLegLength)
    spd=1.0
    joint=4
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[0],force=1000,maxVelocity=spd)
    joint=5
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[1],force=1000,maxVelocity=eachMotorSpeed[1])
    joint=6
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[2],force=1000,maxVelocity=eachMotorSpeed[1])

    a=xyztoang(xvec[2]-botCenterToBack,yvec[2]-botWidthfmCenter,zvec[2],yoffh,upperLegLength,lowerLegLength)  #(x,y,z,yoffh,upperLegLength,lowerLegLength)
    spd=1.0
    joint=8
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[0],force=1000,maxVelocity=spd)
    joint=9
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[1],force=1000,maxVelocity=eachMotorSpeed[2])
    joint=10
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[2],force=1000,maxVelocity=eachMotorSpeed[2])

    a=xyztoang(xvec[3]-botCenterToBack,yvec[3]+botWidthfmCenter,zvec[3],-yoffh,upperLegLength,lowerLegLength)  #(x,y,z,yoffh,upperLegLength,lowerLegLength)
    spd=1.0
    joint=12
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[0],force=1000,maxVelocity=spd)
    joint=13
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[1],force=1000,maxVelocity=eachMotorSpeed[3])
    joint=14
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=a[2],force=1000,maxVelocity=eachMotorSpeed[3])

def dogBody(base_body,basePosition,baseOrientation,linkCollisionShapeIndices,linkPositions,indices,jointTypes,axis):
    body_Mass = 1     ## assumption 1... we see that at 100 at carries well to certain distance. but ultimately falls
    visualShapeId = -1 
    link_Masses=[.1, .1, .1, .1,  #roll to hip to knee to foot
                .1, .1, .1, .1,
                .1, .1, .1, .1,
                .1, .1, .1, .1,
                20]   ### 20 the weight of the payload
    nlnk=len(link_Masses) ## number of links
    linkVisualShapeIndices=[-1]*nlnk    #=[-1,-1,-1, ... , -1]
    linkOrientations=[[0,0,0,1]]*nlnk
    linkInertialFramePositions=[[0,0,0]]*nlnk
    #Note the orientations are given in quaternions (4 params). There are function to convert of Euler angles and back
    linkInertialFrameOrientations=[[0,0,0,1]]*nlnk


    dog = p.createMultiBody(body_Mass,base_body,visualShapeId,basePosition,baseOrientation,
                            linkMasses=link_Masses,
                            linkCollisionShapeIndices=linkCollisionShapeIndices,
                            linkVisualShapeIndices=linkVisualShapeIndices,
                            linkPositions=linkPositions,
                            linkOrientations=linkOrientations,
                            linkInertialFramePositions=linkInertialFramePositions,
                            linkInertialFrameOrientations=linkInertialFrameOrientations,
                            linkParentIndices=indices,
                            linkJointTypes=jointTypes,
                            linkJointAxis=axis)
    return dog		


def initialBalance(dog,joint):
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=0.01,force=1000,maxVelocity=3)
    #Same for the prismatic feet spheres
    joint=3
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=0.0,force=1000,maxVelocity=3)
    joint=7
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=0.0,force=1000,maxVelocity=3)
    joint=11
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=0.0,force=1000,maxVelocity=3)
    joint=15
    p.setJointMotorControl2(dog,joint,p.POSITION_CONTROL,targetPosition=0.0,force=1000,maxVelocity=3)

def addFrictionFootjoints(dog):
    #Add lateral friction to the feet spheres 
    # for joint 3 , joint 7, jooint 11, joint 15 (all the contact joints)
    p.changeDynamics(dog,3,lateralFriction=2)
    p.changeDynamics(dog,7,lateralFriction=2)
    p.changeDynamics(dog,11,lateralFriction=2)
    p.changeDynamics(dog,15,lateralFriction=2)
    


def main():
    # required initialisation of pybullet
    p.connect(p.GUI)
    p.createCollisionShape(p.GEOM_PLANE)
    p.createMultiBody(0,0)
    #Camera paramers to be able to yaw pitch and zoom the camera (Focus remains on the robot) 
    cyaw=10
    cpitch=-15
    cdist=1.5
    # Create a hill
    createHill()
    # Create create a dog made of basic joint points or load a urdf
    base_body,linkCollisionShapeIndices = createDogJoints()
    
    ## dog shape parameters

    ## shapes and weight defined. 
    #link positions wrt the link they are attached to
    # distance of the COM from the front leg along x direction
    botCenterToFront=0.4 
    # distance of the COM from the back leg along -ve x direction
    botCenterToBack=-0.4 
    # distance of the COM from the legs along y direction
    botWidthfmCenter=0.1 

    # positioning of all the combined joints
    xoffh=0.05
    yoffh=0.05
    upperLegLength=0.3
    lowerLegLength=0.3

    # god initial dynamics parameters

    yawInitial=1.3           ##controls yaw of the robot
    
    linkPositions,indices,jointTypes,axis= designJoints(botCenterToFront, botWidthfmCenter,xoffh, yoffh, botCenterToBack, upperLegLength,lowerLegLength)

    #Drop the body in the scene at the following body coordinates
    basePosition = [0,0,1]
    baseOrientation = [0,0,0,1]
    #Main function that creates the dog
    dog = dogBody(base_body,basePosition,baseOrientation,linkCollisionShapeIndices,linkPositions,indices,jointTypes,axis)

    #Due to the weight the prismatic extraweight block needs to be motored up
    
    initialBalance(dog,joint=16)
    
    ##set gravity
    setEnv()
    addFrictionFootjoints(dog)

    #Pre-init robot position
    setlegsxyz([botCenterToFront,botCenterToFront,botCenterToBack,botCenterToBack],[botWidthfmCenter+0.1,-botWidthfmCenter-0.1,botWidthfmCenter+0.1,-botWidthfmCenter-0.1],[-0.5,-0.5,-0.5,-0.5],[1,1,1,1],botCenterToFront,botWidthfmCenter,yoffh,upperLegLength,lowerLegLength,dog,botCenterToBack)

    ## time to pause from initial config walking state
    t0=time.time()
    t=time.time()
    while ((t-t0)<4):
        t=time.time()


    
    robotCenter=np.array([1,1,0.5])        ### sets the init distance from the origin 1 along x and y, 0.5 alongz
    ## 
    footJointsPtsI=np.array([[botCenterToFront,botCenterToFront,botCenterToBack,botCenterToBack],
                [botWidthfmCenter+0.1,-botWidthfmCenter-0.1,botWidthfmCenter+0.1,-botWidthfmCenter-0.1],
                [-0.5,-0.5,-0.5,-0.5]])
    #Set body to the robot pos
    #Init body position and orientation
    quat=p.getQuaternionFromEuler([0,0,yawInitial])
    p.resetBasePositionAndOrientation(dog,robotCenter,quat)   ###set base position of dog urdf to robotCenter and base angle to quat
    #Init leg abs pos
    RyawInitial=RotYawr(yawInitial)
    #transform the foot joints from robot frame to the world frame and move them by robotCenter
    legsOnGroundPos=(np.dot(RyawInitial,footJointsPtsI).T + robotCenter).T   #Apply rotation plus translation

    
    yawRobotFrame=RotYawr(yawInitial)

    #Recalc leg rel pos in robot frame and set the legs
    newGroundPos=(legsOnGroundPos.T-robotCenter).T
    dlegsR=np.dot(yawRobotFrame.T,newGroundPos)
    setlegsxyz(dlegsR[0],dlegsR[1],dlegsR[2],[1,1,1,1],botCenterToFront,botWidthfmCenter,yoffh,upperLegLength,lowerLegLength,dog,botCenterToBack)

    #Calculate a new robot center position from the average of the feet positions
    #Calculate a new robot yaw ditrection also from the feet positions
    frontLegsCenter=(legsOnGroundPos[:,0]+legsOnGroundPos[:,1])/2.0
    backLegCenter=(legsOnGroundPos[:,2]+legsOnGroundPos[:,3])/2.0
    fwdBwdCenterDistance=frontLegsCenter-backLegCenter


    
# Walking speed (changes the walking loop time)
    walkLoopSpd = 400

    #Change general motor speed
    eachMotorSpeed=[12]*4

    #Current leg to change position
    currentLeg=0
    #Init the center for the robot rotation to the current robot pos
    centerOfRotation=backLegCenter
    #Set the body position to the robot position
    xoff=0
    yoff=0
    #Init to walking fwd
    dr=0
    drp=0
    
   


def selectGait():
    keys = p.getKeyboardEvents()
    if keys.get(49):  # Key '1' for the first gait
        return [0, 1, 3, 2]
    elif keys.get(50):  # Key '2' for the second gait
        return [2, 0, 3, 1]
    elif keys.get(51):  # Key '3' for the third gait
        return [0, 2, 1, 3]
    else:
        return [0, 1, 3, 2]  # Default gait



    while (1):
        cubePos, _ = p.getBasePositionAndOrientation(dog)
        p.resetDebugVisualizerCamera( cameraDistance=cdist, cameraYaw=cyaw, cameraPitch=cpitch, cameraTargetPosition=cubePos)

        keys = p.getKeyboardEvents()
        #Keys to change camera
        if keys.get(100):  #D
            cyaw+=1
        if keys.get(97):   #A
            cyaw-=1
        if keys.get(99):   #C
            cpitch+=1
        if keys.get(102):  #F
            cpitch-=1
        if keys.get(122):  #Z
            cdist+=.01
        if keys.get(120):  #X
            cdist-=.01
        #Keys to change the robot walk (fwd, bkw, rot right, rot left)
        if keys.get(65297): #Up
            drp=0
        if keys.get(65298): #Down
            drp=2
        if keys.get(65296): #Right
            drp=1
            centerOfRotation=robotCenter        #Set the center for the robot rotation to the current robot pos
            lseqp=[1,0,2,3] #Change the leg sequence to open up the front arms rather than close them
        if keys.get(65295): #Left
            drp=3
            centerOfRotation=robotCenter
            lseqp=[0,1,3,2] #Change the leg sequence to open up the front arms rather than close them

        #Time cycle
        timeCycle=int(((time.time()-t0)*walkLoopSpd)  % 800)
        #One leg movement in 200 units. one 4-leg walk cycle in 800 units
        #Using <, >, % (modulo) and divide we can easily do something in a specific part of the cycle
        
        #Apply new walking cycle type (e.g. chg from fwd to bkw) only at the start of next cycle
        if timeCycle<20 and (not dr==drp):
            dr=drp
            lseq=lseqp
        
        #Index of the leg to move
        currentLeg=int(timeCycle/200)
        #Actual leg to move
        k=lseq[currentLeg]
        
        #In the beginning of the leg cycle the body is centered at the robot center
        #then it gradually moves in the opposite direction of the leg to be moved 
        #to ensure the center of gravity remains on the other 3 legs
        #when the moving leg goes down again the body center returns to the robot center
        
        if int(timeCycle%200)<10:
            xoff=0
            yoff=0
        elif int(timeCycle%200)<80:
            #it moves opposite to the stepping leg
            xoff+=0.002*(-1+2*int(k/2))  
            #it moves opposite to the stepping leg
            yoff+=0.002*(-1+2*(k%2))     

        elif int(timeCycle%200)>160:
            #it moves opposite to the stepping leg
            xoff-=0.004*(-1+2*int(k/2))
            #it moves opposite to the stepping leg
            yoff-=0.004*(-1+2*(k%2))     
        
        #Recalc leg rel pos in desired robot frame
        newGroundPos=(legsOnGroundPos.T-robotCenter).T  #Translate
        dlegsR=np.dot(yawRobotFrame.T,newGroundPos)  #Rotate (Note the inverse rotation is the transposed matrix)
        #Then apply the body movement and set the legs
        setlegsxyz(dlegsR[0]-xoff-0.03,dlegsR[1]-yoff,dlegsR[2],eachMotorSpeed,botCenterToFront,botWidthfmCenter,yoffh,upperLegLength,lowerLegLength,dog,botCenterToBack)  #0.03 is for tweaking the center of grav.
        

        if int(timeCycle%200)>80:
            newGroundPos=(legsOnGroundPos.T-centerOfRotation).T
            yawlO=np.arctan2(newGroundPos[1,k],newGroundPos[0,k])
            rlO=np.sqrt(newGroundPos[0,k]**2+newGroundPos[1,k]**2)
            if dr==0:
                legsOnGroundPos[0,k]=rlO*np.cos(yawlO)+centerOfRotation[0]+0.01*np.cos(yawInitial)
                legsOnGroundPos[1,k]=rlO*np.sin(yawlO)+centerOfRotation[1]+0.01*np.sin(yawInitial)
            elif dr==1:
                yawlO-=0.015 
                legsOnGroundPos[0,k]=rlO*np.cos(yawlO)+centerOfRotation[0]
                legsOnGroundPos[1,k]=rlO*np.sin(yawlO)+centerOfRotation[1]
            elif dr==2:
                legsOnGroundPos[0,k]=rlO*np.cos(yawlO)+centerOfRotation[0]-0.01*np.cos(yawInitial)
                legsOnGroundPos[1,k]=rlO*np.sin(yawlO)+centerOfRotation[1]-0.01*np.sin(yawInitial)
            elif dr==3:
                yawlO+=0.015 
                legsOnGroundPos[0,k]=rlO*np.cos(yawlO)+centerOfRotation[0]
                legsOnGroundPos[1,k]=rlO*np.sin(yawlO)+centerOfRotation[1]
            
            if int(timeCycle%200)<150:
                #Move leg k upwards 
                legsOnGroundPos[2,k]+=.006
            else:
                #Move leg k wards 
                legsOnGroundPos[2,k]-=.006
        else:
            #Move/keep all legs down to the ground
            legsOnGroundPos[2,0]=0.0
            legsOnGroundPos[2,1]=0.0
            legsOnGroundPos[2,2]=0.0
            legsOnGroundPos[2,3]=0.0
            
        
        #Calculate vectors and matrix for the next loop
        xfrO=(legsOnGroundPos[:,0]+legsOnGroundPos[:,1])/2.0
        xbkO=(legsOnGroundPos[:,2]+legsOnGroundPos[:,3])/2.0
        robotCenter=(xfrO+xbkO)/2.0 
        robotCenter[2]=0.5 # along z axis
        fwdBwdCenterDistance=xfrO-xbkO
        yawInitial=np.arctan2(fwdBwdCenterDistance[1],fwdBwdCenterDistance[0])
        yawRobotFrame=RotYawr(yawInitial)

        time.sleep(0.01)

    p.disconnect()

main()























