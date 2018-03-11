import sys
import hackerrank_utility as hu
# n: num prisoners, m : num candies, s: rand id of prisioner 
def saveThePrisoner(n, m, s):
    # starting at first guy 
    if (s == 1 and m <= n):
        return m

    if (s==1 and m%n==0):
        return n

    # starting at last guy 
    if s == n and m == (n+1):
        return n

    save_him = (s+(m%n)-1)
    return save_him if save_him <= n else (save_him%n)

def main():
    with open('./input/save_the_prisoner.in', 'r') as data:
        t = int( data.readline().strip() )
        res = ''
        for a0 in range(t):
            n, m, s = data.readline().strip().split(' ')
            n, m, s = [int(n), int(m), int(s)]
            result = str(saveThePrisoner(n, m, s))
            res +=result+'\n'
    hu.check_result(res.split('\n')[:-1], 'save_the_prisoner', 1)


if __name__ == '__main__':
    print (hu.time_execution( main ))
