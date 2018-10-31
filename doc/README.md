Argoneum Core
=================

This is the official reference wallet for Argoneum digital currency and comprises the backbone of the Argoneum peer-to-peer network. You can [download Argoneum Core](https://github.com/argoneum/argoneum/releases) or [build it yourself](#building) using the guides below.

Running
---------------------
The following are some helpful notes on how to run Argoneum on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/argoneum-qt` (GUI) or
- `bin/argoneumd` (headless)

### Windows

Unpack the files into a directory, and then run argoneum-qt.exe.

### OS X

Drag Argoneum-Qt to your applications folder, and then run Argoneum-Qt.

### Need Help?

* See the [Argoneum documentation](https://argoneum.atlassian.net/wiki/display/DOC)
for help and more information.
* Ask for help on [#argoneum](http://webchat.freenode.net?channels=argoneum) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=argoneum).
* Ask for help on the [ArgoneumTalk](https://bitcointalk.org/) forums.

Building
---------------------
The following are developer notes on how to build Argoneum Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Argoneum Core repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- Source Code Documentation ***TODO***
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [ArgoneumTalk](https://bitcointalk.org/) forums, in the Development & Technical Discussion board.
* Discuss on [#argoneum](http://webchat.freenode.net/?channels=argoneum) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=argoneum).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
