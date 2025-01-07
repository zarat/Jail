# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language) to integrate in applications and games. Data is exchanged in [JSON](https://www.json.org/json-en.html) format. It is a subset of [ECMAScript 1](https://www.ecma-international.org/wp-content/uploads/ECMA-262_1st_edition_june_1997.pdf)


## Features
 * Dynamically typed
 * Object oriented
 * extendable in c/c++          [Wiki -> Plugins](https://github.com/zarat/jail/wiki/plugins)

## Example
```Javascript
class Test {

    Test: function(value) {
        this.value = value;
    },
    
    Show: function() {
        print(this.value);
    }
    
};

var t = new Test("Hello world");

t.Show();
```
