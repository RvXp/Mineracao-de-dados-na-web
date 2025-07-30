A = [
    [0, 1, 0, 0, 1],
    [0, 0, 1, 1, 0],
    [1, 0, 0, 1, 0],
    [0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0]
]
# graph = {i: [j for j in range(len(row)) if row[j] != 0] for i, row in enumerate(A)}

n = len(A) 
beta = 0.85
t = 1e-6
dif = 1
i = 0
max_i = 1000

v =  [1] * n
e = [1/n] * n
P = [[(A[j][k]/sum(A[j]) if sum(A[j]) > 0 else 1/n) for k in range(n)] for j in range(n)]
m_t = [[1/n for _ in range(n)] for _ in range(n)] # veT
R = [[beta*P[j][k] + (1 - beta) * m_t[j][k] for k in range(n)] for j in range(n)]

rank = v
while dif > t and i < max_i :
    new_rank = [sum(R[j][k] * rank[j] for j in range(n)) for k in range(n)]
    norm = sum(element**2 for element in new_rank) ** 0.5
    new_rank = [element/norm for element in new_rank]
    dif = sum((new_rank[j] - rank[j])**2 for j in range(len(new_rank))) ** 0.5
    rank = new_rank
    i += 1
    
for node, probability in enumerate(new_rank):
    print(f"{node}: {probability:.4f}")

