## Robotic Arm control ##

#### Compiling Python-C-Api Module - Armdriver ####
You should have the a version of python dev
```
sudo apt-get install libpython-dev
```
Go to the module folder and run
```
python setup.py build
```
An then move the armdriver.so module to the same location as the python script you want to use the `import armdriver as lynx`

#### Compiling code ####

In order to compile code in a x86_64 computer, you need to have the libc6-dev-i386 installed
```
sudo apt-get install libc6-dev-i386
```
Then you can type `make`
