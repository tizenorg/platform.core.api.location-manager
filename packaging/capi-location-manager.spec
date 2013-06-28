Name:       capi-location-manager
Summary:    A Location Manager library in Tizen Native API
Version: 0.1.11
Release:    1
Group:      Location/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: 	capi-location-manager.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(location)
BuildRequires:  pkgconfig(capi-base-common)

%description
A Location Manager library in Tizen Native API.


%package devel
Summary:  A Location Manager library in Tizen Native API (Development)
Group:    Location/Development
Requires: %{name} = %{version}-%{release}

%description devel
%devel_desc



%prep
%setup -q
cp %{SOURCE1001} .


%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%license LICENSE
%manifest capi-location-manager.manifest
%{_libdir}/libcapi-location-manager.so.*

%files devel
%manifest %{name}.manifest
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-location-manager.so


