### Automated-Compilation of C/C++ ###
> #### Description ####
> This is an automation script which can generate **direct output**  
> of C/C++ source code.  
>   
> It also contain some other userful features which overall make the   
> process to write and compile code, relatively easily and fast.

#### Options and Commands 
- **`c -profile`**  --> Show current config.
- **`c -cc`** --> Change default compiler.
- **`c -ce`** --> Change defalut editor.
- **`c -ex`** --> Clear extended compilation code
- **`c -reset`** --> Set config. to default.

#### --Use Case-- ####
>  Look at the commands above for reference.

    
  
Source file name : source.c

    
**`c source.c`** -- > This command will generate direct output of the source file.
**`c`** --> After executing above code, `c` will again generate direct output of the source.c
  
> **USE :** -- If you are  constantly editing your source file, you can directly get output   
>  without retyping `gcc source.c` then `./a.out`
> This script saves the previous source file name .

**`c -profile`**  --> This will show you the name of the saved source file.
> NOTE : `c source.c -lm` , the extra `-lm`  treated as **extended compilation code**.  
> Everything work the same.   
>   
> This script also saves this **extended compilation code**.  
> so that if you want to run a **test.c** , you have to just type `c`.
> Not `c test.c -lm`. It will include the extended code automatically.  
>    
> You can see the saved extended code by :  **`c -profile`**.
> You can flush this saved extended code by : **`c -ex`**.

By default, this script uses `gcc` for compiling source files.  
You can change compiler by : **`c -cc`**.

#### Using editor option ####
This script allow user to edit source code by opening any text-editor and after saving  
the source, it will generate the output as soon as the editor exits.  

By default, **vim** is the text-editor.

`c vim source.c -lm` 
- Open source.c in vim.
- after editing source code you exit.
- Genereated output will be on your screen.

If you again want to edit the same source file.  
use : `c vim` -- >  	This will open previous source file with that extended code.  

> `c -ce` used to change the defalut editor.

> **NOTE :** --> Script will save source file name and extended code only  
> the execution is successfull else not.

**If you find any bug or error in this script, please do report in the \<issue\> section.**

> I will upload a video explanation as well.

  


