#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'meta'
VERSION = '0.0.0'


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse([p])


def options(opt):

    import waflib.extras.wurf_dependency_bundle as bundle
    import waflib.extras.wurf_dependency_resolve as resolve

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major_version=2))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='gtest',
        git_repository='github.com/steinwurf/gtest.git',
        major_version=2))

    opt.load("wurf_configure_output")
    opt.load('wurf_dependency_bundle')
    opt.load('wurf_tools')


def configure(conf):

    if conf.is_toplevel():

        conf.load('wurf_dependency_bundle')
        conf.load('wurf_tools')

        conf.load_external_tool('mkspec', 'wurf_cxx_mkspec_tool')
        conf.load_external_tool('runners', 'wurf_runner')
        conf.load_external_tool('install_path', 'wurf_install_path')
        conf.load_external_tool('project_gen', 'wurf_project_generator')

        recurse_helper(conf, 'gtest')

def build(bld):

    if bld.is_toplevel():

        bld.load('wurf_dependency_bundle')

        recurse_helper(bld, 'gtest')

        bld.recurse('test')
        bld.recurse('examples')

    # Export own includes
    bld(name='meta_includes',
        includes='./src',
        export_includes='./src')
