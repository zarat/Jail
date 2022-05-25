# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language) to integrate in applications and games. Data is exchanged in [JSON](https://www.json.org/json-en.html) format.

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

## Download

```
//Windows
curl -L https://github.com/zarat/Jail/releases/download/1.0/jail_windows.zip -o jail_windows.zip

//Linux
wget https://github.com/zarat/Jail/releases/download/1.0/jail_linux.tar
```
