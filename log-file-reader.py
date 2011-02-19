import os
import time

f = open ('Tank-log-file')
a = f.readline ()

while (a != ''):
    os.system('clear') 
    print a,
    for i in xrange (50):
        a = f.readline ()
        print a,
    time.sleep (0.2)
    a = f.readline ()
        
        

