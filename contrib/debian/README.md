
Debian
====================
This directory contains files used to package argoneumd/argoneum-qt
for Debian-based Linux systems. If you compile argoneumd/argoneum-qt yourself, there are some useful files here.

## argoneum: URI support ##


argoneum-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install argoneum-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your argoneum-qt binary to `/usr/bin`
and the `../../share/pixmaps/argoneum128.png` to `/usr/share/pixmaps`

argoneum-qt.protocol (KDE)

