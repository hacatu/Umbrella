import os
import os.path
import sys

join = os.path.join

BASE = os.getcwd()

LIBS = "parser"
EXENAME = "{name}"
WERROR = ""#"-Werror "
STD = "-std=c1x "
WALL = "-Wall "

#Tell Scons to rebuild files whose timestamp changes
Decider("timestamp-match")

Command("bin", [], Mkdir("bin"))

print("BASE={}".format(BASE))

env = Environment(CCFLAGS=STD+WALL+WERROR)

if "CC" in os.environ:
	env["CC"] = os.environ["CC"]
if "AR" in os.environ:
	env["AR"] = os.environ["AR"]
if "RANLIB" in os.environ:
	env["RANLIB"] = os.environ["RANLIB"]

debug = ARGUMENTS.get("debug", 0)
if int(debug):
    env.Append(CCFLAGS = " -g")

SConscript([join("src", "SConstruct")], exports="env BASE EXENAME LIBS")

