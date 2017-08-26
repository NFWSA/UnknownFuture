#!/usr/bin/env bash
# 0 关闭所有格式，还原为初始状态
# 1 粗体/高亮显示 理解为将Win color /?前景左侧颜色变为右侧颜色
# 2 模糊（※）
# 3 斜体（※）
# 4 下划线（单线）
# 5 闪烁（慢） 理解为将Win color /?背景左侧颜色变为右侧颜色
# 6 闪烁（快）（※） 理解为将Win color /?背景左侧颜色变为右侧颜色
# 7 交换背景色与前景色
# 8 隐藏（伸手不见五指，啥也看不见）（※）
# 30-37 前景色，即30+x，x表示不同的颜色（参见下面的“颜色表”）
# 40-47 背景色，即40+x，x表示不同的颜色（参见下面的“颜色表”）
# 注：（1）其中含有（※）标注的编码表示不是所有的终端仿真器都支持，只有少数仿真器支持。
#     （3）更多参数信息请参考“ANSI escape code”。
numTab=`printf 0123456789%X%X%X%X%X%X 10 11 12 13 14 15`
for it in 0 5;
do
    if (( $it == 0 )); then
        ifx=;
    else
        ifx="5;"
    fi
    for i in 40 44 42 46 41 45 43 47 ;
    do
        jcnt=0
        for jt in 0 1;
        do
            if (( $jt == 0 )); then
                jfx=;
            else
                jfx="1;"
            fi
            str=""
            for j in 30 34 32 36 31 35 33 37 ;
            do
                ji=${numTab:jcnt:1};
                let jcnt+=1
                str="${str}\e[${ifx}${jfx}${i};${j}m${ji}";
            done;
            echo -n -e "${str}\e[0m";
        done;
        echo;
    done;
done
