from distutils.core import setup, Extension

module1 = Extension('armdriver',
                    sources=['py_ufrn_al5d.c'],
                    libraries=['m'])

setup(name='Armdriver',
      version='0.1',
      description='This is a wrapper around the ufrn_al5d driver',
      ext_modules=[module1])
