# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language) designed to run unmanaged code in a sandboxed, managed environment local, in a network or in the cloud. JAIL make use of standardized protocols to build applications on top of them. Data is exchanged in [JSON](https://www.json.org/json-en.html) format.

[Download](https://github.com/zarat/Jail/releases)

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

#Update: Port to linux
