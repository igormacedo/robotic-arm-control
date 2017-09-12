from distutils.core import setup, Extension

module1 = Extension('armdriver',
                    sources=['armdriver.c'],
                    include_dirs=['../include'],
                    libraries=['ufrn_lynx', 'm'],
                    library_dirs=['../lib'],
                    extra_compile_args=['-m32'],
                    extra_link_args=['-m32'])

setup(name='Armdriver',
      version='0.1',
      description='This is a wrapper around the ufrn_al5d driver',
      ext_modules=[module1])
