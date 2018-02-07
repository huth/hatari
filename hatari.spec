#
# RPM spec file for Hatari
#
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#

Name:         hatari
URL:          http://hatari.tuxfamily.org/
License:      GPL
Group:        System/Emulators/Other
Autoreqprov:  on
Version:      2.1.0
Release:      1
Summary:      an Atari ST emulator suitable for playing games
Source:       %{name}-%{version}.tar.bz2
#Patch:        %{name}-%{version}.dif
BuildRoot:    %{_tmppath}/%{name}-%{version}-build
Prefix:       /usr

BuildRequires: cmake coreutils cpio cpp diffutils file filesystem findutils tar
BuildRequires: grep gzip libgcc make man mktemp patch readline sed util-linux
BuildRequires: glibc-devel zlib-devel SDL2-devel libpng-devel readline-devel
BuildRequires: portaudio-devel portmidi-devel binutils gcc rpm

# Required by zip2st and atari-hd-image
Requires: unzip
Requires: mtools
Requires: dosfstools

%description
Hatari is an emulator for the Atari ST, STE, TT and Falcon computers.
The Atari ST was a 16/32 bit computer system which was first released by Atari
in 1985. Using the Motorola 68000 CPU, it was a very popular computer having
quite a lot of CPU power at that time.
Unlike many other Atari ST emulators which try to give you a good environment
for running GEM applications, Hatari tries to emulate the hardware of a ST as
close as possible so that it is able to run most of the old ST games and demos.

%prep
%setup
#%patch

%build
# LDFLAGS="-static" LIBS=`sdl-config --static-libs` \
CFLAGS="-O3 -fomit-frame-pointer" \
 ./configure --prefix=/usr
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_bindir}/*
%{_datadir}/%{name}
%{_datadir}/applications/*.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.*
%{_datadir}/icons/hicolor/*/mimetypes/*
%{_datadir}/mime/packages/hatari.xml
%doc %_mandir/man1/*.1*
%dir %_docdir/%{name}
%_docdir/%{name}/*.txt
%_docdir/%{name}/*.html
%dir %_docdir/%{name}/images
%_docdir/%{name}/images/*

%changelog -n hatari

* Wed Feb 07 2018 - Nicolas Pomarede
- Hatari version 2.1.0

* Fri Nov 04 2016 - Nicolas Pomarede
- Hatari version 2.0.0

* Thu Sep 10 2015 - Nicolas Pomarede
- Hatari version 1.9.0

* Wed Jul 30 2014 - Nicolas Pomarede
- Hatari version 1.8.0

* Mon Jun 24 2013 - Nicolas Pomarede
- Hatari version 1.7.0

* Sun Jun 24 2012 - Nicolas Pomarede
- Hatari version 1.6.2

* Fri Jan 13 2012 - Nicolas Pomarede
- Hatari version 1.6.1

* Sun Jan 01 2012 - Nicolas Pomarede
- Hatari "Happy New Year 2012" version 1.6.0

* Tue Jul 19 2011 - Nicolas Pomarede
- Hatari version 1.5.0

* Sat Jun 12 2010 - Nicolas Pomarede
- Hatari version 1.4.0

* Sat Sep 05 2009 - Thomas Huth
- Hatari version 1.3.1

* Sun Aug 16 2009 - Thomas Huth
- Hatari version 1.3.0

* Sat Jan 24 2009 - Thomas Huth
- Hatari version 1.2.0

* Sat Nov 29 2008 - Thomas Huth
- Hatari version 1.1.0

* Wed Jan 02 2008 - Thomas Huth
- Adapted RPM to the latest source code level (aiming at version 1.0.0)

* Sun May 06 2007 - Thomas Huth
- Adapted spec file to be able to build Hatari with RedHat, too

* Sun Aug 27 2006 - Thomas Huth
- Upgraded to version 0.90

* Tue Oct 18 2005 - Thomas Huth
- initial package
