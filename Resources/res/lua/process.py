#concat all lua files into one single file

#read the base file as the entry

f=open("base.lua", "r")
for line in f:
    formatedLine=line.strip()
    if len(formatedLine)>0:
        print line
