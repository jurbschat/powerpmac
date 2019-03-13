from tango import DeviceProxy
import tango
from multiprocessing.dummy import Pool as ThreadPool

print(tango.ApiUtil.get_env_var("TANGO_HOST"))

global1 = DeviceProxy("p11/ppmac/global")
global2 = DeviceProxy("p11/ppmac/global")
global3 = DeviceProxy("p11/ppmac/global")

global1.set_timeout_millis(3000)
global2.set_timeout_millis(3000)
global3.set_timeout_millis(3000)

ds = [global1, global2, global3]
order = [0, 1, 2, 0, 1, 2, 0, 1, 2]

def callX(index):
    ds[index].command_inout("Init");
    return "finished " + str(index)

pool = ThreadPool(4)
result = pool.map(callX, order)
pool.close()
pool.join()

print(result);

