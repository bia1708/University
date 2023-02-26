class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class List:
    def __init__(self):
        self.head = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def initList():
    lst = List()
    lst.head = initListRec()
    return lst


def initListRec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        node = Node(x)
        node.next = initListRec()
        return node
    

'''
tiparirea elementelor unei liste
'''
def show(lst):
    showRec(lst.head)


def showRec(node):
    if node != None:
        print(node.value)
        showRec(node.next)
        

# problem1
def checkInclusion(lst1, lst2):
    return checkInclusionRec(lst1.head, lst2.head)

# we check if node2 is in node1
def checkInclusionRec(node1, node2):
    if node2 is None:
        return True
    if node1.value == node2.value:
        return checkInclusionRec(node1, node2.next)
    if node1.value != node2.value:
        if node1.next is None:
            return False
    return checkInclusionRec(node1.next, node2)


#problem2
def insertElem(lst, e, e1):
    return insertElemRec(lst.head, e, e1)


def insertElemRec(node, e, e1):
    if node is None:
        return False
    if node.value == e:
        newNode = Node(e1)
        nextNode = node.next
        node.next = newNode
        newNode.next = nextNode
        return True
    return insertElemRec(node.next, e, e1)


'''
program pentru test
'''

def testInclusion():
    lst1 = List()
    tail = None
    for i in range(10):
        node = Node(i)
        if tail is not None:
            tail.next = node
        else:
            lst1.head = node
        tail = node
    lst2 = List()
    lst2.head = Node(1)
    lst2.head.next = Node(5)
    assert checkInclusion(lst1, lst2) is True

    lst3 = List()
    lst3.head = Node(10)
    assert checkInclusion(lst1, lst3) is False

def testInsertion():
    lst1 = List()
    tail = None
    for i in range(10):
        node = Node(i)
        if tail is not None:
            tail.next = node
        else:
            lst1.head = node
        tail = node
    assert insertElem(lst1, 4, 20)

    testList = List()
    tail = None
    for i in range(10):
        node = Node(i)
        if tail is not None:
            tail.next = node
        else:

                testList.head = Node(20)
                testList.head.next = node
            else:
                testList.head = node


if i == 5:
        tail = node
    show(testList)

    assert insertElem(lst1, 15, 12) is False


def main():
    testInclusion()
    testInsertion()

main() 
    
    
    
    
