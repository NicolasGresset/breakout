# Coding Convention

You will use the following coding convention:
- each class has a name starting with a capital letter (e.g. `NomDeClasse`).
- each function or method has a name starting with a lower case letter (e.g. `nomDeFonction`).
- variables will use underscore in their name to separate each word (e.g. `table_name`).
- data members will additionnally be postfixed by an underscore as well (e.g. `member_table_name_`).
- you will use `{}` for calling constructors instead of `()` whenever it is possible.
- in your constructors, you will initialize the data members before the actual code of the contructor (i.e. before the opening bracket).
- all your functions and methods will include the name of their parameters (e.g. use `heightOfStackedBox(int nBoxes, float singleBoxHeight)` instead of `heightOfStackedBox(int, float)`)
- you will systematically declare all short functions and methods (one to two lines of code) as inline (and always use inline if you write the function/method implementation in the class definition).

- as much as possible, use english to name variables or commentaries to be consistent