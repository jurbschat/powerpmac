from tango import DeviceProxy
import tango
import time
import matplotlib.pyplot as plt

print(tango.ApiUtil.get_env_var("TANGO_HOST"))

power_pmac = DeviceProxy("p11/pmac/motor4")
power_pmac.Position = 100

power_pmac.set_timeout_millis(600000)
print(power_pmac.ping())
print(power_pmac.state())

rounds = 100000
updateTimes = []
positions = []
start = time.time()
for _ in range(rounds):
    queryStart = time.time()
    a = power_pmac.Position
    #b = power_pmac.Velocity
    c = power_pmac.SoftCwLimitFault
    queryEnd = time.time()
    updateTimes.append((queryEnd - queryStart) * 1000)
    positions.append(a)
end = time.time()

plt.plot(updateTimes)
#plt.plot(positions)
plt.ylabel('milliseconds')
plt.show()

print(str(rounds) + " rounds took " + str(end - start) + "s. " + str((end - start) / rounds * 1000) + "ms per item")