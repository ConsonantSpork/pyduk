# pyduk
Duktape engine wrapper for Python 3

# Installation
## Dependencies
* g++
* make
* cmake 3.15.1+
* Python 3.7+
* Boost libraries 1.67+
  ```shell
  sudo apt install libboost1.67-dev  # install boost libs for Ubuntu/Debian
  ```
* Boost.Python 1.67+
  ```shell
  sudo apt install libboost-python-dev  # install Boost.Python for Ubuntu/Debian
  ```
## Installation process
To install run
```shell
python setup.py install
```
## Troubleshooting
In case of errors like the following
```
CMake Error at /usr/share/cmake-3.16/Modules/FindPackageHandleStandardArgs.cmake:146 (message):
  Could NOT find Boost (missing: python3) (found version "1.67.0")
```
* Make sure that all dependencies are installed correctly;
* Apply path `patches/0001-Change-component-requirement-to-python.patch` and rerun installation command.
  ```shell
  git apply patches/0001-Change-component-requirement-to-python.patch  # apply path to fix cmake Boost component not found error
  ```
# Examples
```python
from pyduk import Context, USE_GLOBAL_POLYFILL

ctx = Context(USE_GLOBAL_POLYFILL)
print(ctx.run("'Hello, ' + 'World!'"))  # 'Hello, World'
print(ctx.run("1 + 2"))  # 3
print(ctx.run("var obj = {key1: 'value1', key2: 'value2'}; obj;"))  # {'key1': 'value1', 'key2': 'value2'}
```

