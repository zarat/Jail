# Jail

Just another interpreted language. Please visit the [Wiki](https://github.com/zarat/Jail/wiki) for more information.

## Features
* Object orientated
* Extendable
* Embedable
* sandbox execution
* cloud ready

A small example
```Javascript
class Example {

    name: "Jail example",
    version: 1.0,
    debug: function() {
        print(this.name + " " + this.version);
    }

};

var func = function() {
    return 2;
};

var ex = new Example();
ex.version = func();
ex.debug();
```
