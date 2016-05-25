Name: capi-location-manager
Summary: A Location Manager library in Tizen Native API
Version: 0.7.0
Release: 1
Group: Location/API
License: Apache-2.0
Source0: %{name}-%{version}.tar.gz
Source1001: %{name}.manifest
BuildRequires: cmake
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(lbs-location)
BuildRequires: pkgconfig(fused-location-client)
BuildRequires: pkgconfig(capi-base-common)
BuildRequires: pkgconfig(capi-system-info)
BuildRequires: pkgconfig(vconf)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A Location Manager library in Tizen Native API


%package devel
Summary:  A Location Manager library in Tizen Native API (Development)
Group:    Location/Development
Requires: %{name} = %{version}-%{release}

%description devel
A Location Manager library in Tizen Native API (Development)


%prep
%setup -q
cp %{SOURCE1001} .

%build

export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DLIBDIR=%{_libdir} -DINCLUDEDIR=%{_includedir} \
-DFULLVER=%{version} -DMAJORVER=${MAJORVER} \

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

#mkdir -p %{buildroot}/usr/share/license
#cp LICENSE %{buildroot}/usr/share/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%license LICENSE
%{_libdir}/libcapi-location-manager.so.*

%files devel
%{_includedir}/location/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-location-manager.so


%if 1
%package test
Summary:    Test application of Location Manager
Group:      Location/Testing
Requires: %{name} = %{version}-%{release}

%description test
Test application of Location Manager

%files test
%manifest test/capi-location-manager-test.manifest
/usr/share/packages/capi-location-manager-test.xml
/opt/usr/devel/location/location_test
%endif
