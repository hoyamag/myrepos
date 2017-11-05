import threenames
print(threenames.b)
print(threenames.b, threenames.c)
print(type((threenames.b, threenames.c)))

from threenames import a,b,c
print(a,b,c)
print(type({a,b}))
print({a,b})
print((type([a,b])))
print([a,b])

print(dir(threenames))
