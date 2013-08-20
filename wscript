#!/usr/bin/env python

import sys, shutil, os

def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

def framework(bld): 
    shutil.rmtree('Iscore.framework', True)
    os.mkdir('Iscore.framework')
    os.mkdir('Iscore.framework/Contents')
    shutil.copy('Mac/Info.plist', 
                'Iscore.framework/Contents/')
    os.mkdir('Iscore.framework/Versions')
    os.mkdir('Iscore.framework/Versions/1')
    os.mkdir('Iscore.framework/Versions/Current')
    shutil.copytree('Includes', 
                'Iscore.framework/Versions/Current/Headers')
    shutil.copytree('Includes', 
                'Iscore.framework/Versions/1/Headers')
    shutil.copy('build/libIscore.dylib', 
                'Iscore.framework/Versions/Current/Iscore')
    shutil.copy('Iscore.framework/Versions/Current/Iscore', 
                'Iscore.framework/Versions/1/Iscore')
    os.symlink('Versions/Current/Iscore', 
                    'Iscore.framework/Iscore')
    os.symlink('Versions/Current/Headers', 
                    'Iscore.framework/Headers')

def build(bld):
    #create the framework after
    bld.add_post_fun(framework)

    #also build the framework
    bld.shlib(
        source       = bld.path.ant_glob('*.cpp')+
                        bld.path.ant_glob('EnginesPrivate/*.cpp')+
                        bld.path.ant_glob('Editor/**/*.cpp')+
                        bld.path.ant_glob('ECOMachine/**/*.cpp')+
                        bld.path.ant_glob('StoryLine/**/*.cpp'),
                        #['libController/Controller.cpp',
                        #'libController/Device.cpp',
                        #'libController/PluginFactories.cpp'],
        use          = ['objs', 'OS'],
        target       = 'Iscore',
        includes     = ['/usr/include', '/usr/local/include', 'Includes'],
        cxxflags     = ['-O3', '-Wall', '-m32'],
        stlib          = ['m', 'xml2', 'DeviceManager', 'gecodekernel', 
                            'gecodeint', 'gecodesearch', 'gecodeset', 
                            'gecodesupport', 'gecodeminimodel', 'gecodedriver'],
        stlibpath      = ['/usr/lib', '/usr/local/lib','..'],
        linkflags      = ['-m32'],
    )

