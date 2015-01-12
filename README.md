====================================
Unattainiumv2 Ubuntu Build
=====================================

sudo apt-get install build-essential libtool autotools-dev autoconf pkg-config libssl-dev git

sudo apt-get install libboost-all-dev

sudo apt-get install libdb4.8-dev

git clone git://github.com/unattainiumv2/UnattainiumV2.git

cd UnattainiumV2

./autogen.sh

./configure

make

cd src

sudo cp unattainiumv2d /usr/bin


=======
UnattainiumV2 Core integration/staging tree
=====================================

http://www.unat.ga

Copyright (c) 2009-2014 UnattainiumV2 Core Developers

What is UnattainiumV2?
----------------

UnattainiumV2 is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. UnattainiumV2 uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. UnattainiumV2 Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the UnattainiumV2 Core software, see http://www.unat.ga

Technical Specifications
---------------------

 - MultiAlgo POW (Scrypt, SHA256D, Qubit, Skein and Groestl) algorithms
 - 30 Second block Target (2.5 min per Algo)
 - 0.25 coin per block
 - Maximum coins
 - Difficulty retarget every 1 block (2.5 Min) Averaged over previous 10 blocks per algo
 
Links
------------------------
Website: http://www.unat.ga

BitcoinTalk: https://bitcointalk.org/index.php?topic=

IRC Channel: http://webchat.freenode.net/?channels=#unatv2

License
-------

UnattainiumV2 Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.
