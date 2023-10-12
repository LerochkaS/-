def power(a, n):
    return (1 if n == 0
            else power(a * a, n // 2) if n % 2 == 0
            else a * power(a, n - 1))
def is_prime (a: int) -> bool:
    for i in range(2, a // 2+1):
        if (a % i == 0):
            return True
    return False 

class GFp2:
    p:int  = 7
    r:int = 2
    while power(r, (p-1)/2)%p == 1 & r < p: r+= 1

    @staticmethod
    def change_mod(self, g: int):
        if is_prime(g):
            GFp2.p = g
            k:int = 2
            while power(r, (g-1)/2)%g == 1 & r < g: r+= 1
            GFp2.r = k

    @staticmethod
    def mod(self):
        print(GFp2.p)
    
    def __init__(self, a: int = 0, b: int  = 0):
        self.p = GFp2.p
        self.r = GFp2.r
        self.a = a%GFp2.p
        self.b = b%GFp2.p
    
    def sum(self, other: "GFp2") ->"GFp2":
        if self.p == other.p:
            a:int = (self.a + other.a)%self.p
            b:int = (self.b + other.b)%self.p
        return GFp2(a, b)
    
    def isum(self, other):
        if self.p == other.p:
            self.a = (self.a+other.a)%self.p
            self.b = (self.b+other.b)%self.p
    

    def mul(self, other) -> "GFp2":
        if self.p == other.p:
            a:int = (self.a*other.b + self.b*other.a)%self.p
            b:int = (self.a * GFp2.r*other.a + self.b*other.b)%self.p
            return GFp2(a, b)
        
    def imul(self, other):
        if self.p == other.p:
            self.a = (self.a*other.b + self.b*other.a)%self.p
            self.b = (self.a * GFp2.r*other.a + self.b*other.b)%self.p
    
    def min(self, other):
        return self.sum((other.mul(-1)))
    
    def inverse(self)-> "GFp2":
        h:int = power(self.a*self.a*self.r - self.b*self.b, self.p-2)
        a:int = self.a*h%self.p
        b:int = -self.b*h%self.p
        return GFp2(a, b)
    
    def print(self):
        print(self.a, "*x+", self.b)

if __name__ is __main__:
    a = GFp2(1, 6)
    print(a.a, a.b)
    print(a)
    b = GFp2(4, 2)
    print(f"b: {b}")
    c = a.sum(b)
    print(f"c = a + b = {c}")
    d = a.mul(b)
    print(f"d = a*b = {d}")
    a.imul(b)
    print(f"а = a*b: {a}")
