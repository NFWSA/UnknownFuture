#!/usr/bin/env python3
import sys
import os

TargetType = {
    'exe' : 0,
    'dll' : 1,
    'lib' : 2
}
compiles = {
    'C' : 'gcc',
    'CFLAGS' : '-Wall -Wextra',
    'CLIBS' : [
    ],
    'CXX' : 'g++',
    'CXXFLAGS' : '-std=c++11 -Wall -Wextra',
    'CXXLIBS' : [
    ]
}

def getFilename(file, ext):
    ret = file.rfind('.')
    if ret == -1:
        return file + '.' + ext
    return file[0:ret] + '.' + ext

def setCompileArg(key, value):
    if key in compiles:
        print("Change defaule compile setting " + key + ' ~')
        if 'LIBS' in key:
            compiles[key].append(value.split(' '))
        else:
            compiles[key] = value
        for x in projects:
            projects[x]['compile'][key] = compiles[key]
        return True
    else:
        return False

def addProject(name):
    if not name.isalpha():
        return False
    print('Project ' + proname + ' created...')
    projects[proname] = {
        'compile' : compiles.copy(),
        'src' : [],
        'path' : '.',
        'target' : proname,
        'type' : TargetType['exe']
    }
    return True

def addProjectSrcs(name, srcs):
    for src in srcs:
        src = src.strip()
        if len(src) == 0:
            continue
        # if not os.exist(src):
        #     return src
        projects[name]['src'].append(src)
        print('Add "' + src + '" to project ' + name + ' ..')

def setProjectAttr(name, key, value):
    print('Change project ' + name + ' setting ' + key + ' ~')
    if key == 'path':
        projects[name]['target'] = value
    elif key == 'target':
        projects[name]['target'] = value
    elif key == 'type':
        if value in TargetType:
            pass
            # TODO
        else:
            projects[name]['type'] = TargetType[value]
    return 1, 2

def mkMakefile(compiles, projects):
    for x in compiles:
        if type(compiles[x]) == list:
            libs = ''
            for lib in compiles[x]:
                libs += ' -llib' + lib
            if len(libs) > 0:
                print('FLAGS += ' + libs)
        else:
            print(x + ' = ' + compiles[x])
    for proname in projects:
        pro = projects[proname]
        for t in TargetType:
            if pro['type'] == TargetType[t]:
                print(getFilename(pro['target'], t) + ' : ',)

mkfile = 'SCutefile.mk'
try:
    file = open(mkfile, 'rb')
except FileNotFoundError:
    print("Error! " + mkfile + " not exist!")
    exit(-1)
cnt = 0
linenum = 0
projects = {}
srcsTags = False
nowName = None
for line in file:
    linenum += 1
    line = line.decode('utf8').split('\n')[0].strip()
    if len(line) == 0 or line[0:1] == '#':
        continue
    cmd = line.split(' ')[0].lower().split('{')[0].strip()
    parms = line[len(cmd):].strip()
    if not srcsTags:
        if cmd == 'project':
            for proname in parms.split():
                if not addProject(proname):
                    print('Error: Project name could only contain a-z and A-Z.')
                    print('       ' + mkfile + ':' + str(linenum) + ' Project name >' + proname + '<')
                    exit(-1)
        elif cmd == 'compile':
            key = parms.split(' ')[0].strip().upper()
            value = parms[len(key):].strip()
            if not setCompileArg(key, value):
                print('Error: Project name could only contain a-z and A-Z.')
                print('       ' + mkfile + ':' + str(linenum) + ' Project name >' + proname + '<')
                exit(-1)
        else:
            if cmd in projects:
                if '{' in line:
                    srcsTags = True
                    nowName = cmd
                    ret = addProjectSrcs(cmd, line[line.find('{') + 1:].split())
                    if ret != None:
                        print('Error: Source file is not exist!')
                        print('       ' + mkfile + ':' + str(linenum) + ' Project name "' + ret + '"')
                        exit(-1)
            elif '.path' in cmd.lower() or '.type' in cmd.lower() or '.target' in cmd.lower():
                name = cmd.split('.')
                key = name[1].strip().lower()
                name = name[0].strip()
                if not name in projects:
                    pass
                else:
                    setProjectAttr(name, key, parms)
    elif srcsTags:
        cmd = nowName
        if '}' in line:
            srcsTags = False
            nowName = None
            line = line[0:line.find('}')]
        ret = addProjectSrcs(nowName, line.split())
        if ret != None:
            print('Error: Source file is not exist!')
            print('       ' + mkfile + ':' + str(linenum) + ' Project name "' + ret + '"')
            exit(-1)
    # print(cmd, parms)
    # print(linenum, len(line), line)
print("Successful!")
mkMakefile(compiles, projects)
exit(0)
