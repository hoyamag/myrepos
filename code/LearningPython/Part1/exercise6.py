L = [1, 2] # Make a 2-item of list
L.append(L) # Append L as a single item to itself
print(L) # Print L: a cyclic/circular object

# Now L is [1, 2, [1, 2, [1, 2, [...]]]]. L has L itself.
# Python assignments always generates references to objects, not copies of them.
