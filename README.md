# QShowDiff
Tool for visualisation of diffs generated from various VCS systems.


## Requirements
For compilation you need only Qt4 devel files.

To create man page you need pod2man and gzip programs.


## Compilation and Installation
For compilation just type:
```sh
  $ make
```

If you want to change default codec used by Qt library. Set up
DEFAULT_CODEC variable in make command. For example:
```sh
  $ make DEFAULT_CODEC=utf-8
```

For installation to /usr/local/ type:
```sh
  $ sudo make install
```
And if you want to change destination dir:
```sh
  $ sudo make PREFIX=/path/to/dir install
```

## Usage
QShowDiff is simple command line tool which reads diff
from standard input and visualise it. What type of diff
is it (and thus how to parse it) is recognized automatically
or can be specified on command line.

### Synopsis
```
qshowdiff [options] [type]
```
If type of input is not specified QShowDiff tries to recognize input by itself.

### Options
 - **`--text-codec`** `codec_name`  Text codec that will be used.
 - **`--available-codecs`** Print out all available codecs.

Currently available types of input: **git**, **bzr**, **svn**, **diffr**, **diff**.

### Examples
To show last changes in git repository (qshowdiff recognize by itself type of input):
```sh
  $ git diff | qshowdiff
```
![](http://qshowdiff.danfis.cz/imgs/qshowdiff/git.png)
 
To genrate patch from svn and visualise them later (with exactly specified type of input):
```sh
  $ svn diff > changes.patch
  $ cat changes.patch | qshowdiff svn
```
![](http://qshowdiff.danfis.cz/imgs/qshowdiff/svn.png)
