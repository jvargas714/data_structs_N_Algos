print('hello!!!')


class tester:
    def __init__(self):
        self.data = 'hello this is data'
    
    def __str__(self):
        return self.data

tst = tester()


print(str(tst))