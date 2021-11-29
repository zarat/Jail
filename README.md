# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language). Data is exchanged in [JSON](https://www.json.org/json-en.html) format.

## Features
 * Dynamically typed
 * Object oriented
 * Extendable

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
