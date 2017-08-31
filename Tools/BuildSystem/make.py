#!/usr/bin/env python3
import sys
import os

TargetType = {
    'exe': 0,
    'dll': 1,
    'lib': 2
}

def repFilename(file, ext):
    ret = file.rfind('.')
    if ret == -1:
        return file + '.' + ext
    return file[:ret] + '.' + ext

def getFilenameNoext(file):
    rlt = file
    ret = file.rfind('/')
    if ret != -1:
        rlt = file[ret + 1:]
    ret = file.rfind('.')
    if ret != -1:
        return rlt
    return rlt[:ret]

def getFilename(file):
    ret = file.rfind('/')
    if ret == -1:
        return file
    return file[ret + 1:]

def getFolder(file):
    ret = file.rfind('/')
    if ret == -1:
        return '.'
    return file[0:ret]

def getLibLinkArg(libs):
    rlt = ''
    for lib in libs:
        rlt += ' -l' + lib
    return rlt

def getFileType(filename):
    name2type = { 'cxx': 'CXX', 'c': 'C', 'cpp': 'CXX' }
    for t in ['cxx', 'c', 'cpp']:
        if filename.lower().rfind(t) == len(filename) - len(t):
            if t in name2type:
                return name2type[t]
            else:
                return 'CXX'
    return 'CXX'


def setCompileArg(compiles, key, value):
    if key in compiles:
        print("Change defaule compile setting " + key + ' ~')
        if 'LIBS' in key:
            compiles[key] += (value.split(' '))
        else:
            compiles[key] = value
        return True
    else:
        return False

def addProject(projects, name):
    if not name.isalpha():
        return False
    print('Project ' + name + ' created...')
    projects[name] = {
        'compile': {},
        'src': [],
        'path': '.',
        'target': name,
        'type': TargetType['exe']
    }
    return True

def addProjectSrcs(projects, name, srcs):
    for src in srcs:
        src = src.strip()
        if len(src) == 0:
            continue
        if not os.path.exists(src):
            return src
        projects[name]['src'].append(src)
        print('Add "' + src + '" to project ' + name + ' ..')

def setProjectAttr(projects, name, key, value):
    print('Change project ' + name + ' setting ' + key + ' ~')
    if key == 'path':
        projects[name]['path'] = value
    elif key == 'target':
        projects[name]['target'] = value
    elif key == 'type':
        if value in TargetType:
            pass
            # TODO
        else:
            projects[name]['type'] = TargetType[value]
    return 1, 2

def mkCompileConfig(compiles, out):
    compiles['CLIBS'] = getLibLinkArg(compiles['CLIBS'])
    compiles['CXXLIBS'] = getLibLinkArg(compiles['CXXLIBS'])
    for x in compiles:
        out.write(x + ' = ' + compiles[x] + '\n')

def mkProjectConfig(compiles, project, out):
    compiler = {}
    for t in compiles:
        if t in project['compile']:
            if 'LIBS' in t:
                compiler[t] = getLibLinkArg(project['compile'][t])
            else:
                compiler[t] = project['compile'][t]
        else:
            compiler[t] = '${' + t + '}'
    CompileConfig = {
        'C': compiler['C'],
        'CFLAGS': compiler['CFLAGS'],
        'CLIBS': compiler['CLIBS'],
        'CXX': compiler['CXX'],
        'CXXFLAGS': compiler['CXXFLAGS'],
        'CXXLIBS': compiler['CXXLIBS'],
    }
    out.write(project['target'] + ' : ')
    files = ''
    ctype = 'CXX'
    oneline = True
    for src in project['src']:
        filename = getFilename(src)
        if getFileType(filename) == 'C':
            ctype = 'C'
        filename = repFilename(filename, 'o')
        if oneline:
            out.write(filename)
            oneline = False
        else:
            out.write(' \\\n  ' + filename)
        files += ' ' + filename
    out.write('\n\t' +
              CompileConfig['CXX'] + ' ' + CompileConfig[ctype + 'FLAGS'] +
              ' -o ' + project['target'] + ' ' + files +
              ' ' + CompileConfig[ctype + 'LIBS'] + '\n\n')
    for src in project['src']:
        filename = getFilename(src)
        targetName = getFilenameNoext(src)
        olddir = os.getcwd()
        pipe = os.popen(compiles[ctype] + ' ' + compiles[ctype + 'FLAGS'] +
                        ' -I' + getFolder(src) + ' -I' + getFolder(src) + '/.. -MM ' + src)
        text = pipe.read()
        ret = pipe.close()
        if ret != None:
            pass
        else:
            out.write(text + '\t')
            out.write(CompileConfig[ctype] + ' ' + CompileConfig[ctype + 'FLAGS'] +
                      ' -c -o ' + repFilename(filename, 'o ') + src + '\n\n')

def mkMakefile(compiles, projects, out = sys.stdout):
    mkCompileConfig(compiles, out)
    out.write('\n\nall : ')
    oneline = True
    for x in projects:
        if oneline:
            out.write(projects[x]['target'])
            oneline = False
        else:
            out.write(' \\\n  ' + projects[x]['target'])
    out.write('\n\n')
    for proname in projects:
        mkProjectConfig(compiles, projects[proname], out)
    out.write('.PHONY clean:\n\t')
    out.write('rm -rf *.o')

def parseFile(mkfile, compiles, projects):
    try:
        file = open(mkfile, 'rb')
    except FileNotFoundError:
        print("Error! " + mkfile + " not exist!")
        return -1
    cnt = 0
    linenum = 0
    srcsTags = False
    nowName = None
    for line in file:
        linenum += 1
        line = line.decode('utf8').split('\n')[0].strip()
        if len(line) == 0 or line[0:1] == '#':
            continue
        cmd = line.split(' ')[0].split('{')[0].strip()
        parms = line[len(cmd):].strip()
        if not srcsTags:
            if cmd.lower() == 'project':
                for proname in parms.split():
                    if not addProject(projects, proname):
                        print('Error: Project name could only contain a-z and A-Z.')
                        print('       ' + mkfile + ':' + str(linenum) + ' Project name >' + proname + '<')
                        return -1
            elif cmd.lower() == 'compile':
                key = parms.split(' ')[0].strip().upper()
                value = parms[len(key):].strip()
                if not setCompileArg(compiles, key, value):
                    print('Error: Project name could only contain a-z and A-Z.')
                    print('       ' + mkfile + ':' + str(linenum) + ' Project name >' + proname + '<')
                    return -1
            else:
                if cmd in projects:
                    if '{' in line:
                        srcsTags = True
                        nowName = cmd
                        ret = addProjectSrcs(
                            projects, cmd, line[line.find('{') + 1:].split()
                        )
                        if ret != None:
                            print('Error: Source file is not exist!')
                            print('       ' + mkfile + ':' + str(linenum) + ' Project name "' + ret + '"')
                            return -1
                elif '.path' in cmd.lower() or '.type' in cmd.lower() or '.target' in cmd.lower():
                    name = cmd.split('.')
                    key = name[1].strip().lower()
                    name = name[0].strip()
                    if not name in projects:
                        pass
                    else:
                        setProjectAttr(projects, name, key, parms)
        elif srcsTags:
            cmd = nowName
            if '}' in line:
                srcsTags = False
                nowName = None
                line = line[0:line.find('}')]
            ret = addProjectSrcs(projects, nowName, line.split())
            if ret != None:
                print('Error: Source file is not exist!')
                print('       ' + mkfile + ':' + str(linenum) + ' Project name "' + ret + '"')
                return -1
    print("Parse successful!")
    # print(compiles)
    return 0

if __name__ == '__main__':
    mkfile = 'SCutefile.mk'
    compiles = {
        'C': 'gcc',
        'CFLAGS': '-Wall -Wextra',
        'CLIBS': [
        ],
        'CXX': 'g++',
        'CXXFLAGS': '-std=c++11 -Wall -Wextra',
        'CXXLIBS': [
        ]
    }
    projects = {}
    ret = parseFile(mkfile, compiles, projects)
    if ret != 0:
        exit(ret)
    file = open('makefile', 'w')
    mkMakefile(compiles, projects, file)
    file.close()

