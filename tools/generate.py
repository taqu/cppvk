import sys
import xml.etree.ElementTree as ET
from enum import IntEnum

class ScopeType(IntEnum):
    EXPORTED = 0
    INSTANCE = 1
    DEVICE = 2
    PHYSICALDEVICE = 3

def parse_command(command : ET.Element, nameToFunc : dict):
    proto = command.find('proto')
    if(None == proto):
        return
    name = proto.find('name')
    if(None == name):
        return
    name = ''.join(name.itertext())
    ret = proto.find('type')
    if(None != ret):
        ret = ''.join(ret.itertext())
    else:
        ret = 'void'

    isInstance = False
    isDevice = False
    isPhysicalDevice = False
    params = []
    names = []
    for param in command.findall('param'):
        type = param.find('type')
        if(None == type):
            continue
        pname = param.find('name')
        if(None == pname):
            continue
        p = ''.join(param.itertext())
        params.append(p)
        names.append(''.join(pname.itertext()))

        if(0<=p.find('VkInstance*')):
            continue
        if(0<=p.find('VkDevice*')):
            continue
        if(0<=p.find('VkPhysicalDevice*')):
            continue

        if('VkInstance' == type.text):
            isInstance = True
        elif('VkDevice' == type.text):
            isDevice = True
        elif('VkPhysicalDevice' == type.text):
            isPhysicalDevice = True

    if(isInstance):
        nameToFunc[name] = (ScopeType.INSTANCE, None, params, names, ret, ScopeType.EXPORTED, False)
    elif(isDevice):
        nameToFunc[name] = (ScopeType.DEVICE, None, params, names, ret, ScopeType.EXPORTED, False)
    elif(isPhysicalDevice):
        nameToFunc[name] = (ScopeType.PHYSICALDEVICE, None, params, names, ret, ScopeType.EXPORTED, False)
    else:
        nameToFunc[name] = (ScopeType.EXPORTED, None, params, names, ret, ScopeType.EXPORTED, False)

def parse_extension(extension : ET.Element, nameToFunc : dict):
    protect = extension.attrib['protect'] if('protect' in extension.attrib) else None
    scopeType = extension.attrib['type'] if('type' in extension.attrib) else None
    if(None == scopeType):
        scopeType = ScopeType.EXPORTED
    elif('instance' == scopeType):
        scopeType = ScopeType.INSTANCE
    elif('device' == scopeType):
        scopeType = ScopeType.DEVICE
    else:
        scopeType = ScopeType.EXPORTED

    for require in extension.findall('require'):
        for command in require.findall('command'):
            name = command.attrib['name'] if('name' in command.attrib) else None
            if(None == name):
                continue
            if(False == (name in nameToFunc)):
                continue
            entry = nameToFunc[name]
            nameToFunc[name] = (entry[0], protect, entry[2], entry[3], entry[4], scopeType, True)

def print_command(name, content):
    if(None != content[1]):
        print('#ifdef '+content[1])

    deffunc = ''
    if(False == content[6]):
        if(ScopeType.EXPORTED == content[5]):
            print('    VLK_EXPORTED_FUNCTION('+name+')')
        elif(ScopeType.INSTANCE == content[5]):
            print('    VLK_INSTANCE_FUNCTION('+name+')')
        elif(ScopeType.DEVICE == content[5]):
            print('    VLK_DEVICE_FUNCTION('+name+')')
        elif(ScopeType.PHYSICALDEVICE == content[5]):
            print('    VLK_PHYSICALDEVICE_FUNCTION('+name+')')
        return
    else:
        if(ScopeType.EXPORTED == content[5]):
            print('    VLK_EXT_EXPORTED_FUNCTION('+name+')')
            deffuc = 'defined(VLK_EXT_EXPORTED_MEMBER) && '
        elif(ScopeType.INSTANCE == content[5]):
            print('    VLK_EXT_INSTANCE_FUNCTION('+name+')')
            deffuc = 'defined(VLK_EXT_INSTANCE_MEMBER) && '
        elif(ScopeType.DEVICE == content[5]):
            print('    VLK_EXT_DEVICE_FUNCTION('+name+')')
            deffuc = 'defined(VLK_EXT_DEVICE_MEMBER) && '
        elif(ScopeType.PHYSICALDEVICE == content[5]):
            print('    VLK_EXT_PHYSICALDEVICE_FUNCTION('+name+')')
            deffuc = 'defined(VLK_EXT_PHYSICALDEVICE_MEMBER) && '

    ret = '' if('void' == content[4]) else 'return '
    if(ScopeType.EXPORTED == content[0]):
        print('#   if ' + deffuc + 'defined(VLK_EXT_DECL_EXPORTED_MEMBER) && defined(VLK_EXT_IMPL_EXPORTED_MEMBER)')
        print('    inline ' + content[4] + ' VLK_EXT_DECL_EXPORTED_MEMBER(' + name + ')(' + ', '.join(content[2]) + '){')
        print('        ' + ret + 'VLK_EXT_IMPL_EXPORTED_MEMBER(' + name + ')(' + ', '.join(content[3]) + ');')
        print('    }')
        print('#   endif')

    elif(ScopeType.INSTANCE == content[0]):
        print('#   if ' + deffuc + 'defined(VLK_EXT_DECL_INSTANCE_MEMBER) && defined(VLK_EXT_IMPL_INSTANCE_MEMBER)')
        print('    inline ' + content[4] + ' VLK_EXT_DECL_INSTANCE_MEMBER(' + name + ')(' + ', '.join(content[2][1:]) + '){')
        print('        ' + ret + 'VLK_EXT_IMPL_INSTANCE_MEMBER(' + name + ')(VLK_MEMBER_INSTANCE, ', ','.join(content[3][1:]) + ');')
        print('    }')
        print('#   endif')

    elif(ScopeType.DEVICE == content[0]):
        print('#   if ' + deffuc + 'defined(VLK_EXT_DECL_DEVICE_MEMBER) && defined(VLK_EXT_IMPL_DEVICE_MEMBER)')
        print('    inline ' + content[4] + ' VLK_EXT_DECL_DEVICE_MEMBER(' + name + ')(' + ', '.join(content[2][1:]) + '){')
        print('        ' + ret + 'VLK_EXT_IMPL_DEVICE_MEMBER(' + name + ')(VLK_MEMBER_DEVICE, ', ','.join(content[3][1:]) + ');')
        print('    }')
        print('#   endif')

    elif(ScopeType.PHYSICALDEVICE == content[0]):
        print('#   if ' + deffuc + 'defined(VLK_EXT_DECL_PHYSICALDEVICE_MEMBER) && defined(VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER)')
        print('    inline ' + content[4] + ' VLK_EXT_DECL_PHYSICALDEVICE_MEMBER(' + name + ')(' + ', '.join(content[2][1:]) + '){')
        print('        ' + ret + 'VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER(' + name + ')(VLK_MEMBER_PHYSICALDEVICE, ', ','.join(content[3][1:]) + ');')
        print('    }')
        print('#   endif')


    if(None != content[1]):
        print('#endif')
    print('')

if(len(sys.argv)<=1):
    sys.exit(0)

tree = ET.parse(sys.argv[1])
root = tree.getroot()

print("""
#ifndef VLK_EXPORTED_FUNCTION
#    define VLK_EXPORTED_FUNCTION(name)
#endif

#ifndef VLK_INSTANCE_FUNCTION
#    define VLK_INSTANCE_FUNCTION(name)
#endif

#ifndef VLK_DEVICE_FUNCTION
#    define VLK_DEVICE_FUNCTION(name)
#endif

#ifndef VLK_PHYSICALDEVICE_FUNCTION
#    define VLK_PHYSICALDEVICE_FUNCTION(name)
#endif

#ifndef VLK_EXT_EXPORTED_FUNCTION
#    define VLK_EXT_EXPORTED_FUNCTION(name)
#endif

#ifndef VLK_EXT_INSTANCE_FUNCTION
#    define VLK_EXT_INSTANCE_FUNCTION(name)
#endif

#ifndef VLK_EXT_DEVICE_FUNCTION
#    define VLK_EXT_DEVICE_FUNCTION(name)
#endif

#ifndef VLK_EXT_PHYSICALDEVICE_FUNCTION
#    define VLK_EXT_PHYSICALDEVICE_FUNCTION(name)
#endif
""")

nameToFunc = {}
for commands in root.findall('commands'):
    for command in commands.findall('command'):
        parse_command(command, nameToFunc)

for extensions in root.findall('extensions'):
    for extension in extensions.findall('extension'):
        parse_extension(extension, nameToFunc)

for scopeType in ScopeType:
    newDict = dict([item for item in nameToFunc.items() if item[1][0]==scopeType])
    for item in newDict.items():
        print_command(item[0], item[1])

print("""
#undef VLK_EXPORTED_FUNCTION
#undef VLK_INSTANCE_FUNCTION
#undef VLK_DEVICE_FUNCTION
#undef VLK_PHYSICALDEVICE_FUNCTION

#undef VLK_EXT_EXPORTED_FUNCTION
#undef VLK_EXT_INSTANCE_FUNCTION
#undef VLK_EXT_DEVICE_FUNCTION
#undef VLK_EXT_PHYSICALDEVICE_FUNCTION

#undef VLK_EXT_DECL_EXPORTED_MEMBER
#undef VLK_EXT_IMPL_EXPORTED_MEMBER

#undef VLK_EXT_DECL_INSTANCE_MEMBER
#undef VLK_EXT_IMPL_INSTANCE_MEMBER
#undef VLK_MEMBER_INSTANCE

#undef VLK_EXT_DECL_DEVICE_MEMBER
#undef VLK_EXT_IMPL_DEVICE_MEMBER
#undef VLK_MEMBER_DEVICE

#undef VLK_EXT_DECL_PHYSICALDEVICE_MEMBER
#undef VLK_EXT_IMPL_PHYSICALDEVICE_MEMBER
#undef VLK_MEMBER_PHYSICALDEVICE
""")
