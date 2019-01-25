from tango import DeviceProxy
import tango

print(tango.ApiUtil.get_env_var("TANGO_HOST"))

power_pmac = DeviceProxy("p11/ppmac/motor")
power_pmac.set_timeout_millis(600000)
print(power_pmac.ping())
print(power_pmac.state())
print(power_pmac.position)