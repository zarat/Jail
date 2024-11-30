# Jail - Just Another Interpreted Language

JAIL is a [general purpose scripting language](https://en.wikipedia.org/wiki/General-purpose_language) to integrate in applications and games. Data is exchanged in [JSON](https://www.json.org/json-en.html) format. It is a subset of [ECMAScript 1](https://www.ecma-international.org/wp-content/uploads/ECMA-262_1st_edition_june_1997.pdf)


## Features
 * Dynamically typed
 * Object oriented
 * Static and dynamic Library
 * Plugin system

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

Jail wurde besonders auf Effizienz optimiert. In Performance-Tests hat sich gezeigt, dass Jail nur 1.5-mal langsamer als C ist, was beeindruckend schnell ist.

 * Python (10–50 Mal langsamer als C) 
 * JavaScript (10–50 Mal langsamer als C)
 * Ruby (20–100 Mal langsamer als C) 
 * PHP (10–50 Mal langsamer als C) 

Im Vergleich zu C, das für seine hohe Ausführungsgeschwindigkeit bekannt ist, bietet Jail somit eine bemerkenswert schnelle Leistung und eignet sich hervorragend für rechenintensive Aufgaben.
