#!/usr/bin/python

import os
import subprocess
import re

bindirs = [os.path.join('bin',d) for d in os.listdir('bin') \
                                 if os.path.isdir(os.path.join('bin',d))]
bindirs.sort()

gdbregexp  = 'Loading section .*|Loading image .*|Start address .*|Transfer rate:.*|0x.* in .*'
gdbregexp += '|First stage .*|Loading setup .*|Loading application .*'

test_output = ""
for d in bindirs:
    for xe in os.listdir(d):
        xe_path = os.path.join(d,xe)
        test_output += "----\n"
        test_output += xe + ":\n\n"
        output = subprocess.check_output(["xgdb","-batch",xe_path,"-ex","connect -s","-ex","r"],
            stderr=subprocess.STDOUT)
        lines = output.split('\n')
        lines = [line for line in lines if not re.match(gdbregexp, line)]
        for line in lines:
            test_output += line+"\n"
        test_output += "----\n\n"

f = open("test.output","w")
f.write(test_output)
f.close()
print "Output written to test.output"
print "Diffing with expected..."

err = subprocess.call(["diff","test.output","expected.output"])

if err == 0:
    print "Tests passed"
else:
    print "ERROR: Mismatch between actual and expected outputs"





