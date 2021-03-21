from building import *
import rtconfig

# get current directory
cwd     = GetCurrentDir()
# The set of source files associated with this SConscript file.

src     = Glob('*.c')
src    += Glob('libnfc/*.c')
src    += Glob('libnfc/drivers/*.c')
src    += Glob('libnfc/chips/*.c')
src    += Glob('libnfc/buses/*.c')

path   =  [cwd + '/include']
path   += [cwd + '/libnfc']
path   += [cwd + '/libnfc/buses']
path   += [cwd + '/libnfc/chips']
path   += [cwd + '/libnfc/drivers']

if GetDepend('LIBNFC_USING_READ_TAG_EXAMPLE'):
    src    += Glob('examples/nfc_read_tag.c')

LOCAL_CCFLAGS = ''

group = DefineGroup('libnfc', src, depend = ['PKG_USING_LIBNFC'], CPPPATH = path, LOCAL_CCFLAGS = LOCAL_CCFLAGS)

Return('group')
