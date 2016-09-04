DEBUGNET FOR VITA
=================
 
===================
 What does this do?
===================
 
  debugnet is a vita small library to debug your homebrew code over udp. It is the same method that i use to debug PlayStation 3 code, so i can use the same host tools for PlayStation Vita and PlayStation 3 to do it.
  
==================
  How do I use it?
==================

 1) Compile and install library and include file

  
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
  
 4) Install debugnetsample.vpk in your vita an run it
 
 You will see in socat terminal window output from your PlayStation Vita:
 
 ```
 debugnet initialized
 Copyright (C) 2010,2015 Antonio Jose Ramos Marquez aka bigboss @psxdev
 This Program is subject to the terms of the Mozilla Public
 License, v. 2.0. If a copy of the MPL was not distributed with this
 file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ready to have a lot of fun...
 [VITA][DEBUG]: Test debug level 1
 [VITA][ERROR]: Test error level 1
 [VITA][INFO]: Test info level 1
 ```
 
 5) ready to have a lot of fun :P and switch done to henkaku and vitasdk

===========================
  Change log
===========================
 - 04/09/2016 Update to support henkaku and last vitasdk
 - 21/01/2016 Update to support last vitasdk 
 
===========================
  Credits
===========================
  
  Special thanks goes to:
  
  - team molecule for bring henkaku to make life easier for homebrew developer 
  - All people who collaborated in #PSP2SDK: @173210, @xerpi(i stole you network initialization code :P from FTPVita), @frangar , @frtomtomdu80, @hykemthedemon , @SMOKE587, @Josh_Axey ... 
  - All ps3dev and ps2dev old comrades
  - xyzz for help with vita toolchain
  
