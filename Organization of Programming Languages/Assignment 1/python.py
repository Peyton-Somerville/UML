'''
    Peyton Somerville
    Original code

    To run: type 'python3' then copy and paste this code into the interpreter
	ctrl-Z to exit python interpreter
'''

m1 = [[1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]]
m2 = [[4, 5, 6],
    [7, 8, 9],
    [10, 11, 12]]

result = [[0, 0, 0],
		[0, 0, 0],
		[0, 0, 0]]

x = y = z = 3

for i in range(x):
    for j in range(y):
        for k in range(z):
           result[i][j] += m1[i][k] * m2[k][j]

print("Matrix 1:")
print(m1[0], "\n", m1[1], "\n", m1[2])

print("\nMatrix 2:")
print(m2[0], "\n", m2[1], "\n", m2[2])

print("\nResult Matrix:")
print(result[0], "\n", result[1], "\n", result[2])