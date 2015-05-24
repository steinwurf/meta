meta
====

meta is a simple C++ library that provide simple helper functions to ease
manipulation of lists of types. In Steinwurf we use template mixin-layers
to build custom erasure correcting codecs (such as Reed-Solomon and Random
Linear Network Codes). meta is used to, at compile time, customize the
behavior of the different codecs.

.. image:: http://buildbot.steinwurf.dk/svgstatus?project=meta
    :target: http://buildbot.steinwurf.dk/stats?projects=meta

.. contents:: Table of Contents:
   :local:

Rant
----

There exists many other libraries with similar capabilities such as `Boost
MPL <http://www.boost.org/doc/libs/1_58_0/libs/mpl/doc/>`_, `Eric Niebler's
meta library <https://github.com/ericniebler/meta>`_, `Fatal
<https://github.com/facebook/fatal/>`_ and `Turbo
<https://github.com/Manu343726/Turbo>`_ just to name a few. Most of these
libraries provide extensive meta programming support. However, since we
only needed limited functionality and MSVC (the Microsoft Visual Studio
Compiler) support we decided to implement the functionality ourselves. In
the above list only Boost.MPL is supported by MSVC because of missing C++11
``constexpr`` support, yeah it sucks.

Usage
-----

The ``meta::typelist`` struct is the main component of the library. It
currently provides a minimal API for e.g. appending and removing types from
the list (since that was what we needed). If you have additional ideas to
how the library can be extended feel free to open an issue or submit
pull-requests.

Header-only
...........

The library itself is header-only so essentially to use it you just
have to clone the repository and setup the right include paths in the
project where you would like to use it.

The library uses C++11 features such as variadic templates, so you
need a relatively recent compiler to use it.

Quick Overview
--------------

The following examples give a quick overview of the functionality provided
by the library.

Create a ``meta::typelist``
...........................

Example:

::

    #include <meta/typelist.hpp>

    int main()
    {
        using types = meta::typelist<double,float>;

        static_assert(std::is_same<types,
            meta::typelist<double,float>>::value, "");
    }

The above creates a ``meta::typelist`` containing two types ``double`` and
``float``.

Appending types
...............

Example:

::

    #include <meta/typelist.hpp>

    int main()
    {
        using types = meta::typelist<>::append<double>::append<float>;

        static_assert(std::is_same<types,
            meta::typelist<double,float>>::value, "");
    }

As with our previous example the above creates a ``meta::typelist``
containing two types ``double`` and ``float``. We can also append types to
an existing ``meta::typelist``.

::

    #include <meta/typelist.hpp>

    int main()
    {
        using types = meta::typelist<double,float>;
        using result = types::append<int>;

        static_assert(std::is_same<result,
             meta::typelist<double,float,int>>::value, "");
    }

Finding types
.............

A common operation to perform is use the ``meta::typelist::find`` meta
function to search the list for a specific type.

The ``find`` meta function has the following signature:

::

    template
    <
        template <class> class Predicate,
        class NotFound = not_found
    >
    using find = typename find<Predicate, NotFound, Types...>::type;

The ``Predicate`` is what is known as a template template class (which
sounds crazy but just means that it is itself a template class). For each
type ``T`` in the ``meta::typelist`` we will instantiate
``Predicate<T>::value`` and if value is a non-zero value we will return the
type ``T``. Otherwise we will do the same for the next type in the list. If
no type is found we return the type specified by the ``NotFound`` template
argument (defaults to ``meta::not_found``).

Example:

::

    #include <meta/typelist.hpp>

    #include <vector>

    int main()
    {
        using types = meta::typelist<std::vector<int>, int, double>;

        using result = types::find<std::is_integral>;

        static_assert(std::is_same<result, int>::value, "");
    }

Visiting types
..............

The ability to visit the types stored in a ``meta::typelist`` allows us to
customize run-time behavior of our programs depending on the types stored
in the ``meta::typelist``.

Example:

::

    #include <meta/typelist.hpp>

    #include <typeinfo>
    #include <iostream>
    #include <vector>

    struct print_types
    {
        template<class T>
        void operator()(T)
        {
            std::cout << typeid(T).name() << std::endl;
        }
    };

    int main()
    {
        using types = meta::typelist<std::vector<int>, int, double>;

        types::visit(print_types());
    }

Removing types
..............

In addition to appending types to the ``meta::typelist`` we can also remove
types. The signature of remove is:

::

    template<template <class> class Predicate>
    using remove = typename remove<Predicate, Types...>::type;

For all types ``T`` contained in the ``meta::typelist`` we instantiate
``Predicate<T>::value`` if value is true then the resulting
``meta::typelist`` will not contain ``T``.

Example:

::

    #include <meta/typelist.hpp>

    #include <vector>

    int main()
    {
        using types = meta::typelist<std::vector<int>, int, double>;

        using result = types::remove<std::is_integral>;

        static_assert(std::is_same<result,
            meta::typelist<std::vector<int>, double>>::value, "");
    }

Unit testing
------------

The unit tests for the stub library are located in the ``test/src`` folder.

We use the Google Unit Testing Framework (gtest) to drive the unit
tests. To build the tests run:

::

    python waf configure
    python waf

Depending on the platform you should see a test binary called
``meta_tests`` in (extension also depends on operating system
e.g. ``.exe`` for windows):

::

    build/platform/test/

Where ``platform`` is typically is either linux, win32 or darwin
depending on your operating system.

License
-------

The meta library is released under the BSD license see the LICENSE.rst file
