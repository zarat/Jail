# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language) to integrate in applications and games. Data is exchanged in [JSON](https://www.json.org/json-en.html) format.

Find Sources [here](https://github.com/zarat/Jail-src)

## Features
 * Dynamically typed
 * Object oriented
 * Extendable
 
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
