# Jail

Just another interpreted language. Please visit the [Wiki](https://github.com/zarat/Jail/wiki) for more information.

## Features
* Object orientated
* Extendable
* Embedable
* sandbox execution

A small example
```Javascript
class Example {

    name: "Jail example",
    version: 1.0,
    debug: function() {
        print(this.name + " " + this.version);
    }

};

var ex = new Example();
ex.version = 2.0;
ex.debug();
```
