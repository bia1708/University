# def func(k):
#     k += 1
#
#
# n = 0
# func(n)
# print(n)

#
# l = [1, 2]
# l2 = [3]
#
# def f3(n):
#     l2 = l[:]
#     l.append(n)
#
# f3(5)
# print(l, l2)

def m2():
    a = lambda x : x + 1
    b = lambda x: x + [1]
    c = b([2])
    d = [a, b, c]
    print(a(2), b([2]))

m2()