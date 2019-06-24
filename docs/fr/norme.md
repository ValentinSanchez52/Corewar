[//]: # (Use this for accents: é ê è)

# Norme a suivre

 - ## `Base`  
	est la [norme 42](https://cdn.intra.42.fr/pdf/pdf/1064/norme.fr.pdf).

---

 - ## `Prototypes de functions`  
	Doivent être écrit:  
```c
type	name(
		type arg1,
		type arg2,
		type arg3
);
```  
	La seule exception est quand vous avez un seul argument vous l'écrire en une ligne.  
	Le nom d'une fonction et de ses variables doivent etre explicites. Chaque fonction doit etre commentee sur son fonctionement, son traitement de la donne, ses valeurs de retour, etc...  
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
	** Affiche une erreur et la detruit si necessaire.
	** Ne retourne rien.
	** Peut `exit` quand le niveau de l'erreur est superieure a `ERR_WARNING`.
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

 - ## `Fichiers`  
	Chaque fichier ne doit contenir qu'une seule fonction nommee comme le fichier.  
	Vous pouvez attribuer `static` aux autres du moment que vous respectez la norme de 42.

---

 - ## `Flags`  
	Vous utiliserez `-Weverything`.

---

 - ## `Pragmas`  
	Les pragmas sont autorisees, n'en abusez juste pas, elles sont timides a 42.

---

 - ## `Variables`  
	Comme dit plus haut, leur nom doit etre explicite.
	N'abusez pas de le qualificatif `static` mais faites donc avec `const`.  
	Vous pouvez utiliser les [`compose litteraux`](https://gcc.gnu.org/onlinedocs/gcc-3.3/gcc/Compound-Literals.html). mais chacun de ses membres doit etre nomme :  
	```c
	some_var = (t_example){
			.field_1 = 42,
			.field_3 = {},
			.field_2 = 0,
	};
	```  
	Cela evite des bugs en cas de changement d'ordre des membres d'une structure.


---

 - ## `Git`  
	### Il y aura 4 types de branches dans le repo :  
	- #### Principaux :  
		Les tests de la `pipeline` doivent passer sur le commit pour fusioner dessus.
		- `Master`, La branche principale, ou le code stable reside.
		- `Hotfix`, ou les bugs de `Master` sont resolus.
		- `Develop`, la branche principale de fusion avant le `Master`.
	- #### Definies par les developpeurs:
		- `Feature`, prefixe par `feature/` sont la ou vous implementez les nouvelles fonctionalités.  
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
	Des `test unitaires` et `test fonctionels` ont besoin d'etre ecris au moins pour les fonction critiques dans l'execution.

