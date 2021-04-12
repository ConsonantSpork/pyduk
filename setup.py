from setuptools import find_packages, setup
from cmake_build_extension import BuildExtension, CMakeExtension

setup(
    name='pyduk',
    version='0.1',
    description='Duktape engine wrapper for Python 3',
    author="Dmitry Belov",
    author_email="dimabelov.tu99@gmail.com",
    packages=find_packages('python'),
    package_dir={'': 'python'},
    ext_modules=[
        CMakeExtension(name='_pyduk',
                       install_prefix='pyduk',
                       cmake_configure_options=[
                           '-DMODULE_ONLY=ON',
                       ]),
    ],
    cmdclass={'build_ext' : BuildExtension},
    zip_safe=False
)
