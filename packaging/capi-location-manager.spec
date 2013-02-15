#sbs-git:slp/api/location-manager capi-location-manager 0.1.0 d1ee09a32e8bc0e9ed48ece37c641a7393c086c5
Name:       capi-location-manager
Summary:    A Location Manager library in Tizen Native API
Version: 0.1.7
Release:    1
Group:      System/Libraries
License:    Apache Licensc, Version 2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(location)
BuildRequires:  pkgconfig(capi-base-common)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A Location Manager library in Tizen Native API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel



%prep
%setup -q


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-location-manager.manifest
%{_libdir}/libcapi-location-manager.so.*

%files devel
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-location-manager.so


