from distutils.core import setup, Extension

module1 = Extension('armdriver',
                    sources=['armdriver.c'],
                    include_dirs=['../x64/include'],
                    libraries=['ufrn_lynx', 'm'],
                    library_dirs=['../x64/lib'],
                    extra_link_args=['-fPIC'])

setup(name='Armdriver',
      version='0.1',
      description='This is a wrapper around the ufrn_al5d driver',
      ext_modules=[module1])
