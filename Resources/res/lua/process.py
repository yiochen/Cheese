#concat all lua files into one single file

#read the base file as the entry


slist=[]
slist.append("base")
wholescript=""
def concatFile(filename):
    global wholescript
    f=open(filename+".lua","r")
    for line in f:
        formatedLine=line.lstrip()

        if len(formatedLine)>0:
            if line.startswith("require"):
                script=line.split('"')[1]
                if script not in slist:
                    slist.append(script)
                    concatFile(script)
            else:
                wholescript=wholescript+line
    f.close()
concatFile("base")
out=open("export.lua",'w')
out.write(wholescript)
out.close()

