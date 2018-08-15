
Debian
====================
This directory contains files used to package anodosd/anodos-qt
for Debian-based Linux systems. If you compile anodosd/anodos-qt yourself, there are some useful files here.

## anodos: URI support ##


anodos-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install anodos-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your anodos-qt binary to `/usr/bin`
and the `../../share/pixmaps/anodos128.png` to `/usr/share/pixmaps`

anodos-qt.protocol (KDE)

