#Node class stores the attributes of the nodes
#The location of the nodes in cartesian coordinates are the relevant attributes 
class Node:
    def __init__(self, x_coord, y_coord):
        self.x_coord = x_coord
        self.y_coord = y_coord

#The path class stores the attributes of a path between two arbitrary nodes
#The slope of the path M and the y intercept B are the relevant attributes
class Path:
    def __init__(self, node1, node2):
        self.node1 = node1
        self.node2 = node2

        #Finding the slope of line connecting the two nodes
        dy = self.node2.y_coord - self.node1.y_coord
        dx = self.node2.x_coord - self.node1.x_coord

        #finding the path length
        self.length = (dy**2 + dx**2)**0.5

        #Edge case: infinite slope
        if dx == 0:
            if dy >= 0:
                self.slope = float("inf")
            else:
                self.slope = float("-inf")
        #Normal case
        else:
            self.slope = dy/dx
        
        #Finding the y_intercept of the line connecting the two nodes
        #Edge case: infinite slope
        if self.slope == float("inf") or self.slope == float("-inf"):
            self.y_int = None
        #Normal case
        else:
            self.y_int = node1.y_coord - self.slope*node1.x_coord


#Check if two non-parallel paths intersect 
def pathsIntersect(path1, path2):

    #Coordinates of point of intersection
    x_intersect = 0
    y_intersect = 0

    #Edge case: both paths have infinite slope
    if (path1.slope == float("inf") or path1.slope == float("-inf")) and (path2.slope == float("inf") or path2.slope == float("-inf")):
        return False, x_intersect, y_intersect
    
    #Edge case: both paths have the same slope
    elif (path1.slope == path2.slope):
        return False, x_intersect, y_intersect
    
    #Edge case: one path has infinite slope
    elif (path1.slope == float("inf") or path1.slope == float("-inf")):
        x_intersect = path1.node1.x_coord
        y_intersect = path2.slope*x_intersect + path2.y_int
    
    elif (path2.slope == float("inf") or path2.slope == float("-inf")):
        x_intersect = path2.node1.x_coord
        y_intersect = path1.slope*x_intersect + path1.y_int
    
    #Find the x and y values of the point of intersection
    else:
        x_intersect = (path2.y_int - path1.y_int)/(path1.slope - path2.slope)
        y_intersect = path1.slope*x_intersect + path1.y_int

    return True, x_intersect, y_intersect