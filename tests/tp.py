def nombre_entier(n: int) -> str:
    if n == 0:
        return "0"
    else: 
        return "S" * n + "0"

def S(n: str) -> str:
    return "S" + n 


def addition(a: str, b: str) -> str:
    if a == "0":
        return b
    elif b == "0":
        return a
    else:
        return addition(a[:-1], b[:-1]) + "S"    

def multiplication(a: str, b: str) -> str:
    if a == "0" or b == "0":
        return "0"
    result = "0"
    for _ in range(len(a) - 1):
        result = addition(result, b)
    return result

def facto_ite(n: int) -> int:
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result


def facto_rec(n: int) -> int:
    return 1 if n == 0 else n * facto_rec(n - 1)


def fibo_rec(n: int) -> int:
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return fibo_rec(n - 1) + fibo_rec(n - 2)

def fibo_ite(n: int) -> int:
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a + b
    return a

def golden_phi(n):
    a = 1
    b = 1
    for i in range(n):
        a, b = b, a + b
    return b / a
    
def sqrt5(n):
    phi = golden_phi(n+1)
    return 2 * phi - 1

def pow(a: float, n: int) -> float:
    return a ** n
