import os
import inspect
print os.path.dirname(os.path.abspath(inspect.stack()[0][1]))
