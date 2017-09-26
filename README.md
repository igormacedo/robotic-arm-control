## Robotic Arm control ##

#### Compiling Python-C-Api Module - Armdriver ####
You should have a version of python dev
```
sudo apt-get install libpython-dev
```
Go to the armdriver-module folder and run
```
python setup.py build_ext -b build
```
An then move the armdriver.so module to the same location as the python script you want to use the `from armdriver import *`
