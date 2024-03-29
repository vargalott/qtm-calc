# qtm-calc

[![Build](https://github.com/vargalott/qtm-calc/actions/workflows/build.yml/badge.svg)](https://github.com/vargalott/qtm-calc/actions/workflows/build.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

qtm-calc is a tool that allows you to calculate the final states and some operational characteristics of a multi-channel queuing system.

qtm-calc is available in two versions:
* a directly executable utility that works with json files;
* a dynamic library designed for embedding into python language (using pybind11).

## Build

1. First of all make sure you have the Boost library installed on your system (see more [Boost installation on Windows](https://www.boost.org/doc/libs/1_75_0/more/getting_started/windows.html) or [Boost installation on *nix](https://www.boost.org/doc/libs/1_75_0/more/getting_started/unix-variants.html));

2. Clone this project and then cd to the project folder;

3. Init the pybind11 git submodule:
```
$ git submodule init
$ git submodule update --recursive
```

4. Configure the project using CMake:
```
$ cmake -B ./build -G <preferred generator> -DCMAKE_BUILD_TYPE=<Debug|Release>
```

5. Then run build command:
```
$ cmake --build ./build --config <Debug|Release> --target <qtm-calc|pyqtmcalc|all>
```
> As you can see, to build the required version of the utility, you must use the *--target* parameter:
> * qtm-calc - build executable version;
> * pyqtmcalc - build python-embedding version;
> * all - build all of them.

6. You've done! The builded binary file(s) available in the build directory.

## Usage

1. For the directly executable version of this program to work, you need a json file with the specified basic characteristics of the queuing system of the following form:

> ```jsonc
> {
>     "channel_count": , // number of system channels
>     "queue_size": , // number of places in the queue
>     "la": , // input flow rate
>     "mu": , // output flow rate
>     "nu": , // impatience rate (optional parameter, default: 0)
>     "n": // number of load sources (optional parameter, default: -1)
> }
> ```
>
> The result will be placed in a json file with the following structure:
> ```jsonc
> {
>     "final_states": {
>         "1": ,
>         "2": ,
>         "3": ,
>         // further for each final state
>     },
>     "avg_queue": , // average queue length
>     "ete": , // system efficiency
>     "avg_time_queue": , // average queue time
>     "perc_served_req": , // percentage of served requests
>     "count_served_req": , // average number of served requests
>     "avg_count_req": // average number of requests
> }
> ```
>
> To run the program, enter:
> ```
> $ qtm-calc <input json file> <output json file>
> ```

2. For embedded version you must make sure that you have successfully built *pyqtmcalc* target and *.pyd or *.so file is available. Then, an example usage in python code:

> ```python
> import pyqtmcalc
>
> x = pyqtmcalc.qtm(10, 1, 1.5, 0.7, 0, -1)
> if x.is_fs_outdated(): # check if fs was calculated since last change of internals
>   x.calc_final_states() # necessary for further action
> print(x.final_states())
>
> # calc operational characteristics
> print(pyqtmcalc.qtm_data.calc_avg_queue(x))
> print(pyqtmcalc.qtm_data.calc_ete(x))
> print(pyqtmcalc.qtm_data.calc_avg_time_queue(x))
> print(pyqtmcalc.qtm_data.calc_perc_served_req(x))
> print(pyqtmcalc.qtm_data.calc_avg_count_served_req(x))
> print(pyqtmcalc.qtm_data.calc_avg_count_req(x))
>
> # get current values of system internals
> print(x.channel_count())
> print(x.queue_size())
> print(x.la())
> print(x.mu())
> print(x.nu())
> print(x.n())
>
> # set new values of system internals
> # after setting new values, you must perform x.calc_final_states() again
> # however, for the qtm_data methods fs calculation will be automatic
> x.channel_count(11)
> x.queue_size(2)
> x.la(2.5)
> x.mu(1.7)
> x.nu(1)
> x.n(1)
>
> print(pyqtmcalc.qtm_data.calc_avg_queue(x)) # will use actual fs
> ```

## Testing

To run project tests:

1. Configure the project using CMake:
```
$ cmake -B ./build -G <preferred generator>
```

2. Run build tests command:
```
$ cmake --build ./build --config <Debug|Release> --target run-tests
```

## License

This project is licensed under the [MIT License](LICENSE).

## Credits

My thanks to the developers of the [Boost C++ Libraries](https://www.boost.org/) and [pybind11](https://github.com/pybind/pybind11).

Especial thanks to [IceArrow256](https://github.com/IceArrow256) and [Vemestael](https://github.com/Vemestael) for help in writing computing algorithms and code structuring.
