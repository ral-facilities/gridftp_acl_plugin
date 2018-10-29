Name:		globus-gridftp-osg-extensions
Version:	0.4
Release:	1%{?dist}
Summary:	OSG extensions for the Globus GridFTP server

Group:		Development/Libraries
License:	ASL 2.0
URL:		https://github.com/bbockelm/globus-gridftp-osg-extensions
# Generated from:
# git archive --format=tgz --prefix=%{name}-%{version}/ v%{version} > %{name}-%{version}.tar.gz
Source0:	%{name}-%{version}.tar.gz

BuildRequires:	globus-common-devel
BuildRequires:  globus-ftp-control-devel
BuildRequires:  globus-gridftp-server-devel
BuildRequires:  cmake

%description
%{summary}

%prep
%setup -q


%build
%cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_LIBDIR=%{_libdir} .
make VERBOSE=1 %{?_smp_mflags}


%install
make install DESTDIR=%{buildroot}


%files
%doc
%{_libdir}/libglobus_gridftp_server_osg.so*

%changelog
* Wed Jul 26 2017 Brian Bockelman <bbockelm@cse.unl.edu> - 0.4-1
- Add support for user load limits.

* Wed Jul 20 2016 Brian Bockelman <bbockelm@cse.unl.edu> - 0.3-1
- Log VOMS information.

* Tue Jul 19 2016 Brian Bockelman <bbockelm@cse.unl.edu> - 0.2-1
- Initial packaging of extensions.



