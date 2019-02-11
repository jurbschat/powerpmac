import sys
import telnetlib
from datetime import datetime

HOST = "192.168.56.96"

try:
    tn = telnetlib.Telnet(HOST)
    #tn.set_debuglevel(100)
except:
    print("Unable to connect to Telnet server: " + HOST)

tn.read_until("login: ")
tn.write("root\n")
tn.read_until("Password: ")
tn.write("deltatau\n")
tn.read_until("/ppmac#")
print("login complete")
tn.write("gpascii -f -2\n")
tn.read_until("Input")
print("gpascii started")

start = datetime.now()
counts = 0
while True:

    cmd = "#1..31pvf?\n"
    tn.write(cmd)
    result = tn.read_until("\x06")

    #print("result: " + result[:-3].strip())
    counts = counts + 1
    now = datetime.now()
    if ((now - start).seconds >= 1):
        print(str(counts) + "queries in last second")
        counts = 0
        start = now