#!/bin/python3

import sys

TENS = {
    10: 'ten',
    11: 'eleven',
    12: 'twelve',
    13: 'thirteen',
    14: 'fourteen',
    15: 'fifteen',
    16: 'sixteen',
    17: 'seventeen',
    18: 'eighteen',
    19: 'nineteen',
    30: 'half'
}

ONES = {
    1: 'one',
    2: 'two',
    3: 'three',
    4: 'four',
    5: 'five',
    6: 'six',
    7: 'seven',
    8: 'eight',
    9: 'nine',
    10: 'ten',
    11: 'eleven',
    12: 'twelve',
    13: 'one'
}

def timeInWords(h, m):
    pastHalf = False
    firstHalf = ''
    secondHalf = ''
    
    # easy even time
    if m == 0:
        return ONES[h] + " o' clock"
    
    # build second half of the statement 
    if m > 30:
        pastHalf = True
        secondHalf = 'to {0}'.format(ONES[h+1])
    else:
        secondHalf = 'past {0}'.format(ONES[h])
    
    # build first half of the statement 
    if m == 15 or m == 45:
        firstHalf = 'quarter '
    elif  m == 30:
        firstHalf = 'half '
    else:
        if not pastHalf:
            tens = int(m/10)
            if tens > 0 and tens < 2:
                firstHalf = TENS[m] + 'minutes '
            elif tens == 2:
                firstHalf = 'twenty ' + ONES[int(m%10)] + ' minutes '
            else:
                firstHalf = ONES[m]
                firstHalf += ' minutes ' if firstHalf != 'one' else ' minute '
        else:
            minToNext = 60 - m
            if minToNext == 1:
                firstHalf = 'one minute '
            elif minToNext >= 10 and minToNext < 20:
                firstHalf = TENS[minToNext] + ' minutes '
            elif minToNext == 20:
                firstHalf = 'twenty minutes '
            elif minToNext > 20:
                firstHalf = 'twenty ' + ONES[minToNext % 10] + ' minutes '
            else:
                firstHalf = ONES[minToNext] + ' minutes '
    return firstHalf + secondHalf

if __name__ == "__main__":
    h = int(input().strip())
    m = int(input().strip())
    result = timeInWords(h, m)
    print(result)
