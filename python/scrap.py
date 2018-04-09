import algos 
import utility as ut 
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17] 
k = 1

print (f'before right rotation of k:{k} rotations ==>\n{x}')
algos.rotate_array_r(x, k)
print(f'after:{x}')

