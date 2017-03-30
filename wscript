#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'meta'
VERSION = '3.0.0'


def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_META_VERSION="{}"'.format(VERSION))

    # Export own includes
    bld(name='meta_includes',
        includes='./src',
        export_includes='./src')

    if bld.is_toplevel():

        # Only build test when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse('test')
        bld.recurse('examples')
