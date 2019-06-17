
# Norm to follow:

 - ## `Base`  
	Is the [42 norm](https://cdn.intra.42.fr/pdf/pdf/1608/norme.en.pdf).

---

 - ## `Function prototypes`  
	should be written this way:  
```c
type	name(
		type arg1,
		type arg2,
		type arg3
);
```  
	The only exception to this is when you have one argument you can write it inline.  
	The name of a function should be explicit of it's doing. Every function should be commented on how it works, treats the data, return values, etc...  
	```c
	typedef struct      s_error
	{
		int             level;
		int             code;
		char            *message;
		void            (*print)(t_error);
		void            (*destructor)(t_error);
	}                   t_error;

	/*
	** Prints an error and destroys it if needed.
	** Returns nothing.
	** Can exit on states superiors than `ERR_WARNING`.
	*/

	void                print_error(
		t_error error
	)
	{
		if (error.message && error.print)
			error.print(error.message);
		if (error.destructor)
			error.destructor(error);
		if (error.level > ERR_WARNING)
			exit(error.code);
	}
	```

---

 - ## `Files`  
	Each file should only contain one function named as the file.  
	You can make `static` functions as well as long as there it respects the 42 norm.

---

 - ## `Flags`  
	You shall use `-Weverything`.

---

 - ## `Pragmas`  
	Pragmas are authorized just don't abuse them, they are shy at 42...

---

 - ## `Variables`  
	Explicit names should be used.
	Don't abuse the `static` qualifier but please do on the `const`.  
	You can use [`compound literals`](https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Compound-Literals.html). every of it's member shall be named :  
	```c
	some_var = (t_example){
			.field_1 = 42,
			.field_3 = {},
			.field_2 = 0,
	};
	```


---

 - ## `Git`  
	### There will be 4 types of branches on the repo :  
	- #### Principals :  
		Tests from the pipeline need to be passed in order to merge into it.
		- `Master`, the main branch where the most stable code resides.
		- `Hotfix`, where bugs of `Master` are being fixed.
		- `Develop`, the main merging branche for staging releases to `Master` branch.
	- #### User defined :
		- `Feature` branches prefixed by `feature/` are where you implement new features.  
	```mermaid
	graph BT;
	master[Master];
	develop[Develop];
	asm[Feature/Asm];
	parser[Feature/Parser_asm];
	vm[Feature/Virtual_machine];
	set[Feature/Instruction_set];
	arena[Feature/Arena];
	develop==>|Trough pipeline|master;
	asm-.->|Trough pipeline|develop;
	vm-.->|Trough pipeline|develop;
	parser-.->asm;
	set-.->vm;
	set-.->asm;
	arena-.->vm;
	```

---

 - ## `Pipeline`
	`Unit tests` needs to be written at least for functions critical in the well being of the program.
	As well `functional tests` need to be written.
