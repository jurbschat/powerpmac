from tango import DeviceProxy
import tango
import time

print(tango.ApiUtil.get_env_var("TANGO_HOST"))

power_pmac = DeviceProxy("p11/pmac/motor4")
power_pmac.set_timeout_millis(600000)
print(power_pmac.ping())
print(power_pmac.state())

print(power_pmac.PositionX2)
power_pmac.Position = 100000
print(power_pmac.state())
print(power_pmac.Position)
time.sleep(2)