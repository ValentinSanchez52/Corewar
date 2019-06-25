# Black beast of args

Black beast of args is a rethink of the standard `get_opt` library at the 42  
   norm. It's structured arround a hashtable that takes the options and calls  
   the callback function and analyze it's return value.
This library is designed for versatility ease of use and freedom of the user.

### Option types

- Single dash  
   Declared by the number of characters of your option name equals 1.  
   They are commutative and additionable.  
   E.g.: `cmd -qnf` where q, n and f are separate options.

- Double dash  
   If they are not single dashed.  
   E.g.: `cmd --help --verbose` where help and verbose are separate options.

### Option arguments

- Remember that any argument is valid. So dashed arguments are valid and are  
   going to be parsed as well.

- The only thing that separate and argument is the way it's formatted in memory.  
   As such an option with whitespaces separating words is valid.

- On single dashed options the arguments number is picked in order of apparition  
   of the corresponding option.

- On double dashed options the arguments are picked normally after the option.

- A callback function can take any number of arguments between 0 and the  
   option's number of argument.

### Examples

```c
int             main(int argc, char **argv)
{
t_hashmap		map = ft_create_hashmap();
t_opt_match		match = (t_opt_match){.arg_count = 0, .func = &callback_func, .types = NULL};

ft_hashmap_set(map, "test", &match); // This will be a double dash argument
bboa_parse_args((t_opt_patterns){&map}, argc, argv); // Run the parsing
}
```
