# **The_Binary_Loader**
## This is a Linux tool to load binary and show its details without running it.

Because nearly all analysis tools needs to parse and (statically) load binary files, it makes sense to have a common framework that provides this ability. In this program, I used **libbfd** to design and implement such a framework to reinforce what I’ve learned so far about binary formats. I also added a small terminal interface called **"load"** to make it easy to use.

**You’ll see the binary loading framework again in almost all of upcoming tools**

**Note** that this is completely different from the dynamic loader provided
by the OS, whose job it is to load binaries into memory to execute them

## **What Is libbfd?**
The Binary File Descriptor library (libbfd) provides a common interface
for reading and parsing all popular binary formats, compiled for a wide
variety of architectures. This includes ELF and PE files for x86 and x86-64
machines. By basing your binary loader on libbfd, you can automatically
support all these formats without having to implement any format-specific
support.
The BFD library is part of the GNU project and is used by many applications in the binutils suite, including objdump, readelf, and gdb. It provides
generic abstractions for all common components used in binary formats,
such as headers describing the binary’s target and properties, lists of sections, sets of relocations, symbol tables, and so on. On Ubuntu, libbfd is part
of the binutils-dev package.
You can find the core libbfd API in /usr/include/bfd.h.
2 Unfortunately,
libbfd can be a bit unwieldy to use, so instead of trying to explain the API
here, let’s dive straight in and explore the API while implementing the
binary-loading framework.

## **prerequisites :**
Install the **GNU project** (if not already installed), You can use this command to do that:
```
sudo apt update
sudo apt install binutils-dev
```



## **How to install**
Open your linux terminal and run the following commands:
```
chmod +x install.sh
./install.sh
```

## **Loader API**
At its core, the whole API centers around only two functions. 
1. **load_binary function**, which takes the name of a binary file to
load (fname), a pointer to a Binary object to contain the loaded binary (bin), and a descriptor of the binary type (type). It loads the requested binary intothe bin parameter and returns an integer value of 0 if the loading process was successful or a value less than 0 if it was not successful
2. **unload_binary**, which simply takes a pointer to a previously
loaded Binary object and unloads it.

## **The "load" interface**
Besides the loader, I added a small terminal interface called **"load"** to make it easy to use. The load program can display some of the most important features of the loader like:
* Binary details
* Sections details
* sections content (raw data)
* symbols details

If you want to display more, Use the [**bfd.h manual**](https://ftp.gnu.org/old-gnu/Manuals/bfd-2.9.1/html_mono/bfd.html) to implement it into the load program 

Run the next command to figure out how to use the load interface:
```
load --help
```

## **References/Resources**
* The  [Practical Binary Analysis](https://practicalbinaryanalysis.com/) book chapter 4
* [Binary File Descriptor Library](https://ftp.gnu.org/old-gnu/Manuals/bfd-2.9.1/html_mono/bfd.html) user-manual
