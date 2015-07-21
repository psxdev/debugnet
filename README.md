DEBUGNET FOR VITA
=================
 
===================
 What does this do?
===================
 
  debugnet is a psp2 small library to depure your homebrew code over udp. It is the same method that i use to depure PlayStation 3 code, so i can use the same host tools for PlayStation Vita and PlayStation 3 to do it.
  
==================
  How do I use it?
==================

 1) Compile and install library and include file

  You need a psp2 toolchain installed in your environment and PSP2SDK must be defined
  
  ```
  cd libdebugnet
  make
  make install
  ```
  
 2) Compile sample
  
  ```
  cd sample
  edit main.c and change your server ip and port to listen udp messages from PlayStation Vita
  make
  ```

 3) Open a terminal and execute (change port if you don't use 18194). It can be in osx, linux or if you have socat like tool on windows
   
  ```
  socat udp-recv:18194 stdout 
  ```
  
 4) Execute sample with rejuvenate
 
 You will see in socat terminal window output from your PlayStation Vita:
 
 ```
 debugnet initialized
 Copyright (C) 2010,2015 Antonio Jose Ramos Marquez aka bigboss @psxdev
 This Program is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ready to have a lot of fun...
 [DEBUG]: Test debug level 1
 [ERROR]: Test error level 1
 [INFO]: Test info level 1
 ```
 
 5) ready to have a lot of fun :P
  
===========================
  Credits
===========================
  
  Special thanks goes to:
  
  - yifanlu to open the doors with rejuvenate. We need PlayStation VitaTV suppport and other cool things so i wait you come back.
  - All people collaborating in #PSP2SDK: @17310, @xerpi(i stole you network initialization code :P from FTPVita), @frangar , @frtomtomdu80, @hykemthedemon , @SMOKE587, @Josh_Axey ... 
  - All ps3dev and ps2dev old comrades
  